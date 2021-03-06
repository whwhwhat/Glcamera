package com.example.asus.camera;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.ImageFormat;
import android.graphics.PixelFormat;
import android.hardware.Camera;
import android.hardware.Camera.PictureCallback;
import android.hardware.Camera.ShutterCallback;
import android.hardware.Camera.Size;
import android.util.Log;
import android.view.SurfaceHolder;

import com.example.asus.util.CamParaUtil;
import com.example.asus.util.FileUtil;
import com.example.asus.util.ImageUtil;

import java.io.IOException;
import java.util.List;

public class CameraInterface {
    private static final String TAG = "yanzi";
    public Camera mCamera;
    private Camera.Parameters mParams;
    private boolean isPreviewing = false;
    private boolean isFaceDetected = false;
    private float mPreviwRate = -1f;
    private static CameraInterface mCameraInterface;
    public int[] resultInt;
//    public Bitmap resultImg;
//    public int w,h;

    //
    public Camera.AutoFocusCallback myAutoFocusCallback = null;
    public SurfaceHolder mHolder;

    public native int[] ImgFun(byte[] buf, int w, int h);

    public native int[] ImgSave(int[] buf, int w, int h);

    public native int[] ImgSaveSketch(int[] buf, int w, int h);

    public native void ImgFunVoid(byte[] buf, int[] des, int w, int h);

    public interface CamOpenOverCallback {
        public void cameraHasOpened();
    }

    private CameraInterface() {

    }

    public static synchronized CameraInterface getInstance() {
        if (mCameraInterface == null) {
            mCameraInterface = new CameraInterface();
        }
        return mCameraInterface;
    }

    /**
     * 打开Camera
     *
     * @param callback
     */
    public void doOpenCamera(CamOpenOverCallback callback) {
        Log.i(TAG, "Camera open....");
        mCamera = Camera.open();
        Log.i(TAG, "Camera open over....");


        myAutoFocusCallback = new Camera.AutoFocusCallback() {

            public void onAutoFocus(boolean success, Camera camera) {
                // TODO Auto-generated method stub
                if (success)//success表示对焦成功
                {
                    Log.i(TAG, "myAutoFocusCallback: 成功...");
                    //myCamera.setOneShotPreviewCallback(null);

                } else {
                    //未对焦成功
                    Log.i(TAG, "myAutoFocusCallback: 失败了...");

                }


            }
        };

        callback.cameraHasOpened();
    }

    /**
     * 开启预览
     *
     * @param holder
     * @param previewRate
     */
    public void doStartPreview(SurfaceHolder holder, float previewRate) {
        Log.i(TAG, "doStartPreview...");
        if (isPreviewing) {
            mCamera.stopPreview();
            return;
        }
        if (mCamera != null) {

            //获取预览图的holder
            mHolder = holder;

            mParams = mCamera.getParameters();


            //mParams.setPictureFormat(PixelFormat.JPEG);//设置拍照后存储的图片格式
            mParams.setPictureFormat(PixelFormat.JPEG);
            CamParaUtil.getInstance().printSupportPictureSize(mParams);
            CamParaUtil.getInstance().printSupportPreviewSize(mParams);
            //设置PreviewSize和PictureSize
            Size pictureSize = CamParaUtil.getInstance().getPropPictureSize(
                    mParams.getSupportedPictureSizes(), previewRate, 800);
            mParams.setPictureSize(pictureSize.width, pictureSize.height);
            Size previewSize = CamParaUtil.getInstance().getPropPreviewSize(
                    mParams.getSupportedPreviewSizes(), previewRate, 800);

            //mParams.setPreviewSize(previewSize.width, previewSize.height);
            mParams.setPreviewSize(640, 480);

            //预览图
//            w = previewSize.width;
//            h = previewSize.height;
//            w = 800;
//            h = 480;

//            resultImg = Bitmap.createBitmap(w,h, Bitmap.Config.RGB_565);

            mCamera.setDisplayOrientation(90);

            CamParaUtil.getInstance().printSupportFocusMode(mParams);
            List<String> focusModes = mParams.getSupportedFocusModes();
//            if(focusModes.contains("continuous-video")){
//                mParams.setFocusMode(Camera.Parameters.FOCUS_MODE_CONTINUOUS_VIDEO);
//            }

            if (focusModes.contains("auto")) {
                mParams.setFocusMode(Camera.Parameters.FOCUS_MODE_AUTO);
            }

            mCamera.setParameters(mParams);

            //mCamera.addCallbackBuffer();


            try {
                mCamera.setPreviewDisplay(holder);
                mCamera.startPreview();//开启预览


            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }

            isPreviewing = true;
            mPreviwRate = previewRate;

            mParams = mCamera.getParameters(); //重新get一次
            Log.i(TAG, "最终设置:PreviewSize--With = " + mParams.getPreviewSize().width
                    + "Height = " + mParams.getPreviewSize().height);
            Log.i(TAG, "最终设置:PictureSize--With = " + mParams.getPictureSize().width
                    + "Height = " + mParams.getPictureSize().height);
        }
    }

    /**
     * 停止预览，释放Camera
     */
    public void doStopCamera() {
        if (null != mCamera) {
            mCamera.setPreviewCallback(null);
            mCamera.stopPreview();
            isPreviewing = false;
            mPreviwRate = -1f;
            mCamera.release();
            mCamera = null;
        }
    }

    /**
     * 聚焦
     */
    public void doFocus() {
        if (isPreviewing && (mCamera != null)) {
            mCamera.autoFocus(myAutoFocusCallback);
//            if (!isFaceDetected){
//
//                isFaceDetected = true;
//                mCamera.startFaceDetection();
//
//            }
//            else
//                isFaceDetected = false;

        }
    }

    /**
     * 拍照
     */
    public void doTakePicture() {
        if (isPreviewing && (mCamera != null)) {
            mCamera.autoFocus(myAutoFocusCallback);
            mCamera.takePicture(mShutterCallback, null, mJpegPictureCallback);
        }
    }


    /*为了实现拍照的快门声音及拍照保存照片需要下面三个回调变量*/
    ShutterCallback mShutterCallback = new ShutterCallback()
            //快门按下的回调，在这里我们可以设置类似播放“咔嚓”声之类的操作。默认的就是咔嚓。
    {
        public void onShutter() {
            // TODO Auto-generated method stub
            Log.i(TAG, "myShutterCallback:onShutter...");
        }
    };
    PictureCallback mRawCallback = new PictureCallback()
            // 拍摄的未压缩原数据的回调,可以为null

    {

        public void onPictureTaken(byte[] data, Camera camera) {
            // TODO Auto-generated method stub
            Log.i(TAG, "myRawCallback:onPictureTaken...");

        }
    };
    PictureCallback mJpegPictureCallback = new PictureCallback()
            //对jpeg图像数据的回调,最重要的一个回调
    {
        public void onPictureTaken(byte[] data, Camera camera) {
            // TODO Auto-generated method stub
            Log.i(TAG, "myJpegCallback:onPictureTaken...");

            Bitmap b = null;

            if (null != data) {
                Bitmap buf = BitmapFactory.decodeByteArray(data, 0, data.length);
                int w = buf.getWidth();
                int h = buf.getHeight();
                int[] bufi = new int[w * h];
                buf.getPixels(bufi, 0, w, 0, 0, w, h);
                resultInt = ImgSaveSketch(bufi, w, h);
                b = Bitmap.createBitmap(h, w, Bitmap.Config.RGB_565);
                b.setPixels(resultInt, 0, h, 0, 0, h, w);

                //b = BitmapFactory.decodeByteArray(data, 0, data.length);//data是字节数据，将其解析成位图
                //不需要手动stop，坑爹！！！！！！！！
//                mCamera.stopPreview();
                isPreviewing = false;
            }
            //保存图片到sdcard
            if (null != b) {

                //设置FOCUS_MODE_CONTINUOUS_VIDEO)之后，myParam.set("rotation", 90)失效。
                //图片竟然不能旋转了，故这里要旋转下
                //Bitmap rotaBitmap = ImageUtil.getRotateBitmap(b, 90.0f);
                FileUtil.saveBitmap(b);
            }
            //再次进入预览
            mCamera.startPreview();
            isPreviewing = true;

        }
    };


}
