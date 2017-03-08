/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpathjoin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:51:21 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strpathjoin(const char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*s3;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (!s1 || !s2)
		return ((s1) ? ft_strdup(s1) : ft_strdup(s2));
	j = ft_strlen(s1);
	if (s1[j - 1] == '/' || s2[0] == '/')
		return ((s1[j - 1] == '/' && s2[0] == '/') ? \
	ft_strjoin(s1, ++s2) : ft_strjoin(s1, s2));
		if (!(s3 = (char *)malloc((j + ft_strlen(s2) + 2))))
		return (NULL);
	i = 0;
	ft_strcpy(s3, s1);
	s3[j++] = '/';
	while (s2[i])
	{
		s3[j] = s2[i];
		j++;
		i++;
	}
	s3[j] = '\0';
	return (s3);
}
