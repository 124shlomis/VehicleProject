#include <iostream>

#include "Vehicle.h"
#include "Path.h"
#include <fstream>

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

    Vehicle Ford(x0,y0,psi,v);
    float* testPose = Ford.getPose();
    cout << "test getPose method, x = " << testPose[0] << ", y = " << testPose[1] << ", psi = " << testPose[2] <<  endl; // test getPose
    delete testPose;
    Ford.setPose(0,0,M_PI/4);
    float* testEgoXY = Ford.globalToEgo(15,15);
    cout << "test globalToEgo method, xEgo = " << testEgoXY[0] << ", yEgo = " << testEgoXY[1]  << endl; // test globalToEgo
    delete testEgoXY;
    Ford.setPose(-1,1,-M_PI/4);
    float* pose = Ford.getPose();
    cout << "test getPose method, xGlobal = " << pose[0] << ", yGlobal = " << pose[1]  << ", psi = " << pose[2] << endl; // test egoToGlobal
    float* testGlobalXY = Ford.egoToGlobal(sqrtf(2),0);
    cout << "test egoToGlobal method, xGlobal = " << testGlobalXY[0] << ", yGlobal = " << testGlobalXY[1]  << endl; // test egoToGlobal
    delete testGlobalXY;
    delete pose;

    Path wayToHeaven;
    float* xyTest = wayToHeaven.pathToGlobal(5000,-10);
    cout << "stToXyTest : " << xyTest[0] << ", " << xyTest[1] << endl;
    delete xyTest;
    float* stTest = wayToHeaven.globalToPath(1,0.5);
    cout << "xyToStTest : " << stTest[0] << ", " << stTest[1] << endl;
    delete stTest;

    return 0;
}
