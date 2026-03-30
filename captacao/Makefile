CC      = gcc
CFLAGS  = -Wall -Wextra -pedantic -std=c99
TARGET  = captacao
SRCS    = main.c app.c lista_dupla.c fila.c pilha.c utils.c
OBJS    = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
