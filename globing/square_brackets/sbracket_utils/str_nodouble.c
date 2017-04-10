/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_nodouble.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 18:40:12 by sgaudin           #+#    #+#             */
/*   Updated: 2017/04/10 14:57:59 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/redir.h"
#include "../../../includes/globing.h"

char			*strjoin_nodouble(char *s1, char *s2)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, j, -1);
	FT_INIT(char *, tmp, NULL);
	FT_INIT(char *, ret, NULL);
	if (!s1 || !s2)
		return (NULL);
	tmp = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	while (s1[i])
	{
		if (!ft_strchr(tmp, s1[i]))
			tmp[++j] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		if (!ft_strchr(tmp, s2[i]))
			tmp[++j] = s2[i];
		i++;
	}
	ret = ft_strdup(tmp);
	free(tmp);
	return (ret);
}

char			*strdup_nodouble(char *str)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, j, -1);
	FT_INIT(char *, tmp, NULL);
	FT_INIT(char *, ret, NULL);
	if (!str)
		return (NULL);
	tmp = ft_strnew(ft_strlen(str) + 1);
	while (str[i])
	{
		if (!ft_strchr(tmp, str[i]))
			tmp[++j] = str[i];
		i++;
	}
	tmp[++j] = '\0';
	ret = ft_strdup(tmp);
	free(tmp);
	return (ret);
}

char			*mult_nodouble(char *str)
{
	FT_INIT(char *, ret, NULL);
	ret = strdup_nodouble(str);
	free(str);
	return (ret);
}
