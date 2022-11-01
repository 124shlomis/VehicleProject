//
// Created by Shlomi Shitrit on 31/10/2022.
//

#include "Steering.h"
#include "defines.h"

Steering::Steering() {
    timeDelay_ = 0.2; // [s]
    arrayLength_ = (unsigned int)(timeDelay_ / DT)+2;
    delayArray_ = new float [arrayLength_];
    for (int i = 0; i < arrayLength_ ; ++i) {
        delayArray_[i] = 0;
    }
    deltaCmdDelayed_ = &delayArray_[1]; // pointer to the first element in array
    zeta_ = 1;
    wn_ = 2 * M_PI * 10; // [rad]
}

Steering::~Steering() {
    delete delayArray_;
}

void Steering::calcDelayedCmd(float deltaDes) {
    for (int i = 0; i < arrayLength_; ++i) {
        delayArray_[i] = delayArray_[i+1];
    }
    delayArray_[arrayLength_-1] = deltaDes;
}

void Steering::calcSteeringDynamics(float deltaDes) {
    calcDelayedCmd(deltaDes);
    calcClosedLoopDynamics();
}

float Steering::getCurrentDelta() const {
    return delta_;
}

void Steering::calcClosedLoopDynamics(){
    deltaDdot_ = -2 * zeta_ * wn_ * deltaDot_ - (wn_ * wn_) * delta_ + (wn_ * wn_) * (*deltaCmdDelayed_);
    deltaDot_ += deltaDdot_ * DT;
    if (deltaDot_ > DELTA_DOT_MAX){
        deltaDot_ = DELTA_DOT_MAX;
    } else if (deltaDot_ < DELTA_DOT_MIN) {
        deltaDot_ = DELTA_DOT_MIN;
    }
    delta_ += deltaDot_ * DT;
    if (delta_ > DELTA_MAX){
        delta_ = DELTA_MAX;
    } else if (delta_ < DELTA_MIN) {
        delta_ = DELTA_MIN;
    }
}