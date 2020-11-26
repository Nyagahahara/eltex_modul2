#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
Лабораторная работа 1. Вариант 4.

Найти в строке последовательность одинаковых символов максимальной длины и переписать 
в выходную строку в виде n1,n2c – начало и длина фрагмента и символ, 
например abcddddddddddddedfg -> 3,12d. Из исходной строки фрагмент удалить. Повторять этот процесс, 
пока в строке есть последовательности, в конце переписать остаток в выходную строку.
*/


char * func1(char *in) {
	char * res = (char *) malloc(255 * sizeof(char));
	int i, len, start, maxLen = 0, maxStart;
	char prev, max;
	while (maxLen != 1) {
		i = 0; len = 1; start = 0; maxLen = 0;	prev = in[0];
		do {
			i++;
			char c = in[i];			
			if (c == prev) {
				len++;
			}
			else {
				if ((len > maxLen) || ((maxLen == 1) && (in[i + 1] == '\0'))) {
					maxLen = len;
					maxStart = start;
					max = prev;
				}
				start = i;
				len = 1;
				prev = c;
			}		
		} while (in[i] != '\0');
		if (maxLen != 1) {
			printf("%d,%d,%c\n", maxStart, maxLen, max);
			for (int j = maxStart; j <= strlen(in); j++)
			{
				in[j] = in[j + maxLen];
			}
		}
	}
	printf("%s\n", in);
	return res;
}

int main()
{
	char * str = (char *) malloc (255 * sizeof(char));
	printf("Enter the string: ");
	scanf("%s", str);
	//str[strlen(str)] = '\0';
	func1(str);
}
