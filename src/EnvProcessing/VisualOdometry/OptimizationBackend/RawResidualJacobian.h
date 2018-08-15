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


#pragma once

 
#include "EnvProcessing/EP_Utils/NumType.h"

namespace Boris_Brain {
	namespace dso {

		struct RawResidualJacobian {
			EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
			// ================== new structure: save independently =============.
			VecNRf resF;

			// the two rows of d[x,y]/d[xi].
			Vec6f Jpdxi[2];            // 2x6

			// the two rows of d[x,y]/d[C].
			VecCf Jpdc[2];            // 2x4

			// the two rows of d[x,y]/d[idepth].
			Vec2f Jpdd;                // 2x1

			// the two columns of d[r]/d[x,y].
			VecNRf JIdx[2];            // 9x2

			// = the two columns of d[r] / d[ab]
			VecNRf JabF[2];            // 9x2


			// = JIdx^T * JIdx (inner product). Only as a shorthand.
			Mat22f JIdx2;                // 2x2
			// = Jab^T * JIdx (inner product). Only as a shorthand.
			Mat22f JabJIdx;            // 2x2
			// = Jab^T * Jab (inner product). Only as a shorthand.
			Mat22f Jab2;            // 2x2

		};
	}
}