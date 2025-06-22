# README.md

## Tic Tac Toe Game

This project is a console-based implementation of the classic Tic Tac Toe game. It allows players to compete against each other or against an AI opponent that uses the minimax algorithm to make optimal moves. The game also keeps track of scores across multiple sessions.

### Features

- Play against an AI or another player.
- Score tracking for wins and draws.
- User-friendly console interface.
- Input validation for player moves.

### Requirements

- C++ compiler (e.g., g++, clang++)
- Standard C++ library

### Installation

1. **Clone the repository**:
   ```bash
   git clone <repository-url>
   cd <repository-directory>
   ```

2. **Compile the code**:
   Use the following command to compile the program:
   ```bash
   g++ -o tic_tac_toe normal.cpp
   ```

### Usage

Run the compiled executable:
```bash
./tic_tac_toe
```

### Controls

- Choose the game mode:
  - **1**: Single Player (You vs AI)
  - **2**: Two Player (Player X vs Player O)
- Enter your move in the format `row column` (e.g., `1 2` for row 1, column 2).
- The game will display the current board after each move.
- After the game ends, you can choose to play again or exit.

### Game Logic

- The game board is represented as a 3x3 grid.
- Players take turns to place their marks (X or O) on the board.
- The game checks for a winner after each move and announces the result.
- If the board is full and there is no winner, the game declares a draw.

### AI Logic

The AI opponent uses the minimax algorithm to evaluate the best possible move. It assigns scores to potential game states and chooses the move that maximizes its chances of winning while minimizing the player's chances.

### Score Tracking

The game keeps track of the number of wins for each player and the number of draws. Scores are saved to a file (`scores.txt`) and loaded at the start of each game session.

### Code Overview

- **Main Functions**:
  - `intialize_board()`: Initializes the game board.
  - `display_board()`: Displays the current state of the board.
  - `get_player_move()`: Prompts the player for their move.
  - `update_board()`: Updates the board with the player's move.
  - `check_win()`: Checks for a winner.
  - `minimax()`: Implements the minimax algorithm for the AI's decision-making.
  - `load_scores()` and `save_scores()`: Load and save game scores.

### License

This project is open-source and available for modification and distribution. Enjoy playing Tic Tac Toe!