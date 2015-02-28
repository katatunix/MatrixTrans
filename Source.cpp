/*******************************************************************************
Lời giải

Gọi best(colCountMax, colProblem) là kết quả tốt nhất khi ta phải giải quyết ma trận gồm
M dòng và colProblem cột từ 1 tới colProblem, mà xài đúng colCountMax cột trống (không biến đổi).

Nếu cột colProblem CÓ được chọn để trống
best(colCountMax, colProblem) = best(colCountMax - 1, colProblem)

Nếu cột colProblem KHÔNG được chọn để trống
(tức là mất 1 phép biến đổi tại nó)
(tức là colCountMax cột để trống nằm hết ở phía trước: từ cột 1 tới cột colProblem - 1)
best(colCountMax, colProblem) = best(colCountMax, colProblem - 1)  + 1

Nếu colCountMax == colProblem (tức là tất cả các cột để trống hết) thì
best(colCountMax, colProblem) = số hàng có 1

Nếu colCountMax == 0 (cứ cột nào có 1 là biến đổi)
best(colCountMax, colProblem) = best(colCountMax, colProblem - 1) + FLAG
trong đó FLAG = zero nếu cột colProblem toàn bit zero hết, ngược lại FLAG = 1

*******************************************************************************/

#include <stdio.h>
#include <conio.h>
 
#define INPUT_FILE "input.txt"
 
#define _SIZE 100
#define SIZE (_SIZE + 1)

#define MIN(x, y) ( (x) < (y) ? (x) : (y) )

int M, N; // size of matrix
char matrix[SIZE][SIZE]; // input matrix
char best[SIZE][SIZE]; // dynamic prog array
char isBit1Row[SIZE];

void readInput() {
	FILE* f = fopen(INPUT_FILE, "rt");
	fscanf(f, "%d %d", &M, &N);
	int i, j, tmp;
	for (i = 1; i <= M; i++)
		for (j = 1; j <= N; j++) {
			fscanf(f, "%d ", &tmp);
			matrix[i][j] = tmp;
		}
	fclose(f);
}

void dynamicProg() {
	for (int i = 1; i <= M; i++) {
		isBit1Row[i] = 0;
	}
  
	best[0][0] = 0;
  
	for (int colProblem = 1; colProblem <= N; colProblem++) {
		char flag = 0;
		int countBit1Rows = 0;
		for (int i = 1; i <= M; i++) {
			if (matrix[i][colProblem]) {
				flag = 1;
				isBit1Row[i] = 1;
			}
			if (isBit1Row[i]) {
				countBit1Rows++;
			}
		}
 
		int colCountMax = 0;
		best[colCountMax][colProblem] = best[colCountMax][colProblem - 1] + flag;

		for (colCountMax = 1; colCountMax < colProblem; colCountMax++) {
			best[colCountMax][colProblem] = MIN(
				best[colCountMax - 1][colProblem],
				best[colCountMax][colProblem - 1] + 1
			);
		}

		colCountMax = colProblem;
		best[colCountMax][colProblem] = countBit1Rows;
	}
 
}

void writeOutput() {
	int min = 0;
    for (int col = 1; col <= N; col++) {
        if (best[col][N] < best[min][N]) {
            min = col;
        }
    }
    printf("%d", best[min][N]);
    getch();
}

void main() {
	readInput();
	dynamicProg();
	writeOutput();
}
