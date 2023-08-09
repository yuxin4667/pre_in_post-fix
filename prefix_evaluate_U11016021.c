#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 80

int stack[N];
int top = -1;

void push(int num)
{
	if (top == N - 1) {
		printf("陣列已滿\n");
		return;
	}
	top++;
	stack[top] = num;
}

int pop(void)
{
	if (top == -1) {
		printf("陣列為空\n");
		return 0;
	}

	int temp = stack[top]; //記錄回傳值
	top--; //將top移到前一格
	return temp;
}

int eval(char* str)
{
	int count = strlen(str) - 1;
	
	for (int i = count; i >= 0; i--)
	{
		if (str[i] >= 48 && str[i] <= 57)
			push(str[i] - '0');
		else
		{
			int temp;
			switch (str[i])
			{
			case'+':
				temp = pop();
				push(temp + pop());
				break;

			case'-':
				temp = pop();
				push(temp - pop());
				break;

			case'*':
				temp = pop();
				push(temp * pop());
				break;

			case'/':
				temp = pop();
				push(temp / pop());
				break;

			default:
				return -1;
			}
		}
	}
	return pop();
}

int main(void)
{
	char str[N];
	printf("輸入prefix運算式: ");
	gets(str);
	printf("%s = %d\n", str, eval(str));

	return 0;
}
