#include <stdio.h>
#include <string.h>

void clear_buffer(char *b, int *i, int s)
{
	printf("%s", b);
	*i = 0;
	memset(b, 0, s);
}

int main(int argc, char *argv[])
{
	char buf[BUFSIZ];
	int i = 0;
	int pc = 0;
	enum state {init, quote, comment} st = init;
	int c;
	while ((c = getchar()) != EOF)
	{
		if (i <= (BUFSIZ - 2))
			clear_buffer(buf, &i, BUFSIZ);
		buf[i++] = c;
		switch (st)
		{
			case init:
				switch (c)
				{
					case '(':
						pc++;
						break;
					case ')':
						pc--;
						break;
					case '"':
						st = quote;
						break;
					case ';':
						st = comment;
						break;
					default:
						break;
				}
				break;
			case quote:
				if (c == '"')
					st = init;
				break;
			case comment:
				if (c == '\n')
					st = init;
				break;
		}
	}
	if (pc > 0)
	{
		while (pc-- > 0)
		{
			if (i <= (BUFSIZ - 2))
				clear_buffer(buf, &i, BUFSIZ);
			buf[i++] = ')';
		}
		buf[i] = 0;
	}
	else if (pc < 0)
		buf[i + pc - 1] = 0;
	printf("%s", buf);
	return 0;
}
