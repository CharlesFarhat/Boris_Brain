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

#include "utils/NumType.h"
#include "algorithm"

namespace dso
{


class FrameShell
{
public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
	int id; 			// INTERNAL ID, starting at zero.
	int incoming_id;	// ID passed into DSO
	double timestamp;		// timestamp passed into DSO.

	// set once after tracking
	SE3 camToTrackingRef;
	FrameShell* trackingRef;

	// constantly adapted.
	SE3 camToWorld;				// Write: TRACKING, while frame is still fresh; MAPPING: only when locked [shellPoseMutex].
	AffLight aff_g2l;
	bool poseValid;

	// statisitcs
	int statistics_outlierResOnThis;
	int statistics_goodResOnThis;
	int marginalizedAt;
	double movedByOpt;


	inline FrameShell()
	{
		id=0;
		poseValid=true;
		camToWorld = SE3();
		timestamp=0;
		marginalizedAt=-1;
		movedByOpt=0;
		statistics_outlierResOnThis=statistics_goodResOnThis=0;
		trackingRef=0;
		camToTrackingRef = SE3();
	}
};


}

