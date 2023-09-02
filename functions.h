#include "globals.h"
//int player_counter = 0;  // Define the global variable
#include <WS2812B.h>
#include <LiquidCrystal_I2C.h>
int new_position = 0;
bool playerc = 0;
int coun = 1;
bool dice = true;
bool selected = false;
int temp = 0;
#include <Arduino.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
WS2812B strip = WS2812B(NUM_LEDS);
//CRGB //leds[NUM_//leds];
int playerPositions[4][4] = {
  { -1, -1, -1, -1 },
  { -1, -1, -1, -1 },
  { -1, -1, -1, -1 },
  { -1, -1, -1, -1 }
};
int playerpass0[4][4] = {
  { 0, 0, 0, 0 },
  { 0, 0, 0, 0 },
  { 0, 0, 0, 0 },
  { 0, 0, 0, 0 }
};
int playablefigures[] = { 0, 0, 0, 0 };
int search[2] = {};
int win = 0;

int roll_dice() {
  int dice_roll = random(1, 7);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("The random roll is: ");
  lcd.setCursor(0, 1);
  lcd.print(dice_roll);
  flag = true;
  delay(1000);
  return dice_roll;
}
int pl = 4;

void button1ISR() {
  selectedPiece = 0;
}
void  button2ISR() {
  selectedPiece = 1;
  if (playerc == 0) {
    player_counter = 2;
    pl = 2;
    playerc = 1;
    return;
  }
}

void button3ISR() {
  selectedPiece = 2;
  if (playerc == 0) {
    player_counter = 3;
    pl = 3;
    playerc = 1;
    return;
  }
}
void button4ISR() {
  selectedPiece = 3;
  if (playerc == 0) {
    player_counter = 4;
    pl = 4;
    playerc = 1;
    return;
  }
}
void button5ISR() {
  selectedPiece = -10;
}
int compare(const void *a, const void *b) {
  return (*(int *)b - * (int *)a);
}
void ledstart() {
  lcd.begin();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Select player");
  lcd.setCursor(0, 1);
  lcd.print("count");
  strip.begin();// Sets up the SPI
  strip.show();
}
void baseboard() {
  strip.setPixelColor(0,  strip.Color(0, 0, 5 ));
  strip.setPixelColor(52, strip.Color(0, 0, 5 ));
  strip.setPixelColor(53, strip.Color(0, 0, 5 ));
  strip.setPixelColor(54, strip.Color(0, 0, 5 ));
  strip.setPixelColor(55, strip.Color(0, 0, 5 ));

  strip.setPixelColor(14, strip.Color(5, 0, 0 ));
  strip.setPixelColor(10, strip.Color(5, 0, 0 ));
  strip.setPixelColor(11, strip.Color(5, 0, 0 ));
  strip.setPixelColor(12, strip.Color(5, 0, 0 ));
  strip.setPixelColor(13, strip.Color(5, 0, 0 ));

  strip.setPixelColor(28, strip.Color(5, 5, 0 ));
  strip.setPixelColor(24, strip.Color(5, 5, 0 ));
  strip.setPixelColor(25, strip.Color(5, 5, 0 ));
  strip.setPixelColor(26, strip.Color(5, 5, 0 ));
  strip.setPixelColor(27, strip.Color(5, 5, 0 ));

  strip.setPixelColor(42, strip.Color(0, 5, 0 ));
  strip.setPixelColor(38, strip.Color(0, 5, 0 ));
  strip.setPixelColor(39, strip.Color(0, 5, 0 ));
  strip.setPixelColor(40, strip.Color(0, 5, 0 ));
  strip.setPixelColor(41, strip.Color(0, 5, 0 ));
  delay(250);
  strip.show();
}
void qsor() {
  for (int i = 0; i < player_counter; i++) {
    int n = 4;
    qsort(playerPositions[i], n, sizeof(int), compare);
  }
}

int determineStartingPlayer() {
  for (int i = 0; i < player_counter; i++) {
    int roll = roll_dice();
    if (roll > highestRoll) {
      highestRoll = roll;
      startingPlayer = i;
    }
    delay(1000);
  }
  return startingPlayer;
}
int active_figures(int playerId) {
  playablefigures[playerId] = 0;
  for (int j = 0; j < 4; j++) {
    if (playerPositions[playerId][j] != -1) {
      playablefigures[playerId] += 1;
    }
  }
  return playablefigures[playerId];
}
void playerled() {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0 ) );
  }
  baseboard();
  for (int i = 0; i < pl; i++) {
    for (int j = 0; j < 4; j++) {
      if (playerPositions[i][j] != -1) {
        if (i == 0) {
          strip.setPixelColor(playerPositions[i][j],  strip.Color(0, 0, 50 ));
        } else if (i == 1) {
          strip.setPixelColor(playerPositions[i][j], strip.Color(50, 0, 0 ));
        } else if (i == 2) {
          strip.setPixelColor(playerPositions[i][j], strip.Color(50, 50, 0 ));
        } else if (i == 3) {
          strip.setPixelColor(playerPositions[i][j], strip.Color(0, 50, 0 ));
        }
      }
    }

  }
  for (uint16_t i = 56; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0 ) );
  }
  for (int i = 0; i < pl; i++) {
    for (int j = 0; i < 4; j++) {
      if (i == 0) {
        for (int k = 56; k < 60 - playablefigures[i]; k++) {
          strip.setPixelColor(k, strip.Color(0, 0, 50 ));
          if (k == 60 - playablefigures[i]-1) {
            i++;
            break;
          }
        }
      } else if (i == 1) {
        for (int qq = 60; qq < 64 - playablefigures[i]; qq++) {
          strip.setPixelColor(qq, strip.Color(50, 0, 0)); 
          if (qq == 64 - playablefigures[i]-1) {
            i++;
            break;
          }
        }
      } else if (i == 2) {
        for (int qw = 64; qw < 68 - playablefigures[i]; qw++) {
          strip.setPixelColor(qw, strip.Color(50, 50, 0)); 
          if (qw == 68 - playablefigures[i]-1) {
            i++;
            break;
          }
        }
      } else if (i == 3) {
        for (int we = 68; we < 72 - playablefigures[i]; we++) {
          strip.setPixelColor(we, strip.Color(0, 50, 0 ));
          if (we == 72 - playablefigures[i]-1) {
            i++;
            break;
          }
        }
      }

    }
  }
  delay(100);
  strip.show();
}

void playerfirstTurn(int playerId, int attempts) {
  int position = 0;
  char message[20];
  // Check if the player has attempts left
  while (attempts > 0) {
    // Simulate rolling a dice (assuming a 6-sided dice)
    dice_roll = roll_dice();  // Generate a random number between 1 and 6
    // Check if the player got a "six"
    if (dice_roll == 6) {
      selectedPiece = 0;
      // Place one piece on START
      // Roll the dice again
      if (playerId == 0) {
        playablefigures[playerId] = 1;
        playerPositions[playerId][selectedPiece] = 0;
      } else if (playerId == 1) {
        playablefigures[playerId] = 1;
        playerPositions[playerId][selectedPiece] = 14;
      } else if (playerId == 2) {
        playablefigures[playerId] = 1;
        playerPositions[playerId][selectedPiece] = 28;
        strip.setPixelColor(playerPositions[playerId][selectedPiece], strip.Color(50, 50, 0));
        delay(111);
        strip.show();
      } else if (playerId == 3) {
        playablefigures[playerId] = 1;
        playerPositions[playerId][selectedPiece] = 42;
      }
      dice_roll = roll_dice();
      // Move the piece as many spaces as the dice shows
      playerPositions[playerId][selectedPiece] += dice_roll;
      break;  // Exit the loop since the player got a "six"
    } else {
      playerPositions[playerId][selectedPiece] = -1;
    }
    active_figures(playerId);
    attempts--;  // Reduce the number of attempts by 1
  }
  playerled();
}
void searchInArray(int playerId, int new_position) {
  for (int i = 0; i < pl; i++) {
    for (int j = 0; j < 4; j++) {
      if (playerPositions[i][j] == new_position && i != playerId) {
        search[0] = i;  // Number found in the array
        search[1] = j;
      } else {
        search[0] = i;  // Number found in the array
        search[1] = j;
      }
    }
  }
}

boolean ispossible(int playerId, int dice_roll, int new_position) {
  // Ask the player to choose a piece to move
  bool possible = false;
  while (possible == 0) {
    if (playerId == 0) {
      if (new_position >= 56) {
        return false;
      }
      if (new_position >= 10 && new_position <= 13) {
        new_position += 4;
      } else if (new_position >= 24 && new_position <= 27) {
        new_position += 4;
      } else if (new_position >= 38 && new_position <= 41) {
        new_position += 4;
      } else if (new_position >= 52 && new_position <= 55) {
        //finnishing condition
        bool collision = false;
        for (int i = 0; i < 4; ++i) {
          if (new_position >= playerPositions[playerId][0] && i != selectedPiece) {
            collision = true;
            selectedPiece = 5;
            //molimo izaberite drugu figuru
            return false;
            break;
          } else {
            playerPositions[playerId][selectedPiece] = new_position;
            return true;
          }
        }
      }
    } else if (playerId == 1) {

      if (playerPositions[playerId][selectedPiece] < 14 && playerPositions[playerId][selectedPiece] != -1) {
        playerpass0[playerId][selectedPiece] = 1;
      }
      if (playerpass0[playerId][selectedPiece] == 1 && new_position > 13) {
        return false;
      }
      if (new_position >= 10 && new_position <= 13) {
        //finnishing condition
        bool collision = false;
        for (int i = 0; i < 4; ++i) {
          if (new_position >= playerPositions[playerId][i] && i != selectedPiece) {
            collision = true;
            possible = false;
            selectedPiece = 5;
            //molimo izaberite drugu figuru
            return false;
            break;
          } else {
            playerPositions[playerId][selectedPiece] = new_position;
            return true;
          }
        }
      } else if (new_position >= 24 && new_position <= 27) {
        new_position += 4;
      } else if (new_position >= 38 && new_position <= 41) {
        new_position += 4;
      } else if (new_position >= 52 && new_position <= 55) {
        new_position = new_position - 51;
      }
    } else if (playerId == 2) {
      if (playerPositions[playerId][selectedPiece] < 28 && playerPositions[playerId][selectedPiece] != -1) {
        playerpass0[playerId][selectedPiece] = 1;
      }
      if (playerpass0[playerId][selectedPiece] == 1 && new_position > 27) {
        return false;
      }
      if (new_position >= 10 && new_position <= 13) {
        new_position += 4;
      } else if (new_position >= 24 && new_position <= 27) {
        //finnishing condition
        bool collision = false;
        for (int i = 0; i < 4; ++i) {
          if (new_position >= playerPositions[playerId][0] && i != selectedPiece) {
            collision = true;
            selectedPiece = 5;
            return false;
            break;
            //molimo izaberite drugu figuru
          } else {
            playerPositions[playerId][selectedPiece] = new_position;
            return true;
          }
        }
      } else if (new_position >= 38 && new_position <= 41) {
        new_position += 4;
      } else if (new_position >= 52 && new_position <= 55) {  //prepraviti iza izlaza
        new_position = new_position - 51;
      }
    } else if (playerId == 3) {
      if (playerPositions[playerId][selectedPiece] < 42 && playerPositions[playerId][selectedPiece] != -1) {
        playerpass0[playerId][selectedPiece] = 1;
      }
      if (playerpass0[playerId][selectedPiece] == 1 && new_position > 41) {
        return false;
      }
      if (new_position >= 10 && new_position <= 13) {
        new_position += 4;
      } else if (new_position >= 24 && new_position <= 27) {
        new_position += 4;
      } else if (new_position >= 38 && new_position <= 41) {
        //finnishing condition
        bool collision = false;
        for (int i = 0; i < 4; ++i) {
          if (new_position >= playerPositions[playerId][0] && i != selectedPiece) {
            collision = true;
            selectedPiece = 5;
            return false;
            break;
            //molimo izaberite drugu figuru
          } else {
            playerPositions[playerId][selectedPiece] = new_position;
            return true;
          }
        }
      } else if (new_position >= 52 && new_position <= 55) {
        new_position = new_position - 51;
      }
    }
    if (new_position >= 55) {  //&& playerId != 3) {
      new_position = new_position - 55;
    }
    int coun = 0;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (playerPositions[i][j] == new_position && i == playerId && playerPositions[i][j] != -1) {
          printf("moj moj moj moj moj moj ");
          return false;
        } else if (playerPositions[i][j] == new_position && playerPositions[i][j] != -1) {
          playerPositions[i][j] = -1;
          playerPositions[playerId][selectedPiece] = new_position;
          return true;
        } else if (playerPositions[i][j] != new_position) {
          coun = coun + 1;
        }
      }
    }
    if (coun == 16) {
      playerPositions[playerId][selectedPiece] = new_position;
      return true;
    }

  }
  return true;
}
bool checkwin() {
  win = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (playerPositions[i][j] != -1) {
        int win = win + 1;
      }
    }
  }
  if (win == 4) {
    return true;
  } else {
    return false;
  }
}


void new_player(int playerId, int new_position) {
  for (int i = 0; i < pl; i++) {
    for (int j = 0; j < 4; j++) {
      if (playerPositions[i][j] == new_position) {
        if (!playerPositions[playerId][j] == new_position) {
          search[0] = i;  // Number found in the array
          search[1] = j;
        } else {
          playerPositions[i][j] = -1;
          playerPositions[playerId][selectedPiece] = new_position;
        }
      } else {
        search[0] = -1;  // Number found in the array
        search[1] = -1;
        playerPositions[playerId][selectedPiece] = new_position;
        temp += 1;
      }
    }
  }
  playerled();
}
void playerTurn(int playerId, bool dice, bool selected) {
  delay(100);
  do {
    if (dice == 1) {
      dice_roll = roll_dice();  // Generate a random number between 1 and 6selectedPiece=-1;
    }
    if (dice_roll == 6) {
      coun += 1;
      //new or select
      if (selected == 0) {
        selectedPiece = -1;
        playerled();
        while (selectedPiece == -1) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("player ");
          lcd.print(playerId);
          lcd.print(" roll");
          lcd.print(dice_roll);
          lcd.setCursor(0, 1);
          lcd.print("Select figure");
          attachInterrupt(digitalPinToInterrupt(BUTTON1_PIN), button1ISR, FALLING);
          attachInterrupt(digitalPinToInterrupt(BUTTON2_PIN), button2ISR, FALLING);
          attachInterrupt(digitalPinToInterrupt(BUTTON3_PIN), button3ISR, FALLING);
          attachInterrupt(digitalPinToInterrupt(BUTTON4_PIN), button4ISR, FALLING);
          //new piece??
          delay(10);
        }
      }
      if (selectedPiece > playablefigures[playerId] - 1) {
        playablefigures[playerId] = playablefigures[playerId] + 1;
      }
    } else {
      if (selected == 0) {
        selectedPiece = -1;
        while (selectedPiece == -1 || selectedPiece > playablefigures[playerId] - 1) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("player ");
          lcd.print(playerId);
          lcd.print(" roll");
          lcd.print(dice_roll);
          lcd.setCursor(0, 1);
          lcd.print("Select figure");
          attachInterrupt(digitalPinToInterrupt(BUTTON1_PIN), button1ISR, FALLING);
          attachInterrupt(digitalPinToInterrupt(BUTTON2_PIN), button2ISR, FALLING);
          attachInterrupt(digitalPinToInterrupt(BUTTON3_PIN), button3ISR, FALLING);
          attachInterrupt(digitalPinToInterrupt(BUTTON4_PIN), button4ISR, FALLING);
          delay(10);
        }
      }
    }

    new_position = playerPositions[playerId][selectedPiece] + dice_roll;
    if (playerPositions[playerId][selectedPiece] == -1 && dice_roll == 6) {
      if (playerId == 0) {
        new_position = 0;
        new_player(playerId, new_position);
      } else if (playerId == 1) {
        new_position = 14;
        new_player(playerId, new_position);
      } else if (playerId == 2) {
        new_position = 28;
        new_player(playerId, new_position);
      } else if (playerId == 3) {
        new_position = 42;
        new_player(playerId, new_position);
      }
      playerled();
    } else {
      if (!ispossible(playerId, dice_roll, new_position)) {
        selectedPiece = -1;
        while (selectedPiece == -1 || selectedPiece > playablefigures[playerId] - 1 || selectedPiece != -10) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("player ");
          lcd.print(playerId);
          lcd.print(" roll");
          lcd.print(dice_roll);
          lcd.setCursor(0, 1);
          lcd.print("Select figure");
          selectedPiece = Serial.read();
          attachInterrupt(digitalPinToInterrupt(BUTTON1_PIN), button1ISR, FALLING);
          attachInterrupt(digitalPinToInterrupt(BUTTON2_PIN), button2ISR, FALLING);
          attachInterrupt(digitalPinToInterrupt(BUTTON3_PIN), button3ISR, FALLING);
          attachInterrupt(digitalPinToInterrupt(BUTTON4_PIN), button4ISR, FALLING);
          attachInterrupt(digitalPinToInterrupt(BUTTON5_PIN), button5ISR, FALLING);
        }
        if (selectedPiece == -10) {
          break;
        }
        if (dice_roll == 6) {
          selectedPiece = -1;
          while (selectedPiece == -1) {
            attachInterrupt(digitalPinToInterrupt(BUTTON1_PIN), button1ISR, FALLING);
            attachInterrupt(digitalPinToInterrupt(BUTTON2_PIN), button2ISR, FALLING);
            attachInterrupt(digitalPinToInterrupt(BUTTON3_PIN), button3ISR, FALLING);
            attachInterrupt(digitalPinToInterrupt(BUTTON4_PIN), button4ISR, FALLING);
            //attachInterrupt(digitalPinToInterrupt(BUTTON5_PIN), button5ISR, FALLING);
            delay(10);
          }

          if (selectedPiece > playablefigures[playerId] - 1) {
            playablefigures[playerId] = playablefigures[playerId] + 1;
          }
          playerTurn(currentPlayer, false, true);
        } else {
          Serial.flush();
          selectedPiece = -1;
          while (selectedPiece == -1 || selectedPiece > playablefigures[playerId] - 1) {
            attachInterrupt(digitalPinToInterrupt(BUTTON1_PIN), button1ISR, FALLING);
            attachInterrupt(digitalPinToInterrupt(BUTTON2_PIN), button2ISR, FALLING);
            attachInterrupt(digitalPinToInterrupt(BUTTON3_PIN), button3ISR, FALLING);
            attachInterrupt(digitalPinToInterrupt(BUTTON4_PIN), button4ISR, FALLING);
            delay(10);
          }
          playerTurn(currentPlayer, false, true);
        }
        if (selectedPiece == -10) {
          break;
        }
      }
      playerled();
    }
    playerled();
    dice_roll = 0;
    coun--;
  } while (coun > 0);
}
