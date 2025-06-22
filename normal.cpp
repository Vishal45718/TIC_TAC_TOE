#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;
const int CELL_SIZE = 200;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
char board[3][3];
bool running = true;
char currentPlayer = 'X';
char winner = ' ';
bool gameOver = false;
SDL_Rect replayButton = {200, 500, 200, 50};

void clearBoard() {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            board[i][j] = ' ';
    currentPlayer = 'X';
    winner = ' ';
    gameOver = false;
}

void drawGrid() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int i = 1; i <= 2; ++i) {
        SDL_RenderDrawLine(renderer, i * CELL_SIZE, 0, i * CELL_SIZE, SCREEN_HEIGHT);
        SDL_RenderDrawLine(renderer, 0, i * CELL_SIZE, SCREEN_WIDTH, i * CELL_SIZE);
    }
}

void drawCircle(int cx, int cy, int radius) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    for (int angle = 0; angle < 360; angle++) {
        int x = cx + radius * cos(angle * M_PI / 180);
        int y = cy + radius * sin(angle * M_PI / 180);
        SDL_RenderDrawPoint(renderer, x, y);
    }
}

void drawMarks() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int x = j * CELL_SIZE;
            int y = i * CELL_SIZE;
            if (board[i][j] == 'X') {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderDrawLine(renderer, x + 40, y + 40, x + CELL_SIZE - 40, y + CELL_SIZE - 40);
                SDL_RenderDrawLine(renderer, x + CELL_SIZE - 40, y + 40, x + 40, y + CELL_SIZE - 40);
            } else if (board[i][j] == 'O') {
                drawCircle(x + CELL_SIZE / 2, y + CELL_SIZE / 2, CELL_SIZE / 2 - 40);
            }
        }
    }
}

char checkWinner() {
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) return board[i][0];
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) return board[0][i];
    }
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) return board[0][0];
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) return board[0][2];
    return ' ';
}

bool isBoardFull() {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i][j] == ' ') return false;
    return true;
}

int evaluate() {
    char result = checkWinner();
    if (result == 'O') return +10;
    if (result == 'X') return -10;
    return 0;
}

int minimax(bool isMax) {
    int score = evaluate();
    if (score == 10 || score == -10 || isBoardFull()) return score;

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    best = std::max(best, minimax(false));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    best = std::min(best, minimax(true));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

void aiMove() {
    int bestVal = -1000;
    int bestRow = -1, bestCol = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                int moveVal = minimax(false);
                board[i][j] = ' ';
                if (moveVal > bestVal) {
                    bestVal = moveVal;
                    bestRow = i;
                    bestCol = j;
                }
            }
        }
    }

    board[bestRow][bestCol] = 'O';
    winner = checkWinner();
    if (winner != ' ' || isBoardFull()) gameOver = true;
    currentPlayer = 'X';
}

void handleClick(int x, int y) {
    if (gameOver) {
        if (x >= replayButton.x && x <= replayButton.x + replayButton.w &&
            y >= replayButton.y && y <= replayButton.y + replayButton.h) {
            clearBoard();
        }
        return;
    }

    int row = y / CELL_SIZE;
    int col = x / CELL_SIZE;
    if (board[row][col] == ' ') {
        board[row][col] = 'X';
        winner = checkWinner();
        if (winner != ' ' || isBoardFull()) gameOver = true;
        else {
            currentPlayer = 'O';
            aiMove();
        }
    }
}

void drawTextBox(const char* text, SDL_Rect box, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &box);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &box);

}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    window = SDL_CreateWindow("Tic Tac Toe (AI)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    clearBoard();

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
                handleClick(e.button.x, e.button.y);
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        drawGrid();
        drawMarks();

        if (gameOver) {
            SDL_Color replayColor = {200, 255, 200, 255};
            drawTextBox("Play Again", replayButton, replayColor);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
