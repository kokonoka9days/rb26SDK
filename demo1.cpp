/**
 * 单相机采集实例
 */
#include <iostream>
#include "./rb26SDK/include/CamreaExmple.hpp"

int main(int argc, char const *argv[])
{
    cv::Mat img;
    using CamreaType = sdk::HikCamera;
    
    sdk::CameraExmple<CamreaType>::CameraSDKInit();
    sdk::CameraExmple<CamreaType> cap1;
    // sdk::CameraExmple<sdk::DahengCamera> cap2;
        

    const char* sn1 = "DA7188471";//KE0210010004  //DA7188471 //DA7188447
    bool mRet1 = cap1.CameraInit((char*)sn1, true, 5000, 0.7, 0.3);
    while(mRet1 ){
        img = cap1.getFrame(0,0);
        if(img.empty()) continue;
        // cap1.putFps();
        
        cv::putText(img, "fps: "+ cv::format("%f",cap1.fps), cv::Point2f(20,20), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,153,255));
        cv::imshow("camrea_sdk_debug", img);
        int key = cv::waitKey(1);
        if(key == 'q') break;
    }    

    

    cap1.~CameraExmple();


     std::cout<<"Camrea open failed"<<endl;
    return 0;
}


