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
 *                     © charles200000 on 26/07/18
*/

#ifndef BORIS_SYSTEM_BRAIN_BORIS_SYSTEM_SETUP_H
#define BORIS_SYSTEM_BRAIN_BORIS_SYSTEM_SETUP_H

#include <iostream>

namespace Boris_Brain {

struct Settings
        {

    int runningDSOLive;             /// Are you willing to launch a dataset ?
    int cameraindex;                /// Camera To use
    int debugout_runquiet;         /// Quiet mode
    int optionPreset;              /// Preset to use 1 / 2 ...
    int disableReconfigure;
    int setting_logStuff;
    int enableLoopClosing;
    int reverse;
    int disableAllDisplay;
    int multiThreading;
    int prefetch;
    int start;
    int end;
    std::string source;
    std::string calib;
    std::string vignette;
    std::string gammaCalib;
    std::string vocab;
    double rescale;
    float playbackSpeed;
    bool debugSaveImages;
    int mode;

};
}




#endif //BORIS_SYSTEM_BRAIN_BORIS_SYSTEM_SETUP_H
