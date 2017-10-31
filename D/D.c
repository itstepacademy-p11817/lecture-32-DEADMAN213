#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include <inttypes.h>
#include <stdlib.h>

uint8_t inputValue(const char* str) {
	uint8_t val = 0;

	printf(str);
	scanf("%hhu", &val);

	return val;
}

int8_t** createTable(const uint8_t rows, const uint8_t colls) {
	int8_t** table = (int8_t**)calloc(rows, sizeof(int8_t*));
	for (uint8_t i = 0; i < rows; i++) {
		*(table + i) = (int8_t*)calloc(colls, sizeof(int8_t));
	}

	return table;
}

int8_t** initTable(int8_t** table, const uint8_t rows, const uint8_t colls) {
	for (uint8_t i = 0; i < rows; i++) {
		for (uint8_t j = 0; j < colls; j++) {
			if (rand() % 2 == 0) {
				*(*(table + i) + j) = rand() % 10;
			}
			else {
				*(*(table + i) + j) = -rand() % 10;
			}
		}
	}

	return table;
}

int8_t** printTable(int8_t** table, const uint8_t rows, const uint8_t colls) {
	for (uint8_t i = 0; i < rows; i++) {
		for (uint8_t j = 0; j < colls; j++) {
			printf("%4hhi", *(*(table + i) + j));
		}
		putchar('\n');
	}

	return table;
}

int8_t** deleteTable(int8_t** table, const uint8_t rows) {
	for (uint8_t i = 0; i < rows; i++) {
		free(*(table + i));
	}
	free(table);

	return NULL;
}

uint8_t** reverseLines(uint8_t** table, uint8_t bgn, uint8_t end) {
	while (end > bgn) {
		uint8_t* box = *(table + bgn);
		*(table + bgn) = *(table + end);
		*(table + end) = box;

		bgn++;
		end--;
	}

	return table;
}

uint8_t** reverseColums(uint8_t** table, uint8_t row, uint8_t bgn, uint8_t end) {
	uint8_t box = 0;

	while (end > bgn) {
		for (uint8_t i = 0; i < row; i++) {
			box = *(*(table + i) + bgn);
			*(*(table + i) + bgn) = *(*(table + i) + end);
			*(*(table + i) + end) = box;
		}

		bgn++;
		end--;
	}

	return table;
}

uint8_t menu() {
	uint8_t ch = 0;

	system("cls");

	printf("Menu:\n");
	printf("1 - Create tables.\n");
	printf("2 - Print tables.\n");
	printf("3 - Move lines or columns.\n");
	printf("4 - Exit.\n");
	printf("Choice: ");
	scanf("%hhu", &ch);

	return ch;
}

void pass() {
	while (getchar() != '\n');
}

uint8_t arrowMenu() {
	system("cls");

	printf("Choose direction:\n");
	printf("%c - Up.\n", 24); //72
	printf("%c - Down.\n", 25); //80
	printf("%c - Left.\n", 26); //75
	printf("%c - Right.\n", 27); //77
	printf("Esc - Exit.\n");

	return _getch();
}

int main(void) {
	uint8_t ch = 0;

	int8_t** table = NULL;
	uint8_t row = 0;
	uint8_t coll = 0;

	while ((ch = menu()) != 4) {
		switch (ch) {
		case 1:
			if (table) {
				table = deleteTable(table, row);
			}

			row = inputValue("Input num of a rows for A: ");
			coll = inputValue("Input num of a colls for A: ");

			table = createTable(row, coll);
			initTable(table, row, coll);

			break;

		case 2:
			if (table) {
				printf("Table A:\n");
				printTable(table, row, coll);
			}
			else {
				printf("Table is empty.\n");
			}

			break;

		case 3: {
			uint8_t moves = inputValue("Input num of moves: ") % row;
			
			while (ch = arrowMenu()) {
				
				if (ch == 0 || ch == 224) {
					continue;
				}

				switch (ch) {
				case 72: //¬верх
					reverseLines(table, 0, moves - 1);
					reverseLines(table, moves, row - 1);
					reverseLines(table, 0, row - 1);
					break;

				case 80: //¬низ
					reverseLines(table, 0, row - moves - 1);
					reverseLines(table, row - moves, row - 1);
					reverseLines(table, 0, row - 1);
					break;

				case 75: //¬лево
					reverseColums(table, row, 0, moves - 1);
					reverseColums(table, row, moves, coll - 1);
					reverseColums(table, row, 0, coll - 1);
					break;

				case 77: //¬право
					reverseColums(table, row, 0, coll - moves - 1);
					reverseColums(table, row, coll - moves, coll - 1);
					reverseColums(table, row, 0, coll - 1);
					break;
				}
				
				if (ch == 27) {
					break;
				}

				printf("\n");
				printTable(table, row, coll);

				_getch();
			}

			break;
		}

		case 4:
			if (table) {
				table = deleteTable(table, row);
				row = 0;
				coll = 0;
			}
			break;

		default:
			printf("Wrong input.\n");
			pass();
			break;
		}

		printf("Press any key.\n");
		_getch();
	}

	if (table) {
		table = deleteTable(table, row);
	}

	return 0;
}