/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 18:23:31 by sgaudin           #+#    #+#             */
/*   Updated: 2016/12/12 18:23:31 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

int		get_len_token(char *str)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, len, 0);
	while (str[i])
	{
		if (str[i] != '*' && str[i] != '[')
			len++;
		if (str[i] == '[')
		{
			len++;
			i += next_bracket(str, '[', i);
		}
		i++;
	}
	return (len);
}

void	check_file(int len, char *s, char *file, t_glob **g)
{
	FT_INIT(int, i, -1);
	FT_INIT(int, j, -1);
	FT_INIT(char *, tmp, NULL);
	while (++j < len)
	{
		if (s[++i] == '[' && ft_strchr((*g)->sbracket->content, file[j]))
		{
			(*g)->sbracket = (*g)->sbracket->next ? (*g)->sbracket->next : (*g)->sbracket;
			i += next_bracket(s, '[', i);
		}
		else if (s[i] == '*')
		{
			tmp = get_next_star(s, i + 1);
			if (!tmp)
			{
				pushback_content(&(*g)->args, ft_strdup(file));
				printf("Création d'argument : %s\n", (*g)->args->content);
				break ;
			}
			if (ft_istrstr(file, tmp, j))
				j = ft_istrstr(file, tmp, j);
			else
				break ;
			i++;
		}
		else if (s[i] != '?' && s[i] != '[' && s[i] != '*' && file[j] != s[i])
			break ;
	}
	if (j == len)
	{
		pushback_content(&(*g)->args, ft_strdup(file));
		printf("Création d'argument : %s\n", (*g)->args->content);
	}
	if (tmp)
		free(tmp);
}

char	*get_token(char *str)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, i2, 0);
	FT_INIT(int, j, 0);
	while (str[i] && !ft_strchr("*[?", str[i]))
		i++;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '/')
		i--;
	i2 = ++i;
	while (str[i] && str[i] != '/')
	{
		i++;
		j++;
	}
	return (ft_strsub(str, i2, j));
}

char	*get_next_star(char *str, int i)
{
	FT_INIT(int, start, i);
	FT_INIT(int, len, 0);
	while (str[i] && str[i] != '*')
	{
		len++;
		i++;
	}
	if (!len)
		return (NULL);
	return (ft_strsub(str, start, len));
}

int		ft_istrstr(const char *s1, const char *s2, int i)
{
	FT_INIT(int, j, 0);
	FT_INIT(int, taille, ft_strlen(s2));
	if (taille == 0)
		return (0);
	while (s1[i] != '\0')
	{
		while (s1[i + j] == s2[j])
		{
			if (j == taille - 1)
				return (i + j);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}