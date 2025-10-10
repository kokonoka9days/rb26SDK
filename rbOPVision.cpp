#include <iostream>
#include <thread>
#include <cstdlib>
#include <chrono>
// #include <rclcpp/rclcpp.hpp>
// #include <sensor_msgs/msg/image.hpp>
// #include <cv_bridge/cv_bridge.h>
// #include <chrono>

// std::mutex mtx;
#include "./SDK/include/CamreaExmple.hpp"


int main(int argc, char const *argv[])
{
    // std::a
    cv::Mat img,img1;
    using CamreaType = sdk::HikCamera;
    
    sdk::CameraExmple<CamreaType>::CameraSDKInit();
    sdk::CameraExmple<CamreaType> cap1;
    // sdk::CameraExmple<sdk::DahengCamera> cap2;
        

        const char* sn1 = "DA7188447";//KE0210010004  //DA7188471 //DA7188447
        bool mRet1 = cap1.CameraInit((char*)sn1, true, 5000, 0.7, 0.3, true);
        while(mRet1 ){
            img = cap1.getFrame(0,0);
            if(cap1.frame_readp.empty()) continue;
            // cap1.put_fps();
            
            cv::putText(cap1.frame_readp, "fps: "+ cv::format("%f",cap1.fps), cv::Point2f(20,20), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,153,255));
            cv::imshow("camrea_sdk_debug", cap1.frame_readp);
            int key = cv::waitKey(1);
            if(key == 'q') break;
        }    

    

    cap1.~CameraExmple();

    // std::thread imshowthread([&](){
    //     while (1)
    //     {
    //         /* code */
           
    //         if(cap1.cap_init ){
    //             std::cout<<"asksdjasd"<<std::endl;
    //             {
    //                 std::lock_guard<std::mutex> lock(mtx);
    //                 cv::imshow("camrea_sdk_debug1", img1);
    //                 cv::imshow("camrea_sdk_debug", img);
    //                 cv::waitKey(1);                    
    //             }
                
    //         }
            
    //     }
        

     std::cout<<"Camrea open failed"<<endl;
    return 0;
}


