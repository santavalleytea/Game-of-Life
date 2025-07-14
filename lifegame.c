#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "lifegame.h"

/* hard-coded world size */
#define WORLDWIDTH 39
#define WORLDHEIGHT 20

/* character representations of cell states */
#define CHAR_ALIVE '*'
#define CHAR_DEAD ' '

/* current cell states of the world */
static int world[WORLDWIDTH][WORLDHEIGHT];

/* next generation cell states */
static int nextstates[WORLDWIDTH][WORLDHEIGHT];

void initialize_world_from_file(const char * filename) {
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		fprintf(stderr, "Error: Could not open file %s\n", filename);
		abort();
	}

	char line[256];
	int y = 0;

	while (fgets(line, sizeof(line), fp) != NULL && y < get_world_height()) {
		for (int x = 0; x < get_world_width(); x++) {
			if (line[x] == CHAR_ALIVE) {
				set_cell_state(x, y, ALIVE);
			} else {
				set_cell_state(x, y, DEAD);
			}
		}

		y++;
	}

	finalize_evolution();
}

void save_world_to_file(const char * filename) {
	FILE* fp = fopen(filename, "w");
	if (fp == NULL) {
		fprintf(stderr, "Error: Could not open file %s\n", filename);
	}

	for (int y = 0; y < get_world_height(); y++) {
		for (int x = 0; x < get_world_width(); x++) {
			int state = get_cell_state(x, y);
			if (state == ALIVE) {
				fputc(CHAR_ALIVE, fp);
			} else {
				fputc(CHAR_DEAD, fp);
			}
		}

		fputc('\n', fp);
	} 

	fclose(fp);
}

/* initializes the world to a hard-coded pattern, and resets
   all the cells in the next generation to DEAD */
void initialize_world(void) {
	int i, j;

	for (i = 0; i < WORLDWIDTH; i++)
		for (j = 0; j < WORLDHEIGHT; j++)
			world[i][j] = nextstates[i][j] = DEAD;
	/* pattern "glider" */
	world[1][2] = ALIVE;
	world[3][1] = ALIVE;
	world[3][2] = ALIVE;
	world[3][3] = ALIVE;
	world[2][3] = ALIVE;
}

int get_world_width(void) {
	return WORLDWIDTH;
}

int get_world_height(void) {
	return WORLDHEIGHT;
}

int get_cell_state(int x, int y) {
	if (x < 0 || x >= WORLDWIDTH || y < 0 || y >= WORLDHEIGHT)
		return DEAD;
	return world[x][y];
}

void set_cell_state(int x, int y, int state) {
	if (x < 0 || x >= WORLDWIDTH || y < 0 || y >= WORLDHEIGHT) {
		fprintf(stderr,"Error: coordinates (%d,%d) are invalid.\n", x, y);
		abort();
	}
	nextstates[x][y] = state;
}

void finalize_evolution(void) {
	int x, y;
	for (x = 0; x < WORLDWIDTH; x++) {
		for (y = 0; y < WORLDHEIGHT; y++) {
			world[x][y] = nextstates[x][y];
			nextstates[x][y] = DEAD;
		}
	}
}

void output_world(void) {
	char worldstr[2*WORLDWIDTH+2];
	int i, j;

	worldstr[2*WORLDWIDTH+1] = '\0';
	worldstr[0] = '+';
	for (i = 1; i < 2*WORLDWIDTH; i++)
		worldstr[i] = '-';
	worldstr[2*WORLDWIDTH] = '+';
	puts(worldstr);
	for (i = 0; i <= 2*WORLDWIDTH; i+=2)
		worldstr[i] = '|';
	for (i = 0; i < WORLDHEIGHT; i++) {
		for (j = 0; j < WORLDWIDTH; j++)
			worldstr[2*j+1] = world[j][i] == ALIVE ? CHAR_ALIVE : CHAR_DEAD;
		puts(worldstr);
	}
	worldstr[0] = '+';
	for (i = 1; i < 2*WORLDWIDTH; i++)
		worldstr[i] = '-';
	worldstr[2*WORLDWIDTH] = '+';
	puts(worldstr);
}
