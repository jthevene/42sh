/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 12:59:02 by sgaudin           #+#    #+#             */
/*   Updated: 2016/12/15 12:59:03 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

int				push_content_path(t_bracket **l, char *s, t_glob *g)
{
	FT_INIT(char *, tmp, NULL);
	if (!bracket_pushback(l))
		return (0);
	if (g->f_path)
		tmp = ft_strjoin(g->f_path, s);
	else
		tmp = ft_strdup(s);
	if (g->l_path)
		(*l)->content = ft_strjoin(tmp, g->l_path);
	else
		(*l)->content = ft_strdup(tmp);
	free(s);
	free(tmp);
	return (1);
}

void	check_file(int len, char *s, char *file, t_glob **g)
{
	FT_INIT(int, i, -1);
	FT_INIT(int, j, -1);
	FT_INIT(char *, tmp, NULL);
	while (++j < len)
	{
		if (s[++i] == '[')
		{
			if (!ft_strchr((*g)->sbracket->content, file[j]))
				break ;
			(*g)->sbracket = (*g)->sbracket->next ? (*g)->sbracket->next : (*g)->sbracket;
			i += next_bracket(s, '[', i);
		}
		else if (s[i] == '*')
		{
			tmp = get_next_star(s, i + 1);
			if (!tmp)
			{
				push_content_path(&(*g)->args, ft_strdup(file), (*g));
//				printf("Création d'argument : %s\n", (*g)->args->content);
				break ;
			}
			if (ft_istrstr(file, tmp, j, (*g)))
				j = ft_istrstr(file, tmp, j, (*g));
			else
				break ;
			printf("check_file : tmp = %s, s : %s, file : %s, i : %d, j : %d\n", tmp, s, file, i, j);
			i += ft_strlen(tmp);
			if (!ft_istrchr(s, '*', i))
			{
				j++;
				break ;
			}
			if (tmp)
				free(tmp);
		}
		else if (s[i] != '?' && s[i] != '[' && s[i] != '*' && file[j] != s[i])
			break ;
	}
	if (j == len)
	{
		push_content_path(&(*g)->args, ft_strdup(file), (*g));
//		printf("Création d'argument : %s\n", (*g)->args->content);
	}
	if (tmp)
		free(tmp);
}
