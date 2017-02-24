/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isallspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by apinho            #+#    #+#             */
/*   Updated: 2017/02/24 18:35:19 by apinho           ###   ########.fr       */
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

char	*trim_end(char *line)
{
	int		i;
	char	*ret;

	i = ft_strlen(line) - 1;
	while (line[i] == ' ' || line[i] == '\t')
		i--;
	ret = ft_strndup(line, i + 1);
	free(line);
	return (ret);
}
