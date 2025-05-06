#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deck.h"
#include "game.h"
#include "settings.h"

int main(){
    srand((unsigned int) time(NULL));

    Card *deck = createDeck();
    if (deck == NULL){
        return 1;
    }



}