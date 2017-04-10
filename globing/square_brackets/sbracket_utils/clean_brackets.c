/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_brackets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 18:40:12 by sgaudin           #+#    #+#             */
/*   Updated: 2017/04/10 14:58:02 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/redir.h"
#include "../../../includes/globing.h"

char		*clean_brackets(char *str)
{
	FT_INIT(int, start, 0);
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
	if (!(ret = ft_strnew(len + 1)))
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
