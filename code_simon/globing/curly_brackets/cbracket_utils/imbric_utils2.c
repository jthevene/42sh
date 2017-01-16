/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imbric_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 10:27:41 by sgaudin           #+#    #+#             */
/*   Updated: 2016/11/30 10:27:41 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/globing.h"

int				i_detect_imbric(char *str)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, j, 0);
	FT_INIT(int, count, 0);
	while (str[i])
	{
		if (str[i] == '{')
		{
			j = i + 1;
			count = 0;
			while (str[j] != '}')
			{
				if (str[j] == '{')
					return (count);
				count++;
				j++;
			}
		}
		i++;
	}
	return (-1);
}

char			*expand_pattern(char *pat, t_glob *glob)
{
	FT_INIT(char *, tmp, NULL);
	FT_INIT(char *, ret, NULL);
	if (!glob->ext_args[0] && !glob->ext_args[1])
		ret = ft_strdup(pat);
	else
	{
		tmp = glob->ext_args[0] ? ft_strjoin(glob->ext_args[0], pat) : NULL;
		if (glob->ext_args[1])
			ret = tmp ? ft_strjoin(tmp, glob->ext_args[1])
			: ft_strjoin(pat, glob->ext_args[1]);
		else
			ret = ft_strdup(tmp);
	}
	if (tmp)
		free(tmp);
	return (ret);
}
