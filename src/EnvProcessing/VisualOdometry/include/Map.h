#pragma once
#ifndef LDSO_MAP_H_
#define LDSO_MAP_H_

#include "NumTypes.h"
#include "Frame.h"
#include "Point.h"
#include "internal/CalibHessian.h"

#include <set>
#include <thread>
#include <mutex>

using namespace std;
using namespace Boris_Brain::ldso::internal;
namespace Boris_Brain {
    namespace ldso {

        class FullSystem;

        /**
         * The global map contains all keyframes and map points, even if they are marginalized or outdated.
         * The map can be saved to and loaded from disk, if you wanna reuse it.
         *
         * The loop closing thread will call the optimize function if there is a consistent loop closure.
         */

        class Map {
        public:
            Map(FullSystem *fs) : fullsystem(fs) {}

            /**
             * add a keyframe into the global map
             * @param kf
             */
            void AddKeyFrame(shared_ptr<Frame> kf);

            /**
             * optimize pose graph of all kfs
             * this will start the pose graph optimization thread (usually takes several seconds to return in my machine)
             * @param allKFs
             * @return true if pose graph thread is started
             */
            bool OptimizeALLKFs();

            /**
             * get number of frames stored in global map
             * @return
             */
            inline int NumFrames() const {
                return frames.size();
            }

            // is pose graph running?
            bool Idle() {
                unique_lock<mutex> lock(mutexPoseGraph);
                return !poseGraphRunning;
            }

            set<shared_ptr<Frame>, CmpFrameID> GetAllKFs() { return frames; }

        private:
            // the pose graph optimization thread
            void runPoseGraphOptimization();

            mutex mapMutex; // map mutex to protect its data
            set<shared_ptr<Frame>, CmpFrameID> frames;      // all KFs by ID
            set<shared_ptr<Frame>, CmpFrameID> framesOpti;  // KFs to be optimized
            shared_ptr<Frame> currentKF = nullptr;

            bool poseGraphRunning = false;  // is pose graph running?
            mutex mutexPoseGraph;

            FullSystem *fullsystem = nullptr;
        };
    }
}
#endif // LDSO_MAP_H_
