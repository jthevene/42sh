/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isallspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 14:31:22 by apinho            #+#    #+#             */
/*   Updated: 2016/09/26 14:11:45 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int		isallspace(char *str)
{
	unsigned int i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (i == (ft_strlen(str)))
		return (1);
	else
		return (0);
}

char	*epur_str(char *str)
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
