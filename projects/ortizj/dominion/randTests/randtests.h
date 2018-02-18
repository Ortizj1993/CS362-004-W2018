//defenitions
#ifndef _RANDTESTS_H
#define _RANDTESTS_H

#include "../dominion.h"
#include "../dominion_helpers.h"
#include "../rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define TESTS 100000

int testassert(int test, char* msg);
void test_header(char* name);
void test_print(int *arr, int n, char* message);
void makeCards(struct gameState *G, int *cardCount, int (*cards)[MAX_DECK], int size);
void setupGame(struct gameState *G, struct gameState *testStatus);

#endif
