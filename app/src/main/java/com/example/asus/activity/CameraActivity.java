package com.example.asus.activity;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Point;
import android.hardware.Camera;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup.LayoutParams;
import android.widget.ImageButton;

import com.example.asus.camera.CameraInterface;
import com.example.asus.camera.preview.CameraSurfaceView;
import com.example.asus.playcamera.R;
import com.example.asus.util.DisplayUtil;

public class CameraActivity extends Activity implements CameraInterface.CamOpenOverCallback {

    static {

        System.loadLibrary("ImgFun");
    }

    private static final String TAG = "yanzi";
    public static int[] resultInt;
    public static Bitmap resultImg;
    public int w, h;
    public int wishedBufferSize;
//    public static byte[] mPreBuffer0 = null,mPreBuffer1 = null,mPreBuffer2 = null,mPreBuffer3 = null,
//            mPreBuffer4 = null,mPreBuffer5 = null,mPreBuffer6 = null,mPreBuffer7 = null,mPreBuffer8 = null,
//            mPreBuffer9 = null,mPreBuffer10 = null,mPreBuffer11 = null,mPreBuffer12 = null,mPreBuffer13 = null,
//            mPreBuffer14 = null,mPreBuffer15 = null,mPreBuffer16 = null;



    //CameraSurfaceView surfaceView;
    public static CameraSurfaceView surfaceView = null;
    public static CameraSurfaceView surfaceView_mo = null;
    ImageButton shutterBtn;
    float previewRate = -1f;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

//        setContentView(R.layout.activity_camera);
//        initUI();
//        initViewParams();
//
//        CameraInterface.getInstance().doOpenCamera(CameraActivity.this);

        //开启新线程open camera
        Thread openThread = new Thread() {
            @Override
            public void run() {
                // TODO Auto-generated method stub
                CameraInterface.getInstance().doOpenCamera(CameraActivity.this);
            }
        };
        openThread.start();

        setContentView(R.layout.activity_camera);
        initUI();
        initViewParams();

        shutterBtn.setOnClickListener(new BtnListeners());

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.camera, menu);
        return true;
    }

    private void initUI() {
        surfaceView = (CameraSurfaceView) findViewById(R.id.camera_surfaceview);
        surfaceView_mo = (CameraSurfaceView) findViewById(R.id.camera_modified_surfaceview);
        shutterBtn = (ImageButton) findViewById(R.id.btn_shutter);
    }

    private void initViewParams() {
        LayoutParams params_origin = surfaceView.getLayoutParams();
        LayoutParams params_modified = surfaceView_mo.getLayoutParams();
//        Point p = DisplayUtil.getScreenMetrics(this);
        params_origin.width = 480;
        params_origin.height = 640;
        params_modified.width = 480;
        params_modified.height = 640;
//        params.width = 720;
//        params.height = 480;

        previewRate = DisplayUtil.getScreenRate(this); //默认全屏的比例预览
        surfaceView.setLayoutParams(params_origin);
        //surfaceView.setVisibility(View.GONE);
        surfaceView_mo.setLayoutParams(params_modified);

        //

        //手动设置拍照ImageButton的大小为120dip×120dip,原图片大小是64×64
        LayoutParams p2 = shutterBtn.getLayoutParams();
        p2.width = DisplayUtil.dip2px(this, 80);
        p2.height = DisplayUtil.dip2px(this, 80);
        ;
        shutterBtn.setLayoutParams(p2);

        w = 640;
        h = 480;
        resultInt = new int[w*h];
        resultImg = Bitmap.createBitmap(h, w, Bitmap.Config.RGB_565);
        wishedBufferSize = w*h*3/2;
//        mPreBuffer0 = new byte[wishedBufferSize];
//        mPreBuffer1 = new byte[wishedBufferSize];
//        mPreBuffer2 = new byte[wishedBufferSize];
//        mPreBuffer3 = new byte[wishedBufferSize];
//        mPreBuffer4 = new byte[wishedBufferSize];
//        mPreBuffer5 = new byte[wishedBufferSize];
//        mPreBuffer6 = new byte[wishedBufferSize];
//        mPreBuffer7 = new byte[wishedBufferSize];
//        mPreBuffer8 = new byte[wishedBufferSize];
//        mPreBuffer9 = new byte[wishedBufferSize];
//        mPreBuffer10 = new byte[wishedBufferSize];
//        mPreBuffer11 = new byte[wishedBufferSize];
//        mPreBuffer12 = new byte[wishedBufferSize];
//        mPreBuffer13 = new byte[wishedBufferSize];
//        mPreBuffer14 = new byte[wishedBufferSize];
//        mPreBuffer15 = new byte[wishedBufferSize];
//        mPreBuffer16 = new byte[wishedBufferSize];

    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {

        CameraInterface.getInstance().doFocus();
        return super.onTouchEvent(event);
    }

    @Override
    protected void onStop() {

        CameraInterface.getInstance().doStopCamera();
        super.onStop();
    }

    @Override
    public void cameraHasOpened() {
        // TODO Auto-generated method stub
        SurfaceHolder holder = surfaceView.getSurfaceHolder();
        CameraInterface.getInstance().doStartPreview(holder, previewRate);
//        CameraInterface.getInstance().mCamera.addCallbackBuffer(mPreBuffer0);
//        CameraInterface.getInstance().mCamera.addCallbackBuffer(mPreBuffer1);
//        CameraInterface.getInstance().mCamera.addCallbackBuffer(mPreBuffer2);
//        CameraInterface.getInstance().mCamera.addCallbackBuffer(mPreBuffer3);
//        CameraInterface.getInstance().mCamera.addCallbackBuffer(mPreBuffer4);
//        CameraInterface.getInstance().mCamera.addCallbackBuffer(mPreBuffer5);
//        CameraInterface.getInstance().mCamera.addCallbackBuffer(mPreBuffer6);
//        CameraInterface.getInstance().mCamera.addCallbackBuffer(mPreBuffer7);
//        CameraInterface.getInstance().mCamera.addCallbackBuffer(mPreBuffer8);
//        CameraInterface.getInstance().mCamera.addCallbackBuffer(mPreBuffer9);
//        CameraInterface.getInstance().mCamera.addCallbackBuffer(mPreBuffer10);
//        CameraInterface.getInstance().mCamera.addCallbackBuffer(mPreBuffer11);
//        CameraInterface.getInstance().mCamera.addCallbackBuffer(mPreBuffer12);
//        CameraInterface.getInstance().mCamera.addCallbackBuffer(mPreBuffer13);
//        CameraInterface.getInstance().mCamera.addCallbackBuffer(mPreBuffer14);
//        CameraInterface.getInstance().mCamera.addCallbackBuffer(mPreBuffer15);
//        CameraInterface.getInstance().mCamera.addCallbackBuffer(mPreBuffer16);

        CameraInterface.getInstance().mCamera.addCallbackBuffer(new byte[wishedBufferSize]);
        CameraInterface.getInstance().mCamera.addCallbackBuffer(new byte[wishedBufferSize]);
        CameraInterface.getInstance().mCamera.addCallbackBuffer(new byte[wishedBufferSize]);
        CameraInterface.getInstance().mCamera.addCallbackBuffer(new byte[wishedBufferSize]);
        CameraInterface.getInstance().mCamera.addCallbackBuffer(new byte[wishedBufferSize]);
        CameraInterface.getInstance().mCamera.addCallbackBuffer(new byte[wishedBufferSize]);
        CameraInterface.getInstance().mCamera.addCallbackBuffer(new byte[wishedBufferSize]);
        CameraInterface.getInstance().mCamera.addCallbackBuffer(new byte[wishedBufferSize]);
        CameraInterface.getInstance().mCamera.addCallbackBuffer(new byte[wishedBufferSize]);
        CameraInterface.getInstance().mCamera.addCallbackBuffer(new byte[wishedBufferSize]);
        CameraInterface.getInstance().mCamera.addCallbackBuffer(new byte[wishedBufferSize]);
        CameraInterface.getInstance().mCamera.addCallbackBuffer(new byte[wishedBufferSize]);
        CameraInterface.getInstance().mCamera.addCallbackBuffer(new byte[wishedBufferSize]);
        CameraInterface.getInstance().mCamera.addCallbackBuffer(new byte[wishedBufferSize]);
        CameraInterface.getInstance().mCamera.addCallbackBuffer(new byte[wishedBufferSize]);
        CameraInterface.getInstance().mCamera.addCallbackBuffer(new byte[wishedBufferSize]);
        CameraInterface.getInstance().mCamera.addCallbackBuffer(new byte[wishedBufferSize]);

//        CameraInterface.getInstance().mCamera.setPreviewCallback(mPreviewCallback);

        CameraInterface.getInstance().mCamera.setPreviewCallbackWithBuffer(mPreviewCallback);
    }

    public Camera.PreviewCallback mPreviewCallback = new Camera.PreviewCallback() {

        public void onPreviewFrame(final byte[] data, final Camera camera) {


            new Thread() {
                public void run() {
                    if (data != null) {
//                        Log.i(TAG, "onPreviewFrameCallback...");
//                        resultInt = CameraInterface.getInstance().ImgFun(data, w, h);
                        //直接计算出来大小
//                        int[] resultInt = new int[307200];
                        CameraInterface.getInstance().ImgFunVoid(data, resultInt, 640, 480);
                        resultImg.setPixels(resultInt, 0, 480, 0, 0, 480, 640);
                        surfaceView_mo.drawFrame(resultImg, true);
                        camera.addCallbackBuffer(data);

                    }
                }
            }.start();
        }
    };


        private class BtnListeners implements OnClickListener {

            @Override
            public void onClick(View v) {
                // TODO Auto-generated method stub
                switch (v.getId()) {
                    case R.id.btn_shutter:
                        CameraInterface.getInstance().doTakePicture();
                        break;

                    default:
                        break;
                }
            }

        }

    }
