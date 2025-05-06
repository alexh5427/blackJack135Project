#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "settings.h"

static const char *suitNames[]={
    "Heart","Diamonds","Clubs","Spades"
};

static const char *rankNames[]={
    "None", "Ace", "2","3","4","5","6","7","8","9","10","Jack","Queen","King"
};


void startGame(Hand *player,Hand *dealer){
    player->cards=malloc(MAX_HAND_CARDS * sizeof(Card));
    dealer->cards=malloc(MAX_HAND_CARDS * sizeof(Card));
    if (player->cards == NULL || dealer->cards == NULL){
        fprintf(stderr, "Failed to Start Game\n");
        exit(1);
    }
    player->count=0;
    dealer->count=0;
}

int findTotal(Hand *hand){
    int total = 0;
    int acesCount = 0;
    for (Card *ptr = hand->cards; ptr < hand->cards + hand->count;ptr++){
        total+=ptr->value;
        if (ptr->value==11){
            acesCount++;
        }
        while (total>21 && acesCount>0){
            total-=10;
            acesCount--;
        }
        return total;
    }
}

void showHand(const char *name, Hand *hand, int hidedealercard){
    printf("%s's hand", name);
    if (!hidedealercard){
        int total = findTotal(hand);
        printf("(total=%d)", total);
    }
    printf(": ");
    for (int i = 0; i < hand->count; i++){
        printf("[hidden]");
    }else{
        const char *rankStr = rankNames[hand->cards[i].rank];
        const char *suitStr = suitNames[hand->cards[i].suit];
        printf("%s of %s", rankStr, suitStr);
    }
    if(i < hand->count - 1){
        printf(",");
    }
}
printf("\n");

void dealerSteve(Hand *dealer, Card *deck, int *deckIndex){
    int total = findTotal(dealer);
    printf("dealers turn...\n");
    printf("Dealer", dealer, 0);
    while (total<17){
        Card newCard = drawCard(deck, deckIndex);
        dealer->cards[dealer->count++]=newCard;
        printf("dealer draws %s of %s \n", rankNames[newCard.rank], suitNames[newCard.suit]);
        total = findTotal(dealer);
    }
    if(total>21){
        printf("Dealer Busts with: %d\n", total);
    } else {
        printf("dealer stands with: %d\n", total);
    }
}


int checkWinner(Hand *player, Hand *dealer){
    int playerTotal = findTotal(player);
    int dealerTotal = findTotal(dealer);
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

    player->count = dealer->count = 0;
    player->cards[player->count++] = drawCard(deck, &deckIndex);
    player->cards[player->count++] = drawCard(deck, &deckIndex);
    dealer->cards[dealer->count++] = drawCard(deck, &deckIndex);
    dealer->cards[dealer->count++] = drawCard(deck, &deckIndex);

    showHand("player", player, 0);
    showHand("dealer", dealer, 1);

    while(1){
        int playerTotal = findTotal(player);
        if (playerTotal>21){
            printf("Bust! Dealer Wins");
            return -1;
        }
        printf("Hit (h) or Stand (s)?");
        if (scanf(" %c", &choice) != 1){
            continue;
        }
        if (choice == 'h' || choice == 'H'){
            Card newCard = drawCard(deck, &deckIndex);
            player->cards[player->count++] = newCard;
            printf("You drew: %s of %s.\n", rankNames[newCard.rank], suitNames[newCard.suit]);
            printf("Total is now: %d.\n", findToal(player));
        }else if (choice == 's' || choice == 'S'){
            break;
        } else{
            printf("enter 'h' or 's' only")
            continue;
        }
    }

    dealerSteve(dealer,deck, &deckIndex);
    int result = checkWinner(player,dealer);
    if(result==1){
        printf("You Win");
    }else if (result == -1){
        printf("dealer Wins");
    }else{
        printf("TIE!");
    }
    return result;
}

