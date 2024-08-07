#ifndef AF_RANDOM_H
#define AF_RANDOM_H

#include <stdlib.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
====================
AF_RANDOM_INIT
Initialise the random engine from the standard lib
====================
*/
static inline void AF_RANDOM_INIT(){
	// seed the random runmber generatorwith the current time.
	srand(time(NULL));
}

/*
====================
AF_RANDOM_RANGE
Random range that takes in min and max floats and produces return float 
====================
*/
static inline float AF_RANDOM_RANGE(float _min, float _max){

	// Generate the random number from randge
	float randomNum = _min + (float)rand() / ((float)RAND_MAX / (_max - _min));
	return randomNum;
}

#ifdef __cplusplus
}
#endif

#endif //AF_RANDOM_H
