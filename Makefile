OBJS = main.o QuoteTree.o Utilities.o
CPPFLAGS = -std=c++11
LIBS = -lcurl

PROG = QuoteVerifier
CC = g++

$(PROG): $(OBJS) 
	$(CC) -o $(PROG) $(OBJS) $(LIBS)

main.o: QuoteTree.h QuoteTree.cpp
	$(CC) $(CPPFLAGS) -c main.cpp 

QuoteTree.o: QuoteTree.h QuoteTree.cpp
	$(CC) $(CPPFLAGS) -c QuoteTree.cpp

Utilities.o: Utilities.h Utilities.cpp
	$(CC) $(CPPFLAGS) -c Utilities.cpp

clean:
	$(RM) $(PROG) $(OBJS)