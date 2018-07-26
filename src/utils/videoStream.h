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

namespace Boris_Brain
{

    class videoStream
    {
    public:
        videoStream(int camIndex, bool useHack, bool UseGray);
        ~videoStream();

        cv::Mat getImage();

    private:

        cv::Mat GrayImages();

        cv::VideoCapture* videocaptureStream;
        bool useOnlyGrayValues;    /// this will convert any value into gray scalars
        cv::Mat image;


    };

}
#endif //ONLINE_PHOTOMETRIC_CALIBRATION_VIDEOSTREAM_H
