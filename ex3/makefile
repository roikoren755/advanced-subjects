COMP = g++-5.3.0
#put all your object files here
OBJS = main.o MainAux.o RPSBoard.o RPSFilePlayerAlgorithm.o RPSGame.o RPSPiece.o RSPPlayer_204057566.o#objects should be placed here!
#The executable filename DON'T CHANGE
EXEC = ex3
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@
#a rule for building a simple c++ source file
#use g++ -MM main.cpp to see dependencies
RPSFilePlayerAlgorithm.o: RPSFilePlayerAlgorithm.cpp RPSFilePlayerAlgorithm.h PlayerAlgorithm.h Point.h PiecePosition.h Board.h FightInfo.h Move.h JokerChange.h RPSPiecePosition.h RPSPoint.h RPSMove.h RPSJokerChange.h RPSFightInfo.h RPSBoard.h RPSPiece.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
RPSGame.o: RPSGame.cpp RPSGame.h RPSPiece.h PlayerAlgorithm.h Point.h PiecePosition.h Board.h FightInfo.h Move.h JokerChange.h RPSBoard.h RPSPiecePosition.h RPSPoint.h RPSFightInfo.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
MainAux.o: MainAux.cpp RSPPlayer_204057566.h PlayerAlgorithm.h Point.h PiecePosition.h Board.h FightInfo.h Move.h JokerChange.h RPSBoard.h RPSPiece.h RPSFilePlayerAlgorithm.h RPSPiecePosition.h RPSPoint.h RPSMove.h RPSJokerChange.h RPSFightInfo.h MainAux.h RPSGame.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
main.o: main.cpp MainAux.h RPSGame.h RPSPiece.h PlayerAlgorithm.h Point.h PiecePosition.h Board.h FightInfo.h Move.h JokerChange.h RPSBoard.h RPSPiecePosition.h RPSPoint.h RPSFightInfo.h #put dependencies here!
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
AlgorithmRegistration.o: AlgorithmRegistration.cpp AlgorithmRegistration.h PlayerAlgorithm.h Point.h PiecePosition.h Board.h FightInfo.h Move.h JokerChange.h TournamentManager.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
RSPPlayer_204057566.so: RSPPlayer_204057566.o RPSBoard.o RPSPiece.o
	$(COMP) RSPPlayer_204057566.o RPSBoard.o RPSPiece.o -shared -o $@
RSPPlayer_204057566.o: RSPPlayer_204057566.cpp RSPPlayer_204057566.h AlgorithmRegistration.h PlayerAlgorithm.h \
						Point.h PiecePosition.h Board.h FightInfo.h Move.h JokerChange.h RPSBoard.h RPSPiece.h \
						RPSPoint.h RPSPiecePosition.h RPSMove.h RPSJokerChange.h
	$(COMP) -fPIC $(CPP_COMP_FLAG) -c $*.cpp
RPSBoard.o: RPSBoard.cpp RPSBoard.h Board.h Point.h RPSPiece.h
	$(COMP) -fPIC $(CPP_COMP_FLAG) -c $*.cpp
RPSPiece.o: RPSPiece.cpp RPSPiece.h
	$(COMP) -fPIC $(CPP_COMP_FLAG) -c $*.cpp

clean:
	rm -f $(OBJS) $(EXEC) *Test *.o