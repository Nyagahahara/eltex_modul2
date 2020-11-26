#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

/*
Лабораторная работа 3. Вариант 4.

Определить структурированный тип и набор  функций для работы с таблицей записей, реализованной в массиве структур. 
В перечень функций входят:
	ввод записи таблицы с клавиатуры;
	загрузка и сохранение  таблицы в текстовом файле;
	просмотр таблицы;
	сортировка таблицы в порядке возрастания заданного поля;
	поиск в таблице элемента с заданным значением поля или с наиболее близким к нему по значению;
	удаление записи;
	изменение (редактирование) записи;
	вычисление с проверкой и использованием всех pfgbctq по заданному условию и формуле (например, общая сумма на всех счетах).
 
 Перечень полей структурированной переменной:
 Фамилия, номер зачетной книжки, факультет, группа.
*/

struct student {
	char * surname;
	int num;
	char * faculty;
	char * group;
};

struct table {
	struct student * students;
	int amount;
};

void insert(struct table * t, struct student s) {
	t->students[t->amount] = s;
	t->amount++;
}

void remove_r(struct table * t, int i) {
	if (i < t->amount) {
		for (int j = i; j < t->amount - 1; j++) {
			t->students[j].num = t->students[j + 1].num;
			t->students[j].surname = t->students[j + 1].surname;
			t->students[j].group = t->students[j + 1].group;
			t->students[j].faculty = t->students[j + 1].faculty;
		}
		t->amount--;
	}
}

void edit(struct table * t, int index, struct student st) {
	t->students[index].num = st.num;
	t->students[index].surname = st.surname;
	t->students[index].group = st.group;
	t->students[index].faculty = st.faculty;
}

void show(struct table * t) {
	struct student st;
	for (int i = 0; i < t->amount; i++) {
		st = t->students[i];
		printf("%d %d %s %s %s\n", i, st.num, st.surname, st.group, st.faculty);
	}
}

void write_file(struct table * t, char * filename) {
	FILE * out;
	out = fopen(filename, "w");
	fprintf(out, "%d\n", t->amount);
	struct student st;
	for (int i = 0; i < t->amount; i++) {
		st = t->students[i];
		fprintf(out, "%d %s %s %s\n", st.num, st.surname, st.group, st.faculty);
	}
	fclose(out);
}

void read_file(struct table * t, char * filename) {
	FILE * in;
	in = fopen(filename, "r");
	int amount = 0;
	fscanf(in, "%d\n", &(amount));
	for (int i = 0; i < amount; i++) {
		int num = 0;
		char * surname = (char *)malloc(255 * sizeof(char));
		char * group = (char *)malloc(10 * sizeof(char));
		char * faculty = (char *)malloc(10 * sizeof(char));
		fscanf(in, "%d %s %s %s\n", &num, surname, group, faculty);
		struct student st;
		st.num = num; st.surname = surname; st.group = group; st.faculty = faculty;
		insert(t, st);
	}
	fclose(in);
}

//сортируем по номеру зачетной книжки
void sort_by_num(struct table * t) {
	for (int i = 0; i < t->amount; i++) {
		for (int j = i + 1; j < t->amount; j++) {
			if (t->students[i].num > t->students[j].num) {
				struct student st = t->students[i];
				t->students[i] = t->students[j];
				t->students[j] = st;
			}
		}
	}
}

//ищем студента по номеру зачетной книжки
struct student search(struct table * t, int s) {
	for (int i = 0; i < t->amount; i++) {
		if (t->students[i].num == s) {
			return t->students[i];
		}
	}
	//совпадений не найдено, ищем ближайший номер зачетной книжки
	int * dif = (int*) malloc(t->amount * sizeof(int*));
	for (int i = 0; i < t->amount; i++) {
		dif[i] = abs(t->students[i].num - s);
	}
	int min_dif = dif[0], min = 0;
	for (int i = 1; i < t->amount; i++) {
		if (dif[i] < min_dif) {
			min_dif = dif[i];
			min = i;
		}
	}
	return t->students[min];
}

//вычисление с проверкой и использованием всех записей
int in_faculty(struct table * t, char * f) {
	int count = 0;
	for (int i = 0; i < t->amount; i++) {
		if (strcmp(t->students[i].faculty, f) == 0) {
			count++;
		}
	}
	return count;
}

int main()
{
	struct table tt;
	tt.students = (struct student *) calloc(10, sizeof(struct student));
	tt.amount = 0;
	int choice = 0;
	while (choice < 10) {
		printf("\nChoose the action:\n");
		printf("1 - insert record\n");
		printf("2 - show table\n");
		printf("3 - remove record\n");
		printf("4 - edit record\n");
		printf("5 - sort by gradebook number\n");
		printf("6 - search\n");
		printf("7 - amount of students of faculty\n");
		printf("8 - save in text file\n");
		printf("9 - read from text file\n");
		printf("other - exit\n");
		printf("Your choice: ");
		scanf("%d", &choice);
		switch (choice) {
		case 1: {
			//ввод записи таблицы с клавиатуры
			int num = 0;
			char * surname = (char *)malloc(255 * sizeof(char));
			char * group = (char *)malloc(10 * sizeof(char));
			char * faculty = (char *)malloc(10 * sizeof(char));
			printf("Insert gradebook number, name, group and faculty:\n");
			scanf("%d %s %s %s", &num, surname, group, faculty);
			struct student st;
			st.num = num;
			st.surname = surname;
			st.group = group;
			st.faculty = faculty;
			insert(&tt, st);
			break;
		}
		case 2: {
			//просмотр таблицы
			show(&tt);
			break;
		}
		case 3: {
			//удаление записи
			printf("Input number of record: ");
			int i = 0;
			scanf("%d", &i);
			remove_r(&tt, i);
			break;
		}
		case 4: {
			//изменение (редактирование записи)
			int num = 0;
			char * surname = (char *)malloc(255 * sizeof(char));
			char * group = (char *)malloc(10 * sizeof(char));
			char * faculty = (char *)malloc(10 * sizeof(char));

			printf("Input index of record to change: ");
			int i = 0;
			scanf("%d", &i);
			if (i < tt.amount) {
				printf("Old record: %d %s %s %s\n", tt.students[i].num,
					tt.students[i].surname, tt.students[i].group, tt.students[i].faculty);
				printf("Input new values: ");
				scanf("%d %s %s %s", &num, surname, group, faculty);

				struct student st;
				st.num = num;
				st.surname = surname;
				st.group = group;
				st.faculty = faculty;
				edit(&tt, i, st);
			}
			break;
		}
		case 5: {
			//сортировка таблицы в порядке возрастания заданного поля
			sort_by_num(&tt);
			break;
		}
		case 6: {
			//поиск
			printf("Input record book number: ");
			int ss = 0;
			scanf("%d", &ss);
			struct student st = search(&tt, ss);
			printf("%d %s %s %s\n", st.num, st.surname, st.group, st.faculty);
			break;
		}
		case 7: {
			//все студенты одного факультета
			printf("%s", "Input faculty: ");
			char * f = (char*)malloc(10 * sizeof(char));
			scanf("%s", f);
			int count = in_faculty(&tt, f);
			printf("%d\n", count);
			free(f);
			break;
		}
		case 8: {
			//сохранение в текстовом файле
			printf("Input filename: ");
			char * filename = (char*)malloc(255 * sizeof(char));
			scanf("%s", filename);
			write_file(&tt, filename);
			free(filename);
			break;
		}
		case 9: {
			//загрузка из текстового файла
			printf("Input filename: ");
			char * filename = (char*)malloc(255 * sizeof(char));
			scanf("%s", filename);
			read_file(&tt, filename);
			free(filename);
			break;
		}
		default: {
			break;
		}
		}
	}
	free(tt.students);
	return 0;
}
