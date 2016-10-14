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

char	*clean_brackets(char *str) // enleve les []
{
	int		i;
	int		len;
	int		start;
	char	*ret;
	
	i = 0;
	ret = NULL;
	len = 0;
	while (str[i] != '[')
		i++;
	start = i + 1;
	while (str[++i] != ']')
		len++;
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

char	*get_rng_str(char *str, int i)// uac-rgs => "c-r"
{
	char	*rng_str;
	
	rng_str = NULL;
	rng_str = ft_strsub(str, i - 1, 3);
	return (rng_str);
}

int		get_len_mix(char *str)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, len, 0);
	FT_INIT(char *, tmp, clean_brackets(str));
	while (tmp[i])
	{
		if (tmp[i] == '-' && tmp[i + 1] && tmp[i - 1])
		{
			len += tmp[i + 1] - tmp[i - 1];
			i++;
		}
		else
			len++;
		i++;
	}
	free(tmp);
	return (len);
}