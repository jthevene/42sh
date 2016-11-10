/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_epurstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 16:44:56 by hjacque           #+#    #+#             */
/*   Updated: 2016/11/10 12:06:16 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_epurstr(char *str)
{
	char	*tmp;
	int		i;
	int		k;

	i = 0;
	k = 0;
	tmp = malloc(sizeof(*tmp) * (ft_strlen(str) + 1));
	while ((str[i] == ' ') || (str[i] == '\t'))
		i++;
	while (str[i])
	{
		tmp[k++] = str[i++];
		while ((str[i] == ' ') || (str[i] == '\t'))
			i++;
		if (((str[i - 1] == ' ') || (str[i - 1] == '\t')) && (str[i]))
		{
			tmp[k] = ' ';
			k++;
		}
	}
	tmp[k] = '\0';
	free(str);
	return (tmp);
}