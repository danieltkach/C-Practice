#include <stdio.h>
#include <stdbool.h>

#define NUM_REGIONS 13
#define MAX_COLORS 4

int colors[NUM_REGIONS] = {0};
int* map[NUM_REGIONS];
int map_sizes[NUM_REGIONS];

bool isSafe(int region, int colorToTry)
{
	for (int i=0; i<map_sizes[region]; i++)
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

	for (int color=0; color<MAX_COLORS; color++)
	{
		if (isSafe(region, color))
			colors[region] = color;

		if (colorMap(region + 1))
			return true;

		colors[region] = 0;
	}

	return false;
}

void printColors()
{
	printf("\nColoring Results\n");
	for (int i=0; i<NUM_REGIONS; i++)
	{
		printf("Region: %d  Color: %d\n", i, colors[i]);
	}
}

int main(void)
{
	if (colorMap(0))
		printColors();
	else
		printf("No solution found using %d colors.\n", MAX_COLORS);
		
	return 0;
}
