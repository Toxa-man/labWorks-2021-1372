#include <iostream>
#include <stdio.h>
int convert_words(char* string, char words[50][50]) {
	int i = 0;
	int words_count = 0;
	while (*string != 0) {
		if (*string != ' ') {
			char* p = &words[words_count][i++];
			*p = *string;
		}
		else if (*(string - 1) != ' ') {
			words[words_count][i] = 0;
			i = 0;
			words_count += 1;
		}
		string++;
	}
	char* p = &words[words_count][i];
	*p = 0;
	return words_count;
}
void swap_strings(char* s1, char* s2) {
	while (1 != 0) {
		if (*s1 == 0) {
			while (*s2) {
				*s1 = *s2;
				*s2 = 0;
				s1++;
				s2++;
			}
			*s1 = 0;
			break;
		}
		if (*s2 == 0) {
			while (*s1) {
				*s2 = *s1;
				*s1 = 0;
				s2++;
				s1++;
			}
			*s2 = 0;
			break;
		}
		char c;
		c = *s1;
		*s1 = *s2;
		*s2 = c;
		s1++;
		s2++;
	}
}
void sort_ascii(int words_count, char words[50][50]) {
	for (int i = 0; i <= words_count; i += 1) {
		if ((words[i][0] == '!') || (words[i][0] == '?') || (words[i][0] == ',') || (words[i][0] == '.')) continue;
		for (int j = i + 1; j <= words_count; j += 1) {
			if ((words[j][0] == '!') || (words[j][0] == '?') || (words[j][0] == ',') || (words[j][0] == '.')) continue;
			char* p1 = &words[i][0];
			char* p2 = &words[j][0];
			int sum1 = 0;
			while (*p1 != 0) {
				sum1 += (int)*p1;
				p1++;
			}
			int sum2 = 0;
			while (*p2 != 0) {
				sum2 += (int)*p2;
				p2++;
			}
			if (sum1 > sum2) { 
				swap_strings(words[i], words[j]);
			}
		}
	}
}
int main(void)
{
	char string[1024];
	printf("Enter string:\n");
	fgets(string, 1024, stdin);
	for (int i = 0; i < 1024; i += 1) if (string[i] == '\n') {
		string[i] = 0;
		break;
	}
	char words[50][50];
	int words_count = convert_words(string, words);
	sort_ascii(words_count, words);
	for (int i = 0; i <= words_count; i++) {
		printf("%s ", words[i]);
	}
	return 0;
}