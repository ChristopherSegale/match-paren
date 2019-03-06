#include <stdio.h>
#include <string.h>

void clear_buffer(char *b, int *i)
{
	int s = sizeof(b);
	printf("%s", b);
	*i = 0;
	memset(b, '\0', s);
}

int main(int argc, char *argv[])
{
	char buf[BUFSIZ];
	int i = 0;
	int pc = 0;
	int igq = 0;
	enum state {init, quote, comment, escape} st = init;
	int c;
	while ((c = getchar()) != EOF)
	{
		if (i <= (BUFSIZ - 3))
			clear_buffer(buf, &i);
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
					case '\\':
						st = escape;
						break;
					default:
						break;
				}
				break;
			case quote:
				if (c == '\\')
					igq = 1;
				if (c == '"')
				{
					if (igq)
						igq = 0;
					else
						st = init;
				}
				break;
			case comment:
				if (c == '\n')
					st = init;
				break;
			case escape:
				st = init;
				break;
		}
	}
	if (pc > 0)
	{
		while (pc-- > 0)
		{
			if (i <= (BUFSIZ - 3))
				clear_buffer(buf, &i);
			buf[i++] = ')';
		}
		buf[i] = '\0';
	}
	else if (pc < 0)
		buf[i + pc] = '\0';
	printf("%s", buf);
	return 0;
}
