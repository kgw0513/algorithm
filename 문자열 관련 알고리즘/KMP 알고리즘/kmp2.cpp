#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)

int skip[10001];
char pat[10000];
char txt[10000];

void set_pattern(char pat[]) {
	int s = 1;
	int e = 0;
	while (pat[s] != '\0') {
		if (pat[s] == pat[e]) {
			skip[++s] = ++e;
		}
		else if (e == 0)skip[++s] = e;
		else e = skip[e];
	}
	for (int i = 1; pat[i] != '\0'; i++) {
		printf("%d ", skip[i]);
	}
	printf("\n");
}

void print_char(char arr[],int p) {
	for (int i = 0; (i <= p && arr[i]!='\0'); i++) {
		printf("%c", arr[i]);
	}
	printf("\n");
}
int kmp(char txt[], char pat[]) {
	int s = 0;
	int e = 0;

	while (txt[s] != '\0' && pat[e] != '\0') {

		if (txt[s] == pat[e]) {

			printf("txt : ");
			print_char(txt, s);
			printf("pat : ");
			print_char(pat, e);

			s++;
			e++;
		}
		else if (e == 0) {

			printf("txt : ");
			print_char(txt, s);
			printf("pat : ");
			print_char(pat, e);

			s++;
		}
		else e = skip[e];

	}

	if (pat[e] == '\0')return s - e;
	return -1;
}
int main() {
	scanf("%s", txt);
	scanf("%s", pat);
	set_pattern(pat);
	printf("%d\n", kmp(txt, pat));
}
