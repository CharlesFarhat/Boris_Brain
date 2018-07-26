/*
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



#pragma once
#include <vector>
#include "utils/NumType.h"
#include "utils/MinimalImage.h"


namespace Boris_Brain {
    namespace dso {

        namespace IOWrap {

            void displayImage(const char *windowName, const MinimalImageB *img, bool autoSize = false);

            void displayImage(const char *windowName, const MinimalImageB3 *img, bool autoSize = false);

            void displayImage(const char *windowName, const MinimalImageF *img, bool autoSize = false);

            void displayImage(const char *windowName, const MinimalImageF3 *img, bool autoSize = false);

            void displayImage(const char *windowName, const MinimalImageB16 *img, bool autoSize = false);


            void displayImageStitch(const char *windowName, const std::vector<MinimalImageB *> images, int cc = 0,
                                    int rc = 0);

            void displayImageStitch(const char *windowName, const std::vector<MinimalImageB3 *> images, int cc = 0,
                                    int rc = 0);

            void displayImageStitch(const char *windowName, const std::vector<MinimalImageF *> images, int cc = 0,
                                    int rc = 0);

            void displayImageStitch(const char *windowName, const std::vector<MinimalImageF3 *> images, int cc = 0,
                                    int rc = 0);

            int waitKey(int milliseconds);

            void closeAllWindows();

        }
    }
}