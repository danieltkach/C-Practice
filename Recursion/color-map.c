#include <stdio.h>
#include <stdbool.h>

#define NUM_REGIONS 13
#define MAX_COLORS 4

int colors[NUM_REGIONS] = {0};
int *map[NUM_REGIONS];
int map_sizes[NUM_REGIONS];

bool isSafe(int region, int colorToTry)
{
  for (int i = 0; i < map_sizes[region]; i++)
  {
    int neighbor = map[region][i];
    if (colors[neighbor] == colorToTry)
      return false;
  }
  return true;
}

bool colorMap(int region)
{
  if (region == NUM_REGIONS)
    return true;

  for (int color = 1; color <= MAX_COLORS; color++)
  {
    if (isSafe(region, color))
    {
      colors[region] = color;
      if (colorMap(region + 1))
        return true;

      colors[region] = 0;
    }
  }

  return false;
}

void printColors()
{
  printf("\nColoring Results\n");
  for (int i = 0; i < NUM_REGIONS; i++)
  {
    printf("Region: %d  Color: %d\n", i, colors[i]);
  }
}

void printRegionColored(int color);

void printAsciiMap() {
  printf("\n\033[1mASCII Map (Color-coded)\033[0m\n\n");

  // Helper macro to print a colored box
  #define PRINT_REGION(ID) printRegionColored(colors[ID])

  // Print layout
  printf("      "); PRINT_REGION(0); printf(" "); PRINT_REGION(1); printf(" "); PRINT_REGION(2); printf("\n");
  printf("      "); PRINT_REGION(3); printf(" "); PRINT_REGION(4); printf(" "); PRINT_REGION(5); printf("\n");
  printf("      "); PRINT_REGION(6); printf(" "); PRINT_REGION(7); printf(" "); PRINT_REGION(8); printf("\n");
  printf("      "); PRINT_REGION(9); printf(" "); PRINT_REGION(10); printf(" "); PRINT_REGION(11); printf("\n");
  printf("          "); PRINT_REGION(12); printf("\n");

  #undef PRINT_REGION
}

// Helper to print colored region box
void printRegionColored(int color) {
  if (color < 1 || color > 4) {
      printf("[ ]");
      return;
  }

  // ANSI color codes: 31=red, 32=green, 33=yellow, 34=blue
  int ansi_color = 30 + color;
  printf("\033[%dm[%d]\033[0m", ansi_color, color);
}

int main(void)
{
  static int neighbors_0[] = {1, 2, 3, 9, 12};
  static int neighbors_1[] = {0, 2, 5};
  static int neighbors_2[] = {0, 1, 3, 4, 5};
  static int neighbors_3[] = {0, 2, 4, 6, 8, 9};
  static int neighbors_4[] = {2, 3, 5, 6, 7, 8};
  static int neighbors_5[] = {1, 2, 8, 11};
  static int neighbors_6[] = {3, 4, 7, 8};
  static int neighbors_7[] = {4, 6, 8};
  static int neighbors_8[] = {3, 5, 6, 7, 9, 10, 11};
  static int neighbors_9[] = {0, 3, 8, 10, 12};
  static int neighbors_10[] = {8, 9, 11, 12};
  static int neighbors_11[] = {5, 8, 10, 12};
  static int neighbors_12[] = {0, 9, 10, 11};

  map[0] = neighbors_0;
  map_sizes[0] = 5;
  map[1] = neighbors_1;
  map_sizes[1] = 3;
  map[2] = neighbors_2;
  map_sizes[2] = 5;
  map[3] = neighbors_3;
  map_sizes[3] = 6;
  map[4] = neighbors_4;
  map_sizes[4] = 6;
  map[5] = neighbors_5;
  map_sizes[5] = 4;
  map[6] = neighbors_6;
  map_sizes[6] = 4;
  map[7] = neighbors_7;
  map_sizes[7] = 3;
  map[8] = neighbors_8;
  map_sizes[8] = 7;
  map[9] = neighbors_9;
  map_sizes[9] = 5;
  map[10] = neighbors_10;
  map_sizes[10] = 4;
  map[11] = neighbors_11;
  map_sizes[11] = 4;
  map[12] = neighbors_12;
  map_sizes[12] = 4;

  if (colorMap(0))
  {
    printColors();
    printAsciiMap();
  }
  else
    printf("No solution found using %d colors.\n", MAX_COLORS);

  return 0;
}
