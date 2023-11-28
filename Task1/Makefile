CC = g++
CFLAGS = -Wall -Wextra -std=c++11
EXEC = main
SRCS = main.cpp modAlphaCipher.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm -f $(OBJS) $(EXEC)
