#include <iostream>

#include "Vehicle.h"
using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    Vehicle Ford(0,0,0,0);
    float* testPose = Ford.getPose();
    cout << "test, x = " << testPose[0] << ", y = " << testPose[1] << ", theta = " << testPose[2] <<  endl;
    delete testPose;
    return 0;
}
