#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

// Define the size of the game board
#define WIDTH 20
#define HEIGHT 20

// Define the symbols used for the game elements
#define SYMBOL_SNAKE '@'
#define SYMBOL_FOOD '*'

// Define the directions for the snake movement
#define DIR_UP 0
#define DIR_DOWN 1
#define DIR_LEFT 2
#define DIR_RIGHT 3

// Define a structure for the snake's body segments
typedef struct {
    int x;
    int y;
} Segment;

// Define a structure for the game state
typedef struct {
    int score;
    int direction;
    Segment snake[WIDTH * HEIGHT];
    int numSegments;
    int foodX;
    int foodY;
} GameState;

// Initialize the game state
void initGameState(GameState *state) {
    state->score = 0;
    state->direction = DIR_RIGHT;
    state->snake[0].x = WIDTH / 2;
    state->snake[0].y = HEIGHT / 2;
    state->numSegments = 1;
    state->foodX = rand() % WIDTH;
    state->foodY = rand() % HEIGHT;
}

// Draw the game board
void drawBoard(GameState *state) {
    int x, y;
    system("cls"); // clear the screen

    // Draw the top border
    for (x = 0; x < WIDTH + 2; x++) {
        printf("#");
    }
    printf("\n");

    // Draw the board contents
    for (y = 0; y < HEIGHT; y++) {
        printf("#");
        for (x = 0; x < WIDTH; x++) {
            // Draw the snake or food if present, otherwise draw an empty space
            if (x == state->snake[0].x && y == state->snake[0].y) {
                printf("%c", SYMBOL_SNAKE);
            } else if (x == state->foodX && y == state->foodY) {
                printf("%c", SYMBOL_FOOD);
            } else {
                int segment;
                for (segment = 1; segment < state->numSegments; segment++) {
                    if (x == state->snake[segment].x && y == state->snake[segment].y) {
                        printf("%c", SYMBOL_SNAKE);
                        break;
                    }
                }
                if (segment == state->numSegments) {
                    printf(" ");
                }
            }
        }
        printf("#\n");
    }

    // Draw the bottom border
    for (x = 0; x < WIDTH + 2; x++) {
        printf("#");
    }
    printf("\n");

    // Print the score
    printf("Score: %d\n", state->score);
}

// Move the snake in the current direction
void moveSnake(GameState *state) {
    int x, y;

    // Move each segment of the snake's body
    for (x = state->numSegments - 1; x > 0; x--) {
        state->snake[x].x = state->snake[x - 1].x;
        state->snake[x].y = state->snake[x - 1].y;
    }

    // Move the head of the snake in the current direction
    switch (state->direction) {
        case DIR_UP:
            state->snake[0].y--;
            break;
        case DIR_DOWN:
            state->snake[0].y++;
            break
