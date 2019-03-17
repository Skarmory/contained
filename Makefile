CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Iinclude
LDFLAGS=
NAME=program

INCL=$(wildcard include/*.h)
INCL+=$(wildcard include/test/*.h)
SRCS=$(wildcard src/*.c)
SRCS+=$(wildcard src/test/*.c)
OBJS=$(SRCS:.c=.o)
DEPS=$(SRCS:.c=.d)

.PHONY: clean $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.c
	$(CC) -MMD $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@rm -f $(DEPS)

-include $(DEPS)
