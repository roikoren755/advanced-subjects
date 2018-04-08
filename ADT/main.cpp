/*
 * main.cpp
 *
 *  Created on: 5 באפר 2018
 *      Author: user
 */
#include <iostream>
#include <cstring>
#include "RPSPiece.h"
#include "RPSCommand.h"
#include "RPSGame.h"

using namespace std;

int main(){
	cout<<"hello world!\n"<<endl;

	Game *game = new Game();
	Command *command = new Command();
	command->toX = 5;
	command->toY = 6;
	command->player = 1;
	cout<<*game<<endl;

}

