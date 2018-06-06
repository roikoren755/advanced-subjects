COMP = g++
#put all your object files here
OBJS = main.o MainAux.o RPSBoard.o RPSGame.o RPSPiece.o TournamentManager.o #objects should be placed here!
SO_OBJS = RSPPlayer_204057566.o RPSBoard.o RPSPiece.o
#The executable filename DON'T CHANGE
EXEC = ex3
SO = RSPPlayer_204057566.so
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@
$(SO): $(SO_OBJS)
	$(COMP) $(SO_OBJS) -shared -o $@
#a rule for building a simple c++ source file
#use g++ -MM main.cpp to see dependencies
AlgorithmRegistration.o: AlgorithmRegistration.cpp AlgorithmRegistration.h PlayerAlgorithm.h Point.h PiecePosition.h Board.h FightInfo.h Move.h JokerChange.h TournamentManager.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
main.o: main.cpp MainAux.h RPSGame.h RPSPiece.h PlayerAlgorithm.h Point.h PiecePosition.h Board.h FightInfo.h Move.h JokerChange.h RPSBoard.h RPSPiecePosition.h RPSPoint.h RPSFightInfo.h #put dependencies here!
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
MainAux.o: MainAux.cpp RSPPlayer_204057566.h PlayerAlgorithm.h Point.h PiecePosition.h Board.h FightInfo.h Move.h JokerChange.h RPSBoard.h RPSPiece.h RPSPiecePosition.h RPSPoint.h RPSMove.h RPSJokerChange.h RPSFightInfo.h MainAux.h RPSGame.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
RPSGame.o: RPSGame.cpp RPSGame.h RPSPiece.h PlayerAlgorithm.h Point.h PiecePosition.h Board.h FightInfo.h Move.h JokerChange.h RPSBoard.h RPSPiecePosition.h RPSPoint.h RPSFightInfo.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
TournamentManager.o: TournamentManager.cpp TournamentManager.h PlayerAlgorithm.h Point.h PiecePosition.h Board.h FightInfo.h Move.h JokerChange.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
RSPPlayer_204057566.o: RSPPlayer_204057566.cpp RSPPlayer_204057566.h AlgorithmRegistration.h PlayerAlgorithm.h Point.h PiecePosition.h Board.h FightInfo.h Move.h JokerChange.h RPSBoard.h RPSPiece.h RPSPoint.h RPSPiecePosition.h RPSMove.h RPSJokerChange.h
	$(COMP) -fPIC $(CPP_COMP_FLAG) -c $*.cpp
RPSBoard.o: RPSBoard.cpp RPSBoard.h Board.h Point.h RPSPiece.h
	$(COMP) -fPIC $(CPP_COMP_FLAG) -c $*.cpp
RPSPiece.o: RPSPiece.cpp RPSPiece.h
	$(COMP) -fPIC $(CPP_COMP_FLAG) -c $*.cpp

.PHONY: all rps_tournament rps_lib
all: $(EXEC) $(SO)
rps_tournament: $(EXEC)
rps_lib: $(SO)

clean:
	rm -f $(OBJS) $(EXEC) *Test *.o