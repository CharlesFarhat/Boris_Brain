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

#include <iostream>
#include <boost/lexical_cast.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace dso;

bool dataset = true;


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
    cout << "Launching Boris brain System, if problem please contact me @ charles.farhat@free.fr" << endl;

    // hook crtl+C.
    boost::thread exThread = boost::thread(exitThread);

    // TODO : launch Point cloud data stream in another thread
    // TODO : launch REMODE thread to compute High density map


    if (dataset)
    {
        dso::VO_Pipeline_dataset datasetDSO(argv, argc);
        datasetDSO.launch_VO_Dataset();
    }
    else
    {
        // Get Video Feed :
        int cameraNumber(0);
        std::cout << "Camera used is : " <<cameraNumber << std::endl;
        cv::VideoCapture cap(cameraNumber);
        if(!cap.isOpened())
        {
            cout << "Cannot open camera or camera is not working !" << endl;
            exit(0);
        }

        cout << "launching the Direct sparse visual odometry system" << endl;

        dso::VO_Pipeline_Live liveDSO(argv, argc);
        liveDSO.lanchLive(cap);
        cap.release();
    }

    printf("System finished.\n");
    std::cout << "test over -----> from main system" << std::endl;
    return 0;
}