/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 02:08:30 by apinho            #+#    #+#             */
/*   Updated: 2016/09/20 15:37:57 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	size_t	len;
	char	*dest;

	if (s == NULL)
		return (NULL);
	while (*s && ft_isspace(*s))
		s++;
	len = ft_strlen(s);
	while (*s && ft_isspace(s[--len]))
		;
	if (!(dest = ft_strnew(len)))
		return (NULL);
	dest = ft_strncpy(dest, s, len + 1);
	dest[len + 1] = '\0';
	return (dest);
}
