#include <bits/stdc++.h>
using namespace std;

char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};

char current_marker;
int current_player;

void drawboard() {
  cout << " " << board[0][0] << "|" << board[0][1] << "|" << board[0][2] << endl;
  cout << "__________\n";
  cout << " " << board[1][0] << "|" << board[1][1] << "|" << board[1][2] << endl;
  cout << "__________\n";
  cout << " " << board[2][0] << "|" << board[2][1] << "|" << board[2][2] << endl;
}

bool placeholder(int slot) {
  int row = slot / 3;
  int col;
  if (slot % 3 == 0) {
    row = row - 1;
    col = 2;
  } else {
    col = (slot % 3) - 1;
  }
  if (board[row][col] != 'X' && board[row][col] != 'O') {
    board[row][col] = current_marker;
    return true;
  } else {
    return false;
  }
}

char winner() {
  for (int i = 0; i < 3; i++) {
    // rows
    if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
      return current_player;
    }
    // col
    if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
      return current_player;
    }
  }
  if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
    return current_player;
  }
  if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
    return current_player;
  }
  return 0;
}

void swap_players_and_marker() {
  if (current_marker == 'X') {
    current_marker = 'O';
  } else {
    current_marker = 'X';
  }
  if (current_player == 1) {
    current_player = 2;
  } else {
    current_player = 1;
  }
}

void game() {
  cout << "Player one, choose your marker : ";
  char marker_pl;
  cin >> marker_pl;
  current_player = 1;
  current_marker = marker_pl;
  drawboard();
  int player_won;
  for (int i = 0; i < 9; i++) {
    cout << "it's a player" << current_player << "'s slot. Enter your slot :";
    int slot;
    cin >> slot;
    if (slot < 1 || slot > 9) {
      cout << "That slot is invalid! Try Another Slot";
      i--;
      continue;
    }
    if (!placeholder(slot)) {
      cout << "That slot occupied! Try Another Slot";
      i--;
      continue;
    }
    drawboard();
    player_won = winner();
    if (player_won == 1) {
      cout << "player one won! congratulations";
      break;
    }
    if (player_won == 2) {
      cout << "player Two won! congratulations";
      break;
    }
    swap_players_and_marker();
  }
  if (player_won == 0) {
    cout << "That is a tie game!";
  }
}

int main() {
  game();
  return 0;
}
