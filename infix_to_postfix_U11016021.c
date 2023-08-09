#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define N 80

char stack[N];
char op[5] = { '(', '+', '-', '*', '/'};
int p[5] = { 0, 1, 1, 2, 2};
int top = -1;

void push(char op)
{
	if (top == N - 1) {
		printf("堆疊已滿\n");
		return;
	}
	top++;
	stack[top] = op;
}

char pop(void) 
{
	if (top == -1) {
		printf("堆疊為空\n");
		return 0;
	}
	char temp = stack[top];
	top--;
	return temp;
}
int priority(char x, char y)
{
	int i, j;
	for (i = 0; i < 5; i++) {
		if (x == op[i])
			break;
	}
	for (j = 0; j < 5; j++) {
		if (y == op[j])
			break;
	}
	if (p[j] >= p[i])
		return 0;
	else
		return 1;
}

int empty(void)
{
	if (top == -1)
		return 0;
	else
		return -1;
}

void print(void)
{
	for (int i = top; i >= 0; i--)
		printf("%c", stack[i]);
}

int main(void)
{
	char s[N];
	printf("Infix: ");

	fgets(s, N, stdin); //換行'\n'會被讀入s
	s[strlen(s) - 1] = '\0'; //將'\n'那格改成'\0'

	
	for (int i = 0; s[i] != '\0'; i++) 
	{
		char x = s[i];
		int p;

		if (x - '0' >= 0 && x - '0' <= 9)
			printf("%c ", x);
		
		else
		{
			switch (x)
			{
			case'(':
				push(x);
				break;

			case')':
				x = stack[top];
				pop();
				while (x != '(') {
					printf("%c ", x);
					x = pop(); //x記錄為stack[top]並pop
				}
				break;

			case'+':
			case'-':
			case'*':
			case'/':
				//stack[top]要有值(否則是亂數)才能比優先順序 -> stack為空直接push
				while(empty() != 0 && priority(x, stack[top]) == 0)
				{
					printf("%c ", stack[top]);
					pop();
				}
				push(x);
				break;

			default:
				break;
			}
		}
	}
	print();
	return 0;
}
