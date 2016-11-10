/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 14:31:22 by apinho            #+#    #+#             */
/*   Updated: 2016/11/10 12:12:02 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parse.h"

char	*search(char *src, char *str1, char *str2)
{
	int i;
	int j;
	int	firstOcc;

	i = 0;
	j = 0;
	while (src[i] != '\0')
	{
		while (src[i] != str1[0] && src[i] != str2[0] && src[i] != '\0')
			i++;
		if (src[i] == '\0')
			return (NULL);
		firstOcc = i;
		while (src[i] == str1[j] && src[i] != '\0' && str1[j] != '\0')
		{
			i++;
			j++;
		}
		if (!str1[j])
			return ((char*)&src[firstOcc]);
		while (src[i] == str2[j] && src[i] != '\0' && str2[j] != '\0')
		{
			i++;
			j++;
		}
		if (str2[j] == '\0')
			return ((char*)&src[firstOcc]);
		if (src[i] == '\0')
			return (NULL);
		i = firstOcc + 1;
		j = 0;
	}
	return (NULL);
}
