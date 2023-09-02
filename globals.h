// globals.h
#ifndef GLOBALS_H
#define GLOBALS_H
#define BUTTON1_PIN PA0//4
#define BUTTON2_PIN PA1
#define BUTTON3_PIN PA2
#define BUTTON4_PIN PA3
#define BUTTON5_PIN PA4
#define MAX_PLAYERS 4  // Set the maximum number of players, adjust as needed
#define MAX_PIECES 4
#define NUM_LEDS 5
#define NUM_LEDS 72  // Change this value to match the number of LEDs in your strip
#define DATA_PIN D1   // Change this value to match the GPIO pin connected to the LED data pin
extern int player_counter;
extern int broj;
extern int tempp;
extern bool dice;
extern bool playerc;
extern bool selected;
extern int active[4];
extern int new_position;
extern int win;
extern int pl;
extern int coun;
//extern int player_count;
extern int selectedPiece;
extern int playerPosition;
extern int playerpass0[4][4];
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
