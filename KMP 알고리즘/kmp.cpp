#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)

//XABCABDABAC
int kmp(const char txt[], const char pat[]) {
	
	//패턴을 일단 세팅합시다.
	int pat_arr[1000] = {};
	int s = 0;//패턴의 시작 값은 0이기에 상관없습니다.
	//또한 s는 앞 비교용으로 비교하는동안 앞질러 갈 수 없는 구조입니다.

	for (int e = 1; e < strlen(pat); e++) {
		while (s > 0 && pat[s] != pat[e]) {
			//printf("%d -> %d\n", s, pat_arr[s]);
			s = pat_arr[s-1];
		}
		if (pat[s] == pat[e]) {
			s++;
			pat_arr[e] = s;
		}
		//printf("%d : %d\n", e, pat_arr[e]);
	}

	//이제 세팅이 끝났으니 txt랑 비교해서 맞는 부분을 찾아 반환합시다.

	s = 0;//이 부분은 pat에서 어느 부분에 알맞는지 알려줍니다.
	int ans = -1;
	//찾는 방식도 kmp 세팅과정과 비슷합니다.
	for (int i = 0; i < strlen(txt); i++) {
		while (s > 0 && pat[s] != txt[i])s = pat_arr[s-1];
		if (pat[s] == txt[i])
			s++;
		if (s >= strlen(pat)) {
			ans = i - strlen(pat) + 1;
			break;
		}
	}

	return ans;
}

int main() {
	char text[1000];
	char pattern[1000];
	printf("input text : ");
	scanf("%s", text);
	printf("input pattern : ");
	scanf("%s", pattern);

	int idx = kmp(text, pattern);
	if (idx == -1)
		printf("텍스트에 패턴이 없습니다.\n");
	else
		printf("%d 인덱스에 패턴이 있습니다.\n", idx);
	return 0;
}
