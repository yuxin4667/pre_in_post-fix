#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define N 80

char stack[N];
int stack_top = -1;

char prefix[N];
int prefix_top = -1;

char op[5] = { ')', '+', '-', '*', '/' };
int p[5] = { 0, 1, 1, 2, 2 };

void prefix_push(char ch)
{
	if (prefix_top == N - 1) {
		printf("堆疊已滿\n");
		return;
	}
	prefix_top++;
	prefix[prefix_top] = ch;
}

void push(char op)
{
	if (stack_top == N - 1) {
		printf("堆疊已滿\n");
		return;
	}
	stack_top++;
	stack[stack_top] = op;
}

char pop(void)
{
	if (stack_top == -1) {
		printf("堆疊為空\n");
		return 0;
	}
	char temp = stack[stack_top];
	stack_top--;
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
	if (p[j] > p[i])
		return 0;
	else
		return 1;
}

int empty(void)
{
	if (stack_top == -1)
		return 0;
	else
		return -1;
}

void print(void)
{
	if (empty() == -1) {
		for (int i = stack_top; i >= 0; i--)
			prefix_push(stack[i]);
	}
	for (int i = prefix_top; i >= 0; i--)
		printf("%c ", prefix[i]);
}

int main(void)
{
	char s[N];
	printf("Infix: ");
	fgets(s, N, stdin); //換行'\n'會被讀入s

	for (int i = s[strlen(s) - 1]; i >= 0 ; i--)
	{
		char x = s[i];
		int p;

		if (x - '0' >= 0 && x - '0' <= 9)
			prefix_push(x);

		else
		{
			switch (x)
			{
			case')':
				push(x);
				break;

			case'(':
				x = stack[stack_top];
				pop();
				while (x != ')') {
					prefix_push(x);
					x = pop(); //x記錄為stack[top]並pop
				}
				break;

			case'+':
			case'-':
			case'*':
			case'/':
				//stack[top]要有值(否則是亂數)才能比優先順序 -> stack為空直接push
				while (empty() != 0 && priority(x, stack[stack_top]) == 0)
				{
					prefix_push(stack[stack_top]);
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
