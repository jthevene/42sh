/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:51:14 by hjacque          ###   ########.fr       */
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
