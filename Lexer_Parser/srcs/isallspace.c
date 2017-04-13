/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isallspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/04/13 10:15:50 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int		isallspace(char *str)
{
	unsigned int i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (i == (ft_strlen(str)))
		return (1);
	else
		return (0);
}

char	*epur_str(char *str)
{
	char	*tmp;
	int		i;
	int		k;

	i = 0;
	k = 0;
	tmp = malloc(sizeof(*tmp) * (ft_strlen(str) + 1));
	while ((str[i] == ' ') || (str[i] == '\t'))
		i++;
	while (str[i])
	{
		tmp[k++] = str[i++];
		while ((str[i] == ' ') || (str[i] == '\t'))
			i++;
		if (((str[i - 1] == ' ') || (str[i - 1] == '\t')) && (str[i]))
		{
			tmp[k] = ' ';
			k++;
		}
	}
	tmp[k] = '\0';
	free(str);
	return (tmp);
}

char	*trim_end(char *line)
{
	int		i;
	char	*ret;

	i = ft_strlen(line) - 1;
	while (line[i] == ' ' || line[i] == '\t')
		i--;
	ret = ft_strndup(line, i + 1);
	free(line);
	return (ret);
}

int		and_or_error(t_token *token, char *line, int pos, int i)
{
	if (line[pos + 1] == '&')
	{
		token->type = AND;
		i = pos;
		pos = pos + 2;
		add_lexeme(token, line, pos, i);
	}
	else
	{
		token->type = 50;
		i = pos;
		pos++;
		add_lexeme(token, line, pos, i);
	}
	return (pos);
}
