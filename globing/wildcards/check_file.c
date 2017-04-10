/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 19:41:58 by sgaudin           #+#    #+#             */
/*   Updated: 2017/04/10 14:57:49 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

static t_checkfile	*init_checkfile(int *i, int *j, int len, char *s)
{
	FT_INIT(t_checkfile *, cf, NULL);
	if (!(cf = (t_checkfile *)malloc(sizeof(t_checkfile))))
		return (NULL);
	cf->i = i;
	cf->j = j;
	cf->len = len;
	cf->s = ft_strdup(s);
	return (cf);
}

static int			free_checkfile(char **tmp, t_checkfile **cf)
{
	if (tmp && (*tmp))
		free((*tmp));
	if (cf && (*cf))
	{
		if ((*cf)->s)
			free((*cf)->s);
		if ((*cf)->file)
			free((*cf)->file);
		free((*cf));
		(*cf) = NULL;
	}
	return (0);
}

static int			check_star(char *file, t_checkfile *cf, t_glob *g)
{
	FT_INIT(char *, tmp, get_next_star(cf->s, (*cf->i) + 1));
	FT_INIT(int, ret, 0);
	cf->file = ft_strdup(file);
	if (!tmp)
	{
		push_content_path(&g->args, ft_strdup(cf->file), g);
		return (free_checkfile(&tmp, &cf));
	}
	if ((ret = ft_istrstr(cf->file, tmp, (*cf->j), g)))
		(*cf->j) = ret == -1 ? 0 : ft_istrstr(cf->file, tmp, (*cf->j), g);
	else
		return (free_checkfile(&tmp, &cf));
	(*cf->i) += ft_strlen(tmp);
	if (!ft_istrchr(cf->s, '*', (*cf->i)))
	{
		(*cf->j)++;
		return (free_checkfile(&tmp, &cf));
	}
	else if (ft_istrchr(cf->s, '*', (*cf->i)) && (*cf->j) + 1 == cf->len)
		(*cf->j)--;
	if (tmp)
		free(tmp);
	tmp = NULL;
	return (1);
}

void				check_file(int len, char *s, char *file, t_glob **g)
{
	FT_INIT(int, i, -1);
	FT_INIT(int, j, -1);
	FT_INIT(t_checkfile *, cf, NULL);
	while (++j < len)
	{
		if (s[++i] == '[')
		{
			if (!ft_strchr((*g)->sbracket->content, file[j]))
				break ;
			(*g)->sbracket = (*g)->sbracket->next
			? (*g)->sbracket->next : (*g)->sbracket;
			i += next_bracket(s, '[', i);
		}
		else if (s[i] == '*')
		{
			cf = init_checkfile(&i, &j, len, s);
			if (!check_star(file, cf, (*g)))
				break ;
			free_checkfile(NULL, &cf);
		}
		else if (s[i] != '?' && s[i] != '[' && s[i] != '*' && file[j] != s[i])
			break ;
	}
	if (j == len && i + 1 == (int)ft_strlen(s))
		push_content_path(&(*g)->args, ft_strdup(file), (*g));
}
