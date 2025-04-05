#include "navigation.h"
#include "planet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printMenu(void) {
    printf("\n--- Navigation Console ---\n");
    printf("I > Info for current time and space\n");
    printf("P > Display Planet Data\n");
    printf("F > Formulae\n");
    printf("H > Hohmann Transfer Time\n");
    printf("T > TRAVEL SYSTEM\n");
    printf("M > Menu\n");
    printf("0 > Quit\n");
}

int main(void) {
    Planet earth = { "Earth", 1.0, 365.25 };
    Planet mars  = { "Mars", 1.523, 687.0 };
    
    ShipState state;
    state.currentTime = 100.0;
    state.shipPosition = getPlanetPosition(earth, state.currentTime);
    strcpy(state.currentLocation.name, "Earth");
    strcpy(state.currentLocation.description, "Earth: our vibrant blue home planet.");
    state.currentLocation.position = state.shipPosition;
    state.currentLocation.arrivalTime = state.currentTime;
    
    printf("You are on << Mineral-Raider-1 >>\n");
    printInfo(&state);
    
    char choice;
    while (1) {
        printf("System Option ('M' for menu) >> ");
        scanf(" %c", &choice);
        
        if (choice == 'P' || choice == 'p') {
            printf("\nEarth: Orbit Radius = %.3f AU, Orbital Period = %.2f days\n", earth.orbitRadius, earth.orbitalPeriod);
            printf("Mars:  Orbit Radius = %.3f AU, Orbital Period = %.2f days\n", mars.orbitRadius, mars.orbitalPeriod);
        } else if (choice == 'F' || choice == 'f') {
            printFormulae();
        } else if (choice == 'H' || choice == 'h') {
            hohmannTransferTime(&state);
        } else if (choice == 'T' || choice == 't') {
            travelSystemExecute(&state);
        } else if (choice == 'I' || choice == 'i') {
            printInfo(&state);
        } else if (choice == 'M' || choice == 'm') {
            printMenu();
        } else if (choice == '0') {
            printf("Exiting Navigation Console. Safe travels!\n");
            break;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }
    
    return 0;
}
