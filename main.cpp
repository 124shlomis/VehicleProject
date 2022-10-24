#include <iostream>

#include "Vehicle.h"
using namespace std;

int main(int argc, char **argv) {
    if (argc != 9){
        cout << "Error number of arguments. please try again" << endl;
        return  -1;
    }
    // Get I.C:
    float x0 = stof(argv[2]);
    float y0 = stof(argv[4]);
    float psi = stof(argv[6]);
    float v = stof(argv[8]);

    cout << "Hello, World!" << argv[1] << endl;

    Vehicle Ford(x0,y0,psi,v);
    float* testPose = Ford.getPose();
    cout << "test getPose method, x = " << testPose[0] << ", y = " << testPose[1] << ", psi = " << testPose[2] <<  endl; // test getPose
    delete testPose;
    Ford.setPose(0,0,3.14/4);
    float* testEgoXY = Ford.globalToEgo(15,15);
    cout << "test globalToEgo method, xEgo = " << testEgoXY[0] << ", yEgo = " << testEgoXY[1]  << endl; // test globalToEgo
    delete testEgoXY;
    return 0;
}
