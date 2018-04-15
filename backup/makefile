COMP = g++-5.3.0
#put all your object files here
OBJS = main.o MainAux.o RPSCommandFactory.o RPSGame.o RPSPiece.o  #objects should be placed here!
#The executable filename DON'T CHANGE
EXEC = ex1
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@
#a rule for building a simple c++ source file
#use g++ -MM main.cpp to see dependencies
MainAux.o: MainAux.cpp MainAux.h RPSCommandFactory.h RPSGame.h RPSCommand.h RPSPiece.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
RPSCommandFactory.o: RPSCommandFactory.cpp RPSCommandFactory.h RPSCommand.h RPSPiece.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
RPSPiece.o: RPSPiece.cpp RPSPiece.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
RPSGame.o: RPSGame.cpp RPSGame.h RPSPiece.cpp RPSPiece.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
main.o: main.cpp #put dependencies here!
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
clean:
	rm -f $(OBJS) $(EXEC) *Test *.o