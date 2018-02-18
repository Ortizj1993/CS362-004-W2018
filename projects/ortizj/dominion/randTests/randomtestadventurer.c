#include "randtests.h"

void runTest(struct gameState *G, struct gameState *testStatus) {
  int test_condition;
  int whoseTurn = G->whoseTurn;
  int drawntreasure = 0;
  int cardDrawn;
  int temphand[MAX_HAND];
  int z = 0; //  temporary hand counter

  test_condition = AdventurerEffect(G, z, drawntreasure, temphand);
  test_assert(!test_condition, "Expected Return Value");

  //adventurer code from dominion.c
  while(drawntreasure < 2) {
    if (testStatus->deckCount[whoseTurn] <1) { //empty deck means shuffle discard then add to deck
      test_condition = shuffle(whoseTurn, testStatus);
      test_assert(!test_condition, "Expected Deck Count");
    }
    test_condition = drawCard(whoseTurn, testStatus);
    test_assert(!test_condition, "Expected Hand Count");
    cardDrawn = testStatus->hand[whoseTurn][testStatus->handCount[whoseTurn]-1]; //most recently drawn card is top card of hand
    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
      drawntreasure++;
    else{
      temphand[z]=cardDrawn;
      testStatus->handCount[whoseTurn]--; //I believe this should remove the most recent drawn card
      z++;
    }
  }

  //not entirely sure why this is buggy if z goes below zero there is potential error if two treasures are drawn
  while(z-1 >= 0) {
	  testStatus->discard[whoseTurn][testStatus->discardCount[whoseTurn]++]=temphand[z-1]; // discard all cards in play that have been drawn
    z = z-1;
  }
  //gamestates memory comparison
  test_assert(!memcmp(testStatus->hand[whoseTurn], G->hand[whoseTurn], MAX_HAND), "Drew Treasure");
  test_assert(!memcmp(testStatus, G, sizeof(struct gameState)), "Affected Gamestate Size");

}

int main(){
	struct gameState G, testStatus;
	int i;
	srand(time(NULL));
	test_header("##Adventurer Random Test Beginning##");
	for (i = 0; i < TESTS; i++) {
		setupGame(&G, &testStatus);
		runTest(&G, &testStatus);
	}
	test_header("##Adventurer Random Test Completed##");


	return 0;

}
