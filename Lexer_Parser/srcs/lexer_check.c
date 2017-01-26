#include "../includes/sh.h"

int		check_ope(t_token *token, char *line, int pos, int i)
{
	if (ft_isope(line[pos]) == 1)
	{
		token->type = AND;
		i = pos;
		pos = pos + 2;
		add_lexeme(token, line, pos, i);
	}
	else if (ft_isope(line[pos]) == 2)
	{
		if (line[pos + 1] == '<')
		{
			token->type = DLESS;
			i = pos;
			pos = pos + 2;
			add_lexeme(token, line, pos, i);
		}
		else
		{
			token->type = LESS;
			i = pos;
			pos++;
			add_lexeme(token, line, pos, i);
		}
	}
	else if (ft_isope(line[pos]) == 3)
	{
		if (line[pos + 1] == '>')
		{
			token->type = DMORE;
			i = pos;
			pos = pos + 2;
			add_lexeme(token, line, pos, i);
		}
		else
		{
			token->type = MORE;
			i = pos;
			pos++;
			add_lexeme(token, line, pos, i);
		}
	}
	else if (ft_isope(line[pos]) == 4)
	{
		if (line[pos + 1] == '|')
		{
			token->type = OR;
			i = pos;
			pos = pos + 2;
			add_lexeme(token, line, pos, i);
		}
		else
		{
			token->type = PIPE;
			i = pos;
			pos++;
			add_lexeme(token, line, pos, i);
		}
	}
	else if (ft_isope(line[pos]) == 5)
	{
		token->type = SEMICOLON;
		i = pos;
		pos++;
		add_lexeme(token, line, pos, i);
	}
	return (pos);
}

int        ft_isprintnotope(char c)
{
	if (ft_isope(c) >= 1)
        return (0);
    else if (c == '(')
        return (0);
    else if (c == ')')
        return (0);
    else if (c == '$')
        return (0);
    else if (c == '`')
        return (0);
    else if (c == ' ')
        return (0);
    else if (c == '\t')
        return (0);
    else if (c == '\n')
        return (0);
    else if (c == '\"')
    	return (0);
    else if (c == '\'')
    	return (0);
    else if (ft_isprint(c) == 1)
        return (1);
    return (0);
}

void	print_tokens(t_token *token)
{
	int		i;

	i = 1;
	printf("\n***TOKEN_LIST***\n");
	while (token)
	{
		printf("TOKEN %d\n", i);
		printf("type : (%d)\n", token->type);
		printf("lexeme : (%s)\n", token->lexeme);
		token = token->next;
		i++;
	}
}

t_token	*init_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->next = NULL;
	return (token);
}