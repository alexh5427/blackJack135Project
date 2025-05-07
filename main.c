#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deck.h"
#include "game.h"


int main(){
    srand((unsigned int) time(NULL));

    Card *deck = createDeck();
    if (!deck){
        return 1;
    }
    shuffleDeck(deck);
    Hand player, dealer;
    startGame(&player, &dealer);
    int running=1;
    while (running){
        printf("\n1.Play\n2.Quit\nChoose: ");
        int choice;
        scanf(" %d",&choice);
        if (choice==1){
            shuffleDeck(deck);
            playRound(&player,&dealer,deck);
        }else if (choice==2){
            running=0;
        }else{
            printf("try again");
        }
    }
    free(player.cards);
    free(dealer.cards);
    freeDeck(deck);
    return 0;



}