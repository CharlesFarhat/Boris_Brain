/**
 *
 * ____             _        _____           _
 *|  _ \           (_)      / ____|         | |
 *| |_) | ___  _ __ _ ___  | (___  _   _ ___| |_ ___ _ __ ___
 *|  _ < / _ \| '__| / __|  \___ \| | | / __| __/ _ \ '_ ` _ \
 *| |_) | (_) | |  | \__ \  ____) | |_| \__ \ ||  __/ | | | | |
 *|____/ \___/|_|  |_|___/ |_____/ \__, |___/\__\___|_| |_| |_| 2018
 *                                  __/ |
 *                                 |___/
 *
 *                     © Charles200000
*/

#include "videoStream.h"

using namespace API_MGN;

namespace Boris_Brain
{
    videoStream::videoStream(char* devPath, bool UseGray = false) : useOnlyGrayValues(UseGray)
    {
        /* generic way :

        videocaptureStream = new cv::VideoCapture();
        videocaptureStream->open(camIndex);
        videocaptureStream->set(CV_CAP_PROP_FRAME_WIDTH, 1280);
        videocaptureStream->set(CV_CAP_PROP_FRAME_HEIGHT, 960);
        if(!videocaptureStream->isOpened()) {
            std::cout << "Camera not supported / camera not working !" << std::endl;
            exit(0);
        }
        else
        {
            std::cout << "Camera used is : " << camIndex << std::endl;
        }
        /// Use hack to correct openCV bug where you have blank image with working cameras (VERY ANNOYING !!!!)
        if (useHack)
        {
            cv::Mat image;
            videocaptureStream->read(image);
        }
         */

        myCam = new API_MGN::Camera(devPath);
        /* USB 3.0 */
        /* 8-bit Greyscale 1280 x 720 60 fps */
        myCam->set_format(1280, 720, API_MGN::fourcc_to_pixformat('G','R','E','Y'), 1, 60);

        /* 8-bit Greyscale 1280 x 960 45 fps */
        //camera.set_format(1280, 960, Withrobot::fourcc_to_pixformat('G','R','E','Y'), 1, 45);

        /* 8-bit Greyscale 320 x 240 160 fps */
        //camera.set_format(320, 240, Withrobot::fourcc_to_pixformat('G','R','E','Y'), 1, 160);

        /* 8-bit Greyscale 640 x 480 80 fps */
        //camera.set_format(640, 480, Withrobot::fourcc_to_pixformat('G','R','E','Y'), 1, 80);



        /*
        * get current camera format (image size and frame rate)
        */
        camFormat = new API_MGN::camera_format;
        myCam->get_current_format(*camFormat);

       if (!myCam->start()) {
            perror("Failed to start. camera");
            exit(0);
        }

        cv::Mat srcImg(cv::Size(camFormat->width, camFormat->height), CV_8UC1);
    }

    cv::Mat videoStream::getImage()
    {

        if (useOnlyGrayValues)
        {
            return GrayImages();
        }
        else
        {
            /* Copy a single frame(image) from camera(oCam-1MGN). This is a blocking function. */
            int size = myCam->get_frame(srcImg.data, camFormat->image_size, 1);

            /* If the error occured, restart the camera. */
            if (size == -1) {
                printf("error number: %d\n", errno);
                perror("Cannot get image from camera");
                myCam->stop();
                myCam->start();
            }
            return srcImg;
        }
    }

    cv::Mat videoStream::GrayImages()
    {
        /* Copy a single frame(image) from camera(oCam-1MGN). This is a blocking function. */
        int size = myCam->get_frame(srcImg.data, camFormat->image_size, 1);

        /* If the error occured, restart the camera. */
        if (size == -1) {
            printf("error number: %d\n", errno);
            perror("Cannot get image from camera");
            myCam->stop();
            myCam->start();
        }
        srcImg.convertTo(srcImg, CV_8UC1);
        cv::cvtColor(srcImg, srcImg, cv::COLOR_RGB2GRAY);

        assert(srcImg.type() == CV_8UC1);
        assert(srcImg.channels() == 1);

        return srcImg;
    }

    videoStream::~videoStream()
    {
        /*
     * Stop streaming
     */
        myCam->stop();

        delete myCam;
        delete camFormat;
        std::cout << "closing camera stream !!" << std::endl;
    }
}

