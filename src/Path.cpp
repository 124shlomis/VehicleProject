//
// Created by Shlomi Shitrit on 25/10/2022.
//

#include "Path.h"
#include <cmath>

Path::Path() { // Path instructor - built from 3 segments: 2 straight lines and a radius.
    ds_ = 1;
    nPoints_ = 10000;
    xGlobalPath_ = new float[nPoints_]{0.0};
    yGlobalPath_ = new float[nPoints_]{0.0};
    int firstSegNumPoints = 500;
    float rTurn = 30; // 2nd segment is a radius.
    float dTheta = ds_/rTurn;
    float theta = -float(M_PI)/2 + dTheta;
    int secondSegmentNumPoints = int(M_PI/2 / dTheta);
    int thirdSegmentNumPoints = nPoints_ - secondSegmentNumPoints - firstSegNumPoints;

    for(int i =1; i < firstSegNumPoints; i++){ // First segment - straight line.
        xGlobalPath_[i] = xGlobalPath_[i-1] + ds_;
    }

    for (int i = firstSegNumPoints; i < firstSegNumPoints + secondSegmentNumPoints ; ++i) { // 2nd segment - radius
        xGlobalPath_[i] = xGlobalPath_[firstSegNumPoints-1] + rTurn * cos(theta);
        yGlobalPath_[i+1] = rTurn + rTurn * sin(theta);
        theta += dTheta;
    }

    for (int i = nPoints_ - thirdSegmentNumPoints; i < nPoints_ ; ++i) {
        xGlobalPath_[i] = xGlobalPath_[i-1];
        yGlobalPath_[i] = yGlobalPath_[i-1] + ds_;
    }

}

Path::~Path() {
    delete xGlobalPath_;
    delete yGlobalPath_;
}

float *Path::getPathX() const {
    return xGlobalPath_;
}

float *Path::getPathY() const {
    return yGlobalPath_;
}

int Path::getPathNumPoints() const {
    return nPoints_;
}
