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


#pragma once

 
#include "EnvProcessing/EP_Utils/globalCalib.h"
#include "vector"
 
#include "EnvProcessing/EP_Utils/NumType.h"
#include <iostream>
#include <fstream>
#include "EnvProcessing/EP_Utils/globalFuncs.h"
#include "EnvProcessing/VisualOdometry/OptimizationBackend/RawResidualJacobian.h"

namespace Boris_Brain {
	namespace dso {

		class PointHessian;

		class FrameHessian;

		class CalibHessian;

		class EFResidual;


		enum ResLocation {
			ACTIVE = 0, LINEARIZED, MARGINALIZED, NONE
		};
		enum ResState {
			IN = 0, OOB, OUTLIER
		};

		struct FullJacRowT {
			Eigen::Vector2f projectedTo[MAX_RES_PER_POINT];
		};

		class PointFrameResidual {
		public:
			EIGEN_MAKE_ALIGNED_OPERATOR_NEW

			EFResidual *efResidual;

			static int instanceCounter;


			ResState state_state;
			double state_energy;
			ResState state_NewState;
			double state_NewEnergy;
			double state_NewEnergyWithOutlier;


			void setState(ResState s) { state_state = s; }


			PointHessian *point;
			FrameHessian *host;
			FrameHessian *target;
			RawResidualJacobian *J;


			bool isNew;

/**
* Copyright 2016 Technical University of Munich and Intel.
* Developed by Jakob Engel
*/

			Eigen::Vector2f projectedTo[MAX_RES_PER_POINT];
			Vec3f centerProjectedTo;

			~PointFrameResidual();

			PointFrameResidual();

			PointFrameResidual(PointHessian *point_, FrameHessian *host_, FrameHessian *target_);

			double linearize(CalibHessian *HCalib);


			void resetOOB() {
				state_NewEnergy = state_energy = 0;
				state_NewState = ResState::OUTLIER;

				setState(ResState::IN);
			};

			void applyRes(bool copyJacobians);

			void debugPlot();

			void printRows(std::vector<VecX> &v, VecX &r, int nFrames, int nPoints, int M, int res);
		};
	}
}