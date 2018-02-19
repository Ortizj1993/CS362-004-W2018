CC = gcc
CFLAGS = -Wall -fpic -coverage -lm -fprofile-arcs -ftest-coverage -g
OBJ = dominion.o rngs.o

TEST_PATH = ./randTests/
TEST_FILES = $(TEST_PATH)randtests.h $(TEST_PATH)test_template.o
TEST_TYPE = -b

define runTest =
$(TEST_PATH)$(word 2, $^) &> $@result.out
gcov $(TEST_TYPE) $< >> $@result.out
cat $<.gcov >> $@result.out
endef


######################
#### BASE OBJECTS ####

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
	
#######################
##### RANDOM TESTS ####

test_template.o: $(TEST_PATH)test_template.c $(TEST_PATH)randtests.h
	gcc $(CFLAGS) -c $(TEST_PATH)test_template.c -o test_template.o
	
## adventurer

randomtestadventurer.out: randomtestadventurer
	cat dominion.c.gcov >> randomtestadventurer.out
	
randomtestadventurer: $(TEST_PATH)randomtestadventurer.c $(TEST_FILES) $(OBJ)
	gcc $(CFLAGS) -o randomtestadventurer -g $(TEST_PATH)randomtestadventurer.c $(TEST_PATH)test_template.o $(OBJ)
	./randomtestadventurer > randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out
	
## smithy
randomtestcard1.out: randomtestcard1
	cat dominion.c.gcov >> randomtestcard1.out
	
randomtestcard1: $(TEST_PATH)randomtestcard1.c $(TEST_FILES) $(OBJ)
	gcc $(CFLAGS) -o randomtestcard1 -g $(TEST_PATH)randomtestcard1.c $(TEST_PATH)test_template.o $(OBJ)
	./randomtestcard1 > randomtestcard1.out
	gcov dominion.c >> randomtestcard1.out
	
## Village
randomtestcard2.out: randomtestcard2
	cat dominion.c.gcov >> randomtestcard2.out
	
randomtestcard2: $(TEST_PATH)randomtestcard2.c $(TEST_FILES) $(OBJ)
	gcc $(CFLAGS) -o randomtestcard2 -g $(TEST_PATH)randomtestcard2.c $(TEST_PATH)test_template.o $(OBJ)
	./randomtestcard2 > randomtestcard2.out
	gcov dominion.c >> randomtestcard2.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

.PHONY: clean

clean:
	rm -f *.o *.out playdom.exe playdom test.exe test player player.exe testInit randomtestadventurer randomtestcard1 testInit.exe *.gcov *.gcda *.gcno *.so
	
