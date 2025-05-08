#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "deck.h"


static const char *suits[]={"Heart","Diamonds","Clubs","Spades"};

static const char *ranks[]={"None", "Ace", "2","3","4","5","6","7","8","9","10","Jack","Queen","King"};


void startGame(Hand *player,Hand *dealer){
    player->cards=malloc(MAX_HAND_CARDS * sizeof(Card));
    dealer->cards=malloc(MAX_HAND_CARDS * sizeof(Card));
    if (!player->cards||!dealer->cards){
        fprintf(stderr, "Failed to Start Game\n");
        exit(1);
    }
    player->count=0;
    dealer->count=0;
}

int calculateTotal(Hand* hand){
    int total = 0;
    int acesCount = 0;
    for (int i = 0; i < hand->count; i++){
        total+=hand->cards[i].value;
        if (hand->cards[i].value==11){
            acesCount++;
        }
    }
    while (total>21 && acesCount>0){
        total-=10;
        acesCount--;
    }
    return total;
    
}


void showHand(const char *name, Hand *hand, int hidedealercard){
    printf("%s's hand", name);
    if (!hidedealercard){
        printf("(total=%d)", calculateTotal(hand));
    }
    printf(": ");
    for (int i = 0; i < hand->count; i++){
        if (i==0 && hidedealercard){
            printf("[hidden]");
        } else {
            printf("%s of %s", ranks[hand->cards[i].rank], suits[hand->cards[i].suit]);
        }
        if (i < hand->count -1){
            printf(", ");
        }
    }
    printf("\n");
}


void dealerSteve(Hand* dealer, Card* deck, int* deckIndex){
    printf("dealers turn...\n");
    showHand("Dealer", dealer, 0);
    while (calculateTotal(dealer)<17){
        dealer->cards[dealer->count++]= drawCard(deck, deckIndex);
        printf("dealer draws %s of %s \n", ranks[dealer->cards[dealer->count-1].rank], suits[dealer->cards[dealer->count-1].suit]);
    }
}

int checkWinner(Hand *player, Hand *dealer){
    int playerTotal = calculateTotal(player);
    int dealerTotal = calculateTotal(dealer);
    if(playerTotal>21){
        return -1;
    }
    if(dealerTotal>21){
        return 1;
    }
    if(playerTotal>dealerTotal){
        return 1;
    }
    if(dealerTotal>playerTotal){
        return -1;
    }
    return 0;
}

int playRound (Hand *player, Hand *dealer, Card *deck){
    int deckIndex = 0;
    char choice;

    player->count = 0;
    dealer->count = 0;

    player->cards[player->count++] = drawCard(deck, &deckIndex);
    player->cards[player->count++] = drawCard(deck, &deckIndex);
    dealer->cards[dealer->count++] = drawCard(deck, &deckIndex);
    dealer->cards[dealer->count++] = drawCard(deck, &deckIndex);

    showHand("player", player, 0);
    showHand("dealer", dealer, 1);

    while(1){
        int total = calculateTotal(player);
        if (total>21){
            printf("Bust! Dealer Wins");
            return -1;
        }
        printf("Hit (h) or Stand (s)?");
        scanf(" %c", &choice);

        if (choice == 'h' || choice == 'H'){
            player->cards[player->count++] = drawCard(deck, &deckIndex);
            printf("You drew: %s of %s.\n", ranks[player->cards[player->count-1].rank], suits[player->cards[player->count-1].suit]);
            printf("Total is now: %d.\n", calculateTotal(player));
        }else if (choice == 's' || choice == 'S'){
            break;
        } else{
            printf("enter 'h' or 's' only");
        }
    }

    printf("\n\n");

    dealerSteve(dealer,deck, &deckIndex);
    int re = checkWinner(player,dealer);
    if(re==1){
        printf("\n");
        printf("You Win\n");
    }else if (re == -1){
        printf("\n");
        printf("dealer Wins\n");
    }else{
        printf("\n");
        printf("TIE!\n");
    }
    return re;
}

