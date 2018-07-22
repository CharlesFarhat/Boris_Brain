# Boris Main System : Brain

This is part of the Boris system. Please see Boris system README file for full details.
As an overview we could say that the Boris Brain is mainly focus on environment processing and AI brain. The environment processing part is made of the Visual Odometry system, 3D reconstruction on the fly and send point cloud data to the Boris server.
Please see diagram below to understand how the system is working.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

# Prerequisites

In order to run the system you need Both the **Boris Utils** and the **Boris Server** running on the machine. Running the system on an embedded device is recommended (jetson tx2...)

### Default dependencies :

Obviously GCC !
 
 #### Cmake
	sudo apt-get install cmake
    
#### Boost - c++ Librairies (thread and system are needed)

	sudo apt-get install libboost-all-dev

#### Eigen 3 - Linear algebra

    apt-get install libeigen3-dev

#### CUDA 9.1
Follow the instructions at https://developer.nvidia.com/cuda-downloads

#### OpenCV - Computer vision library for loading and displaying images
You can install with apt :
```
sudo apt-get install libopencv-dev
```
**BUT** in order to use it with Boris
It is recommended to custom build OpenCV with CUDA and Qt support !

> To do soo :
> https://docs.opencv.org/3.3.1/d7/d9f/tutorial_linux_install.html
> and for jetson : https://docs.opencv.org/master/d6/d15/tutorial_building_tegra_cuda.html update it with cuda 9.0
> !!!be ready to spend some time on nvidia forums, lot's of errors and on jetson tx2 you actually need a patch in order to make it run !!
> Finally you need to add `-DWITH_QT` when you cmake it :)

 
#### CuDNN (last version available)
To be found at https://developer.nvidia.com/cudnn

 #### The PCl library :

Please see how to build it here : 
http://pointclouds.org/documentation/tutorials/compiling_pcl_posix.php

### Boris Utils :
**CRITICAL**
You need to first build boris utils system !!!

See : https://github.com/charles200000/Boris_Utils

##### At the end you should have Boris Utils, Sophus, fast, OpenCV (With CUDA, QT support), CuDNN, The PCL, Boost, Eigen working.
####  yeah you're over !! Hope it didn't took you 3 weeks ;)

# Building

Once you have all dependencies and the Boris utils build you can proceed :

```
git clone --recursive https://github.com/charles200000/Boris_Brain
cd Boris_Brain/
mkdir build/
cmake ..
make -j "number of thread available"
```
you can configure the cmakelist.cmake to change G2O or Qt usage.

## Deployment
please check the wiki, I will try to create a compete documentation but this is time consuming and I don't have that much time so....


## Authors

* **Charles200000** - *Initial work*

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Hahahaha if it's working the first time pleassseeeee send me a video and I will make a mem out of it !!!!
