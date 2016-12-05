/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 15:57:00 by sgaudin           #+#    #+#             */
/*   Updated: 2016/02/03 10:33:32 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*new_string;
	size_t	index;

	index = 0;
	if (s)
	{
		if (start + len <= ft_strlen(s))
		{
			new_string = (char*)malloc(sizeof(new_string) * ft_strlen(s) + 1);
			if (new_string != NULL)
			{
				while (index < len)
					new_string[index++] = s[start++];
				new_string[index] = '\0';
				return (new_string);
			}
		}
	}
	return (NULL);
}
