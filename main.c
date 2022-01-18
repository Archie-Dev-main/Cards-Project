#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include"cards.h"

int main(int argc, char* argv[])
{
    // Player One and Two, the inital count, and the round counter
    Card* p1Head = NULL;
    Card* p2Head = NULL;
    int initCardCount;
    int round = 1;
    // srand call
    srand((int)time(0));
    if (argc < 2) {
        printf("ERROR: NOT ENOUGH ARGUMENTS: MISSING AN INTEGER");
        return -1;
    }

    if (atoi(argv[1]) < 0) {
        printf("ERROR: INCORRECT ARGUMENT: INT IS LESS THAN 0 OR INPUT IS NOT AN INT");
        return -1;
    }

    printf("============= PLAYER 1 V PLAYER 2 SHOWDOWN ============\n");

    initCardCount = atoi(argv[1]);
    printf("Start size: %d\n", initCardCount);

    p1Head = buildCards(initCardCount);
    printf("Player 1 starting cards: ");
    printCards(p1Head);
    printf("\n");

    p2Head = buildCards(initCardCount);
    printf("Player 2 starting cards: ");
    printCards(p2Head);
    printf("\n\n");

    // Game Logic
    while (p1Head != NULL && p2Head != NULL) {
        // Round printed statements
        printf("----- ROUND %d -----\n", round);
        printf("Player 1 (%d): ", getLength(p1Head));
        printCard(p1Head);
        printf("\n");
        printf("Player 2 (%d): ", getLength(p2Head));
        printCard(p2Head);
        printf("\n");

        // Cases for when both players do the same thing
        if (p1Head->type == ATTACK && p2Head->type == ATTACK) {
            printf("Both players ATTACK.\n");
            if (p1Head->value > p2Head->value) {
                p1Head = removeCard(p1Head);
                p1Head = addCard(p1Head, createCard());
                p2Head = removeCard(p2Head);
                printf("Player 1 wins and gets a new card. Player 2 loses their next card into the abyss.\n");
            }
            else if (p1Head->value < p2Head->value){
                p1Head = removeCard(p1Head);
                p2Head = removeCard(p2Head);
                p2Head = addCard(p2Head, createCard());
                printf("Player 2 wins and gets a new card. Player 1 loses their next card into the abyss.\n");
            }
            else {
                p1Head = removeCard(p1Head);
                p2Head = removeCard(p2Head);
                printf("Nothing happens.\n");
            }
        }
        else if (p1Head->type == DEFEND && p2Head->type == DEFEND) {
            p1Head = removeCard(p1Head);
            p2Head = removeCard(p2Head);
            printf("Nothing happens.\n");
        }
        else if (p1Head->type == RUN && p2Head->type == RUN) {
            p1Head = removeCard(p1Head);
            p1Head = removeCard(p1Head);
            p2Head = removeCard(p2Head);
            p2Head = removeCard(p2Head);
            printf("Both players lose their next card into the abyss.\n");
        } // Cases for Attack and Defense
        else if (p1Head->type == ATTACK && p2Head->type == DEFEND) {
            printf("Player 1 ATTACKs and Player 2 DEFENDs.\n");
            if (p1Head->value > p2Head->value) {
                p1Head = removeCard(p1Head);
                p1Head = addCard(p1Head, createCard());
                p2Head = removeCard(p2Head);
                printf("Player 1 wins and gets a new card.\n");
            }
            else {
                p1Head = removeCard(p1Head);
                p1Head = removeCard(p1Head);
                p2Head = removeCard(p2Head);
                printf("Player 1 loses and Player 2 survives.\n");
                printf("Player 1 loses their next card into the abyss.\n");
            }
        }
        else if (p1Head->type == DEFEND && p2Head->type == ATTACK) {
            printf("Player 2 ATTACKs and Player 1 DEFENDs.\n");
            if (p1Head->value < p2Head->value) {
                p1Head = removeCard(p1Head);
                p2Head = removeCard(p2Head);
                p2Head = addCard(p2Head, createCard());
                printf("Player 2 wins and gets a new card.\n");
            }
            else {
                p1Head = removeCard(p1Head);
                p2Head = removeCard(p2Head);
                p2Head = removeCard(p2Head);
                printf("Player 2 loses and Player 1 survives.\n");
                printf("Player 2 loses their next card into the abyss.\n");
            }
        } // Cases for Attack and Run
        else if (p1Head->type == ATTACK && p2Head->type == RUN) {
            printf("Player 1 ATTACKs and Player 2 RUNs.\n");
            p1Head = removeCard(p1Head);
            p2Head = removeCard(p2Head);
            p2Head = removeCard(p2Head);
            printf("Player 2 loses their next card into the abyss.\n");
        }
        else if (p1Head->type == RUN && p2Head->type == ATTACK) {
            printf("Player 2 ATTACKs and Player 1 RUNs.\n");
            p1Head = removeCard(p1Head);
            p1Head = removeCard(p1Head);
            p2Head = removeCard(p2Head);
            printf("Player 1 loses their next card into the abyss.\n");
        } // Cases for Defend and Run
        else if (p1Head->type == DEFEND && p2Head->type == RUN) {
            printf("Player 1 DEFENDs and Player 2 RUNs.\n");
            p1Head = removeCard(p1Head);
            p2Head = removeCard(p2Head);
            p2Head = removeCard(p2Head);
            printf("Player 1 gets a new card. Player 2 loses their next card into the abyss.\n");
        }
        else {
            printf("Player 2 DEFENDs and Player 1 RUNs.\n");
            p1Head = removeCard(p1Head);
            p1Head = removeCard(p1Head);
            p2Head = removeCard(p2Head);
            printf("Player 2 gets a new card. Player 1 loses their next card into the abyss.\n");
        }
        round++;
        printf("\n");
    }
    
    // End of the game
    printf ("============ GAME OVER  =============\n\n");
    printf("Player 1 ending cards: ");
    printCards(p1Head);
    printf("\n");
    printf("Player 2 ending cards: ");
    printCards(p2Head);
    printf("\n\n");
    if (p1Head == NULL) {
        printf("Player 1 ran out of cards. Player 2 wins.\n");
    }
    else {
        printf("Player 2 ran out of cards. Player 1 wins.\n");
    }
    printf("The end.");
    destroyCards(p1Head);
    destroyCards(p2Head);
    return 0;
}