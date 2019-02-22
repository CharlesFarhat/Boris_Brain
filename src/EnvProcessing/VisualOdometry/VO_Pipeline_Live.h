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


/*
 * Main entry of the system.
 * Launching SVO, REMODE and the PCl to server thread.
 * getting video feed and then sending to SVO
 */

#ifndef BORIS_SYSTEM_BRAIN_VO_PIPELINE_H
#define BORIS_SYSTEM_BRAIN_VO_PIPELINE_H

#include <iostream>
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>
#include <opencv2/opencv.hpp>
/* OLD stuff just here in case I need it !
#include "EnvProcessing/EP_Utils/settings.h"
#include "EnvProcessing/VisualOdometry/FullSystem/FullSystem.h"
#include "EnvProcessing/EP_Utils/Undistort.h"
#include "EnvProcessing/IOWrapper/Pangolin/PangolinDSOViewer.h"
#include "EnvProcessing/IOWrapper/OutputWrapper/SampleOutputWrapper.h"
#include "EnvProcessing/IOWrapper/Output3DWrapper.h"
#include "EnvProcessing/IOWrapper/ImageDisplay.h"
#include "EnvProcessing/EP_Utils/globalFuncs.h"
#include "EnvProcessing/EP_Utils/NumType.h"
#include "EnvProcessing/EP_Utils/DatasetReader.h"
#include "EnvProcessing/VisualOdometry/OptimizationBackend/MatrixAccumulators.h"
#include "EnvProcessing/VisualOdometry/FullSystem/PixelSelector2.h"
#include "EnvProcessing/EP_Utils/globalCalib.h"
 */


#include "frontend/FullSystem.h"
#include "utils/DatasetReader.h"
#include "Settings.h"
#include "frontend/Undistort.h"
#include "frontend/ImageRW.h"
#include "frontend/ImageAndExposure.h"
#include "internal/GlobalFuncs.h"
#include "internal/GlobalCalib.h"

#include "Boris_System_Setup.h"
#include "CamerasAPI/videoStream.h"

namespace Boris_Brain {
    namespace ldso {

        class VO_Pipeline_dataset {
        public:
            VO_Pipeline_dataset(Settings *run_settings);

            ~VO_Pipeline_dataset();

            void settingsDefault(int preset);

            void launch_VO_Dataset();

        private:
            std::string vignette = "";
            std::string gammaCalib = "";
            std::string source = "";
            std::string calib = "";
            std::string vocPath = "";
            double rescale = 1;
            bool reverse = false;
            int start = 0;
            int end = 100000;
            bool prefetch = false;
            float playbackSpeed = 0;    // 0 for linearize (play as fast as possible, while sequentializing tracking & mapping). otherwise, factor on timestamps.
            bool preload = false;
            int mode = 0;
        };


        class VO_Pipeline_Live {
        public:
            VO_Pipeline_Live(Settings *run_settings);

            ~VO_Pipeline_Live();

            void lanchLive(int index);


        private:
            std::string calib = "";
            std::string vignetteFile = "";
            std::string gammaFile = "";
            std::string vocPath = "";
            int frameID = 0;
        };

    }
}
#endif //BORIS_SYSTEM_BRAIN_VO_PIPELINE_H
