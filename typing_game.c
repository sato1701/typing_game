#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <windows.h>

#define cont_count_MAX 20 //一時的に使用　後に、プレイヤーが設定

struct Words{
	char word[20];
	_Bool WasUsed;
} contents[100];

int data_read();
void calc_show(double, int, int);

int main(){
	const int FILE_NUM = data_read();
	int cont_count = 0;
	int cont_index = 0;
	int word_index = 0;
	int all_count = 0;
	int success_count = 0;
	char tmp;
	char show_word[20] = "";
	clock_t start, end;

	srand((unsigned)time(NULL));
	start = clock();

	while(cont_count < cont_count_MAX){
		do{
			cont_index = rand() % FILE_NUM;
		}while(contents[cont_index].WasUsed);
		contents[cont_index].WasUsed = TRUE;

		while(contents[cont_index].word[word_index] != '\0'){

			system("cls");
			printf("typing miss ... %2d\n\n", all_count - success_count);
			puts(contents[cont_index].word);
			strncpy(show_word, contents[cont_index].word, word_index);
			puts(show_word);

			tmp = getch();

			if(tmp == 0x1b){
				printf("強制終了！");
				exit(0);
			}
			if(tmp == contents[cont_index].word[word_index]){
				word_index++;
				success_count++;
			}
			all_count++;
		}
		cont_count++;
		word_index = 0;
		for(int k = 0; k < 20; k++)
			show_word[k] = '\0';
	}

	end = clock();

	calc_show((double)(end-start) / CLOCKS_PER_SEC, success_count, all_count);
	return 0;
}

int data_read(){
	FILE *datafile;
	int file_index = 0;
	int word_end;

	datafile = fopen("WordsFile.txt", "r");
	if(datafile == NULL){
		printf("ファイルの読み取りでエラーが発生しました。\n");
		exit(1);
	}

	//fscanf(datafile, "%d\n", &file_index);
	while((fgets(contents[file_index].word, 20, datafile)) != NULL){
		word_end = strlen(contents[file_index].word)-1;
		contents[file_index].word[word_end] = '\0';
		file_index++;
	}

	fclose(datafile);

	return file_index;
}

void calc_show(double time_diff, int success, int all){
	double wpm;
	double accuracy;
	double score;

	wpm = all / (time_diff / 60);
	accuracy = (double)success / all * 100;
	score = wpm * pow((accuracy/100), 3);

	system("cls");
	printf("time...  %.2lf[s]\n", time_diff);
	printf("WPM....  %.2lf\n", wpm);
	printf("正確性..  %.2lf\n", accuracy);
	printf("score..  %.2lf\n", score);
}
