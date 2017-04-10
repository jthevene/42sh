/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_brck.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 18:40:11 by sgaudin           #+#    #+#             */
/*   Updated: 2017/04/10 14:58:33 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/globing.h"

char		*i2_recreate_string(char *str, int index, t_bracket *patterns)
{
	FT_INIT(char *, new_str, ft_strsub(str, 0, index));
	FT_INIT(char *, tmp, NULL);
	FT_INIT(int, i, 0);
	FT_INIT(int, j, 0);
	while (patterns->next)
	{
		tmp = ft_strjoin(new_str, patterns->content);
		free(new_str);
		new_str = ft_strjoin(tmp, ",");
		free(tmp);
		patterns = patterns->next;
	}
	tmp = ft_strjoin(new_str, patterns->content);
	free(new_str);
	index += next_comma(str, index);
	i = index;
	while (str[++index])
		j++;
	new_str = ft_strsub(str, i, j + 1);
	free(str);
	str = ft_strjoin(tmp, new_str);
	free(tmp);
	free(new_str);
	return (str);
}

void		i2_recup_patterns(char *str, char *tmp, int i, t_glob *glob)
{
	FT_INIT(t_clist *, multi, i_create_multi_list(ft_strdup(tmp)));
	FT_INIT(t_bracket *, patterns, NULL);
	FT_INIT(char *, tmp2, NULL);
	while ((tmp2 = i_multi_patterns(&multi, 0)))
	{
		bracket_pushback(&patterns);
		patterns->content = ft_strdup(tmp2);
		free(tmp2);
	}
	free_tclist(&multi);
	rewind_tbracket(&patterns);
	tmp2 = i2_recreate_string(str, i, patterns);
	free_tbracket(&patterns);
	i_algo_imbricated(tmp2, glob);
	free(tmp);
}

void		i2_hub_imbric(char *str, int i, t_glob *glob)
{
	FT_INIT(int, ret, 0);
	FT_INIT(char *, tmp, NULL);
	while (str[i] != '{')
		i++;
	while (str[++i])
	{
		if ((ret = next_comma(str, i)) == -1)
		{
			tmp = ft_strsub(str, i, ft_strlen(str) - i - 1);
			if (ft_strchr(tmp, '{'))
				i2_recup_patterns(str, tmp, i, glob);
			break ;
		}
		else
		{
			tmp = ft_strsub(str, i, ret);
			if (ft_strchr(tmp, '{'))
			{
				i2_recup_patterns(str, tmp, i, glob);
				break ;
			}
			i += next_comma(str, i);
			free(tmp);
		}
	}
}
