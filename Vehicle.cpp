//
// Created by Shlomi Shitrit on 24/10/2022.
//

#include <cmath>
#include "Vehicle.h"


Vehicle::Vehicle(float x0, float y0, float psi, float v) {
    x_ = x0;
    y_ = y0;
    psi_ = psi;
    v_ = v;
    psiDot_ = 0;
    delta_ = 0;
}

float* Vehicle::getPose() const {
    auto* Pose = new float[3];
    Pose[0] = x_;
    Pose[1] = y_;
    Pose[2] = psi_;
    return Pose;
}

void Vehicle::setDelta(float delta) {
    delta_ = delta;
}

float *Vehicle::globalToEgo(float xGlobal, float yGlobal) const {
    auto * xyEgo = new float[2];
    float xEgo = 0;
    float yEgo = 0;
    float xTmp = xGlobal - x_; // Translation.
    float yTmp = yGlobal - y_; // Translation.
    xEgo = cos(psi_) * xTmp + sin(psi_) * yTmp; // Rotation
    yEgo = -sin(psi_) * xTmp + cos(psi_) * yTmp; // Rotation
    xyEgo[0] = xEgo;
    xyEgo[1] = yEgo;
    return xyEgo;
}

void Vehicle::setPose(float x, float y, float psi) {
    x_ = x;
    y_ = y;
    psi_ = psi;
}
