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
#include "utils/settings.h"
#include "EnvProcessing/VisualOdometry/FullSystem/FullSystem.h"
#include "utils/Undistort.h"
#include "EnvProcessing/IOWrapper/Pangolin/PangolinDSOViewer.h"
#include "EnvProcessing/IOWrapper/OutputWrapper/SampleOutputWrapper.h"
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <opencv2/opencv.hpp>
#include "EnvProcessing/IOWrapper/Output3DWrapper.h"
#include "EnvProcessing/IOWrapper/ImageDisplay.h"
#include <boost/thread.hpp>
#include "utils/globalFuncs.h"
#include "utils/NumType.h"
#include "utils/DatasetReader.h"
#include "EnvProcessing/VisualOdometry/OptimizationBackend/MatrixAccumulators.h"
#include "EnvProcessing/VisualOdometry/FullSystem/PixelSelector2.h"
#include "utils/globalCalib.h"
#include "Boris_System_Setup.h"

#include "CamerasAPI/videoStream.h"

namespace Boris_Brain {
    namespace dso {

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
            double rescale = 1;
            bool reverse = false;
            int start = 0;
            int end = 100000;
            bool prefetch = false;
            float playbackSpeed = 0;    // 0 for linearize (play as fast as possible, while sequentializing tracking & mapping). otherwise, factor on timestamps.
            bool preload = false;
            bool useSampleOutput = false;
            int mode = 0;
            dso::FullSystem *fullSystem = 0;
            ImageFolderReader *reader = 0;


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
            bool useSampleOutput = false;
            dso::FullSystem *fullSystem = 0;
            dso::Undistort *undistorter = 0;
            int frameID = 0;
        };

    }
}
#endif //BORIS_SYSTEM_BRAIN_VO_PIPELINE_H
