#include "../includes/sh.h"

int		token_squote(t_token *token, char *line, int pos, int i)
{
	pos++;
	token->type = SQUOTE;
	i = pos;
	while (line[pos] != '\'')
		pos++;
	add_lexeme(token, line, pos, i);
	pos++;
	return (pos);
}

int		token_dquote(t_token *token, char *line, int pos, int i)
{
	pos++;
	token->type = DQUOTE;
	i = pos;
	while (line[pos] != '\"')
		pos++;
	add_lexeme(token, line, pos, i);
	pos++;
	return (pos);
}

char	*finish_quotes(char *line)
{
	FT_INIT(int, i, 1);
	FT_INIT(char*, tmp, ft_strdup(line));
	while (i != 0)
	{
		i = unfinished_quote(tmp);
		if (i == 1)
			tmp = finish_the_squote(tmp);
		else if (i == 2)
			tmp = finish_the_dquote(tmp);
	}
	if (!tmp)
		tmp = line;
	else
		free(line);
	return (tmp);
}

t_token	*get_token(t_token *token, int type)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == type)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

int		compare_end(char *str1, char *str2)
{
	FT_INIT(int, i, ft_strlen(str1));
	FT_INIT(int, e, i - 2);
	FT_INIT(int, x, 0);
	while(str2[x] == str1[e] && str1[e] && str2[x])
	{
		x++;
		e++;
	}
	if (e == i)
		return (1);
	return (0);
}