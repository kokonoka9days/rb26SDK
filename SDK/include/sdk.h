#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>
#include <cstdlib>

using  ClockPoint =  std::chrono::time_point<std::chrono::high_resolution_clock>;
#define    NowTime     std::chrono::high_resolution_clock::now()

namespace sdk
{
    class Camera{
    public:
        char* cap_sn;
        int64_t SensorWidth = -1, SensorHeight = -1;
        ClockPoint time_point = NowTime;
        double fps = 0;
        bool cap_init = false;

        // virtual bool CameraSDKInit() = 0;

        virtual bool CameraInit( char *sn, 
                            bool autoWhiteBalance , 
                            int expoosureTime , 
                            double gainFactor , 
                            double dGammaParam , 
                            bool aim ) = 0 ;

        double update_timer(){
            fps = 1./((double) std::chrono::duration_cast< std::chrono::microseconds> ( NowTime - time_point ).count() / 1000000);
            time_point = NowTime;
            return fps;
        }


    };
} // namespace sdk
