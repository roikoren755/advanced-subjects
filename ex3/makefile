COMP = g++
#put all your object files here
OBJS = main.o MainAux.o RPSBoard.o RPSFilePlayerAlgorithm.o RPSGame.o RPSPiece.o #objects should be placed here!
#The executable filename DON'T CHANGE
EXEC = ex2
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@
RSPPlayer_204057566.so: RSPPlayer_204057566.o
	$(COMP) -shared RSPPlayer_204057566.o -o $@
#a rule for building a simple c++ source file
#use g++ -MM main.cpp to see dependencies
RPSBoard.o: RPSBoard.cpp RPSBoard.h Board.h Point.h RPSPiece.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
RSPPlayer_204057566.o: RSPPlayer_204057566.cpp RSPPlayer_204057566.h PlayerAlgorithm.h Point.h PiecePosition.h Board.h FightInfo.h Move.h JokerChange.h RPSBoard.h RPSPiece.h RPSPoint.h RPSPiecePosition.h RPSMove.h RPSJokerChange.h AlgorithmRegistration.h
	$(COMP) -fPIC $(CPP_COMP_FLAG) -c $*.cpp
RPSFightInfo.o: RPSFightInfo.h FightInfo.h RPSPoint.h Point.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
RPSFilePlayerAlgorithm.o: RPSFilePlayerAlgorithm.cpp RPSFilePlayerAlgorithm.h PlayerAlgorithm.h Point.h PiecePosition.h Board.h FightInfo.h Move.h JokerChange.h RPSPiecePosition.h RPSPoint.h RPSMove.h RPSJokerChange.h RPSFightInfo.h RPSBoard.h RPSPiece.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
RPSGame.o: RPSGame.cpp RPSGame.h RPSPiece.h PlayerAlgorithm.h Point.h PiecePosition.h Board.h FightInfo.h Move.h JokerChange.h RPSBoard.h RPSPiecePosition.h RPSPoint.h RPSFightInfo.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
RPSJokerChange.o: RPSJokerChange.h JokerChange.h Point.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
RPSMove.o: RPSMove.h Move.h Point.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
RPSPiece.o: RPSPiece.cpp RPSPiece.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
RPSPiecePosition.o: RPSPiecePosition.h PiecePosition.h Point.h RPSPoint.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
RPSPoint.o: RPSPoint.h Point.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
MainAux.o: MainAux.cpp RSPPlayer_204057566.h PlayerAlgorithm.h Point.h PiecePosition.h Board.h FightInfo.h Move.h JokerChange.h RPSBoard.h RPSPiece.h RPSFilePlayerAlgorithm.h RPSPiecePosition.h RPSPoint.h RPSMove.h RPSJokerChange.h RPSFightInfo.h MainAux.h RPSGame.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
main.o: main.cpp MainAux.h RPSGame.h RPSPiece.h PlayerAlgorithm.h Point.h PiecePosition.h Board.h FightInfo.h Move.h JokerChange.h RPSBoard.h RPSPiecePosition.h RPSPoint.h RPSFightInfo.h #put dependencies here!
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
AlgorithmRegistration.o: AlgorithmRegistration.cpp AlgorithmRegistration.h PlayerAlgorithm.h Point.h PiecePosition.h Board.h FightInfo.h Move.h JokerChange.h TournamentManager.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

clean:
	rm -f $(OBJS) $(EXEC) *Test *.o