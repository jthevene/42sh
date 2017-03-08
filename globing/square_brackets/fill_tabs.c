/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tabs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:46:17 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

char			*fill_rng(char *str)
{
	FT_INIT(int, diff, 0);
	FT_INIT(int, i, 0);
	FT_INIT(int, last, 1);
	FT_INIT(char *, ret, NULL);
	FT_INIT(char *, tmp, ft_strchr(str, '[')
		? clean_brackets(str) : ft_strdup(str));
	FT_INIT(int, first, tmp[0]);
	while (tmp[last] != '-')
		last++;
	if (!(ret = (char *)malloc(sizeof(char) * (tmp[2] - tmp[0] + 1))))
		return (NULL);
	last++;
	diff = tmp[last] - tmp[0];
	while (i <= diff)
	{
		ret[i] = first;
		i++;
		first++;
	}
	ret[i] = '\0';
	free(tmp);
	tmp = strdup_nodouble(ret);
	free(ret);
	return (tmp);
}

char			*fill_nomult(char *str)
{
	FT_INIT(int, i, 32);
	FT_INIT(int, j, 0);
	FT_INIT(char *, tmp, ft_strchr(str, '[')
		? clean_brackets(str) : ft_strdup(str));
	FT_INIT(char *, ret, strdup_nodouble(tmp));
	free(tmp);
	tmp = ft_strdup(ret);
	free(ret);
	if (!(ret = (char *)malloc(sizeof(char) * (94 - ft_strlen(tmp)) + 2)))
		return (NULL);
	while (i <= 126)
	{
		if (!strchr(tmp, i))
		{
			ret[j] = i;
			j++;
		}
		i++;
	}
	ret[j] = '\0';
	free(tmp);
	return (ret);
}

char			*fill_norng(char *str)
{
	FT_INIT(int, i, 32);
	FT_INIT(int, j, 0);
	FT_INIT(int, last, 0);
	FT_INIT(char *, ret, NULL);
	FT_INIT(char *, tmp, clean_brackets(str));
	FT_INIT(int, first, tmp[1]);
	if (!(ret = ft_strnew((94 - (tmp[2] - tmp[0])) + 1)))
		return (NULL);
	while (tmp[last] != '-')
		last++;
	last++;
	while (i <= 126)
	{
		if (i == first)
			i = tmp[last] + 1;
		ret[j] = i;
		i++;
		j++;
	}
	ret[j] = '\0';
	free(tmp);
	return (ret);
}

static void		create_mix(char *tmp_str, char **ret, int i)
{
	FT_INIT(char *, tmp_rng, NULL);
	FT_INIT(char *, tmp_rng2, NULL);
	FT_INIT(char *, tmp_ret, NULL);
	tmp_rng2 = get_rng_str(tmp_str, i);
	tmp_rng = fill_rng(tmp_rng2);
	tmp_ret = (*ret);
	(*ret) = strjoin_nodouble(tmp_rng, (*ret));
	free(tmp_rng);
	free(tmp_rng2);
	free(tmp_ret);
}

char			*fill_mix(char *str)
{
	FT_INIT(int, i, 0);
	FT_INIT(char *, tmp_ret, NULL);
	FT_INIT(char *, tmp_str, clean_brackets(str));
	FT_INIT(char *, ret, ft_strnew(get_len_mix(tmp_str) + 1));
	get_letters(&ret, tmp_str);
	while (tmp_str[i])
	{
		if (tmp_str[i] == '-')
			create_mix(tmp_str, &ret, i);
		i++;
	}
	if (tmp_str[0] == '!')
	{
		tmp_ret = fill_nomult(ret);
		free(tmp_str);
		free(ret);
		return (tmp_ret);
	}
	free(tmp_str);
	return (ret);
}
