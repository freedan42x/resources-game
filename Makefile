CC = gcc
CFLAGS = -std=gnu99 # -Wall -Wextra -Wno-missing-braces
LIBS = -lm

SRCDIR = src
OBJDIR = obj

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $< $(CFLAGS) -o $@

main: $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) -o $@ $^
