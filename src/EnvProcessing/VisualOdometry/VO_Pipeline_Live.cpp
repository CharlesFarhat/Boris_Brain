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


/**
 * Main entry of the system.
 * Launching SVO, REMODE and the PCl to server thread.
 * getting video feed and then sending to SVO
 */

#include "VO_Pipeline_Live.h"
#include <locale.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;
using namespace Boris_Brain::dso;

namespace Boris_Brain {
    namespace dso {

        VO_Pipeline_dataset::VO_Pipeline_dataset(Settings *run_settings) {

                if (run_settings->sampleoutput == 1)
                {
                    useSampleOutput = true;
                    printf("USING SAMPLE OUTPUT WRAPPER!\n");
                }

                if (run_settings->debugout_runquiet == 1) {
                    setting_debugout_runquiet = true;
                    printf("QUIET MODE, I'll shut up!\n");
                }

                settingsDefault(run_settings->optionPreset);

                if (run_settings->disableReconfigure == 0) {
                    disableReconfigure = true;
                    printf("DISABLE RECONFIGURE!\n");
                }

                if (run_settings->setting_logStuff == 1) {
                    setting_logStuff = false;
                    printf("DISABLE LOGGING!\n");
                }

                if (run_settings->reverse == 1) {
                    reverse = true;
                    printf("REVERSE!\n");
                }

                if (run_settings->disableAllDisplay == 1) {
                    disableAllDisplay = true;
                    printf("NO GUI!\n");
                }

                if (run_settings->multiThreading == 1) {
                    multiThreading = false;
                    printf("NO MultiThreading!\n");
                }

                if (run_settings->prefetch == 1) {
                    prefetch = true;
                    printf("PREFETCH!\n");
                }

                start = run_settings->start;
                printf("START AT %d!\n", start);



                end = run_settings->end;
                printf("END AT %d!\n", end);


                source = run_settings->source;
                printf("loading data from %s!\n", source.c_str());

                calib = run_settings->calib;
                printf("loading calibration from %s!\n", calib.c_str());

                vignette = run_settings->vignette;
                printf("loading vignette from %s!\n", vignette.c_str());


                gammaCalib = run_settings->gammaCalib;
                printf("loading gammaCalib from %s!\n", gammaCalib.c_str());


                rescale = run_settings->rescale;
                printf("RESCALE %f!\n", rescale);

                playbackSpeed = run_settings->playbackSpeed;
                printf("PLAYBACK SPEED %f!\n", playbackSpeed);


            if (run_settings->debugSaveImages == 1) {
                    debugSaveImages = true;
                    if (42 == system("rm -rf images_out"))
                        printf("system call returned 42 - what are the odds?. This is only here to shut up the compiler.\n");
                    if (42 == system("mkdir images_out"))
                        printf("system call returned 42 - what are the odds?. This is only here to shut up the compiler.\n");
                    if (42 == system("rm -rf images_out"))
                        printf("system call returned 42 - what are the odds?. This is only here to shut up the compiler.\n");
                    if (42 == system("mkdir images_out"))
                        printf("system call returned 42 - what are the odds?. This is only here to shut up the compiler.\n");
                    printf("SAVE IMAGES!\n");
                }

                mode = run_settings->mode;
                if (run_settings->mode == 0) {
                    printf("PHOTOMETRIC MODE WITH CALIBRATION!\n");
                }
                if (run_settings->mode == 1) {
                    printf("PHOTOMETRIC MODE WITHOUT CALIBRATION!\n");
                    setting_photometricCalibration = 0;
                    setting_affineOptModeA = 0; //-1: fix. >=0: optimize (with prior, if > 0).
                    setting_affineOptModeB = 0; //-1: fix. >=0: optimize (with prior, if > 0).
                }
                if (run_settings->mode == 2) {
                    printf("PHOTOMETRIC MODE WITH PERFECT IMAGES!\n");
                    setting_photometricCalibration = 0;
                    setting_affineOptModeA = -1; //-1: fix. >=0: optimize (with prior, if > 0).
                    setting_affineOptModeB = -1; //-1: fix. >=0: optimize (with prior, if > 0).
                    setting_minGradHistAdd = 3;
                }

            printf("could parse argument !!!! \n");

        }

        void VO_Pipeline_dataset::settingsDefault(int preset) {
            printf("\n=============== PRESET Settings: ===============\n");
            if (preset == 0 || preset == 1) {
                printf("DEFAULT settings:\n"
                       "- %s real-time enforcing\n"
                       "- 2000 active points\n"
                       "- 5-7 active frames\n"
                       "- 1-6 LM iteration each KF\n"
                       "- original image resolution\n", preset == 0 ? "no " : "1x");

                playbackSpeed = (preset == 0 ? 0 : 1);
                preload = preset == 1;
                setting_desiredImmatureDensity = 1500;
                setting_desiredPointDensity = 2000;
                setting_minFrames = 5;
                setting_maxFrames = 7;
                setting_maxOptIterations = 6;
                setting_minOptIterations = 1;

                setting_logStuff = false;
            }

            if (preset == 2 || preset == 3) {
                printf("FAST settings:\n"
                       "- %s real-time enforcing\n"
                       "- 800 active points\n"
                       "- 4-6 active frames\n"
                       "- 1-4 LM iteration each KF\n"
                       "- 424 x 320 image resolution\n", preset == 0 ? "no " : "5x");

                playbackSpeed = (preset == 2 ? 0 : 5);
                preload = preset == 3;
                setting_desiredImmatureDensity = 600;
                setting_desiredPointDensity = 800;
                setting_minFrames = 4;
                setting_maxFrames = 6;
                setting_maxOptIterations = 4;
                setting_minOptIterations = 1;

                benchmarkSetting_width = 424;
                benchmarkSetting_height = 320;

                setting_logStuff = false;
            }

            printf("==============================================\n");
        }



        void VO_Pipeline_dataset::launch_VO_Dataset() {

            reader = new ImageFolderReader(source, calib, gammaCalib, vignette);
            reader->setGlobalCalibration();


            if (setting_photometricCalibration > 0 && reader->getPhotometricGamma() == 0) {
                printf("ERROR: dont't have photometric calibation. Need to use commandline options mode=1 or mode=2 ");
                exit(1);
            }


            int lstart = start;
            int lend = end;
            int linc = 1;
            if (reverse) {
                printf("REVERSE!!!!");
                lstart = end - 1;
                if (lstart >= reader->getNumImages())
                    lstart = reader->getNumImages() - 1;
                lend = start;
                linc = -1;
            }


            fullSystem = new FullSystem();
            fullSystem->setGammaFunction(reader->getPhotometricGamma());
            fullSystem->linearizeOperation = (playbackSpeed == 0);


            IOWrap::PangolinDSOViewer *viewer = 0;
            if (!disableAllDisplay) {
                viewer = new IOWrap::PangolinDSOViewer(wG[0], hG[0], false);
                fullSystem->outputWrapper.push_back(viewer);
            }


            if (useSampleOutput)
                fullSystem->outputWrapper.push_back(new IOWrap::SampleOutputWrapper());



            // to make MacOS happy: run this in dedicated thread -- and use this one to run the GUI.
            // change to boost
            boost::thread runthread([&]() {
                std::vector<int> idsToPlay;
                std::vector<double> timesToPlayAt;
                for (int i = lstart; i >= 0 && i < reader->getNumImages() && linc * i < linc * lend; i += linc) {
                    idsToPlay.push_back(i);
                    if (timesToPlayAt.size() == 0) {
                        timesToPlayAt.push_back((double) 0);
                    } else {
                        double tsThis = reader->getTimestamp(idsToPlay[idsToPlay.size() - 1]);
                        double tsPrev = reader->getTimestamp(idsToPlay[idsToPlay.size() - 2]);
                        timesToPlayAt.push_back(timesToPlayAt.back() + fabs(tsThis - tsPrev) / playbackSpeed);
                    }
                }


                std::vector<ImageAndExposure *> preloadedImages;
                if (preload) {
                    printf("LOADING ALL IMAGES!\n");
                    for (int ii = 0; ii < (int) idsToPlay.size(); ii++) {
                        int i = idsToPlay[ii];
                        preloadedImages.push_back(reader->getImage(i));
                    }
                }

                struct timeval tv_start;
                gettimeofday(&tv_start, NULL);
                clock_t started = clock();
                double sInitializerOffset = 0;


                for (int ii = 0; ii < (int) idsToPlay.size(); ii++) {
                    if (!fullSystem->initialized)    // if not initialized: reset start time.
                    {
                        gettimeofday(&tv_start, NULL);
                        started = clock();
                        sInitializerOffset = timesToPlayAt[ii];
                    }

                    int i = idsToPlay[ii];


                    ImageAndExposure *img;
                    if (preload)
                        img = preloadedImages[ii];
                    else
                        img = reader->getImage(i);


                    bool skipFrame = false;
                    if (playbackSpeed != 0) {
                        struct timeval tv_now;
                        gettimeofday(&tv_now, NULL);
                        double sSinceStart = sInitializerOffset + ((tv_now.tv_sec - tv_start.tv_sec) +
                                                                   (tv_now.tv_usec - tv_start.tv_usec) /
                                                                   (1000.0f * 1000.0f));

                        if (sSinceStart < timesToPlayAt[ii])
                            usleep((int) ((timesToPlayAt[ii] - sSinceStart) * 1000 * 1000));
                        else if (sSinceStart > timesToPlayAt[ii] + 0.5 + 0.1 * (ii % 2)) {
                            printf("SKIPFRAME %d (play at %f, now it is %f)!\n", ii, timesToPlayAt[ii], sSinceStart);
                            skipFrame = true;
                        }
                    }


                    if (!skipFrame) fullSystem->addActiveFrame(img, i);


                    delete img;

                    if (fullSystem->initFailed || setting_fullResetRequested) {
                        if (ii < 250 || setting_fullResetRequested) {
                            printf("RESETTING!\n");

                            std::vector<IOWrap::Output3DWrapper *> wraps = fullSystem->outputWrapper;
                            delete fullSystem;

                            for (IOWrap::Output3DWrapper *ow : wraps) ow->reset();

                            fullSystem = new FullSystem();
                            fullSystem->setGammaFunction(reader->getPhotometricGamma());
                            fullSystem->linearizeOperation = (playbackSpeed == 0);


                            fullSystem->outputWrapper = wraps;

                            setting_fullResetRequested = false;
                        }
                    }

                    if (fullSystem->isLost) {
                        printf("LOST!!\n");
                        break;
                    }

                }
                fullSystem->blockUntilMappingIsFinished();
                clock_t ended = clock();
                struct timeval tv_end;
                gettimeofday(&tv_end, NULL);


                fullSystem->printResult("result.txt");


                int numFramesProcessed = abs(idsToPlay[0] - idsToPlay.back());
                double numSecondsProcessed = fabs(
                        reader->getTimestamp(idsToPlay[0]) - reader->getTimestamp(idsToPlay.back()));
                double MilliSecondsTakenSingle = 1000.0f * (ended - started) / (float) (CLOCKS_PER_SEC);
                double MilliSecondsTakenMT = sInitializerOffset + ((tv_end.tv_sec - tv_start.tv_sec) * 1000.0f +
                                                                   (tv_end.tv_usec - tv_start.tv_usec) / 1000.0f);
                printf("\n======================"
                       "\n%d Frames (%.1f fps)"
                       "\n%.2fms per frame (single core); "
                       "\n%.2fms per frame (multi core); "
                       "\n%.3fx (single core); "
                       "\n%.3fx (multi core); "
                       "\n======================\n\n",
                       numFramesProcessed, numFramesProcessed / numSecondsProcessed,
                       MilliSecondsTakenSingle / numFramesProcessed,
                       MilliSecondsTakenMT / (float) numFramesProcessed,
                       1000 / (MilliSecondsTakenSingle / numSecondsProcessed),
                       1000 / (MilliSecondsTakenMT / numSecondsProcessed));
                //fullSystem->printFrameLifetimes();
                if (setting_logStuff) {
                    std::ofstream tmlog;
                    tmlog.open("logs/time.txt", std::ios::trunc | std::ios::out);
                    tmlog << 1000.0f * (ended - started) / (float) (CLOCKS_PER_SEC * reader->getNumImages()) << " "
                          << ((tv_end.tv_sec - tv_start.tv_sec) * 1000.0f +
                              (tv_end.tv_usec - tv_start.tv_usec) / 1000.0f) / (float) reader->getNumImages() << "\n";
                    tmlog.flush();
                    tmlog.close();
                }

            });


            if (viewer != 0)
                viewer->run();

            runthread.join();

            for (IOWrap::Output3DWrapper *ow : fullSystem->outputWrapper) {
                ow->join();
                delete ow;
            }

            printf("EXIT NOW!\n");
        }


        VO_Pipeline_dataset::~VO_Pipeline_dataset() {
            printf("DELETE FULLSYSTEM!\n");
            delete fullSystem;

            printf("DELETE READER!\n");
            delete reader;
        }



/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
///                                                               Live system
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/
/******************************************************************************************************************************************/

        VO_Pipeline_Live::VO_Pipeline_Live(Settings *run_settings)
        {

            if (run_settings->sampleoutput == 1)
            {
                useSampleOutput = true;
                printf("USING SAMPLE OUTPUT WRAPPER!\n");
            }

            if (run_settings->debugout_runquiet == 1) {
                setting_debugout_runquiet = true;
                printf("QUIET MODE, I'll shut up!\n");
            }

            if (run_settings->setting_logStuff == 1) {
                setting_logStuff = false;
                printf("DISABLE LOGGING!\n");
            }

            if (run_settings->disableAllDisplay == 1) {
                disableAllDisplay = true;
                printf("NO GUI!\n");
            }

            if (run_settings->multiThreading == 1) {
                multiThreading = false;
                printf("NO MultiThreading!\n");
            }


            calib = run_settings->calib;
            printf("loading calibration from %s!\n", calib.c_str());

            vignetteFile = run_settings->vignette;
            printf("loading vignette from %s!\n", vignetteFile.c_str());


            gammaFile = run_settings->gammaCalib;
            printf("loading gammaCalib from %s!\n", gammaFile.c_str());

            printf("could parse argument !!!!\n");


        }

        void VO_Pipeline_Live::lanchLive(int index) {
            setting_desiredImmatureDensity = 1000;
            setting_desiredPointDensity = 1200;
            setting_minFrames = 5;
            setting_maxFrames = 7;
            setting_maxOptIterations = 4;
            setting_minOptIterations = 1;
            setting_logStuff = false;
            setting_kfGlobalWeight = 1.3;

            printf("MODE WITH CALIBRATION, but without exposure times!\n");
            setting_photometricCalibration = 2;
            setting_affineOptModeA = 0;
            setting_affineOptModeB = 0;

            undistorter = Undistort::getUndistorterForFile(calib, gammaFile, vignetteFile);

            setGlobalCalib(
                    (int) undistorter->getSize()[0],
                    (int) undistorter->getSize()[1],
                    undistorter->getK().cast<float>());


            fullSystem = new FullSystem();
            fullSystem->linearizeOperation = false;

            if (!disableAllDisplay)
                fullSystem->outputWrapper.push_back(new IOWrap::PangolinDSOViewer(
                        (int) undistorter->getSize()[0],
                        (int) undistorter->getSize()[1]));


            if (useSampleOutput)
                fullSystem->outputWrapper.push_back(new IOWrap::SampleOutputWrapper());


            if (undistorter->photometricUndist != 0)
                fullSystem->setGammaFunction(undistorter->photometricUndist->getG());


            // Start openCV cameraStream
            videoStream stream("/dev/video0", true);

            while (true) {

                cv::Mat img = stream.getImage();

                if (setting_fullResetRequested) {
                    std::vector<IOWrap::Output3DWrapper *> wraps = fullSystem->outputWrapper;
                    delete fullSystem;
                    for (IOWrap::Output3DWrapper *ow : wraps) ow->reset();
                    fullSystem = new FullSystem();
                    fullSystem->linearizeOperation = false;
                    fullSystem->outputWrapper = wraps;
                    if (undistorter->photometricUndist != 0)
                        fullSystem->setGammaFunction(undistorter->photometricUndist->getG());
                    setting_fullResetRequested = false;
                }
                MinimalImageB minImg((int) img.cols, (int) img.rows, (unsigned char *) img.data);
                ImageAndExposure *undistImg = undistorter->undistort<unsigned char>(&minImg, 1, 0, 1.0f);
                fullSystem->addActiveFrame(undistImg, frameID);
                frameID++;
                delete undistImg;

                char c = (char) cv::waitKey(25);
                if (c == 27)
                    break;
            }
        }


        VO_Pipeline_Live::~VO_Pipeline_Live() {

            for (IOWrap::Output3DWrapper *ow : fullSystem->outputWrapper) {
                ow->join();
                delete ow;
            }

            delete undistorter;
            delete fullSystem;
        }
    }
}