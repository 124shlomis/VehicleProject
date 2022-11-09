//
// Created by Shlomi Shitrit on 24/10/2022.
//

#include <cmath>
#include "../include/Vehicle.h"
#include "../include/defines.h"
#include "../include/Path.h"

Vehicle::Vehicle(float x0, float y0, float psi, float v) {
    x_ = x0;
    y_ = y0;
    psi_ = psi;
    v_ = v;
}

float* Vehicle::getPose() const {
    auto* Pose = new float[3];
    Pose[0] = x_;
    Pose[1] = y_;
    Pose[2] = psi_;
    return Pose;
}

void Vehicle::setDelta(float delta) {
    this->Steer.calcSteeringDynamics(delta);
}

float *Vehicle::globalToEgo(float xGlobal, float yGlobal) const {
    auto * xyEgo = new float[2];
    float xTmp = xGlobal - x_; // Translation.
    float yTmp = yGlobal - y_; // Translation.
    float xEgo = cos(psi_) * xTmp + sin(psi_) * yTmp; // Rotation
    float yEgo = -sin(psi_) * xTmp + cos(psi_) * yTmp; // Rotation
    xyEgo[0] = xEgo;
    xyEgo[1] = yEgo;
    return xyEgo;
}

float *Vehicle::egoToGlobal(float xEgo, float yEgo) const {
    auto * xyGlobal = new float[2];
    float xTmp = cos(psi_) * xEgo - sin(psi_) * yEgo; // Rotation
    float yTmp = sin(psi_) * xEgo + cos(psi_) * yEgo; // Rotation
    float xGlobal = x_ + xTmp; // Translation.
    float yGlobal = y_ + yTmp; // Translation.
    xyGlobal[0] = xGlobal;
    xyGlobal[1] = yGlobal;
    return xyGlobal;
}

void Vehicle::setPose(float x, float y, float psi) {
    x_ = x;
    y_ = y;
    psi_ = psi;
}

void Vehicle::calcXKinematics() {
    float xDot = v_ * cos(psi_);
    x_ += xDot * DT;
}

void Vehicle::calcYKinematics() {
    float yDot = v_ * sin(psi_);
    y_ += yDot * DT;
}

void Vehicle::calcPsiKinematics() {
    float psiDot = v_ * tan(Steer.getCurrentDelta()) / wheelBase_;
    psi_ += psiDot * DT;
}

void Vehicle::calcVehicleKinematics() {
    calcXKinematics();
    calcYKinematics();
    calcPsiKinematics();
}

float Vehicle::calcRefDelta(float currentS) const {
    // Calculate Steering angle delta:
    // First Step: get the reference waypoint
    Path AuxPath;
    float refS = currentS + lookAheadDistance_;
    if (refS > AuxPath.getPathLength()){
        refS = AuxPath.getPathLength();
    }
    float* refXY = AuxPath.pathToGlobal(refS,0);
    // Calculate alpha
    float* refXYEgo = globalToEgo(refXY[0], refXY[1]);
    float alpha = atan2(refXYEgo[1], refXYEgo[0]);
    float refDelta = atan(2 * wheelBase_ * sin(alpha) / lookAheadDistance_);
    delete refXY;
    delete refXYEgo;
    return refDelta;
}

float Vehicle::getDelta() {
    return this->Steer.getCurrentDelta();
}
