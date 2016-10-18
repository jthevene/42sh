#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*current_line;

void	fill_current_line(char c)
{
	char	tmp1[2];
	char	*tmp2;
	int 	len;

	tmp2 = NULL;
	len = 0;
	if (!current_line)
	{
		if (!(current_line = (char*)malloc(sizeof(char) * 2)))
			return;
		current_line[0] = c;
		current_line[1] = '\0';
	}
	else
	{
		tmp1[0] = c;
		tmp1[1] = '\0';
		tmp2 = strdup(current_line);
		len = strlen(current_line);
		if (!(current_line = (char*)malloc(sizeof(char) * len + 2)))
			return;
		current_line = strcat(tmp2, tmp1);
		free(tmp2);
	}
}

int		main(void)
{
	current_line = NULL;
	fill_current_line('a');
	printf("%s\n", current_line);
	fill_current_line('b');
	printf("%s\n", current_line);
	fill_current_line('c');
	printf("%s\n", current_line);
	fill_current_line('d');
	printf("%s\n", current_line);
	return (0);
}