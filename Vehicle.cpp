//
// Created by Shlomi Shitrit on 24/10/2022.
//

#include "Vehicle.h"


Vehicle::Vehicle(float x0, float y0, float theta, float v) {
    x_ = x0;
    y_ = y0;
    theta_ = theta;
    v_ = v;
}

float* Vehicle::getPose() {
    float* Pose = new float[3];
    Pose[0] = x_;
    Pose[1] = y_;
    Pose[2] = theta_;
    return Pose;
}
