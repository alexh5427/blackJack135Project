#include <stdio.h>
#include <stdlib.h>
#include "deck.h"

Card* createDeck(){
    Card* deck = malloc (DECK_SIZE * sizeof(Card));
    if (deck == NULL){
        fprintf(stderr, "FAILED!\n");
        return NULL;
    }
    Card *cardPtr = deck;
    for (int suit = 0; suit < 4; suit++){
        for (int rank = 1; rank <=13; rank++){
            cardPtr->rank = rank;
            cardPtr->suit = suit;
            if (rank == 1){
                cardPtr->value = 11;
            } else if (rank >= 10){
                cardPtr->value = 10;
            } else {
                cardPtr->value = rank;
            }
            cardPtr++;
        }
    }
    return deck;
}


void shuffleDeck(Card* deck){
    for (int i = DECK_SIZE - 1; i > 0; i--){
        int j = rand() % (i+1);
        Card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}


Card drawCard(Card* deck, int* deckIndex){
    return deck[(*deckIndex)++];
}

void freeDeck(Card* deck){
    free(deck);
}