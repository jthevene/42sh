/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 18:03:08 by sgaudin           #+#    #+#             */
/*   Updated: 2017/01/16 18:03:09 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

void			check_file(int len, char *s, char *file, t_glob **g)
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
			(*g)->sbracket = (*g)->sbracket->next
			? (*g)->sbracket->next : (*g)->sbracket;
			i += next_bracket(s, '[', i);
		}
		else if (s[i] == '*')
		{
			tmp = get_next_star(s, i + 1);
			if (!tmp)
			{
				push_content_path(&(*g)->args, ft_strdup(file), (*g));
				break ;
			}
			if (ft_istrstr(file, tmp, j, (*g)))
				j = ft_istrstr(file, tmp, j, (*g));
			else
				break ;
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
		push_content_path(&(*g)->args, ft_strdup(file), (*g));
	if (tmp)
		free(tmp);
}