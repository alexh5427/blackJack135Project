#ifndef GAME_H
#define GAME_H
#include "deck.h"
#define MAX_HAND_CARDS 12

typedef struct{
    Card *cards;
    int count;
} Hand;

void startGame(Hand *player, Hand *dealer);

int playRound(Hand *player, Hand *dealer, Card *deck);

int findTotal(Hand *hand);

void showHand(const char *name, Hand *hand, int hidedealercard);

void dealerSteve(Hand *dealer, Card *deck, int *deckIndex);

int checkWinner(Hand *player, Hand *dealer);

#endif