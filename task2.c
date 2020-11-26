#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

/*
Лабораторная работа 2. Вариант 4. Упаковка переменных различного типа в заданном формате. 

Задание: Разработать две функции, одна из которых вводит с клавиатуры набор данных 
в произвольной последовательности и размещает в памяти в заданном формате. 
Другая функция читает  эти  данные  и выводит на экран. 
Программа запрашивает и размещает в памяти несколько наборов данных при помощи первой функции,
а затем читает их и выводит на экран при помощи второй. Размещение данных производить 
в выделенном массиве байтов с  контролем  его переполнения.

Вариант:
Упакованная строка, содержащая символьное представление длинных целых чисел.
Все символы строки, кроме цифр, помещаются в последовательность в исходном виде.
Последовательность цифр преобразуется в целую переменную, 
которая записывается в упакованную строку, предваренная символом \1. Конец строки - символ \0.
*/

//вводит данные с клавиатуры и размещает в заданном массиве байтов
void input(char * array, int size) {
	int n = 0;
	char * p1 = array;
	char prev, c = '\0';
	int subnumber = 0;
	printf("Input long number: ");
	do {
		prev = c;
		c = getchar();
		if ((c >= 'a') && (c <= 'z') || (c >= 'A') && (c <= 'Z') || (c == '\n')) {
			if ((prev >= '0') && (prev <= '9')) {
				char t = '\1';
				memcpy(p1, &t, sizeof(char));
				p1 += sizeof(char);

				memcpy(p1, &subnumber, sizeof(int));
				p1 += sizeof(int);
			}
			if (c != '\n') {
				memcpy(p1, &c, sizeof(char));
				p1 += sizeof(char);
			}
		}
		if ((c >= '0') && (c <= '9')) {		
			if ((prev >= '0') && (prev <= '9')) {
				//контроль за переполнением разрядов int
				if (10 * (INT_MAX - subnumber) < (c - '0')) {
					char t = '\1';
					memcpy(p1, &t, sizeof(char));
					p1 += sizeof(char);
					memcpy(p1, &subnumber, sizeof(int));
					p1 += sizeof(int);
					subnumber = c - '0';
				}
				else {
					subnumber = subnumber * 10 + c - '0';
				}
			}
			if ((prev >= 'a') && (prev <= 'z') || (prev >= 'A') && (prev <= 'Z') || (prev == '\0')) {
				subnumber = c - '0';
			}
		}
	} while ((c != '\n') && (p1 < (array + (size - 2) * sizeof(char))));
	if (c != '\n') {
		printf("Array is full. No more digits will be recorded.\n");
	}
	char t = '\0';
	memcpy(p1, &t, sizeof(char));
}

//читает данные и записывает в выходной массив символов
void output(char * array, char * res, int size) {
	char * p1 = res;	// указатель по выходному массиву
	char * p2 = array;	//указатель по входному массиву
	char c = *p2;
	while ((c != '\0') && (p2 < (res + (size - 2) * sizeof(char)))) {
		if ((c >= 'a') && (c <= 'z') || (c >= 'A') && (c <= 'Z')) {
			memcpy(p1, &c, sizeof(char));
			p2 += sizeof(char);
			p1 += sizeof(char);
		}
		if (c == '\1') {
			p2 += sizeof(char);
			
			int num = *(int*)p2;
			p2 += sizeof(int);

			int numb = num, len = 0;
			while (numb) {
				numb /= 10;
				len++;
			}
			
			char * ms = (char*)malloc(len * sizeof(char));
			int i = 0;
			for (i; i < len; ++i, num /= 10) {
				char t = '0' + num % 10;
				memcpy(ms+i, &t, sizeof(char));
			}
			char t;
			for (i = 0; i < len / 2; i++) {
				t = ms[i];
				ms[i] = ms[len - 1 - i];
				ms[len - 1 - i] = t;
			}
			memcpy(p1, ms, len);
			p1 += len * sizeof(char);
			free(ms);
		}
		c = *p2;
	}
	if (c != '\0') {
		printf("Array is full. No more digits will be recorded.\n");
	}
	*p1 = '\0';
}

int main()
{
	int size = 255;
	char * array = (char *) malloc(size * sizeof(char));
	char * res = (char *)malloc(2 * size * sizeof(char)); input(array, size);
	printf("\nThe array is: %s\n", array);
	output(array, res, 2*size);
	printf("\nThe result is: %s\n", res);
	free(array);
	free(res);
}
