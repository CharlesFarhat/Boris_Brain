# Boris Main System : Brain

This is part of the Boris system. Please see Boris system README file for full details.
As an overview we could say that the Boris Brain is mainly focus on environment processing and AI brain. The environment processing part is made of the Visual Odometry system, 3D reconstruction on the fly and send point cloud data to the Boris server.
Please see diagram below to understand how the system is working.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

# Prerequisites

In order to run the system you need Both the **Boris Utils** and the **Boris Server** running on the machine. Running the system on an embedded device is recommended (jetson tx2...)

### Default dependencies :

### Boris Utils :
**CRITICAL**
You need to first build boris utils system !!!
All dependencies are explained in the boris utils repo :

See : https://github.com/charles200000/Boris_Utils

#### The PCl library :

Please see how to build it here : 
http://pointclouds.org/documentation/tutorials/compiling_pcl_posix.php

> you will need VTK as well :)



##### At the end you should have Boris Utils, Sophus, OpenCV (With CUDA), CuDNN, The PCL, Boost, Eigen working.
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
