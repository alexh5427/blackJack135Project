#ifndef DECK_H
#define DECk_H
#define DECK_SIZE 52

typedef struct{
    int rank; // 1 is ace 13 king
    int suit;  //0=H 1=D 2=C 3=S
    int value;
} Card;

Card* createDeck();

void shuffleDeck(Card* deck);

Card drawCard(Card* deck, int* deckIndex);

void freeDeck(Card* deck);


#endif