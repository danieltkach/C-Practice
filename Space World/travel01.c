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
double computeHohmannTransferTime(double r1, double r2) {
    double a_transfer = (r1 + r2) / 2.0;         // Semi-major axis of the transfer orbit.
    double period_transfer = 365.25 * pow(a_transfer, 1.5);  // Full period of the transfer orbit (Earth's period as reference).
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
    
    // Assume the space station is at Earth's position at departure time.
    double departureTime = 100.0; // in days from the reference.
    Vector3D earthPos = getPlanetPosition(earth, departureTime);
    printf("At departure time = %.2f days, Earth's space station position is:\n", departureTime);
    printf("  x = %.4f AU, y = %.4f AU\n", earthPos.x, earthPos.y);
    
    // Interactive Menu Loop.
    int choice = 0;
    while (1) {
        printf("\n--- Navigation Console ---\n");
        printf("1. Display Planet Data\n");
        printf("2. Planet Position Formulae\n");
        printf("3. Compute Hohmann Transfer Time\n");
        printf("4. Enter Your Calculated Arrival Coordinates\n");
        printf("5. Departure Time\n");
        // printf("9. Show Ephemeris Table for Mars\n");
        printf("0. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        // Display planet information.
        if (choice == 1) {
            printf("\nEarth: Orbit Radius = %.3f AU, Orbital Period = %.2f days\n", earth.orbitRadius, earth.orbitalPeriod);
            printf("Mars:  Orbit Radius = %.3f AU, Orbital Period = %.2f days\n", mars.orbitRadius, mars.orbitalPeriod);
        
        // Planet Position Formulae
        } else if (choice == 2) {
          printf("angle = 2 * PI * (time / planet.orbitalPeriod)\n");
          printf("X = planet.orbitRadius * cos(angle)");
          printf("Y = planet.orbitRadius * sin(angle)");
          printf("0.0 (2D approximation: movement in the ecliptic plane only");
        
        // Show an ephemeris table.
        } else if (choice == 9) {
            double start, end, interval;
            printf("Enter start time (in days) for the ephemeris table: ");
            scanf("%lf", &start);
            printf("Enter end time (in days) for the ephemeris table: ");
            scanf("%lf", &end);
            printf("Enter time interval (in days): ");
            scanf("%lf", &interval);
            printEphemeris(mars, start, end, interval);
            
        // Compute Hohmann Transfer Time
        } else if (choice == 3) {
          double playerOrbitRadius;
          double destinationOrbitRadius;
          printf("\nYour orbit radius (AU): ");
          scanf("%lf", &playerOrbitRadius);
          printf("Destination orbit radius (AU): ");
          scanf("%lf", &destinationOrbitRadius);
          double transferTime = computeHohmannTransferTime(playerOrbitRadius, destinationOrbitRadius);
          printf("Calculated Hohmann transfer time: %.2f days\n", transferTime);

        // Let the player input their calculated arrival coordinates.
        } else if (choice == 4) {
            Vector3D playerCalculated;
            printf("\nCalculated X coordinate: ");
            scanf("%lf", &playerCalculated.x);
            printf("Calculated Y coordinate: ");
            scanf("%lf", &playerCalculated.y);
            playerCalculated.z = 0.0;

            double arrivalTime;
            printf("Arrival time: ");
            scanf("%lf", &arrivalTime);
            
            Vector3D targetMarsPos = getPlanetPosition(mars, arrivalTime);
            checkNavigation(playerCalculated, targetMarsPos);
       
        // Departure (Current) Time.
        } else if (choice == 5) {
          printf("Departure Time (current time): %.2f\n", departureTime);

        // Exit
        } else if (choice == 0) {
            printf("Exiting Navigation Console. Safe travels!\n");
            break;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }
    
    return 0;
}
