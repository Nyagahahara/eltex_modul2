#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

/*
Лабораторная работа 4. Вариант 4.

Функция находит в строке фрагменты, симметричные относительно центрального символа, 
длиной 7 и более символов (например, "abcdcba") и возвращает динамический массив указателей на копии таких фрагментов.
*/

char ** func4(char * source_string) {
	char ** result = (char **) malloc(10 * sizeof(char*));
	for (int i = 0; i < 10; i++) {
		result[i] = NULL;
	}
	int counter = 0;
	int i = 3;	//т.к. фрагмент не менее 7 символов
	int length = strlen(source_string);
	for (i; i < length - 3; i++) {
		int j = 1;
		while ((source_string[i - j] == source_string[i + j]) && (j < i) && (i + j < length)) {
			j++;
		}
		if (j > 3) {
			char * res = (char*) malloc(255 * sizeof(char));
			for (int c = 0, k = i - j + 1; k < i + j; c++, k++) {
				res[c] = source_string[k];
			}
			res[2 * j - 1] = '\0';
			result[counter] = res;
			counter++;
		}
	}
	return result;
}

int main()
{
	char * str = (char*) malloc(255 * sizeof(char));
	printf("Input string: ");
	scanf("%s", str);
	char ** res = func4(str);
	int c = 0;
	while (res[c] != NULL) {
		printf("%s\n", res[c]);
		c++;
	}
}
