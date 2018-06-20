#include <string>
#include <utility>

#include "ex4_header.h"
#include "unit_test_util.h"

using std::string;
using std::get;

static bool test1(){
	GameBoard<12, 7, char, 4> board;
	int i = 0;
	for (int row =0; row < 12; row++){
		for(int col =0; col < 7; col++){
			board.setPiece(row, col, 'P', i);
			i = (i+1)%4;
		}
	}

	int occurence[4]= {0,0,0,0};
	for(auto pieceInfo : board){
		occurence[get<3>(pieceInfo)]++;
	}

	for(int i = 0;i<4;i++){
		if (occurence[i] != 21){
			return false;
		}
	}
	return true;
}

static bool test2() {
	GameBoard<10, 10, char, 5> board;
	int pieces = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			board.setPiece(i * 2, j * 2, 'A' + i, j);
			pieces++;
		}
	}

	int i = 0;
	int occurenceByPiece[5]= {0,0,0,0,0};
	int occurenceByPlayer[5] = {0,0,0,0,0};
	int occurenceByPlayerAndPiece[5][5] = {{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
	for (const auto& piece: board) {
		occurenceByPiece[get<2>(piece) - 'A']++;
		occurenceByPlayer[get<3>(piece)]++;
		occurenceByPlayerAndPiece[get<3>(piece)][get<2>(piece) - 'A']++;
		i++;
	}

	if (i != 25) {
		return false;
	}

	bool debugging = false;

	for (int j = 0; j < 5; j++) {
		int count = 0;
		for (const auto& piece: board.allOccureneceOfPiece('A' + j)) {
			if (debugging) {
				std::cout << std::get<1>(piece) << std::endl;
			}
			count++;
		}

		if (count != occurenceByPiece[j]) {
			std::cout << count << " != " << occurenceByPiece[j] << std::endl;
			return false;
		}
	}

	for (int j = 0; j < 5; j++) {
		int count = 0;
		for (const auto& piece: board.allPiecesOfPlayer(j)) {
			if (debugging) {
				std::cout << std::get<1>(piece) << std::endl;
			}
			count++;
		}

		if (count != occurenceByPlayer[j]) {
			std::cout << count << " != " << occurenceByPlayer[j] << std::endl;
			return false;
		}
	}

	for (int j = 0; j < 5; j++) {
		for (int k = 0; k < 5; k++) {
			int count = 0;
			for (const auto& piece: board.allOccureneceOfPieceForPlayer('A' + k, j)) {
				if (debugging) {
					std::cout << std::get<1>(piece) << std::endl;
				}
				count++;
			}

			if (count != occurenceByPlayerAndPiece[j][k]) {
				std::cout << count << " != " << occurenceByPlayerAndPiece[j][k] << std::endl;
				return false;
			}
		}
	}

	return true;
}

int main(){
	RUN_TEST(test1);
	RUN_TEST(test2);
	return 0;
}
