/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets_cases.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 12:36:19 by jules             #+#    #+#             */
/*   Updated: 2016/10/07 13:34:21 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/redir.h"
#include "../includes/globing.h"

char	*fill_rng(char *str) /* Test de la derniere fois : ls [a-c] ---> lmn... A corriger. */
{
	int		diff;

	FT_INIT(int, i, 0);
	FT_INIT(int, first, str[0]);
	FT_INIT(int, last, 1);
	FT_INIT(char *, ret, NULL);
	FT_INIT(char *, tmp, clean_brackets(str));
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
	printf("ret = %s\n", ret);
	free(tmp);
	return (ret);
}

char	*fill_nomult(char *str) // [!...]
{
	int		i;
	int		j;
	char	*ret;

	i = 32;
	j = 0;
	ret = NULL;
	str = clean_brackets(str);
	if (!(ret = (char *)malloc(sizeof(char) * (94 - ft_strlen(str)) + 1)))
		return (NULL);
	while (i <= 126)
	{
		if (!strchr(str, i))
		{
			ret[j] = i;
			j++;
		}
		i++;
	}
	ret[j] = '\0';
	return (ret);
}

char	*fill_norng(char *str) // [!.-.]
{
	FT_INIT(int, i, 32);
	FT_INIT(int, j, 0);
	FT_INIT(int, first, str[0]);
	FT_INIT(int, last, 0);
	FT_INIT(char *, ret, NULL);
	str = clean_brackets(str);
	if (!(ret = (char *)malloc(sizeof(char) * (94 - (str[2] - str[0])) + 1)))
		return (NULL);
	while (str[last] != '-')
		last++;
	last++;
	while (i <= 126)
	{
		if (i == first)
			i = str[last] + 1;
		ret[j] = i;
		i++;
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

/*

char	*fill_mix(char *str, int i) // [ae-rt]
{
	FT_INIT(int, j, 0);
	FT_INIT(int, k, 0);
	char	*ret;

	if (ft_strchr(str, '[') && ft_strchr(str, ']'))
		str = clean_brackets(str);
	while (str[i] != '-')
		i++;
	if (!(ret = (char *)malloc(sizeof(char) * (str[i + 1] - str[i - 1]) + ft_strlen(str) - 2)))
		return (NULL);
	while (str[j] != '\0')
	{
		if (j == i - 1)
			j += 3;
		ret[k] = str[j];
		j++;
		k++;
	}
	ret = ft_strjoin(fill_rng(get_rng_str(str, i)), ret);
	if (str[1] == '!')
		ret = fill_nomult(ret);
	return (ret);
}

*/

char	*fill_mix(char *str)
{
	FT_INIT(int, i, 0);
	FT_INIT(char *, tmp, clean_brackets(str));
	FT_INIT(char *, ret, NULL);
	if (!(ret = (char *)malloc(sizeof(char) * get_len_mix(tmp) + 1)))
		return (NULL);
	ft_bzero(ret, get_len_mix(tmp));
	get_letters(&ret, tmp);
	printf("ret first phase = %s\n", ret);
	while (str[i])
	{
		if (str[i] == '-')
		{

		}
		i++;
	}
	free(tmp);
	free(ret);
	return (NULL);
}
