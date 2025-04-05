#include "navigation.h"
#include "planet.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define THRESHOLD 0.1  // distance tolerance (in AU)
#define PI 3.141592653589793

// Prints the current ship status with custom formatting.
void printInfo(ShipState *state) {
    double distanceFromSun = sqrt(state->shipPosition.x * state->shipPosition.x +
                                  state->shipPosition.y * state->shipPosition.y);
    printf("Space-Time Information:\n");
    printf("-T- Current Time (departure time): %.2f days\n", state->currentTime);
    printf("-P- Current Ship Position:\n");
    printf("  x = %.4f AU\n  y = %.4f AU\n  z = %.4f AU\n",
           state->shipPosition.x, state->shipPosition.y, state->shipPosition.z);
    printf("\n-L- Location data: \n");
    printf("  Distance from the Sun: %.4f AU\n", distanceFromSun);
    printf("  Name: %s\n", state->currentLocation.name);
    printf("  Description: %s\n", state->currentLocation.description);
    printf("\n<-> Oxygen levels: Not available\n");
    printf("@^@ Fuel levels: Not available\n");
    printf("-+- Food levels: Unknown\n");
}

// Prints the orbital formulae.
void printFormulae(void) {
    printf("\nANGLE = 2 * PI * (time / planet.orbitalPeriod)\n");
    printf("X = planet.orbitRadius * cos(ANGLE)\n");
    printf("Y = planet.orbitRadius * sin(ANGLE)\n");
    printf("Z = 0.0 (2D approximation: movement in the ecliptic plane only)\n");
}

// Computes the Hohmann transfer time (in days) between two circular orbits.
// Returns 0 if the orbit radii are (almost) identical.
double computeHohmannTransferTime(double r1, double r2) {
    if (fabs(r1 - r2) < 1e-6)
        return 0.0;
    double a_transfer = (r1 + r2) / 2.0;
    double period_transfer = 365.25 * pow(a_transfer, 1.5);
    return period_transfer / 2.0;
}

// Computes phasing time for same-orbit transfers.
// Calculates the fraction of an orbit (based on angular difference) and returns corresponding time.
double computePhasingTime(Vector3D current, Vector3D target, double orbitalPeriod) {
    double angleCurrent = atan2(current.y, current.x);
    double angleTarget  = atan2(target.y, target.x);
    double dtheta = fabs(angleTarget - angleCurrent);
    if (dtheta > PI)
        dtheta = 2 * PI - dtheta;
    return (dtheta / (2 * PI)) * orbitalPeriod;
}

// Displays either the Hohmann transfer time or phasing time (if same orbit) based on input orbit radii.
void hohmannTransferTime(ShipState *state) {
    double playerOrbitRadius, destinationOrbitRadius;
    printf("\nYour orbit radius (AU): ");
    scanf("%lf", &playerOrbitRadius);
    printf("Destination orbit radius (AU): ");
    scanf("%lf", &destinationOrbitRadius);
    
    if (fabs(playerOrbitRadius - destinationOrbitRadius) < 1e-6) {
        Vector3D target;
        printf("Same orbit detected. Enter the target X coordinate (AU): ");
        scanf("%lf", &target.x);
        printf("Enter the target Y coordinate (AU): ");
        scanf("%lf", &target.y);
        target.z = 0.0;
        double orbitalPeriod = 365.25 * pow(playerOrbitRadius, 1.5);
        double phasingTime = computePhasingTime(state->shipPosition, target, orbitalPeriod);
        printf("Calculated phasing transfer time: %.2f days\n", phasingTime);
    } else {
        double transferTime = computeHohmannTransferTime(playerOrbitRadius, destinationOrbitRadius);
        printf("Calculated Hohmann transfer time: %.2f days\n", transferTime);
    }
}

// TRAVEL SYSTEM: Prompts the player to input their calculated trajectory, then updates the ShipState.
void travelSystemExecute(ShipState *state) {
    Vector3D playerCalculated;
    printf("\nEnter your calculated X coordinate: ");
    scanf("%lf", &playerCalculated.x);
    printf("Enter your calculated Y coordinate: ");
    scanf("%lf", &playerCalculated.y);
    printf("Enter your calculated Z coordinate: ");
    scanf("%lf", &playerCalculated.z);
    double arrivalTime;
    printf("Enter your calculated Arrival Time (in days): ");
    scanf("%lf", &arrivalTime);
    
    state->shipPosition = playerCalculated;
    state->currentTime = arrivalTime;
    updateCurrentLocation(state, arrivalTime);
}

// Determines the current location by comparing ship's position to known positions (Earth and Mars).
void determineLocation(Vector3D pos, double time, ShipState *state) {
    Planet earth = { "Earth", 1.0, 365.25 };
    Planet mars  = { "Mars", 1.523, 687.0 };
    Vector3D earthPos = getPlanetPosition(earth, time);
    Vector3D marsPos  = getPlanetPosition(mars, time);
    
    double dEarth = calculateDistance(pos, earthPos);
    double dMars = calculateDistance(pos, marsPos);
    
    if (dEarth < THRESHOLD) {
         strcpy(state->currentLocation.name, "Earth");
         strcpy(state->currentLocation.description, "Earth: our vibrant blue home planet.");
         state->currentLocation.position = earthPos;
         state->currentLocation.arrivalTime = time;
    } else if (dMars < THRESHOLD) {
         strcpy(state->currentLocation.name, "Mars");
         strcpy(state->currentLocation.description, "Mars: the Red Planet, a potential destination for exploration.");
         state->currentLocation.position = marsPos;
         state->currentLocation.arrivalTime = time;
    } else {
         strcpy(state->currentLocation.name, "Unknown");
         strcpy(state->currentLocation.description, "You have arrived at an unknown celestial location.");
         state->currentLocation.position = pos;
         state->currentLocation.arrivalTime = time;
    }
}

// Updates the current location in the ShipState.
void updateCurrentLocation(ShipState *state, double arrivalTime) {
    state->currentTime = arrivalTime;
    determineLocation(state->shipPosition, state->currentTime, state);
    printf("You have arrived at %s.\n", state->currentLocation.name);
}
