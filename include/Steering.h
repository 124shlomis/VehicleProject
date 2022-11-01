//
// Created by Shlomi Shitrit on 31/10/2022.
//

#ifndef VEHICLEPROJECT_STEERING_H
#define VEHICLEPROJECT_STEERING_H


class Steering {
public:
    Steering();
    ~Steering();
    void calcSteeringDynamics(float deltaDes);
    float getCurrentDelta() const;
private:
    float* deltaCmdDelayed_= nullptr; // [rad] steering angle
    float delta_ = 0; // [rad] steering angle
    float deltaDdot_ = 0; // [rad/s^2] steering acc
    float deltaDot_ = 0; // [rad/s] steering rate;
    float zeta_; // dumping ratio
    float wn_; // [Hz] natural frequency
    float timeDelay_; // [s] system time delay
    float* delayArray_; // array to contain commands because of delay.
    unsigned int arrayLength_; // array above length
    void calcDelayedCmd(float deltaDes);
    void calcClosedLoopDynamics();
};


#endif //VEHICLEPROJECT_STEERING_H
