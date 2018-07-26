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



videoStream::videoStream(int camIndex, bool useHack = false, bool UseGray = false) : cameraIndex(camIndex), useHack(useHack), useOnlyGrayValues(UseGray)
{
    videocaptureStream = new cv::VideoCapture();
    videocaptureStream->open(cameraIndex);
    if(!videocaptureStream->isOpened()) {
        std::cout << "Camera not supported / camera not working !" << std::endl;
        exit(0);
    }
    else
    {
        std::cout << "Camera used is : " << camIndex << std::endl;
    }

    if (useHack)
    {
        cv::Mat image;
        videocaptureStream->read(image);
    }
}

cv::Mat videoStream::getImage()
{

    if (useOnlyGrayValues)
    {
        return GrayImages();
    }
    else
    {
        videocaptureStream->read(image);
        if (image.empty()) {
            std::cout
                    << "Img read is empty !!! Stream is not fonctionning well please check if your cam is recording (check your cables !!!"
                    << std::endl;
            exit(0);
        }
        return image;
    }
}

cv::Mat videoStream::GrayImages()
{
    videocaptureStream->read(image);
    image.convertTo(image, CV_8UC1);
    cv::cvtColor(image, image, cv::COLOR_RGB2GRAY);

    assert(image.type() == CV_8U);
    assert(image.channels() == 1);

    if (image.empty()) {
        std::cout
                << "Img read is empty !!! Stream is not fonctionning well please check if your cam is recording (check your cables !!!"
                << std::endl;
        exit(0);
    }

    return image;
}

videoStream::~videoStream()
{
    delete videocaptureStream;
    std::cout << "closing opencvStream !!" << std::endl;
}