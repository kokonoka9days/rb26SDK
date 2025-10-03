# rb26SDK
## 简介
该仓库为电科中山RoboBrave战队26赛季自瞄所需硬件驱动(因为目前只有相机驱动和串口通信驱动)，相机SDK包括海康相机、大恒相机。
## 🌟该项目的亮眼之处？
- 📦&ensp;大恒与海康驱动分别封装成sdk::DahengCamrea、sdk::HikCamrea类，并继承sdk::Camrea类，用户可通过实例化模版类继承的普通类sdk::CameraExmple\<sdk::DahengCamrea或sdk::HikCamrea>并调用实例化类的成员方法来启动相机，框架逻辑清晰方便阅读和使用
- 📃&ensp;注释多，不需要耗费太多精力来阅读
- 📷&ensp;含单相机与多相机启动示例代码
- 含vscode cmake配置，在CMakeLists.txt改一下mvs包所在路径(也可能不需要改)，即可f5无脑启动

## 运行环境 
ubuntu20.04、22.04

## 项目依赖
- OpenCV
- 大恒sdk
- 海康sdk
- cmake
  
