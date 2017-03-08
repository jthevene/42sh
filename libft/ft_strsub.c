/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:51:24 by hjacque          ###   ########.fr       */
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
			new_string = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1));
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
