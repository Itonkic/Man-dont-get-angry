#include <time.h>
#include "functions.h"
#include <stdlib.h>
#include "globals.h"

int player_counter = 0;
int active[] = { 0, 0, 0, 0 };
int tempp = 0;
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

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  pinMode(BUTTON3_PIN, INPUT_PULLUP);
  pinMode(BUTTON4_PIN, INPUT_PULLUP);
  pinMode(BUTTON5_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON1_PIN), button1ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON2_PIN), button2ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON3_PIN), button3ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON4_PIN), button4ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON5_PIN), button5ISR, FALLING);
  /*find how many players will be playing*/
  ledstart();
  while (player_counter == 0) {
    //player_count4();
    Serial.print("");
  }
  /*find which player goes first*/
  
  currentPlayer = determineStartingPlayer();
  Serial.print("Player ");
  Serial.print(currentPlayer);
  Serial.print(" starts the game with the highest roll: ");
  Serial.println(highestRoll);
  /*first roll 3 times*/
  baseboard();
  for (int i = 0; i < player_counter; i++) {
    playerfirstTurn(currentPlayer, 3);
    currentPlayer = currentPlayer + 1;
    if (currentPlayer == player_counter) {
      Serial.println("ASDALKSDFHKSLDGH");
      currentPlayer = 0;
    }
    delay(1000);  // Add a small delay between players' turns (optional)
  }
  lcd.begin();
}

void loop() {
  while (!checkwin()) {
    qsor();
    //baseboard();
    for (int i = 0; i <= 3; i++) {
      Serial.print("Player no: ");
      Serial.println(i);
      for (int k = 0; k <= 3; k++) {
        Serial.print(" Player figure: ");
        Serial.print(k);
        Serial.print("Position: ");
        Serial.println(playerPositions[i][k]);
      }
    }
    delay(1000);
    Serial.print("current player: ");
    Serial.print(currentPlayer);
    Serial.print(" playable figures: ");
    Serial.println(playablefigures[currentPlayer]);
    if (active_figures(currentPlayer) >= 1) {
      Serial.print("PlayerTurn()");
      coun = 1;
      int tempp = 0;
      playerTurn(currentPlayer, true, false);
      delay(1000);  // Add a small delay between players' turns (optional)
    } else {
      playerfirstTurn(currentPlayer, 1);
    }
    currentPlayer += 1;
    if (currentPlayer == player_counter) {
      currentPlayer = 0;
    }
  }
}
