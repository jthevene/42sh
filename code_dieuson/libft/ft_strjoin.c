/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 15:33:45 by sgaudin           #+#    #+#             */
/*   Updated: 2016/02/03 10:30:35 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	size;
	char			*joined;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	joined = (char*)malloc(sizeof(joined) * size);
	joined = ft_strnew(size);
	if (joined == NULL)
		return (NULL);
	joined = ft_strcat(joined, s1);
	joined = ft_strcat(joined, s2);
	return (joined);
}
