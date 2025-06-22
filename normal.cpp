#include <iostream>
#include <utility>
#include <fstream>
#include <limits>
using namespace std;

const int SIZE = 3;

void intialize_board(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = ' ';
}

void display_board(char board[SIZE][SIZE]) {
    cout << "+----+---+---+\n";
    for (int i = 0; i < SIZE; i++) {
        cout << "| ";
        for (int j = 0; j < SIZE; j++)
            cout << board[i][j] << " | ";
        cout << "\n";
    }
    cout << "+---+---+---+\n";
}

pair<int, int> get_player_move() {
    int row, col;
    bool valid_input = false;
    while (!valid_input) {
        cout << "Enter your move (1-3,1-3): (row column): ";
        cin >> row >> col;
        if (cin.fail() || row < 1 || row > 3 || col < 1 || col > 3) {
            cout << "Invalid input. Try again.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        valid_input = true;
    }
    return make_pair(row, col);
}

void switch_turn(char &current_player) {
    current_player = (current_player == 'X') ? 'O' : 'X';
}

bool update_board(int row, int col, char board[SIZE][SIZE], char current_player) {
    if (row < 1 || row > 3 || col < 1 || col > 3 || board[row - 1][col - 1] != ' ')
        return false;
    board[row - 1][col - 1] = current_player;
    return true;
}

char check_row_win(const char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return board[i][0];
    return ' ';
}

char check_column_win(const char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return board[0][i];
    return ' ';
}

char check_diagonal_win(const char board[SIZE][SIZE]) {
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return board[0][0];
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return board[0][2];
    return ' ';
}

char check_win(const char board[SIZE][SIZE]) {
    char winner = check_row_win(board);
    if (winner == ' ') winner = check_column_win(board);
    if (winner == ' ') winner = check_diagonal_win(board);
    return winner;
}

bool is_board_full(const char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] == ' ') return false;
    return true;
}

void print_draw() {
    cout << "It's a draw!\n";
}

int evaluate(const char board[SIZE][SIZE]) {
    char winner = check_win(board);
    if (winner == 'O') return +10;
    if (winner == 'X') return -10;
    return 0;
}

int minimax(char board[SIZE][SIZE], int depth, bool isMax) {
    int score = evaluate(board);
    if (score == 10 || score == -10 || is_board_full(board)) return score;

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    best = max(best, minimax(board, depth + 1, false));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    best = min(best, minimax(board, depth + 1, true));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

pair<int, int> get_ai_move(char board[SIZE][SIZE]) {
    int bestVal = -1000;
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                int moveVal = minimax(board, 0, false);
                board[i][j] = ' ';
                if (moveVal > bestVal) {
                    bestMove = {i + 1, j + 1};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

void load_scores(int &x_wins, int &o_wins, int &draws) {
    ifstream infile("scores.txt");
    if (infile >> x_wins >> o_wins >> draws) {
        cout << "\nPrevious scores loaded.\n";
    } else {
        x_wins = o_wins = draws = 0;
    }
}

void save_scores(int x_wins, int o_wins, int draws) {
    ofstream outfile("scores.txt");
    outfile << x_wins << " " << o_wins << " " << draws << endl;
}

int main() {
    int x_wins = 0, o_wins = 0, draws = 0;
    load_scores(x_wins, o_wins, draws);

    int game_mode = 0;
    while (game_mode != 1 && game_mode != 2) {
        cout << "Choose Game Mode:\n";
        cout << "1. Single Player (You vs AI)\n";
        cout << "2. Two Player (Player X vs Player O)\n";
        cout << "Enter 1 or 2: ";
        cin >> game_mode;
        if (cin.fail() || (game_mode != 1 && game_mode != 2)) {
            cout << "Invalid input. Please enter 1 or 2.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }

    while (true) {
        char board[SIZE][SIZE];
        intialize_board(board);
        char current_player = 'X';
        char winner = ' ';

        while (true) {
            display_board(board);
            cout << "Current Player: " << current_player << "\n";
            pair<int, int> player_move;

            if (game_mode == 1 && current_player == 'O') {
                cout << "AI is thinking...\n";
                player_move = get_ai_move(board);
            } else {
                player_move = get_player_move();
            }

            if (!update_board(player_move.first, player_move.second, board, current_player)) {
                cout << "Invalid move. Try again.\n";
                continue;
            }

            winner = check_win(board);
            if (winner != ' ') {
                display_board(board);
                cout << "Player " << winner << " wins!\n";
                if (winner == 'X') x_wins++;
                else o_wins++;
                break;
            }

            if (is_board_full(board)) {
                display_board(board);
                print_draw();
                draws++;
                break;
            }

            switch_turn(current_player);
        }

        save_scores(x_wins, o_wins, draws);

        cout << "\n\U0001F3C6 Scoreboard:\n";
        cout << "Player X: " << x_wins << "\n";
        if (game_mode == 1)
            cout << "AI (Player O): " << o_wins << "\n";
        else
            cout << "Player O: " << o_wins << "\n";
        cout << "Draws: " << draws << "\n";

        char choice;
        cout << "\nWould you like to play again? (y/n): ";
        cin >> choice;
        if (choice != 'y' && choice != 'Y') {
            cout << "\nThanks for playing!\n";
            break;
        }
        system("clear");
    }
    return 0;
}
