COMP = g++
#put all your object files here
OBJS = main.o #objects should be placed here!
#The executable filename DON'T CHANGE
EXEC = ex2
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@
#a rule for building a simple c++ source file
#use g++ -MM main.cpp to see dependencies
RPSBoard.o: RPSBoard.cpp RPSBoard.h Board.h Point.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
RPSPoint.o: RPSPoint.h Point.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
main.o: main.cpp #put dependencies here!
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
clean:
	rm -f $(OBJS) $(EXEC) *Test *.o