//define
#include "randtests.h"



void runTest(struct gameState *G, struct gameState *testStatus) {
  int test_condition;
  int whoseTurn = G->whoseTurn;
  int handPos = (rand() % (G->handCount[whoseTurn])) + 1;

	
	
  test_condition = SmithyEffect(G, whoseTurn, handPos);
  test_assert(!test_condition, "Expected Return Value");

  // code from dominion.c for Smithy
  	//+3 Cards
  	int i;
        for (i = 0; i < 3; i++)
  	{
  	  drawCard(whoseTurn, testStatus);
  	}

  //discard card from hand
  discardCard(handPos, whoseTurn, testStatus, 0);

  //compares all memory of gamestates
  test_assert(!memcmp(testStatus->hand[whoseTurn], G->hand[whoseTurn], MAX_HAND), "Drew Treasure");
  test_assert(!memcmp(testStatus, G, sizeof(struct gameState)), "Affected Gamestate Size");

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
