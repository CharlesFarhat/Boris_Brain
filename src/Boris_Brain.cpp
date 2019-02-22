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

#include <locale.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "EnvProcessing/VisualOdometry/VO_Pipeline_Live.h"
#include "Boris_System_Setup.h"
#include "utils/CLI11.hpp"

#include <iostream>
#include <boost/lexical_cast.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace Boris_Brain::ldso;

void my_exit_handler(int s)
{
    printf("Caught signal %d\n",s);
    exit(1);
}

void exitThread()
{

    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = my_exit_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);
    while(true) pause();
}


int main(int argc, char* argv[])
{
    CLI::App app("Boris Brain system");

    Boris_Brain::Settings run_settings;
    run_settings.runningDSOLive = 2; // Set to 2 in order no to launch by default
    run_settings.cameraindex = 0;
    run_settings.debugout_runquiet = 0;
    run_settings.optionPreset = 0;
    run_settings.disableReconfigure = 1;
    run_settings.setting_logStuff = 0;
    run_settings.reverse = 0;
    run_settings.disableAllDisplay = 0;
    run_settings.multiThreading = 0;
    run_settings.prefetch = 0;
    run_settings.start = 0;
    run_settings.end = 100000;
    run_settings.source = "nope";
    run_settings.calib = "nope";
    run_settings.vignette = "nope";
    run_settings.gammaCalib = "nope";
    run_settings.vignette = "nope";
    run_settings.rescale = 1;
    run_settings.playbackSpeed = 0;
    run_settings.debugSaveImages = 0;
    run_settings.mode = 0;
    run_settings.enableLoopClosing = 1;



    app.add_option("-c, --cameraIndex", run_settings.cameraindex, "camera index to use", true);
    app.add_option("-l, --runningLive", run_settings.runningDSOLive, "Are you launching live or using the dataset ?", true);
    app.add_option("-f, --files", run_settings.source, "if you are using dataset MANDATORY !", true);

    app.add_option("vocab =", run_settings.vocab, "", true);
    app.add_option("calib=", run_settings.calib, "", true);
    app.add_option("vignette=", run_settings.vignette, "", true);

    app.add_option("-q, --quiet", run_settings.debugout_runquiet, "", true);
    app.add_option("-p, --preset", run_settings.optionPreset, "", true);
    app.add_option("-r, --reconfigure", run_settings.disableReconfigure, "", true);
    app.add_option("--nolog", run_settings.setting_logStuff, "", true);
    app.add_option("--reverse", run_settings.reverse, "", true);
    app.add_option("--nogui", run_settings.disableAllDisplay, "", true);
    app.add_option("--nomt", run_settings.multiThreading, "", true);
    app.add_option("--prefetch", run_settings.prefetch, "", true);
    app.add_option("--start", run_settings.start, "", true);
    app.add_option("--end", run_settings.end, "", true);
    app.add_option("--rescale", run_settings.rescale, "", true);
    app.add_option("--speed", run_settings.playbackSpeed, "", true);
    app.add_option("--save", run_settings.debugSaveImages, "", true);
    app.add_option("-m, --mode", run_settings.mode, "", true);
    app.add_option("-g, --gamma", run_settings.gammaCalib, "", true);
    app.add_option("--loopClosure", run_settings.enableLoopClosing, "", true);




    CLI11_PARSE(app, argc, argv);

    cout << "Launching Boris brain System, if problem please contact me @ charles200000@maclg.net" << endl;

    // hook crtl+C TODO : haddle user input
    boost::thread exThread = boost::thread(exitThread);

    // TODO : launch Point cloud data stream in another thread



    if (run_settings.runningDSOLive == 1)
    {
        cout << "launching the Direct sparse visual odometry system" << endl;

        Boris_Brain::ldso::VO_Pipeline_Live liveDSO(&run_settings);
        liveDSO.lanchLive(run_settings.cameraindex);
    }
    else if (run_settings.runningDSOLive == 0)
    {
        Boris_Brain::ldso::VO_Pipeline_dataset datasetDSO(&run_settings);
        datasetDSO.launch_VO_Dataset();
    }
    else
    {
        printf("insufficient args ! \n");
        exit(0);
    }

    // TODO : launch REMODE thread to compute High density map

    printf("System finished.\n");
    std::cout << "test over -----> from main system bye hope to see you soon \n" << std::endl;
    return 0;
}
