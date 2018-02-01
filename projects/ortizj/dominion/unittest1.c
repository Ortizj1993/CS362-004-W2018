/*
 * cardtest2.c
 *
 
 */

/*
 
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>

#include "rngs.h"
#include <stdlib.h>

#define UNITTEST "getCost(int)"

int main() {
	
	int test_success = 0;
	int cost = 0;
	
			//note: used instructor file as template for this test
    int newCards = 0;
    int discarded = 0; //no discards
    int xtraCoins = 0;
	int xtraActions = 0;
	int turnAction = 1;
	int xtraBuys = 0;
    int shuffledCards = 0;
	int temphand[MAX_HAND];

	int i = 0, j, m;
    int handpos = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	int opponent = 1;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	printf("**********Testing Function: %s ***********\n", UNITTEST);
	
	for (i = 0; i < 25; i++){
		
		switch(i){
			
			cost = getCost(k);
			//for some reason doesn't print cost
			printf("%d --------\n", cost);
			
			//victory cards
			case province:
				test_success = test_success = testassert(cost == 8, test_success);
				break;
				
			case duchy:
				test_success = testassert(cost == 5, test_success);
				break;
				
			case estate:
				test_success = testassert(cost == 2, test_success);
				break;
				
			case curse:
				test_success = testassert(cost == 0, test_success);
				break;
				
			//treasure cards
			case gold:
				test_success = testassert(cost == 6, test_success);
				break;

			case silver:
				test_success = testassert(cost == 3, test_success);
				break;
				
			case copper:
				test_success = testassert(cost == 0, test_success);
				break;
				
			//kingdom cards bugged in assignment 2 (check if they work properly)
				
			case adventurer:
				test_success = testassert(cost == 6, test_success);
				break;
				
			case smithy:
				test_success = testassert(cost == 4, test_success);
				break;
				
			case feast:
				test_success = testassert(cost == 4, test_success);
				break;
				
			case village:
				test_success = testassert(cost == 3, test_success);
				break;
				
			case mine:
				test_success = testassert(cost == 5, test_success);
				break;
				
			//other kingdom cards

			case council_room:
				test_success = testassert(cost == 5, test_success);
				break;
				
			case steward:
				test_success = testassert(cost == 3, test_success);
				break;

			case tribute:
				test_success = testassert(cost == 5, test_success);
				break;

			case ambassador:
				test_success = testassert(cost == 3, test_success);
				break;

			case cutpurse:
				test_success = testassert(cost == 4, test_success);
				break;

			case embargo:
				test_success = testassert(cost == 2, test_success);
				break;

			case outpost:
				test_success = testassert(cost == 5, test_success);
				break;

			case gardens:
				test_success = testassert(cost == 4, test_success);
				break;

			case remodel:
				test_success = testassert(cost == 5, test_success);
				break;

			case baron:
				test_success = testassert(cost == 4, test_success);
				break;
				
			case salvager:
				test_success = testassert(cost == 4, test_success);
				break;

			case sea_hag:
				test_success = testassert(cost == 4, test_success);
				break;

			case treasure_map:
				test_success = testassert(cost == 4, test_success);;
				break;

			case great_hall:
				test_success = testassert(cost == 3, test_success);
				break;

			case minion:
				test_success = testassert(cost == 5, test_success);
				break; 
			
		}
		
		//check if switch case was out of bounds
		if (i < 0 || i > 26){
			test_success = testassert(0, test_success);
			printf("\n Test %d Failed\n\n", i);
		} else {
			printf("\n Test %d Passed\n\n", i);
		}
		
		printf("--------\n");
			
	}

	
	//Test that player drew 1 card
	newCards = 1;
	printf("\n Hand count = %d, Expected hand count = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	test_success = testassert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded, test_success);
	
	printf("\n Deck count = %d, Expected deck count = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] + shuffledCards - newCards);
	test_success = testassert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] + shuffledCards - newCards, test_success);
	
	//Test that player got 0 extra actions
	xtraActions = 0;
	printf("\n Actions = %d, Expected number of actions = %d\n", testG.numActions - turnAction, G.numActions + xtraActions - turnAction);
	test_success = testassert((testG.numActions - turnAction) == (G.numActions + xtraActions - turnAction), test_success);
	
	//Test that buys do not increase
	printf("\n Buys = %d, Expected number of buys = %d\n", testG.numBuys, G.numBuys + xtraBuys);

	test_success = testassert(testG.numBuys == (G.numBuys + xtraBuys), test_success);
 
	//Test that no state changes occured for the other player	
	printf("\n Opponent hand count = %d, Opponent expected hand count = %d\n", testG.handCount[opponent], G.handCount[opponent]);
	test_success = testassert(testG.handCount[opponent] == (G.handCount[opponent]), test_success);
 
	printf("\n Opponent deck count = %d, Opponent expected deck count = %d\n", testG.deckCount[opponent], G.deckCount[opponent]);
 	test_success = testassert(testG.deckCount[opponent] == (G.deckCount[opponent]), test_success);
 
 	//Test that no state changes occured to the victory card piles
 	printf("\n Testing victory card piles\n");
 
 	test_success = testassert(testG.supplyCount[estate] == G.supplyCount[estate], test_success);
 	test_success = testassert(testG.supplyCount[duchy] == G.supplyCount[duchy], test_success);
 	test_success = testassert(testG.supplyCount[province] == G.supplyCount[province], test_success);
 
 	//Test that no state changes occured to the kingdom card piles
 	printf("\n Testing kingdom card piles\n");
 
 	test_success = testassert(testG.supplyCount[adventurer] == G.supplyCount[adventurer], test_success);
 	test_success = testassert(testG.supplyCount[embargo] == G.supplyCount[embargo], test_success);
 	test_success = testassert(testG.supplyCount[village] == G.supplyCount[village], test_success);
 	test_success = testassert(testG.supplyCount[minion] == G.supplyCount[minion], test_success);
 	test_success = testassert(testG.supplyCount[mine] == G.supplyCount[mine], test_success);
 	test_success = testassert(testG.supplyCount[cutpurse] == G.supplyCount[cutpurse], test_success);
 	test_success = testassert(testG.supplyCount[sea_hag] == G.supplyCount[sea_hag], test_success);
 	test_success = testassert(testG.supplyCount[tribute] == G.supplyCount[tribute], test_success);
 	test_success = testassert(testG.supplyCount[smithy] == G.supplyCount[smithy], test_success);
 	test_success = testassert(testG.supplyCount[council_room] == G.supplyCount[council_room], test_success);
  	
 	printf("\n test_success = %d", test_success);
 	if(test_success == 1){
 		printf("\n *******%s TEST PASSED*********\n", UNITTEST);
 	}
 	else {
 		printf("\n *******%s TEST FAILED*********\n", UNITTEST);
 	}
	return 0;
}
