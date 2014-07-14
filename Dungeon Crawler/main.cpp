/* TO DO:
Instead of using stdlib.h, the c++ way of using c libs is to prefix them with
c and remove the .h. E.g. #include <cstdlib>

You should look for native c++ ways to do things. Using rand with a modulus
like that is actually slightly biased towards lower numbers, it's better to
#include <random> and use std::uniform_int_distribution,
have a look at the documentation.
This is a c++11 features so make sure you enable it in your compile
(from the command line compile with -std=c++11) Also have a look at the
chrono library for time. With regards to style, I'd change the names of the
arguments of drawboard to reflect their meaning, as you do when you call them
in main(). Generally, having a,b, and c as variable names is a bad practice
unless they are actually arbitrary constants with no meaning.
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void drawboard(int a, int b, int c);

int main() {
  int rows, columns, traps;
  cout << "How many rows would you like the gameboard to have? ";
  cin >> rows;
  cout << "And how many columns? ";
  cin >> columns;
  cout << "And how many traps? (Difficutly) ";
  cin >> traps;

  drawboard(rows,columns,traps);
}

//Draw the game board
void drawboard(int a=6, int b=6, int c=6){
  //Initialize random seed
  srand(time(NULL));
  //Array for the gameboard area
  char board[a][b];

  //Populate the gameboard with empty spaces (Space character)
  //For loop increments row to populate
  for (int i=0;i<a;i++) {
    //For loop increments column to populate
    for (int j=0;j<b;j++) {
      board[i][j] = ' ';
    }
  }

  //Declare entities to be placed on the board
  char player = 'P';
  char gold = 'G';
  char trap = 'T';
  int trapamount = c;

  //Calculate positions for entities
  //Calculate random player position
  int playera = rand() % a;
  int playerb = rand() % b;
  board[playera][playerb] = player;
  //Calculate random gold position; wont be equal to player position
  int golda, goldb;
  do {
    golda = rand() % a;
    goldb = rand() % b;
  } while (golda == playera && goldb == playerb);
  board[golda][goldb] = gold;
  //Calculate trap locations
  int trapa, trapb;
  for (int traploc=0;traploc<trapamount;traploc++) {
    do {
      trapa = rand() % a;
      trapb = rand() % b;
    } while ((trapa == playera && trapa == golda) || (trapb == playerb && goldb));
    board[trapa][trapb] = trap;
  }

  //Print the top border
  for (int bcol=0;bcol<b+2;bcol++) {cout << "X";};
  cout<<"\n";

  //Print side borders and table
  for (int boardrow=0;boardrow<a;boardrow++) {
    cout << "X";
    for (int boardcol=0;boardcol<b;boardcol++) {
      cout << board[boardrow][boardcol];
    }
    cout << "X" << "\n";
  }

  //Print the bottom border
  for (int bcol=0;bcol<b+2;bcol++) {cout << "X";};
}
