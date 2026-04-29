# README.md

# 🎮 Tic Tac Toe with AI (Minimax)

A console-based Tic Tac Toe game built in C++ featuring an **unbeatable AI powered by the Minimax algorithm**. The game supports both single-player (vs AI) and two-player modes, along with persistent score tracking across sessions.

##  Highlights
-  Optimal AI using Minimax (never loses)
-  Dual modes: Player vs AI / Player vs Player
-  Persistent score tracking using file storage
-  Robust input validation and clean CLI interaction

### Features

- Play against an AI or another player.
- Score tracking for wins and draws.
- Clean and intuitive command-line interface.
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

##  How the AI Works

The AI uses the Minimax algorithm to evaluate all possible game states recursively. It assigns scores based on outcomes:

- Win → +1  
- Loss → -1  
- Draw → 0  

By simulating every possible move, the AI always chooses the optimal strategy, making it impossible to defeat. 

### Score Tracking

The game keeps track of the number of wins for each player and the number of draws. Scores are saved to a file (`scores.txt`) and loaded at the start of each game session.

## 📸 Sample Output
*Screenshot coming soon*

### Code Overview

- **Main Functions**:
  - `initialize_board()`: Initialises the game board.
  - `display_board()`: Displays the current state of the board.
  - `get_player_move()`: Prompts the player for their move.
  - `update_board()`: Updates the board with the player's move.
  - `check_win()`: Checks for a winner.
  - `minimax()`: Implements the minimax algorithm for the AI's decision-making.
  - `load_scores()` and `save_scores()`: Load and save game scores.

 
### License

This project is open-source and available for modification and distribution. Enjoy playing Tic Tac Toe!
