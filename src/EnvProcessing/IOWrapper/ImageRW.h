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
#include "utils/NumType.h"
#include "utils/MinimalImage.h"

namespace dso
{
namespace IOWrap
{

MinimalImageB* readImageBW_8U(std::string filename);
MinimalImageB3* readImageRGB_8U(std::string filename);
MinimalImage<unsigned short>* readImageBW_16U(std::string filename);


MinimalImageB* readStreamBW_8U(char* data, int numBytes);

void writeImage(std::string filename, MinimalImageB* img);
void writeImage(std::string filename, MinimalImageB3* img);
void writeImage(std::string filename, MinimalImageF* img);
void writeImage(std::string filename, MinimalImageF3* img);

}
}
