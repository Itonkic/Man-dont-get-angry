// globals.h
#ifndef GLOBALS_H
#define GLOBALS_H
#define BUTTON1_PIN 1
#define BUTTON2_PIN 2
#define BUTTON3_PIN 5
#define BUTTON4_PIN 6
#define BUTTON5_PIN 7
#define MAX_PLAYERS 4  // Set the maximum number of players, adjust as needed
#define MAX_PIECES 4

extern int player_counter;
extern int broj;
extern int active[4];
extern int new_position;
extern int win;
extern int coun;
//extern int player_count;
extern int selectedPiece;
extern int playerPosition;
extern int playerPositions[4][4];
extern int playablefigures[4];
extern int search[2];
extern int currentPlayer;  // Index of the current player
extern bool defined_first;
const extern int numPiecesPerPlayer;  // You can change this value according to your game
extern int dice_roll;
volatile extern int buttonValue;
extern int highestRoll;
extern int startingPlayer;
extern bool flag;
#endif
