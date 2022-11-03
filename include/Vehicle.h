//
// Created by Shlomi Shitrit on 24/10/2022.
//

#ifndef VEHICLEPROJECT_VEHICLE_H
#define VEHICLEPROJECT_VEHICLE_H


#include "Steering.h"

class Vehicle {
public:
    Vehicle(float x0, float y0, float psi, float v); // constructor
    void setPose(float x,float y, float psi);
    void setDelta(float delta);
    float * getPose() const;
    float * globalToEgo(float xGlobal,float yGlobal) const;
    float * egoToGlobal(float xEgo, float yEgo) const;
    void calcVehicleKinematics();
    float calcRefDelta(float currentS) const;
private:
    float x_=0; // [m]
    float y_=0; // [m]
    float psi_=0; // [rad]
    float v_=0; // [m/s]
    const float wheelBase_= 2.728; // [m]
    Steering Steer;
    float lookAheadDistance_= 20; // [m]
    void calcXKinematics();
    void calcYKinematics();
    void calcPsiKinematics();
};


#endif //VEHICLEPROJECT_VEHICLE_H
