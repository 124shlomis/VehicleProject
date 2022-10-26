//
// Created by Shlomi Shitrit on 25/10/2022.
//

#ifndef VEHICLEPROJECT_PATH_H
#define VEHICLEPROJECT_PATH_H


class Path {
public:
    Path(); // constructor
    ~Path(); // destructor
    float* getPathX() const;
    float* getPathY() const;
    int getPathNumPoints() const;

private:
    float ds_ = 0; // distance between waypoints in meters.
    int nPoints_ = 0; // number of points
    float* xGlobalPath_= nullptr; // x coordinates
    float* yGlobalPath_= nullptr; // x coordinates
};


#endif //VEHICLEPROJECT_PATH_H
