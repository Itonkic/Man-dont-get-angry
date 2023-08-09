#include "globals.h"
//int player_counter = 0;  // Define the global variable
int new_position = 0;
int coun = 0;
int playerPositions[4][4] = {
  { -1, -1, -1, -1 },
  { -1, -1, -1, -1 },
  { -1, -1, -1, -1 },
  { -1, -1, -1, -1 }
};
int playablefigures[] = { 0, 0, 0, 0 };
int search[2] = {};
int win = 0;
int roll_dice() {
  int dice_roll = random(1, 7);
  Serial.print("The random roll is: ");
  Serial.println(dice_roll);
  flag = true;
  return dice_roll;
}
int pl = 0;
void IRAM_ATTR button1ISR() {
  selectedPiece = 0;
  Serial.println(selectedPiece);
  //dice_roll=roll_dice();
}
void IRAM_ATTR button2ISR() {
  selectedPiece = 1;
  Serial.println();
  Serial.println(selectedPiece);
}
void IRAM_ATTR button3ISR() {
  selectedPiece = 2;
  Serial.println(selectedPiece);
}
void IRAM_ATTR button4ISR() {
  selectedPiece = 3;
  Serial.println(selectedPiece);
}
void IRAM_ATTR player_count2() {
  player_counter = 2;
  pl = 2;
  Serial.println("BROJ igraca 2");
}
void IRAM_ATTR player_count3() {
  player_counter = 3;
  pl = 3;
  Serial.println("BROJ igraca 3");
}
void IRAM_ATTR player_count4() {
  player_counter = 4;
  pl = 4;
  Serial.println(" ");
  Serial.println("BROJ igraca 4");
}
void IRAM_ATTR button5ISR() {
}
int compare(const void *a, const void *b) {
  return (*(int *)b - *(int *)a);
}

void qsor() {
  for (int i = 0; i < player_counter; i++) {
    int n = 4;
    qsort(playerPositions[i], n, sizeof(int), compare);
    /*for (int k = 0; k < n; k++) {
        Serial.print(playerPositions[i][k]);
    }*/
    //Serial.println(" ");
  }

  /*
  for (int i = 0; i < player_counter; i++) {

    int n = sizeof(playerPositions[i]) / sizeof(playerPositions[0]);

    // Sorting the array in ascending order using qsort
    qsort(playerPositions[i], n, sizeof(int), compare);

    // Printing the sorted array
    for (int i = 0; i < n; i++) {
      Serial.println(playerPositions[0][i]);
    }
  }*/
}


int determineStartingPlayer() {
  for (int i = 0; i < player_counter; i++) {
    Serial.print("player number:");
    Serial.println(i);
    int roll = roll_dice();
    if (roll > highestRoll) {
      highestRoll = roll;
      startingPlayer = i;
    }
    delay(1000);
  }

  return startingPlayer;
}

void playerfirstTurn(int playerId, int attempts) {
  int position = 0;
  // Check if the player has attempts left
  while (attempts > 0) {
    // Simulate rolling a dice (assuming a 6-sided dice)
    dice_roll = roll_dice();  // Generate a random number between 1 and 6
    // Check if the player got a "six"
    if (dice_roll == 6) {
      // Place one piece on START
      if (playerId == 0) {
        Serial.println("if player 0");
        playablefigures[playerId] = 1;
        playerPositions[playerId][0] = 0;
      } else if (playerId == 1) {
        Serial.println("if player 1");
        playablefigures[playerId] = 1;
        playerPositions[playerId][0] = 14;
      } else if (playerId == 2) {
        Serial.println("if player 2");
        playablefigures[playerId] = 1;
        playerPositions[playerId][0] = 28;
      } else if (playerId == 3) {
        Serial.println("if player 3");
        playablefigures[playerId] = 1;
        playerPositions[playerId][0] = 42;
      }
      // Roll the dice again
      dice_roll = roll_dice();
      // Move the piece as many spaces as the dice shows
      playerPositions[playerId][0] += dice_roll;
      // Serial.print("player Id: "); Serial.print(playerId);
      Serial.print(" player position: ");
      Serial.println(playerPositions[playerId][0]);
      break;  // Exit the loop since the player got a "six"
    } else {
      // Serial.println("else");
      playerPositions[playerId][0] = -1;
    }
    attempts--;  // Reduce the number of attempts by 1
  }
}

//promjeniti <4
void searchInArray(int playerId, int new_position) {
  for (int i = 0; i < pl; i++) {
    for (int j = 0; j < 4; j++) {
      if (playerPositions[i][j] == new_position) {
        search[0] = i;  // Number found in the array
        search[1] = j;
        Serial.println("searchinarr1");
        Serial.println(new_position);
        Serial.println(playerPositions[i][j]);
      } else {
        search[0] = -1;  // Number found in the array
        search[1] = -1;
        Serial.println("searchinarr2");
        Serial.println(new_position);
        Serial.println(playerPositions[i][j]);
      }
    }
  }
}

int active_figures(int playerId) {
  playablefigures[playerId] = 0;
  for (int j = 0; j < 4; j++) {
    if (playerPositions[playerId][j] != -1) {
      playablefigures[playerId] += 1;
      Serial.println("active");
      Serial.println(playablefigures[playerId]);
    } else {
      Serial.println("active");
      Serial.println(playablefigures[playerId]);
    }
  }
  return playablefigures[playerId];
}


void ispossible(int playerId, int dice_roll, int new_position) {
  // Ask the player to choose a piece to move
  Serial.println("ASD");
  bool possible = false;
  while (possible == false) {
    if (new_position > 55 && dice_roll > 4) {
      new_position = new_position - 55;
    }
    if (playerId == 0) {
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
          if (new_position >= playerPositions[playerId][i]) {
            collision = true;
            selectedPiece = -1;
            //molimo izaberite drugu figuru
            break;
          }
        }
      }
    } else if (playerId == 1) {
      if (new_position >= 10 && new_position <= 13) {
        //finnishing condition
        bool collision = false;
        for (int i = 0; i < 4; ++i) {
          if (new_position >= playerPositions[playerId][i]) {
            collision = true;
            selectedPiece = -1;
            //molimo izaberite drugu figuru
            break;
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
      if (new_position >= 10 && new_position <= 13) {
        new_position += 4;
      } else if (new_position >= 24 && new_position <= 27) {
        //finnishing condition
        bool collision = false;
        for (int i = 0; i < 4; ++i) {
          if (new_position >= playerPositions[playerId][i]) {
            collision = true;
            selectedPiece = -1;
            break;
            //molimo izaberite drugu figuru
          }
        }
      } else if (new_position >= 38 && new_position <= 41) {
        new_position += 4;
      } else if (new_position >= 52 && new_position <= 55) {
        new_position = new_position - 51;
      }
    } else if (playerId == 3) {
      new_position = 42;
      if (new_position >= 10 && new_position <= 13) {
        new_position += 4;
      } else if (new_position >= 24 && new_position <= 27) {
        new_position += 4;
      } else if (new_position >= 38 && new_position <= 41) {
        //finnishing condition
        bool collision = false;
        for (int i = 0; i < 4; ++i) {
          if (new_position >= playerPositions[playerId][i]) {
            collision = true;
            selectedPiece = -1;
            break;
            //molimo izaberite drugu figuru
          }
        }
      } else if (new_position >= 52 && new_position <= 55) {
        new_position = new_position - 51;
      }
    }
    if (new_position >= 55) {
      new_position = new_position - 55;
    }

    searchInArray(playerId, new_position);
    if (search[0] == playerId) {
      Serial.println(new_position);
      Serial.println("found same ID");
      selectedPiece = -1;
    } else {
      Serial.println(new_position);
      Serial.println("found different ID");
      Serial.println("found id search[0] with piece search[1]");
      //change pieces
      playerPositions[search[0]][search[1]] = -1;
      playerPositions[playerId][selectedPiece] = new_position;
      playablefigures[search[0]] -= 1;
      //  return true;
    }
  }
  //return true;
}
bool checkwin() {
  Serial.println("ASD");
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
  searchInArray(playerId, new_position);
  if (search[0] == playerId) {
    Serial.println(new_position);
    Serial.println("found same ID");
    selectedPiece = -1;
  } else {
    Serial.println(new_position);
    Serial.println("found different ID");
    Serial.println("found id search[0] with piece search[1]");
    //change pieces
    playerPositions[search[0]][search[1]] = -1;
    playerPositions[playerId][selectedPiece] = new_position;
    playablefigures[search[0]] -= 1;
  }
}

void playerTurn(int playerId) {
  while (coun>0) {
  dice_roll = roll_dice();  // Generate a random number between 1 and 6selectedPiece=-1;
  if (dice_roll == 6) {
    coun += 1;
  }
  while (selectedPiece < 0 || selectedPiece >= 4) {
    //select to move or new figure
    attachInterrupt(digitalPinToInterrupt(BUTTON1_PIN), button1ISR, FALLING);
    Serial.print(" ");
  }
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
  } else {
    ispossible(playerId, dice_roll, new_position);
    //new_position = playerPositions[playerId][selectedPiece] + dice_roll;
  }
  coun--;
}
}
