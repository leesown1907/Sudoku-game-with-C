#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#define SIZE 9
#define BLOCK 3

void printBoard(int board[][SIZE]);
void playGame(int level);
int isValidMove(int board[][SIZE], int row, int col, int num);
int isBoardFull(int board[][SIZE]);
int solveSudoku(int board[][SIZE]);
int nextround(int board[][SIZE]);
void check(int board[][SIZE], int row, int col);
void sudoku(int board[][SIZE]);
void solveSudokuPuzzle(int board[][SIZE]);
void copyboard(int board[][SIZE], int dupeboard[][SIZE]);

void printBoard(int board[][SIZE]) {
    int i, j;
    printf("\n              Sudoku Board\n");
    printf("\n");
    printf("   [0][1][2]   [3][4][5]   [6][7][8]\n");
    for (i = 0; i < SIZE; i++) {
        printf("[%d] ", i);
        for (j = 0; j < SIZE; j++) {
            if (j % BLOCK == 0 && j != 0) {
                printf("|  ");
            }
            if (board[i][j] == 0) {
                printf("-  ");
            }
            else {
                printf("%d  ", board[i][j]);
            }
        }
        printf("\n");
        if ((i + 1) % BLOCK == 0 && i != SIZE - 1) {
            printf("    ---------|-----------|---------\n");
        }
    }
    printf("\n");
}

void playGame(int level) {
    int board[SIZE][SIZE];
    int dupeboard[SIZE][SIZE];
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            board[i][j] = 0;
        }
    }
    int filledCells;
    if (level == 1) {
        filledCells = 30;
    }
    else if (level == 2) {
        filledCells = 20;
    }
    else if (level == 3) {
        filledCells = 10;
    }
    srand(time(NULL));
    int row, col, num;
    do {
        int count = 0;
        while (count < filledCells) {
            row = rand() % SIZE;
            col = rand() % SIZE;
            num = rand() % SIZE + 1;
            if (board[row][col] == 0 && isValidMove(board, row, col, num)) {
                board[row][col] = num;
                count++;
            }
        }
        copyboard(board, dupeboard);
        if (solveSudoku(dupeboard)) {
            break;
        }
        else {
            for (row = 0; row < SIZE; row++) {
                for (col = 0; col < SIZE; col++) {
                    board[row][col] = 0;
                }
            }
        }
    } while (1);
    printBoard(board);
    sudoku(board);
}

int isValidMove(int board[][SIZE], int row, int col, int num) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        if (board[row][i] == num || board[i][col] == num) {
            return 0;
        }
    }
    int startRow = row - row % BLOCK;
    int startCol = col - col % BLOCK;
    for (i = 0; i < BLOCK; i++) {
        for (j = 0; j < BLOCK; j++) {
            if (board[startRow + i][startCol + j] == num) {
                return 0;
            }
        }
    }
    return 1;
}

int isBoardFull(int board[][SIZE]) {
    int row, col;
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            if (board[row][col] == 0) {
                return 0; 
            }
        }
    }
    return 1; 
}

int solveSudoku(int board[][SIZE]) {
    int row, col, num;
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            if (board[row][col] == 0) {
                for (num = 1; num <= SIZE; num++) {
                    if (isValidMove(board, row, col, num)) {
                        board[row][col] = num;
                        if (solveSudoku(board)) {
                            return 1;
                        }
                        board[row][col] = 0;
                    }
                }
                return 0;
            }
        }
    }
    return 1;
}

int nextround(int board[][SIZE]) {
    int row, col;
    int c = 0;
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            if (board[row][col] == 0) {
                return 1;
            }
        }
    }
    return 0;
}

void check(int board[][SIZE], int row, int col) {
    int num;
    printf("\nNhap vao mot so: ");
    scanf("%d", &num);
    if (isValidMove(board, row, col, num)) {
        board[row][col] = num;
        printf("\nNuoc di hop le!\n");
        printBoard(board);
        if (!nextround(board)) {
            printf("\nChuc mung! Ban da giai thanh cong Sudoku!\n");
        }
        else {
            printf("\nTiep tuc choi...\n");
        }
    }
    else {
        printf("\nNuoc di khong hop le. Hay nhap lai. \n");
    }
}

void sudoku(int board[][SIZE]) {
    int row, col;
    printf("\nBat dau choi\n");
    while (nextround(board)) {
        printf("\nNhap vao so hang (0-8) và so cot (0-8): ");
        scanf("%d %d", &row, &col);
        if (row >= 0 && row < SIZE && col >= 0 && col < SIZE) {
            if (board[row][col] == 0) {
                check(board, row, col);
            }
            else {
                printf("\nO nay da duoc dien. Hay chon mot o khac. \n");
            }
        }
        else {
            printf("\nSo hang hoac cot khong hop le. Hay nhap lai. \n");
        }
    }
}

void copyboard(int board[][SIZE], int dupeboard[][SIZE]) {
    int row, col;
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            dupeboard[row][col] = board[row][col];
        }
    }
}

void solveSudokuPuzzle(int board[][SIZE]) {
    if (solveSudoku(board)) {
        printf("\nDa giai xong!\n");
        printBoard(board);
    }
    else {
        printf("\nKhong the giai duoc Sudoku nay!\n");
    }
}

int main() {
    int choice, level;
    printf("\nWelcome to Sudoku!\n");
    do {
        printf("\nMenu:\n");
        printf("1. Bat dau choi\n");
        printf("2. Giai Sudoku\n");
        printf("3. Thoat\n");
        printf("Lua chon (1-3): ");
        scanf("%d", &choice);
        switch (choice) {
        case 1: {
            printf("\nChon do kho:\n");
            printf("1. De\n");
            printf("2. Binh thuong\n");
            printf("3. Kho\n");
            printf("Lua chon (1-3): ");
            scanf("%d", &level);
            switch (level) {
            case 1: {
                playGame(level);
                break;
            }
            case 2: {
                playGame(level);
                break;
            }
            case 3: {
                playGame(level);
                break;
            }
            default: {
                printf("\nLua chon khong hop le. Hay chon lai. \n");
            }
            }
        }
            break;
        case 2: {
            int board[SIZE][SIZE];
            printf("\nNhap vao Sudoku (Nhap 0 voi o trong):\n");
            int i, j;
			for (i = 0; i < SIZE; i++) {
                for (j = 0; j < SIZE; j++) {
                    printf("Nhap vao so cho hang %d, cot %d: ", i, j);
                    scanf("%d", &board[i][j]);
                }
            }
            printf("\nSudoku vua nhap vao\n");
            printBoard(board);
            printf("\nDang tim loi giai...\n");
            solveSudokuPuzzle(board);
            break;
        }
        case 3:
            printf("\nCam on vi da choi Sudoku!\n");
            break;
        default:
            printf("\nLua chon khong hop le. Hay chon lai. \n");
        }

    } while (choice != 3);
    return 0;
}

