add_library(BorisBrain_VisualOdometry
        src/Feature.cc
        src/Frame.cc
        src/Point.cc
        src/Setting.cc
        src/Camera.cc
        src/Map.cc

        src/internal/PointHessian.cc
        src/internal/FrameHessian.cc
        src/internal/GlobalCalib.cc
        src/internal/FrameFramePrecalc.cc
        src/internal/Residuals.cc
        src/internal/ImmaturePoint.cc
        src/internal/PR.cc

        src/internal/OptimizationBackend/AccumulatedSCHessian.cc
        src/internal/OptimizationBackend/AccumulatedTopHessian.cc
        src/internal/OptimizationBackend/EnergyFunctional.cc

        src/frontend/CoarseTracker.cc
        src/frontend/CoarseInitializer.cc
        src/frontend/FullSystem.cc
        src/frontend/DSOViewer.cc
        src/frontend/FeatureDetector.cc
        src/frontend/FeatureMatcher.cc
        src/frontend/LoopClosing.cc
        src/frontend/PixelSelector2.cc
        src/frontend/Undistort.cc
        src/frontend/ImageRW_OpenCV.cc
)
target_link_libraries(
        BorisBrain_VisualOdometry
        ${THIRD_PARTY_LIBS}
)