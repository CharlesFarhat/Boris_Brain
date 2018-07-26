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

// Tools used in the system, you will find math background and utilities for reading and undistorted images



#pragma once
#include "utils/settings.h"
#include "utils/NumType.h"

namespace Boris_Brain {

	namespace dso {
		extern int wG[PYR_LEVELS], hG[PYR_LEVELS];
		extern float fxG[PYR_LEVELS], fyG[PYR_LEVELS],
				cxG[PYR_LEVELS], cyG[PYR_LEVELS];

		extern float fxiG[PYR_LEVELS], fyiG[PYR_LEVELS],
				cxiG[PYR_LEVELS], cyiG[PYR_LEVELS];

		extern Eigen::Matrix3f KG[PYR_LEVELS], KiG[PYR_LEVELS];

		extern float wM3G;
		extern float hM3G;

		void setGlobalCalib(int w, int h, const Eigen::Matrix3f &K);
	}
}