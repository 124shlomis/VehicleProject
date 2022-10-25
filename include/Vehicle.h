//
// Created by Shlomi Shitrit on 24/10/2022.
//

#ifndef VEHICLEPROJECT_VEHICLE_H
#define VEHICLEPROJECT_VEHICLE_H


class Vehicle {
public:
    Vehicle(float x0, float y0, float psi, float v); // constructor
    void setPose(float x,float y, float psi);
    void setDelta(float delta);
    float * getPose() const;
    float * globalToEgo(float xGlobal,float yGlobal) const;
private:
    float x_=0;
    float y_=0;
    float psi_=0;
    float v_=0;
    float psiDot_=0;
    float delta_=0;
};


#endif //VEHICLEPROJECT_VEHICLE_H
