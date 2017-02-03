#include "../includes/sh.h"

char	*finish_line_backslash(char *line)
{
	char *myline;

	ft_strdel(&g_shell.prompt);
	ft_putstr("\n");
	myline = prompt_dquote("> ");
	myline = ft_strjoin(line, myline);
	return (myline);
}

char	*finish_the_squote(char *line)
{
	char *myline;

	ft_strdel(&g_shell.prompt);
	ft_putstr("\n");
	myline = prompt_dquote("quote> ");
	myline = ft_strjoin(line, myline);
	return (myline);
}

char	*finish_the_dquote(char *line)
{
	char *myline;

	ft_strdel(&g_shell.prompt);
	ft_putstr("\n");
	myline = prompt_dquote("dquote> ");
	myline = ft_strjoin(line, myline);
	return (myline);
}

int		quote_in_word(char *line, int pos)
{
	if (line[pos] == '\"')
	{
		pos++;
		while (line[pos] != '\"')
			pos++;
		pos++;
	}
	else if (line[pos] == '\'')
	{
		pos++;
		while (line[pos] != '\'')
			pos++;
		pos++;
	}
	return (pos);
}
