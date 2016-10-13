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

/*
static char		*get_rng_str(char *str, int i)// uac-rgs => "c-r"
{
	char	*rng_str;
	
	rng_str = NULL;
	rng_str = ft_strsub(str, i - 1, 3);
	return (rng_str);
}
*/
char	*fill_rng(char *str) // globbing [a-c] str = "a-c", return une str avec tous les char imprimables sauf "abc"
{
	int		i;
	int		first;
	int		last;
	int		diff;
	char	*ret;

	i = 0;
	first = str[0];
	last = 1;
	ret = NULL;
	str = clean_brackets(str);
	while (str[last] != '-')
		last++;
	if (!(ret = (char *)malloc(sizeof(char) * (str[2] - str[0] + 1))))
		return (NULL);
	last++;
	diff = str[last] - str[0];
	while (i <= diff)
	{
		ret[i] = first;
		i++;
		first++;
	}
	ret[i] = '\0';
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
		return (NULL);	while (i <= 126)
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
	int		i;
	int		j;
	int		first;
	int		last;
	char	*ret;

	i = 32;
	j = 0;
	first = str[0];
	last = 0;
	ret = NULL;
	str = clean_brackets(str);
	if (!(ret = (char *)malloc(sizeof(char) * (94 - (str[2] - str[0])) + 1)))
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

char	*fill_mix(char *str) /*** Probleme de compte sur le ;en, a revoir ! ***/
{
	FT_INIT(int, i, 0);
	FT_INIT(int, len, 0);
	FT_INIT(char *, ret, NULL);
	str = clean_brackets(str);
	while (str[i])
	{
		if (str[i] == '-' && str[i + 1] && str[i - 1])
		{
			len += str[i + 1] - str[i - 1];
			i++;
		}
		len++;
		i++;
	}
	if (!(ret = (char *)malloc(sizeof(char) * len + ft_strlen(str) - 2)))
		return (NULL);
	printf("len = %d\n", len);
	return (NULL);
}