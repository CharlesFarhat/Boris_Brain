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
* Copyright 2016 Technical University of Munich and Intel.
* Developed by Jakob Engel
*/


#pragma once
 
#include "utils/NumType.h"

namespace Boris_Brain {
	namespace dso {

		enum PixelSelectorStatus {
			PIXSEL_VOID = 0, PIXSEL_1, PIXSEL_2, PIXSEL_3
		};


		class FrameHessian;

		class PixelSelector {
		public:
			EIGEN_MAKE_ALIGNED_OPERATOR_NEW;

			int makeMaps(
					const FrameHessian *const fh,
					float *map_out, float density, int recursionsLeft = 1, bool plot = false, float thFactor = 1);

			PixelSelector(int w, int h);

			~PixelSelector();

			int currentPotential;


			bool allowFast;

			void makeHists(const FrameHessian *const fh);

		private:

			Eigen::Vector3i select(const FrameHessian *const fh,
								   float *map_out, int pot, float thFactor = 1);


			unsigned char *randomPattern;


			int *gradHist;
			float *ths;
			float *thsSmoothed;
			int thsStep;
			const FrameHessian *gradHistFrame;
		};
	}
}
