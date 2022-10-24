//
// Created by Shlomi Shitrit on 24/10/2022.
//

#ifndef VEHICLEPROJECT_VEHICLE_H
#define VEHICLEPROJECT_VEHICLE_H


class Vehicle {
public:
    Vehicle(float x0, float y0, float theta, float v); // constructor
    float * getPose();

private:
    float x_; //
    float y_;
    float theta_;
    float v_;
    float thetadot_=0;
    float delta_=0;
};


#endif //VEHICLEPROJECT_VEHICLE_H
