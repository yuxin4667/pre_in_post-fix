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

int eval(char *str)
{
	char* p = str;
	while (*p)
	{
		if (*p >= 48 && *p <= 57)
			push(*p - '0');
		else 
		{
			int temp;
			switch (*p)
			{
			case'+':
				temp = pop();
				push(pop() + temp);
				break;

			case'-':
				temp = pop();
				push(pop() - temp);
				break;

			case'*':
				temp = pop();
				push(pop() * temp);
				break;

			case'/':
				temp = pop();
				push(pop() / temp);
				break;

			default:
				return -1;
			}
		}	
		p++;
	}
	return pop();
}

int main(void)
{
	char str[N];
	printf("輸入postfix運算式: ");
	gets(str);
	printf("%s = %d\n", str, eval(str));
	
	return 0;
}