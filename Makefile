CC = gcc
CFLAGS = -Wall -Wextra -std=c99

OBJS = main.o deck.o game.o

blackjack: $(OBJS)
	$(CC) $(CFLAGS) -o blackjack $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o blackjack