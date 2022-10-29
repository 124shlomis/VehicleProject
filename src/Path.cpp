//
// Created by Shlomi Shitrit on 25/10/2022.
//

#include "Path.h"
#include <cmath>

Path::Path() { // Path instructor - built from 3 segments: 2 straight lines and a radius.
    ds_ = 1;
    nPoints_ = 10000;
    pathLength_ = ds_ * float(nPoints_ - 1);
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

float *Path::pathToGlobal(float s, float t) const {
    //validity check:
    if (s < 0 || s > pathLength_){
        return nullptr;
    }
    auto* xyGlobal = new float[2];
    float xGlobal;
    float yGlobal;
    // temporary point till s:
    float xTmp;
    float yTmp;
    // direction vector at s:
    float xDir;
    float yDir;

    float indexFloat = s / ds_;
    float flooredIndex = floor(indexFloat);
    if (s == pathLength_){
        xTmp = xGlobalPath_[nPoints_-1];
        yTmp = yGlobalPath_[nPoints_-1];
        xDir = xTmp - xGlobalPath_[nPoints_-2];
        yDir = yTmp - yGlobalPath_[nPoints_-2];
    }
    else if (s == 0){
        xTmp = xGlobalPath_[0];
        yTmp = yGlobalPath_[0];
        xDir = xGlobalPath_[1] - xTmp;
        yDir = yGlobalPath_[1] - yTmp;
    }
    else {
        if ((indexFloat - flooredIndex) == 0) {
            xTmp = xGlobalPath_[int(flooredIndex)];
            yTmp = yGlobalPath_[int(flooredIndex)];
            xDir = xTmp - xGlobalPath_[int(flooredIndex) - 1];
            yDir = yTmp - yGlobalPath_[int(flooredIndex) - 1];
        } else {
            xTmp = (indexFloat - flooredIndex) *
                   (xGlobalPath_[int(flooredIndex) + 1] - xGlobalPath_[int(flooredIndex)]) +
                   xGlobalPath_[int(flooredIndex)];
            yTmp = (indexFloat - flooredIndex) *
                   (yGlobalPath_[int(flooredIndex) + 1] - yGlobalPath_[int(flooredIndex)]) +
                   yGlobalPath_[int(flooredIndex)];
            xDir = xTmp - xGlobalPath_[int(flooredIndex)];
            yDir = yTmp - yGlobalPath_[int(flooredIndex)];
        }
    }
    float xDirNormalized = xDir / hypot(xDir,yDir);
    float yDirNormalized = yDir / hypot(xDir,yDir);
    // find perp vector by cross product with z axis:
    float xPerpDirNormalized = -yDirNormalized;
    float yPerpDirNormalized = xDirNormalized;
    // multiply by t:
    float xPerpDir = xPerpDirNormalized * t;
    float yPerpDir = yPerpDirNormalized * t;
    // calculate global point:
    xGlobal = xTmp + xPerpDir;
    yGlobal = yTmp + yPerpDir;

    xyGlobal[0] = xGlobal;
    xyGlobal[1] = yGlobal;
    return xyGlobal;
}

float *Path::globalToPath(float x, float y) const {
    auto* stPath = new float[2];
    float t;
    float s;
    float distanceToWP;
    // find the minimum distance to find perpendicular point:
    float minDistance = INFINITY;
    float secondMinDistance = INFINITY;
    int minInd = 0;
    int secondMinInd = 0;
    for (int i = 0; i < nPoints_; ++i) {
        distanceToWP = hypot(x - xGlobalPath_[i], y - yGlobalPath_[i]);
        if (distanceToWP <= minDistance){
            minDistance = distanceToWP;
            minInd = i;
        }
    }
    for (int i = 0; i < nPoints_; ++i) {
        distanceToWP = hypot(x - xGlobalPath_[i], y - yGlobalPath_[i]);
        if ((distanceToWP <= secondMinDistance) && (distanceToWP > minDistance )){
            secondMinDistance = distanceToWP;
            secondMinInd = i;
        }
    }
    // TODO: fine interpolation and take care to over edges cases.

    float sDirX = (xGlobalPath_[secondMinInd] - xGlobalPath_[minInd]);
    float sDirY = yGlobalPath_[secondMinInd] - yGlobalPath_[minInd];
    float sDirXNormalized = sDirX / hypot(sDirX,sDirY);
    float sDirYNormalized = sDirY / hypot(sDirX,sDirY);
    float positivePerpDirX = -sDirYNormalized * minDistance;
    float positivePerpDirY = sDirXNormalized * minDistance;
    float distanceToPositive = hypot(x - (xGlobalPath_[minInd] + positivePerpDirX), y - (yGlobalPath_[minInd] + positivePerpDirY));
    float distanceToNegative = hypot(x - (xGlobalPath_[minInd] - positivePerpDirX), y - (yGlobalPath_[minInd] - positivePerpDirY));
    if (distanceToPositive < distanceToNegative){
        t = +minDistance;
    } else{
        t = -minDistance;
    }

    s = ds_ * float(minInd);

    stPath[0] = s;
    stPath[1] = t;
    return stPath;
}
