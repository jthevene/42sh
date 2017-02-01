/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 12:00:12 by apinho            #+#    #+#             */
/*   Updated: 2016/09/26 12:00:29 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinfree(char *s1, char *s2, int flag_str_to_free)
{
	size_t		len1;
	size_t		len2;
	char		*ret;

	if ((!s1 || !s2) && !flag_str_to_free)
		return (ft_strjoin(s1, s2));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(ret = (char *)malloc(sizeof(char) * (len1 + len2 + 1))))
		return (NULL);
	while (s1 && *s1)
		*ret++ = *s1++;
	while (s2 && *s2)
		*ret++ = *s2++;
	*ret = '\0';
	if (s1 && (flag_str_to_free == 1 || flag_str_to_free == 3))
		free(s1 - len1);
	if (s2 && (flag_str_to_free == 2 || flag_str_to_free == 3))
		free(s2 - len2);
	return (ret - len1 - len2);
}
