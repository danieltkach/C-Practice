#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.141592653589793

// Structure to store a point or vector in 3D space.
typedef struct {
    double x;
    double y;
    double z;
} Vector3D;

// Structure to store planetary data.
typedef struct {
    char name[32];
    double orbitRadius;    // in Astronomical Units (AU)
    double orbitalPeriod;  // in days
} Planet;

// Function to calculate a planet's position assuming a circular orbit in the ecliptic plane.
// 'time' is in days from a reference point.
Vector3D getPlanetPosition(Planet planet, double time) {
    double angle = 2 * PI * (time / planet.orbitalPeriod);
    Vector3D pos;
    pos.x = planet.orbitRadius * cos(angle);
    pos.y = planet.orbitRadius * sin(angle);
    pos.z = 0.0; // 2D approximation: movement in the ecliptic plane only.
    return pos;
}

// Function to compute the distance between two 3D points.
double calculateDistance(Vector3D a, Vector3D b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2));
}

// Function to compute the Hohmann transfer time between two circular orbits.
// Uses a simplified form of Kepler's third law.
// The result is in days.
double computeHohmannTransferTime(double r1, double r2) {
    double a_transfer = (r1 + r2) / 2.0;         // Semi-major axis of the transfer orbit.
    double period_transfer = 365.25 * pow(a_transfer, 1.5);  // Full period (Earth's period as reference).
    return period_transfer / 2.0;                // Travel time is half the orbital period.
}

// Function to check the player's calculated coordinates against the target position.
int checkNavigation(Vector3D playerInput, Vector3D targetPosition) {
    double error = calculateDistance(playerInput, targetPosition);
    const double tolerance = 0.05; // Tolerance in AU.
    
    if (error <= tolerance) {
         printf("Correct! You have set the proper trajectory.\n");
         return 1;
    } else {
         printf("Incorrect trajectory: error = %.4lf AU. Adjust your calculations.\n", error);
         return 0;
    }
}

// Function to print an ephemeris table for a planet over a specified time range.
void printEphemeris(Planet planet, double startTime, double endTime, double interval) {
    printf("\nEphemeris for %s:\n", planet.name);
    printf("Time (days)    x (AU)      y (AU)\n");
    for (double t = startTime; t <= endTime; t += interval) {
        Vector3D pos = getPlanetPosition(planet, t);
        printf("%8.2f    %8.4f    %8.4f\n", t, pos.x, pos.y);
    }
    printf("\n");
}

int main(void) {
    // Define Earth's and Mars' orbital parameters.
    Planet earth = { "Earth", 1.0, 365.25 };
    Planet mars  = { "Mars", 1.523, 687.0 };
    
    // Starting condition: the ship is at Earth's position at departure time.
    double departureTime = 100.0; // in days from the reference epoch.
    Vector3D shipPosition = getPlanetPosition(earth, departureTime);
    
    // Display initial mission briefing.
    printf("At departure time = %.2f days, Earth's space station position is:\n", departureTime);
    printf("  x = %.4f AU\n  y = %.4f AU\n", shipPosition.x, shipPosition.y);
    
    // Interactive Menu Loop.
    char choice;
    while (1) {
        printf("\n--- Navigation Console ---\n");
        printf("P > Display Planet Data\n");
        printf("F > Planet Position Formulae\n");
        printf("H > Compute Hohmann Transfer Time\n");
        printf("T > TRAVEL SYSTEM\n");
        printf("I > Info for current time and space\n");
        printf("0 > Quit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        
        if (choice == 'P' || choice == 'p') {
            printf("\nEarth: Orbit Radius = %.3f AU, Orbital Period = %.2f days\n", earth.orbitRadius, earth.orbitalPeriod);
            printf("Mars:  Orbit Radius = %.3f AU, Orbital Period = %.2f days\n", mars.orbitRadius, mars.orbitalPeriod);
        
        } else if (choice == 'F' || choice == 'f') {
            printf("\nANGLE = 2 * PI * (time / planet.orbitalPeriod)\n");
            printf("X = planet.orbitRadius * cos(ANGLE)\n");
            printf("Y = planet.orbitRadius * sin(ANGLE)\n");
            printf("Z = 0.0 (2D approximation: movement in the ecliptic plane only)\n");
            
        } else if (choice == 'H' || choice == 'h') {
            double playerOrbitRadius;
            double destinationOrbitRadius;
            printf("\nYour orbit radius (AU): ");
            scanf("%lf", &playerOrbitRadius);
            printf("Destination orbit radius (AU): ");
            scanf("%lf", &destinationOrbitRadius);
            double transferTime = computeHohmannTransferTime(playerOrbitRadius, destinationOrbitRadius);
            printf("Calculated Hohmann transfer time: %.2f days\n", transferTime);
        
        } else if (choice == 'T' || choice == 't') {
            // TRAVEL SYSTEM: Let the player input their calculated trajectory.
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
            
            // Compute target Mars position based on arrival time.
            Vector3D targetMarsPos = getPlanetPosition(mars, arrivalTime);
            // Check player's input against the target.
            int result = checkNavigation(playerCalculated, targetMarsPos);
            
            // Update ship's position and time.
            shipPosition = playerCalculated;
            departureTime = arrivalTime;
            if(result) {
                printf("Your ship has successfully arrived at the intended destination.\n");
            } else {
                printf("Your ship landed off-course. Adjust your trajectory and try again.\n");
            }
            
        } else if (choice == 'I' || choice == 'i') {
            double distanceFromSun = sqrt(shipPosition.x * shipPosition.x + shipPosition.y * shipPosition.y);
            printf("\n--- Current Space Info ---\n");
            printf("Current Time (departure time): %.2f days\n", departureTime);
            printf("Current Ship Position:\n");
            printf("  x = %.4f AU\n  y = %.4f AU\n  z = %.4f AU\n", shipPosition.x, shipPosition.y, shipPosition.z);
            printf("Distance from the Sun: %.4f AU\n", distanceFromSun);
            
        } else if (choice == '0') {
            printf("Exiting Navigation Console. Safe travels!\n");
            break;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }
    
    return 0;
}
