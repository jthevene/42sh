/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 15:01:24 by sgaudin           #+#    #+#             */
/*   Updated: 2016/10/14 15:01:47 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/redir.h"
#include "../includes/globing.h"

char		*clean_brackets(char *str) // enleve les []
{
	int		start;

	FT_INIT(int, i, 0);
	FT_INIT(int, len, 0);
	FT_INIT(char *, ret, NULL);
	while (str[i] && str[i] != '[')
		i++;
	start = i + 1;
	i++;
	while (str[i] && str[i] != ']')
	{
		i++;
		len++;
	}
	if (!(ret = (char *)malloc(sizeof(char) * len)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		ret[i] = str[start];
		i++;
		start++;
	}
	ret[i] = '\0';
	return (ret);
}

int			check_rng(char *str) // Check si on a un rng valide ([a-g] valide, [z-a] invalide)
{
	FT_INIT(int, i, 0);
	FT_INIT(char *, tmp, clean_brackets(str));
	if (!ft_strchr(tmp, '-'))
	{
		free(tmp);
		return (1);
	}
	while (tmp[i])
	{
		if (tmp[i] == '-' && tmp[i - 1] && tmp[i + 1] 
			&& tmp[i + 1] != ']' && tmp[i - 1] != '[')
		{
			if (tmp[i - 1] > tmp[i + 1])
			{
				free(tmp);
				return (0);
			}
			i++;
		}
		i++;
	}
	free(tmp);
	return (1);
}
