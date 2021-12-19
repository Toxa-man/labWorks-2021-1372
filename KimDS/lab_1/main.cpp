#include<iostream>
#include <stdio.h>
#include <stdlib.h>
int convert_string(char* string, char** words) {
	int words_count = 0;
	while (*string) {
		if (*string != ' ') {
			char* p = words[words_count];
			words_count += 1;
			while ((*string != ' ') && (*string)) *(p++) = *(string++);
			*p = 0;
		}
		else string++;
	}
	return words_count;
}
void replace_strings(char* string1, char* string2) {
	while (*string2) {
		*string1 = *string2;
		*string2 = 0;
		string1++;
		string2++;
	}
	*string1 = 0;
}
void sdvig(char** words, int words_count, int i) {
	int j = words_count + 1;
	words_count += 1;
	for (; j > i + 1; j -= 1) {
		replace_strings(words[j], words[j - 1]);
	}
}
int space_marks(char** words, int words_count, char* marks, int* boolean_non_space, int* boolean_space) {
	for (int i = 0; i < words_count; i += 1) {
		for (int j = 0; words[i][j] != 0; j += 1) {
			int bl = 1;
			if (j == 0) for (int k = 0; marks[k] != 0; k += 1) if (words[i][j] == marks[k]) {
				bl = 0;
				boolean_space[i] = 1;
			}
			if (bl) {
				for (int k = 0; marks[k] != 0; k += 1) if (words[i][j] == marks[k]) {
					sdvig(words, words_count, i);
					words_count += 1;
					int k = 0;
					while (words[i][j] != 0) {
						words[i + 1][k] = words[i][j];
						words[i][j] = 0;
						k += 1;
						j += 1;
					}
					j = 0;
					boolean_non_space[i + 1] = 1;
					i += 2;
				}
			}
		}
	}
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
int compare_strings(char* s1, char* s2) {
	int boolean = 1;
	while ((*s1) && (*s2)) {
		if ((*s1 != *s2) || ((*(s1 + 1) == 0) && (*(s2 + 1))) || ((*(s2 + 1) == 0) && (*(s1 + 1)))) {
			boolean = 0;
			break;
		}
		s1++;
		s2++;
	}
	return boolean;
}
void ascii_sort(char** words, int words_count, int* boolean_non_space, int* boolean_space) {
	for (int i = 0; i < words_count; i += 1) {
		if (boolean_non_space[i] || boolean_space[i]) continue;
		for (int j = i + 1; j < words_count; j += 1) {
			if (boolean_non_space[j] || boolean_space[j]) continue;
			if (compare_strings(words[i], words[j])) continue;
			int p1 = 0;
			int p2 = 0;
			char* s1 = words[i];
			char* s2 = words[j];
			while (*s1) {
				p1 += (int)*s1;
				s1++;
			}
			while (*s2) {
				p2 += (int)*s2;
				s2++;
			}
			if (p1 > p2) swap_strings(words[i], words[j]);
		}
	}
}
int main() {
	char* string;
	string = (char*)malloc(1024 * sizeof(char));
	std::cout << "Enter string: ";
	fgets(string, 1024, stdin);
	int length_s = 0;
	for (; string[length_s] != '\n'; length_s += 1);
	string[length_s] = 0;
	char** words;
	words = (char**)malloc(100 * sizeof(char*));
	for (int i = 0; i < 100; i += 1) {
		words[i] = (char*)malloc(256 * sizeof(char));
	}
	int words_count = convert_string(string, words);
	char marks[] = { '.',',','!','?','\0' };
	int* boolean_non_space;
	boolean_non_space = (int*)malloc(100 * sizeof(int));
	for (int i = 0; i < 100; i += 1) {
		boolean_non_space[i] = 0;
	}
	int* boolean_space;
	boolean_space = (int*)malloc(100 * sizeof(int));
	for (int i = 0; i < 100; i += 1) {
		boolean_space[i] = 0;
	}
	words_count = space_marks(words, words_count, marks, boolean_non_space, boolean_space);
	ascii_sort(words, words_count, boolean_non_space, boolean_space);
	for (int i = 0; i < words_count; i += 1) {
		if (boolean_non_space[i + 1]) {
			printf("%s", words[i]);
		}
		else {
			printf("%s ", words[i]);
		}
	}
	return 0;
}