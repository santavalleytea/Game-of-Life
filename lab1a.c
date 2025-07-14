#include "lifegame.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* number of generations to evolve the world */
#define NUM_GENERATIONS 50

/* this function should set the state of all
   the cells in the next generation and call
   finalize_evolution() to update the current
   state of the world to the next generation */
void next_generation(void);

/* this function should return the state of the cell
   at (x,y) in the next generation, according to the
   rules of Conway's Game of Life (see handout) */
int get_next_state(int x, int y);

/* this function should calculate the number of alive
   neighbors of the cell at (x,y) */
int num_neighbors(int x, int y);

int main(void)
{
	int n;

	initialize_world();

	for (n = 0; n < NUM_GENERATIONS; n++)
		next_generation();

	output_world();

	return 0;
}

void next_generation(void) {
	/* For every cell, set the state in the next
	   generation according to the Game of Life rules */
	
	for (int y = 0; y < get_world_height(); y++) {
		for (int x = 0; x < get_world_width(); x++) {
			int state = get_next_state(x, y);
			set_cell_state(x, y, state);
		}
	}
	
	finalize_evolution(); /* called at end to finalize */
}

int get_next_state(int x, int y) {
	int state = get_cell_state(x,y);
	int neighbor = num_neighbors(x,y);

	if (state == ALIVE) {
		if (neighbor > 3 || neighbor < 2) {
			return DEAD;
		} else {
			return ALIVE;
		}
	} else if (state == DEAD) {
		if (neighbor == 3) {
			return ALIVE;
		} else {
			return DEAD;
		}
	}

	return DEAD;
}

int num_neighbors(int x, int y) {
	int count = 0;
	for (int dx = -1; dx <= 1; dx++) {
		for (int dy = -1; dy <=1; dy++) {
			// skip (x,y) cell since we want the cells around it
			if (dx == 0 && dy == 0) {
				continue;
			}

			if (get_cell_state(x+dx, y+dy) != DEAD) {
				count++;
			}
		}
	}

	return count;
}
