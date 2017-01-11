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

int		ft_check_bracket(char *s1, int i, int stop, t_glob *g)
{
	FT_INIT(int, ret, 0);
	FT_INIT(char, last, i - 1 >= 0 ? s1[i - 1] : '\0');
	while (s1[i])
	{
		if (last)
		{
			if (ft_strchr(g->sbracket->content, s1[i]) && s1[i - 1] == last)
			{
				if (stop == TRUE)
					return (i);
				else
					ret = i;
			}			
		}
		else if (ft_strchr(g->sbracket->content, s1[i]))
		{
			if (stop == TRUE)
				return (i);
			else
				ret = i;
		}
		i++;
	}
	return (ret);
}

int		ft_istrstr(char *s1, char *s2, int i, t_glob *g)
{
	FT_INIT(int, j, 0);
	FT_INIT(int, ret, 0);
	FT_INIT(int, taille, ft_strlen(s2));
	if (!taille || !g)
		return (0);
	i = s2[j] == '?' ? i + 1 : i;
	while (s1[i])
	{
		j = s2[j] == '?' ? j + 1 : j;
		ret = i + j;
		while (s1[i + j] && s2[j] && (s1[i + j] == s2[j] || s2[j] == '[' || s2[j] == '?'))
		{
			if (s2[j] == '[')
			{
				ret = ft_check_bracket(s1, i + j
				, j + next_bracket(s2, '[', j) == taille - 1 ? FALSE : TRUE, g);
				j += next_bracket(s2, '[', j);
//				printf("s1 = %s, s2 = %s, ret = %d, j = %d\n", s1, s2, ret, j);
			}
			if (j == taille - 1)
			{
//				printf("ret = %d\n", ret);
				return (ret);
			}
//			j += s2[j] == '[' ? next_bracket(s2, '[', j) : 1;
			j++;
			ret++;
		}
		j = 0;
		i++;
	}
//	printf("%s ===> fail ret = %d\n", s1, ret);
	return (0);
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
//			printf("check_file : tmp = %s, s : %s, file : %s, i : %d, j : %d, len : %d\n", tmp, s, file, i, j, len);
			i += ft_strlen(tmp);
			if (!ft_istrchr(s, '*', i))
			{
				j++;
				break ;
			}
			else if (ft_istrchr(s, '*', i) && j + 1 == len)
				j--;
			if (tmp)
				free(tmp);
			tmp = NULL;
		}
		else if (s[i] != '?' && s[i] != '[' && s[i] != '*' && file[j] != s[i])
			break ;
	}
	if (j == len && i + 1 == (int)ft_strlen(s))
	{
		push_content_path(&(*g)->args, ft_strdup(file), (*g));
//		printf("Création d'argument : %s\n", (*g)->args->content);
	}
	if (tmp)
		free(tmp);
}
