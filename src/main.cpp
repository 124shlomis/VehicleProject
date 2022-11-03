#include <iostream>
#include <fstream>

#include "../include/Vehicle.h"
#include "../include/Path.h"
#include "../include/defines.h"

using namespace std;

int main(int argc, char **argv) {
    if (argc != 9){
        cout << "Error number of arguments. please try again" << endl;
        return  -1;
    }
    cout << "Simulation Started, Please Wait..." << endl;
    // Get I.C:
    float x0 = stof(argv[2]);
    float y0 = stof(argv[4]);
    float psi = stof(argv[6]);
    float v = stof(argv[8]);

    // Construct relevant classes:
    Vehicle Ford(x0,y0,psi,v);
    Path stateRoute1;
    // Move path to txt file for plot:
    ofstream txtFile;
    txtFile.open("pathPoints.txt");
    auto* startPtrX = stateRoute1.getPathX();
    auto* startPtrY = stateRoute1.getPathY();
    for (int i = 0; i < stateRoute1.getPathNumPoints() ; ++i) {
        txtFile << *startPtrX << " " << *startPtrY << endl;
        startPtrX++;
        startPtrY++;
    }
    txtFile.close();

    double t = 0; // initialize time;
    float* initialST = stateRoute1.globalToPath(x0,y0); // initialize current s coordinate
    float currentS = initialST[0];
    delete initialST;
    float refDelta;
    int writeCounter = 0;
    bool writeToTxtFile = true;
    txtFile.open("VehiclePosition.txt"); // file for vehicle position

    // Main loop:
    while ((t < T_FINAL) && (currentS < stateRoute1.getPathLength()) ){
        float* vehiclePose = Ford.getPose();
        float* currentST = stateRoute1.globalToPath(vehiclePose[0],vehiclePose[1]);
        currentS = currentST[0];
        refDelta = Ford.calcRefDelta(currentS); // calculate steering angle according to pure pursuit algorithm
        Ford.setDelta(refDelta); // steering dynamics
        Ford.calcVehicleKinematics(); // calculate vehicle kinematics

        // write vehicle position to a txt file every 0.1 [s]:
        if (writeCounter > 100){
            writeToTxtFile = true;
        }
        if (writeToTxtFile) {
            txtFile << vehiclePose[0] << " " << vehiclePose[1] << " " << t << endl;
            writeCounter = 0;
            writeToTxtFile = false;
        }
        writeCounter++;

        t += DT; // increase time
        delete vehiclePose; // free allocated memory
        delete currentST;
    }

    // case start simulation over final position:
    if ((currentS >= stateRoute1.getPathLength()) & (t == 0) )  {
        txtFile << x0 << " " << y0 << " " << t << endl;
    }
    txtFile.close();
    cout << "Simulation Finished" << endl;
    return 0;
}
