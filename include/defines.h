//
// Created by Shlomi Shitrit on 01/11/2022.
//
#include <cmath>
#ifndef VEHICLEPROJECT_DEFINES_H
#define VEHICLEPROJECT_DEFINES_H
    #define DT                 float(0.001) // integration step size;
    #define DELTA_DOT_MAX      float(20 * M_PI/180)
    #define DELTA_DOT_MIN      float(-20 * M_PI/180)
    #define DELTA_MAX          float(45 * M_PI/180)
    #define DELTA_MIN          float(-45 * M_PI/180)
#endif //VEHICLEPROJECT_DEFINES_H
