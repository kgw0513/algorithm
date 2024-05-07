#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)

//XABCABDABAC
int kmp(const char txt[], const char pat[]) {
	
	//������ �ϴ� �����սô�.
	int pat_arr[1000] = {};
	int s = 0;//������ ���� ���� 0�̱⿡ ��������ϴ�.
	//���� s�� �� �񱳿����� ���ϴµ��� ������ �� �� ���� �����Դϴ�.

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

	//���� ������ �������� txt�� ���ؼ� �´� �κ��� ã�� ��ȯ�սô�.

	s = 0;//�� �κ��� pat���� ��� �κп� �˸´��� �˷��ݴϴ�.
	int ans = -1;
	//ã�� ��ĵ� kmp ���ð����� ����մϴ�.
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
		printf("�ؽ�Ʈ�� ������ �����ϴ�.\n");
	else
		printf("%d �ε����� ������ �ֽ��ϴ�.\n", idx);
	return 0;
}
