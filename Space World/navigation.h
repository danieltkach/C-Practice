#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "planet.h"

// Encapsulate the ship's state in a structure.
typedef struct {
    double currentTime;
    Vector3D shipPosition;
    struct {
        char name[64];
        char description[256];
        Vector3D position;
        double arrivalTime;
    } currentLocation;
} ShipState;

// Function prototypes:
void printInfo(ShipState *state);
void printFormulae(void);
double computeHohmannTransferTime(double r1, double r2);
double computePhasingTime(Vector3D current, Vector3D target, double orbitalPeriod);
void hohmannTransferTime(ShipState *state);
void travelSystemExecute(ShipState *state);
void determineLocation(Vector3D pos, double time, ShipState *state);
void updateCurrentLocation(ShipState *state, double arrivalTime);

#endif
