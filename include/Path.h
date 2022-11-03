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
    float getPathLength() const;
    float* pathToGlobal(float s, float t) const;
    float* globalToPath(float x, float y) const;

private:
    float ds_ = 0; // distance between waypoints in meters.
    int nPoints_ = 0; // number of points
    float pathLength_ = 0; // path length
    float* xGlobalPath_; // x coordinates
    float* yGlobalPath_; // y coordinates
};


#endif //VEHICLEPROJECT_PATH_H
