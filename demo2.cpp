/**
 * 多相机采集实例
 */
#include <iostream>
#include <thread>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>

#include "./rb26SDK/include/CamreaExmple.hpp"

//线程安全队列
template <typename T, bool PopWhenFull = false>
class ThreadSafeQueue
{
public:
  ThreadSafeQueue(
    size_t max_size, std::function<void(void)> full_handler = [] {})
  : max_size(max_size), full_handler(full_handler)
  {
  }

  void push(const T & value)
  {
    std::unique_lock<std::mutex> lock(mutex);

    if (queue.size() >= max_size) {
      if (PopWhenFull) {
        queue.pop();
      } else {
        full_handler();
        return;
      }
    }

    queue.push(value);
    not_empty_condition_.notify_all();
  }

  void pop(T & value)
  {
    std::unique_lock<std::mutex> lock(mutex);

    not_empty_condition_.wait(lock, [this] { return !queue.empty(); });

    if (queue.empty()) {
      std::cerr << "Error: Attempt to pop from an empty queue." << std::endl;
      return;
    }

    value = queue.front();
    queue.pop();
  }

  T pop()
  {
    std::unique_lock<std::mutex> lock(mutex);

    not_empty_condition_.wait(lock, [this] { return !queue.empty(); });

    T value = std::move(queue.front());
    queue.pop();
    return std::move(value);
  }

  T front()
  {
    std::unique_lock<std::mutex> lock(mutex);

    not_empty_condition_.wait(lock, [this] { return !queue.empty(); });

    return queue.front();
  }

  void back(T & value)
  {
    std::unique_lock<std::mutex> lock(mutex);

    if (queue.empty()) {
      std::cerr << "Error: Attempt to access the back of an empty queue." << std::endl;
      return;
    }

    value = queue.back();
  }

  bool empty()
  {
    std::unique_lock<std::mutex> lock(mutex);
    return queue.empty();
  }

  void clear()
  {
    std::unique_lock<std::mutex> lock(mutex);
    while (!queue.empty()) {
      queue.pop();
    }
    not_empty_condition_.notify_all();  // 如果其他线程正在等待队列不为空，这样可以唤醒它们
  }

private:
  std::queue<T> queue;
  size_t max_size;
  mutable std::mutex mutex;
  std::condition_variable not_empty_condition_;
  std::function<void(void)> full_handler;//阻塞处理方式
};

template <typename CamreaType>
class CameraCaptureThread{
public:
    ThreadSafeQueue<cv::Mat> images_queue;
    std::unique_ptr<std::thread> camera_capture_thread = nullptr;
    std::unique_ptr<sdk::CameraExmple<CamreaType>> camera = nullptr;
    bool cap_is_running  = true;
    CameraCaptureThread( const char *sn, 
                            bool autoWhiteBalance ,
                            int expoosureTime , 
                            double gainFactor , 
                            double dGammaParam ,
                            bool flip,
                            bool mirror): images_queue(1){
        camera = std::make_unique<sdk::CameraExmple<CamreaType>>();
        cap_is_running = camera->CameraInit((char*)sn, 
                                    autoWhiteBalance, 
                                    expoosureTime, 
                                    gainFactor, 
                                    dGammaParam
                                    );
        if(!cap_is_running) return;
        camera_capture_thread = std::make_unique<std::thread>([&](){
            while(cap_is_running){
                cv::Mat img = camera->getFrame(flip,mirror);
                if(img.empty()) continue;
                // cap.putFps();
                cv::putText(img, "fps: "+ cv::format("%f",camera->fps), cv::Point2f(20,20), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,153,255));
                images_queue.push(img);
            }    

        });

    }

    void ThreadJoin(){
        if(camera_capture_thread != nullptr){
            camera_capture_thread->join();
        }
    }

};

int main(int argc, char const *argv[])
{
    using CamreaType1 = sdk::HikCamera;
    sdk::CameraExmple<CamreaType1>::CameraSDKInit();
    using CamreaType2 = sdk::DahengCamera;
    sdk::CameraExmple<CamreaType2>::CameraSDKInit();
    CameraCaptureThread<CamreaType1> capTh1("DA7188471",true, 5000, 0.7, 0.3, 0,0);
    CameraCaptureThread<CamreaType2> capTh2("KE0210010003",true, 5000, 0.7, 0.3, 0,0);
        
    std::thread run([&](){
        while (capTh1.cap_is_running && capTh2.cap_is_running)
        {
           cv::Mat img1, img2;
           capTh1.images_queue.pop(img1);
           capTh2.images_queue.pop(img2);
           if(!img1.empty()) cv::imshow("img1", img1);
           if(!img2.empty()) cv::imshow("img2", img2);
           if(cv::waitKey(1) == 'q') break;
        }
        capTh1.cap_is_running = capTh2.cap_is_running = false;
    });
    run.join();
    capTh1.ThreadJoin();
    capTh2.ThreadJoin();
    return 0;
}
