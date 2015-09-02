#include "com_example_asus_camera_CameraInterface.h"
#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

using namespace cv;

void removePepperNoise(Mat &mask);



JNIEXPORT jintArray JNICALL Java_com_example_asus_camera_CameraInterface_ImgFun
        (JNIEnv *env, jobject obj, jbyteArray buf, jint w, jint h) {

    jbyte *cbuf;
    cbuf = env->GetByteArrayElements(buf, NULL);
    if (cbuf == NULL) {
        return 0;
    }

//    int len = env->GetArrayLength(buf);
//    unsigned char* ccbuf = new unsigned char[len];
//    env->GetByteArrayRegion (buf, 0, len, reinterpret_cast<jbyte*>(ccbuf));


    //Mat InputImg(h, w, CV_8UC4, (unsigned char *)cbuf);
    Mat InputImg(h+h/2, w, CV_8UC1, (uchar *)cbuf);
    Mat gray_temp(InputImg,Rect(0,0,w,h));

//    Mat InputImg_temp(h, w, CV_8UC4);
    Mat InputImg_temp(w, h, CV_8UC4);

//    Mat gray_temp;//,BGR_temp;
//    Mat OutputImg;

//    Mat mbgr(h, w, CV_8UC3);



//    cvtColor(InputImg,gray_temp,CV_YUV2GRAY_420);
//    cvtColor(InputImg, mbgr, CV_YUV420sp2BGR);
    //cvtColor(mbgr, InputImg_temp,CV_BGR2BGRA);
//    cvtColor(mbgr,gray_temp,CV_BGR2GRAY);

//    cvtColor(InputImg,gray_temp,CV_BGRA2GRAY);
//    cvtColor(InputImg,BGR_temp,CV_BGRA2BGR);

//    Mat medianResult;
//    medianBlur(gray_temp, medianResult,5);


    //Canny
//    Mat temp;
//    double canny_thresh =  threshold(gray_temp,temp,0,255,THRESH_BINARY_INV|THRESH_OTSU );
//    Canny(gray_temp, OutputImg, canny_thresh*0.4, canny_thresh, 3);


    //cartoon
//    Mat temp,mask,small_mat,big_mat,small_temp;
//    Laplacian(gray_temp, temp,CV_8U,5);

    //sobel


    Mat grad_x, grad_y,abs_grad_x,abs_grad_y,big_mat;

//    resize(gray_temp,small_mat,Size(),0.5,0.5,INTER_AREA);
//    Sobel( small_mat, grad_x, CV_16S, 1, 0);
//    Sobel( small_mat, grad_y, CV_16S, 0, 1);
//    convertScaleAbs( grad_x, abs_grad_x );
//    convertScaleAbs( grad_y, abs_grad_y );
//    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, temp );
//    resize(temp,big_mat,Size(),2,2,INTER_LINEAR);

    Sobel( gray_temp, grad_x, CV_16S, 1, 0);
    Sobel( gray_temp, grad_y, CV_16S, 0, 1);
    convertScaleAbs( grad_x, abs_grad_x );
    convertScaleAbs( grad_y, abs_grad_y );
    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, big_mat );
//    threshold(temp,mask,0,255,THRESH_BINARY_INV | THRESH_OTSU  );
    //removePepperNoise(mask);

//    BGR_temp.copyTo(InputImg_temp,mask);
//    cvtColor(InputImg_temp,OutputImg,CV_BGR2BGRA);
//


////    Size small_size,origin_size;
////    small_size.width = w/2;
////    small_size.height = h/2;
////    origin_size.width = w;
////    origin_size.height = h;
//
////    Mat small_temp = Mat(small_size,CV_8UC1);
//
////    resize(InputImg,small_mat,small_size,0,0,INTER_LINEAR);
//
//    resize(BGR_temp,small_mat,Size(),0.5,0.5,INTER_LINEAR);
//    bilateralFilter(small_mat,small_temp,5,80,20);
//    resize(small_temp,big_mat,Size(),2,2,INTER_LINEAR);
//
//    big_mat.copyTo(InputImg_temp,mask);
//    cvtColor(InputImg_temp,OutputImg,CV_BGR2BGRA);




//    //Laplacian with OTSu
//    Mat temp;
//    Laplacian(gray_temp, temp,CV_8U,5);
//    threshold(temp,OutputImg,0,255,THRESH_BINARY_INV|THRESH_OTSU );

//    //sobel
//    Mat grad_x, grad_y;
//    Mat abs_grad_x, abs_grad_y;
//    int ddepth = CV_16S;
//
//    /// Gradient X
//    //Scharr( gray_temp, grad_x, ddepth, 1, 0);
//    Sobel( gray_temp, grad_x, ddepth, 1, 0, 3);
//    convertScaleAbs( grad_x, abs_grad_x );
//
//    /// Gradient Y
//    //Scharr( gray_temp, grad_y, ddepth, 0, 1);
//    Sobel( gray_temp, grad_y, ddepth, 0, 1, 3);
//    convertScaleAbs( grad_y, abs_grad_y );
//
//    /// Total Gradient (approximate)
//    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, OutputImg );


    //因为灰度图最终以4通道bmp形式显示，所以将得到的灰度图gray_temp的数据赋值到4通道的imageData中
    uchar* ptr = InputImg_temp.ptr(0);

//    for(int i = 0; i < w*h; i++){
//        //得到的canny图像原本是单通道，但java中显示bmp时只能4通道或三通道，为了使显示的图像时灰
//        //度的，把canny图像的数据值赋给一个4通道的InputImg
//        //对于一个int四字节，其彩色值存储方式为：BGRA
//        ptr[4*i+1] = InputImg.data[i];
//        ptr[4*i+2] = InputImg.data[i];
//        ptr[4*i+0] = InputImg.data[i];
//    }

    int k = 0;
    for(int j=h-1;j>=0;j--){

        for(int i = 0;i<w;i++){

            int n = h*i+j;
            ptr[4*n+1] = big_mat.data[k];
            ptr[4*n+2] = big_mat.data[k];
            ptr[4*n+0] = big_mat.data[k];
            k++;
        }
    }

    int size = w * h;
    jintArray result = env->NewIntArray(size);
    env->SetIntArrayRegion(result, 0, size, (jint*)ptr);
//    env->SetIntArrayRegion(result, 0, size, (jint*)InputImg_temp.data);
    env->ReleaseByteArrayElements(buf, cbuf, 0);
    return result;
}

JNIEXPORT void JNICALL Java_com_example_asus_camera_CameraInterface_ImgFunVoid
        (JNIEnv *env, jobject obj, jbyteArray buf, jintArray des, jint w, jint h) {

    jbyte *cbuf;
    cbuf = env->GetByteArrayElements(buf, NULL);


    jint *dbuf;
    dbuf = env->GetIntArrayElements(des, NULL);

//    int len = env->GetArrayLength(buf);
//    unsigned char* ccbuf = new unsigned char[len];
//    env->GetByteArrayRegion (buf, 0, len, reinterpret_cast<jbyte*>(ccbuf));


    //Mat InputImg(h, w, CV_8UC4, (unsigned char *)cbuf);
    Mat InputImg(h+h/2, w, CV_8UC1, (uchar *)cbuf);
    Mat gray_temp(InputImg,Rect(0,0,w,h));

//    Mat InputImg_temp(h, w, CV_8UC4);
    Mat InputImg_temp(w, h, CV_8UC4,(uchar *)dbuf);

//    Mat gray_temp;//,BGR_temp;
//    Mat OutputImg;

//    Mat mbgr(h, w, CV_8UC3);



//    cvtColor(InputImg,gray_temp,CV_YUV2GRAY_420);
//    cvtColor(InputImg, mbgr, CV_YUV420sp2BGR);
    //cvtColor(mbgr, InputImg_temp,CV_BGR2BGRA);
//    cvtColor(mbgr,gray_temp,CV_BGR2GRAY);

//    cvtColor(InputImg,gray_temp,CV_BGRA2GRAY);
//    cvtColor(InputImg,BGR_temp,CV_BGRA2BGR);

//    Mat medianResult;
//    medianBlur(gray_temp, medianResult,5);


    //Canny
//    Mat temp;
//    double canny_thresh =  threshold(gray_temp,temp,0,255,THRESH_BINARY_INV|THRESH_OTSU );
//    Canny(gray_temp, OutputImg, canny_thresh*0.4, canny_thresh, 3);


    //cartoon
//    Mat temp,mask,small_mat,big_mat,small_temp;
//    Laplacian(gray_temp, temp,CV_8U,5);

    //sobel


    Mat grad_x, grad_y,abs_grad_x,abs_grad_y,big_mat;

//    resize(gray_temp,small_mat,Size(),0.5,0.5,INTER_AREA);
//    Sobel( small_mat, grad_x, CV_16S, 1, 0);
//    Sobel( small_mat, grad_y, CV_16S, 0, 1);
//    convertScaleAbs( grad_x, abs_grad_x );
//    convertScaleAbs( grad_y, abs_grad_y );
//    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, temp );
//    resize(temp,big_mat,Size(),2,2,INTER_LINEAR);

    Sobel( gray_temp, grad_x, CV_16S, 1, 0);
    Sobel( gray_temp, grad_y, CV_16S, 0, 1);
    convertScaleAbs( grad_x, abs_grad_x );
    convertScaleAbs( grad_y, abs_grad_y );
    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, big_mat);
//    threshold(temp,mask,0,255,THRESH_BINARY_INV | THRESH_OTSU  );
    //removePepperNoise(mask);

//    BGR_temp.copyTo(InputImg_temp,mask);
//    cvtColor(InputImg_temp,OutputImg,CV_BGR2BGRA);
//


////    Size small_size,origin_size;
////    small_size.width = w/2;
////    small_size.height = h/2;
////    origin_size.width = w;
////    origin_size.height = h;
//
////    Mat small_temp = Mat(small_size,CV_8UC1);
//
////    resize(InputImg,small_mat,small_size,0,0,INTER_LINEAR);
//
//    resize(BGR_temp,small_mat,Size(),0.5,0.5,INTER_LINEAR);
//    bilateralFilter(small_mat,small_temp,5,80,20);
//    resize(small_temp,big_mat,Size(),2,2,INTER_LINEAR);
//
//    big_mat.copyTo(InputImg_temp,mask);
//    cvtColor(InputImg_temp,OutputImg,CV_BGR2BGRA);




//    //Laplacian with OTSu
//    Mat temp;
//    Laplacian(gray_temp, temp,CV_8U,5);
//    threshold(temp,OutputImg,0,255,THRESH_BINARY_INV|THRESH_OTSU );

//    //sobel
//    Mat grad_x, grad_y;
//    Mat abs_grad_x, abs_grad_y;
//    int ddepth = CV_16S;
//
//    /// Gradient X
//    //Scharr( gray_temp, grad_x, ddepth, 1, 0);
//    Sobel( gray_temp, grad_x, ddepth, 1, 0, 3);
//    convertScaleAbs( grad_x, abs_grad_x );
//
//    /// Gradient Y
//    //Scharr( gray_temp, grad_y, ddepth, 0, 1);
//    Sobel( gray_temp, grad_y, ddepth, 0, 1, 3);
//    convertScaleAbs( grad_y, abs_grad_y );
//
//    /// Total Gradient (approximate)
//    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, OutputImg );


    //因为灰度图最终以4通道bmp形式显示，所以将得到的灰度图gray_temp的数据赋值到4通道的imageData中
    uchar* ptr = InputImg_temp.ptr(0);

//    for(int i = 0; i < w*h; i++){
//        //得到的canny图像原本是单通道，但java中显示bmp时只能4通道或三通道，为了使显示的图像时灰
//        //度的，把canny图像的数据值赋给一个4通道的InputImg
//        //对于一个int四字节，其彩色值存储方式为：BGRA
//        ptr[4*i+1] = InputImg.data[i];
//        ptr[4*i+2] = InputImg.data[i];
//        ptr[4*i+0] = InputImg.data[i];
//    }

    int k = 0;
    for(int j=h-1;j>=0;j--){

        for(int i = 0;i<w;i++){

            int n = h*i+j;
            ptr[4*n+1] = big_mat.data[k];
            ptr[4*n+2] = big_mat.data[k];
            ptr[4*n+0] = big_mat.data[k];
            k++;
        }
    }

//    int size = w * h;
//    jintArray result = env->NewIntArray(size);
//    env->SetIntArrayRegion(result, 0, size, (jint*)ptr);
//    env->SetIntArrayRegion(result, 0, size, (jint*)InputImg_temp.data);
    env->ReleaseByteArrayElements(buf, cbuf, 0);
    env->ReleaseIntArrayElements(des, dbuf, 0);
}



JNIEXPORT jintArray JNICALL Java_com_example_asus_camera_CameraInterface_ImgSave
        (JNIEnv *env, jobject obj, jintArray buf, jint w, jint h) {

    jint *cbuf;
    cbuf = env->GetIntArrayElements(buf, NULL);
    if (cbuf == NULL) {
        return 0;
    }

//    int len = env->GetArrayLength(buf);
//    unsigned char* ccbuf = new unsigned char[len];
//    env->GetByteArrayRegion (buf, 0, len, reinterpret_cast<jbyte*>(ccbuf));


    Mat InputImg(h, w, CV_8UC4, (unsigned char *)cbuf);
//    Mat InputImg(h+h/2, w, CV_8UC1, (uchar *)cbuf);
//    Mat gray_temp(InputImg,Rect(0,0,w,h));

//    Mat InputImg_temp(h, w, CV_8UC4);
    Mat InputImg_temp(w, h, CV_8UC4);

    Mat gray_temp;//,BGR_temp;
//    Mat OutputImg;

//    Mat mbgr(h, w, CV_8UC3);



//    cvtColor(InputImg,gray_temp,CV_YUV2GRAY_420);
//    cvtColor(InputImg, mbgr, CV_YUV420sp2BGR);
    //cvtColor(mbgr, InputImg_temp,CV_BGR2BGRA);
//    cvtColor(mbgr,gray_temp,CV_BGR2GRAY);

    cvtColor(InputImg,gray_temp,CV_BGRA2GRAY);
//    cvtColor(InputImg,BGR_temp,CV_BGRA2BGR);

//    Mat medianResult;
//    medianBlur(gray_temp, medianResult,5);


    //Canny
//    Mat temp;
//    double canny_thresh =  threshold(gray_temp,temp,0,255,THRESH_BINARY_INV|THRESH_OTSU );
//    Canny(gray_temp, OutputImg, canny_thresh*0.4, canny_thresh, 3);


    //cartoon
//    Mat temp,mask,small_mat,big_mat,small_temp;
//    Laplacian(gray_temp, temp,CV_8U,5);

    //sobel


    Mat grad_x, grad_y,abs_grad_x,abs_grad_y,temp;//,small_mat,big_mat;

//    resize(gray_temp,small_mat,Size(),0.5,0.5,INTER_AREA);
    Sobel( gray_temp, grad_x, CV_16S, 1, 0);
    Sobel( gray_temp, grad_y, CV_16S, 0, 1);
    convertScaleAbs( grad_x, abs_grad_x );
    convertScaleAbs( grad_y, abs_grad_y );
    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, temp );
//    resize(temp,big_mat,Size(),2,2,INTER_LINEAR);
//    threshold(temp,mask,0,255,THRESH_BINARY_INV | THRESH_OTSU  );
    //removePepperNoise(mask);

//    BGR_temp.copyTo(InputImg_temp,mask);
//    cvtColor(InputImg_temp,OutputImg,CV_BGR2BGRA);
//


////    Size small_size,origin_size;
////    small_size.width = w/2;
////    small_size.height = h/2;
////    origin_size.width = w;
////    origin_size.height = h;
//
////    Mat small_temp = Mat(small_size,CV_8UC1);
//
////    resize(InputImg,small_mat,small_size,0,0,INTER_LINEAR);
//
//    resize(BGR_temp,small_mat,Size(),0.5,0.5,INTER_LINEAR);
//    bilateralFilter(small_mat,small_temp,5,80,20);
//    resize(small_temp,big_mat,Size(),2,2,INTER_LINEAR);
//
//    big_mat.copyTo(InputImg_temp,mask);
//    cvtColor(InputImg_temp,OutputImg,CV_BGR2BGRA);




//    //Laplacian with OTSu
//    Mat temp;
//    Laplacian(gray_temp, temp,CV_8U,5);
//    threshold(temp,OutputImg,0,255,THRESH_BINARY_INV|THRESH_OTSU );

//    //sobel
//    Mat grad_x, grad_y;
//    Mat abs_grad_x, abs_grad_y;
//    int ddepth = CV_16S;
//
//    /// Gradient X
//    //Scharr( gray_temp, grad_x, ddepth, 1, 0);
//    Sobel( gray_temp, grad_x, ddepth, 1, 0, 3);
//    convertScaleAbs( grad_x, abs_grad_x );
//
//    /// Gradient Y
//    //Scharr( gray_temp, grad_y, ddepth, 0, 1);
//    Sobel( gray_temp, grad_y, ddepth, 0, 1, 3);
//    convertScaleAbs( grad_y, abs_grad_y );
//
//    /// Total Gradient (approximate)
//    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, OutputImg );


    //因为灰度图最终以4通道bmp形式显示，所以将得到的灰度图gray_temp的数据赋值到4通道的imageData中
    uchar* ptr = InputImg_temp.ptr(0);

//    for(int i = 0; i < w*h; i++){
//        //得到的canny图像原本是单通道，但java中显示bmp时只能4通道或三通道，为了使显示的图像时灰
//        //度的，把canny图像的数据值赋给一个4通道的InputImg
//        //对于一个int四字节，其彩色值存储方式为：BGRA
//        ptr[4*i+1] = temp.data[i];
//        ptr[4*i+2] = temp.data[i];
//        ptr[4*i+0] = temp.data[i];
//    }

    int k = 0;
    for(int j=h-1;j>=0;j--){

        for(int i = 0;i<w;i++){

            int n = h*i+j;
            ptr[4*n+1] = temp.data[k];
            ptr[4*n+2] = temp.data[k];
            ptr[4*n+0] = temp.data[k];
            k++;
        }
    }

    int size = w * h;
    jintArray result = env->NewIntArray(size);
    env->SetIntArrayRegion(result, 0, size, (jint*)ptr);
//    env->SetIntArrayRegion(result, 0, size, (jint*)InputImg_temp.data);
    env->ReleaseIntArrayElements(buf, cbuf, 0);
    return result;
}

JNIEXPORT jintArray JNICALL Java_com_example_asus_camera_CameraInterface_ImgSaveSketch
        (JNIEnv *env, jobject obj, jintArray buf, jint w, jint h) {

    jint *cbuf;
    cbuf = env->GetIntArrayElements(buf, NULL);
    if (cbuf == NULL) {
        return 0;
    }


    Mat InputImg(h, w, CV_8UC4, (unsigned char *)cbuf);
    Mat InputImg_temp(h, w, CV_8UC4);
    Mat OutputImg_temp(w, h, CV_8UC4);

    Mat gray_temp,BGR_temp,gray_ori;
    Mat OutputImg;

    cvtColor(InputImg,gray_ori,CV_BGRA2GRAY);
    cvtColor(InputImg,BGR_temp,CV_BGRA2BGR);

    Mat medianResult;
    medianBlur(gray_ori, gray_temp,7);


    //Canny
//    Mat temp;
//    double canny_thresh =  threshold(gray_temp,temp,0,255,THRESH_BINARY_INV|THRESH_OTSU );
//    Canny(gray_temp, OutputImg, canny_thresh*0.4, canny_thresh, 3);


    //cartoon
    Mat temp,mask,small_mat,big_mat,small_temp;
    Laplacian(gray_temp, temp,CV_8U,5);

    //sobel


//    Mat grad_x, grad_y,abs_grad_x,abs_grad_y,temp,small_mat,big_mat;

//    resize(gray_temp,small_mat,Size(),0.5,0.5,INTER_AREA);
//    Sobel( gray_temp, grad_x, CV_16S, 1, 0);
//    Sobel( gray_temp, grad_y, CV_16S, 0, 1);
//    convertScaleAbs( grad_x, abs_grad_x );
//    convertScaleAbs( grad_y, abs_grad_y );
//    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, temp );
//    resize(temp,big_mat,Size(),2,2,INTER_LINEAR);

    threshold(temp,mask,0,255,THRESH_BINARY_INV | THRESH_OTSU  );
//    threshold(temp,mask,80,255,THRESH_BINARY_INV);
    //removePepperNoise(mask);

    BGR_temp.copyTo(InputImg_temp,mask);
    cvtColor(InputImg_temp,OutputImg,CV_BGR2BGRA);
//


//    Size small_size;//,origin_size;
//    small_size.width = w/2;
//    small_size.height = h/2;
////    origin_size.width = w;
////    origin_size.height = h;
//
////    Mat small_temp = Mat(small_size,CV_8UC1);
//
////    resize(InputImg,small_mat,small_size,0,0,INTER_LINEAR);
//

//    resize(BGR_temp,small_mat,Size(),0.5,0.5,INTER_AREA);
//    bilateralFilter(small_mat,small_temp,5,80,30);
//    resize(small_temp,big_mat,Size(),2,2,INTER_LINEAR);
//

//    Mat tmp = Mat(small_size, CV_8UC3);
//    int repetitions = 1;  // Repetitions for strong cartoon effect.
//    for (int i = 0; i<repetitions; i++) {
//        int ksize = 5; // Filter size.
//        int sigmaColor = 30; // Filter color strength.
//        int sigmaSpace = 50; // Spatial strength.
//        bilateralFilter(BGR_temp, tmp, ksize, sigmaColor, sigmaSpace);
//        bilateralFilter(tmp, BGR_temp, ksize, sigmaColor, sigmaSpace);
//    }
//
//    BGR_temp.copyTo(InputImg_temp,mask);
//    cvtColor(InputImg_temp,OutputImg,CV_BGR2BGRA);




//    //Laplacian with OTSu
//    Mat temp;
//    Laplacian(gray_temp, temp,CV_8U,5);
//    threshold(temp,OutputImg,0,255,THRESH_BINARY_INV|THRESH_OTSU );

//    //sobel
//    Mat grad_x, grad_y;
//    Mat abs_grad_x, abs_grad_y;
//    int ddepth = CV_16S;
//
//    /// Gradient X
//    //Scharr( gray_temp, grad_x, ddepth, 1, 0);
//    Sobel( gray_temp, grad_x, ddepth, 1, 0, 3);
//    convertScaleAbs( grad_x, abs_grad_x );
//
//    /// Gradient Y
//    //Scharr( gray_temp, grad_y, ddepth, 0, 1);
//    Sobel( gray_temp, grad_y, ddepth, 0, 1, 3);
//    convertScaleAbs( grad_y, abs_grad_y );
//
//    /// Total Gradient (approximate)
//    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, OutputImg );


    //因为灰度图最终以4通道bmp形式显示，所以将得到的灰度图gray_temp的数据赋值到4通道的imageData中
    uchar* ptr = OutputImg_temp.ptr(0);

//    for(int i = 0; i < w*h; i++){
//        //得到的canny图像原本是单通道，但java中显示bmp时只能4通道或三通道，为了使显示的图像时灰
//        //度的，把canny图像的数据值赋给一个4通道的InputImg
//        //对于一个int四字节，其彩色值存储方式为：BGRA
//        ptr[4*i+1] = temp.data[i];
//        ptr[4*i+2] = temp.data[i];
//        ptr[4*i+0] = temp.data[i];
//    }

    int k = 0;
    for(int j=h-1;j>=0;j--){

        for(int i = 0;i<w;i++){

            int n = h*i+j;
            ptr[4*n+1] = OutputImg.data[4*k+1];
            ptr[4*n+2] = OutputImg.data[4*k+2];
            ptr[4*n+0] = OutputImg.data[4*k+0];
            k++;
        }
    }

    int size = w * h;
    jintArray result = env->NewIntArray(size);
    env->SetIntArrayRegion(result, 0, size, (jint*)ptr);
//    env->SetIntArrayRegion(result, 0, size, (jint*)InputImg_temp.data);
    env->ReleaseIntArrayElements(buf, cbuf, 0);
    return result;
}

void removePepperNoise(Mat &mask) {
    for (int y = 2; y < mask.rows - 2; y++) {

        //get access to each of the five rows near the pixel
        uchar *pUp2 = mask.ptr(y - 2);
        uchar *pUp1 = mask.ptr(y - 1);
        uchar *pThis = mask.ptr(y);
        uchar *pDown1 = mask.ptr(y + 1);
        uchar *pDown2 = mask.ptr(y + 2);

        //skip the first and the last 2 pixels on each row
        pThis += 2;
        pUp1 += 2;
        pUp2 += 2;
        pDown1 += 2;
        pDown2 += 2;

        for (int x = 2; x < mask.cols - 2; x++)
        {
            uchar value = *pThis;
            if (value == 0)
            {
                bool above, left, below, right, surroundings;
                above = *(pUp2 - 2) && *(pUp2 - 1) && *(pUp2) && *(pUp2 + 1) && *(pUp2 + 2);
                left = *(pUp1 - 2) && *(pThis - 2) && *(pDown1 - 2);
                below = *(pDown2 - 2) && *(pDown2 - 1) && *(pDown2) && *(pDown2 + 1) && *(pDown2 + 2);
                right = *(pUp1 + 2) && *(pThis + 2) && *(pDown1 + 2);
                surroundings = above && left && below && right;

                if (surroundings == true)
                {
                    *(pUp1 - 1) = 255;
                    *(pUp1 + 0) = 255;
                    *(pUp1 + 1) = 255;
                    *(pThis - 1) = 255;
                    *(pThis + 0) = 255;
                    *(pThis + 1) = 255;
                    *(pDown1 - 1) = 255;
                    *(pDown1 + 0) = 255;
                    *(pDown1 + 1) = 255;
                    pThis += 2;
                    pUp1 += 2;
                    pUp2 += 2;
                    pDown1 += 2;
                    pDown2 += 2;

                }
            }

            pThis++;
            pUp1++;
            pUp2++;
            pDown1++;
            pDown2++;

        }

    }
}