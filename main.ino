#include <time.h>
#include "functions.h"
#include <stdlib.h>
#include "globals.h"
int player_counter = 0;

int broj = 0;
int playerPosition = 0;
int selectedPiece = -1;
int currentPlayer = 0;  // Index of the current player
bool defined_first = false;
const int numPiecesPerPlayer = 4;  // You can change this value according to your game
int dice_roll = 0;
volatile int buttonValue = 0;
int highestRoll = 0;
int startingPlayer = 0;
bool flag = true;

//#include <FastLED.h>
#define NUM_LEDS 30  // Change this value to match the number of LEDs in your strip
#define LED_PIN D0   // Change this value to match the GPIO pin connected to the LED data pin

//CRGB leds[NUM_LEDS];
void setup() {
  randomSeed(analogRead(0));
  Serial.begin(9600);
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  /* pinMode(BUTTON2_PIN, INPUT_PULLUP);
  pinMode(BUTTON3_PIN, INPUT_PULLUP);
  pinMode(BUTTON4_PIN, INPUT_PULLUP);
  pinMode(BUTTON5_PIN, INPUT_PULLUP);*/
  attachInterrupt(digitalPinToInterrupt(BUTTON1_PIN), button1ISR, FALLING);
  /* attachInterrupt(digitalPinToInterrupt(BUTTON2_PIN), button2ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON3_PIN), button3ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON4_PIN), button4ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON5_PIN), button5ISR, FALLING);*/
  // Show the initial LED strip with the game board
  //  FastLED.show();
  /*find how many players will be playing*/
  while (player_counter == 0) {
    // attachInterrupt(digitalPinToInterrupt(BUTTON1_PIN), player_count2, FALLING);
    //   attachInterrupt(digitalPinToInterrupt(BUTTON1_PIN), player_count3, FALLING);
    player_count4();
    attachInterrupt(digitalPinToInterrupt(BUTTON1_PIN), player_count4, FALLING);
  }

  /*find which player goes first*/
  currentPlayer = determineStartingPlayer();
  Serial.print("Player ");
  Serial.print(currentPlayer);
  Serial.print(" starts the game with the highest roll: ");
  Serial.println(highestRoll);
  /*first roll 3 times*/

  for (int i = 0; i < player_counter; i++) {
    //  Serial.print("Player :");Serial.println(currentPlayer);Serial.println(player_counter);
    playerfirstTurn(currentPlayer);
    //   Serial.print("Trenutni player:");Serial.println(currentPlayer);
    currentPlayer = currentPlayer + 1;
    /*   Serial.print("Player + 1 :");Serial.println(currentPlayer);
    Serial.print("player counter: ");Serial.println(player_counter);
    Serial.print("for count "); Serial.println(i);*/
    if (currentPlayer == player_counter) {
      Serial.println("ASDALKSDFHKSLDGH");
      currentPlayer = 0;
    }
    delay(1000);  // Add a small delay between players' turns (optional)
  }
}

void loop() {
  qsor();
  while(!checkwin()){
  for (int i = 0; i <= 3; i++) {
    //for (int k = 0; k <= 3; k++) {
    Serial.print("Player no: ");
    Serial.print(i);
    // Serial.print(" Player figure: ");
    //   Serial.print(k);
    Serial.print("Position: ");
    Serial.println(playerPositions[i][0]);
    //   }
  }
  //Serial.println(playerPositions[currentPlayer][0]);
  for (int i = 0; i < player_counter; i++) {
    //updateLEDStrip();
    Serial.print("current player: ");
    Serial.print(currentPlayer);
    Serial.print(" playable figures: ");
    Serial.println(playablefigures[currentPlayer]);

    if (playablefigures[currentPlayer] >= 1) {
      playerTurn(currentPlayer);
      if (dice_roll == 6) {
        currentPlayer = currentPlayer;
      } else {
        currentPlayer = currentPlayer + 1;
      }
      delay(1000);  // Add a small delay between players' turns (optional)
    } else {
      nofigures(currentPlayer);
      if (dice_roll == 6) {
        currentPlayer = currentPlayer;
      } else {
        currentPlayer = currentPlayer + 1;
      }
    }
    if (currentPlayer == player_counter && dice_roll != 6) {
      currentPlayer = 0;
    }
    

    }
  }
}
