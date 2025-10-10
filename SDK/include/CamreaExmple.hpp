#pragma once

#include "./daheng/daheng.hpp"
#include "./hik/hik.hpp"

#include <csignal>

namespace sdk{


    template<class CamreaType>
    class CameraExmple : public CamreaType{
    public:
        cv::Mat frame_readp;
        
        ~CameraExmple(){
            CamreaType::~CamreaType();
        }


        void putResolution(){
            // try{
                 std::cout<<"分辨率为： width "<<this->SensorWidth<<"   hight "<<this->SensorHeight<<std::endl;
            // }catch(){

            // }
           
        }

        void put_fps(){ 
            std::cout<<"fps: "<<this->fps<<std::endl;
            std::cout<<"delay: "<<1./this->fps<<std::endl;
        }

        cv::Mat getFrame(bool flip = false, bool mirror = false){
            frame_readp = CamreaType::getFrame(flip, mirror);
            return frame_readp;
        }
        
        // CameraExmple(){
        //      signal(SIGINT, this->~T());
        // }
        

    };  


}
