#include <stdio.h>

int main(int argc, char *argv[])
{
	char buf[BUFSIZ];
	int i = 0;
	int op = 0;
	int cl = 0;
	int igc = 0;
	int diff;
	char c = getchar();
	while (c != EOF)
	{
		buf[i] = c;
		if (c == '"')
		{
			do
			{
				i++;
				c = getchar();
				buf[i] = c;
			} while (c != '"');
		}
		if (c == ';') /* ignore comments */
			igc = 1;
		if (igc && buf[i - 1] == '\n')
			igc = 0;
		if (c == '(' && !igc)
			op++;
		if (c == ')' && !igc)
			cl++;
		i++;
		c = getchar();
	}
	if (op > cl)
	{
		diff = op - cl;
		while (diff > 0)
		{
			buf[i] = ')';
			diff--;
			i++;
		}
		buf[i] = NULL;
	}
	else if (op < cl)
	{
		diff = cl - op;
		buf[i - diff] = NULL;
	}
	printf("%s", buf);
	return 0;
}
