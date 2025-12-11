# rb26SDK
## 简介
该仓库为26赛季自瞄所需C++相机驱动，实现工业相机初始化、参数设置、图像采集并转换成opencv cv::Mat格式，相机SDK包括海康相机、大恒相机。

## 🌟该项目的亮眼之处？
- 📦&ensp;大恒与海康驱动分别封装成sdk::DahengCamrea、sdk::HikCamrea类，并继承sdk::Camrea类，用户可通过实例化模版类继承的普通类sdk::CameraExmple\<sdk::DahengCamrea或sdk::HikCamrea>并调用实例化类的成员方法来启动相机，框架逻辑清晰方便阅读和使用
- 📃&ensp;注释多，不需要耗费太多精力来阅读
- 📷&ensp;含单相机与多相机启动示例代码

## 须知
1.确保相机依赖全部已安装完毕、sdk软件正常\
2、该sdk在hik MV-CS-016-10UC上测试gamma功能不可用\
3、确保相机线usb端连接电脑的USB 3.0接口\
4、有的电脑存在hik相机设备检测数量比实际设备数量多1的情况，不影响正常使用\
5、曝光时间单位是us，增益取值限定在0~1之间
## 👐运行环境 
1.ubuntu20.04、22.04\
2.Intel NUC

## ⏫项目依赖
- OpenCV
- 大恒sdk
- 海康sdk
- cmake


### To-do List
- [ ] 大恒相机的降噪功能没试验过 在c软件开发说明书226页
- [ ] ros2 为相机实例构建image_transport::CameraPublisher。 直接在sdk图像指针所指向的缓冲转换成sensor_msgs::msg::Image的格式，无需经过cv::Mat的转换,后面会在git上多一个ros分支出来
- [ ] 大恒ProcessData使用std::funsion<>+std::unordered_map哈希表映射
