//defining header file

#include "randtests.h"

void runTest(struct gameState *G, struct gameState *testStatus) {
  int test_condition;
  int whoseTurn = G->whoseTurn;
  int handPos = (rand() % (G->handCount[whoseTurn])) + 1;

  test_condition = VillageEffect(G, whoseTurn, handPos);
  test_assert(!test_condition, "Expected Return Value");

  //Village code from dominion.c
	//+1 Card
    drawCard(whoseTurn, testStatus);

    //+2 Actions
    testStatus->numActions = testStatus->numActions + 2;

    //discard played card from hand
    discardCard(handPos, whoseTurn, &testStatus, 0);

  //compares all memory of gamestates
  test_assert(!memcmp(testStatus->hand[whoseTurn], G->hand[whoseTurn], MAX_HAND), "Drew Treasure");
  
}

int main(){
	struct gameState G, testStatus;
	int i;
	srand(time(NULL));
	test_header("##Smithy Random Test Beginning##");
	for (i = 0; i < TESTS; i++) {
		setupGame(&G, &testStatus);
		runTest(&G, &testStatus);
	}
	test_header("##Smithy Random Test Completed##");


	return 0;

}
