#pragma once
#include <iostream>

#define LOGV(x) std::cout << #x << ": " << x << std::endl;
#define LOGS(x) std::cout << x << std::endl;

static float Normalize(float val, float min, float max)
{ 
	return (val - min) / (max - min);
}

static double RandomRange(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    range = min + (rand() / div);
	//LOGV(range)
    return range;
}
