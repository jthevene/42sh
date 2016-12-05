/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 02:05:20 by apinho            #+#    #+#             */
/*   Updated: 2016/09/21 23:03:50 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*ret;

	if (s1 == NULL || s2 == NULL)
	{
		if (s1 == NULL && s2 != NULL)
			return (ft_strdup(s2));
		if (s1 != NULL && s2 == NULL)
			return (ft_strdup(s1));
		if (s1 == NULL && s2 == NULL)
			return (NULL);
	}
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(ret = (char *)malloc(sizeof(char) * (len1 + len2 + 1))))
		return (NULL);
	while (s1 && *s1)
		*ret++ = *s1++;
	while (s2 && *s2)
		*ret++ = *s2++;
	*ret = '\0';
	return (ret - len1 - len2);
}
