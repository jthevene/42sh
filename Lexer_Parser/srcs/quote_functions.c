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

char	*prompt_dquote(char *quote_type)
{
	FT_INIT(char*, c, g_shell.c);
	FT_INIT(char*, tmp, NULL);
	FT_INIT(char*, str_to_return, "");
	ft_putstr(quote_type);
	g_shell.cursor_x = ft_strlen(quote_type);
	tputs(tgetstr("sc", NULL), 1, ft_putchar_int);
	while (readkey())
	{
		c = g_shell.c;
		if (c[0] == 10)
			break ;
		else
		{
			fill_current_line(c[0]);
			g_shell.cursor_x++;
			ft_putstr(c);
			tmp = str_to_return;
			str_to_return = ft_strjoin(str_to_return, c);
			if (ft_strlen(tmp))
				ft_strdel(&tmp);
		}
	}
	return (str_to_return);
}
