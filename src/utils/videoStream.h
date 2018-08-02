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

#ifndef ONLINE_PHOTOMETRIC_CALIBRATION_VIDEOSTREAM_H
#define ONLINE_PHOTOMETRIC_CALIBRATION_VIDEOSTREAM_H

#include <opencv2/opencv.hpp>
#include "CamerasAPI/MGN-U/API-MGN_camera.hpp"

namespace Boris_Brain
{

    class videoStream
    {
    public:
        videoStream(char* devPath, bool UseGray);
        ~videoStream();

        cv::Mat getImage();

    private:

        cv::Mat GrayImages();


        API_MGN::Camera* myCam = 0;
        API_MGN::camera_format* camFormat= 0;
        //cv::VideoCapture* videocaptureStream;
        bool useOnlyGrayValues;    /// this will convert any value into gray scalars
        cv::Mat srcImg;


    };

}
#endif //ONLINE_PHOTOMETRIC_CALIBRATION_VIDEOSTREAM_H
