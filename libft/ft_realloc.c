/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 13:07:21 by apinho            #+#    #+#             */
/*   Updated: 2016/09/20 15:36:05 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_realloc(void *str, int sizebase, int size)
{
	unsigned char	*tmp;
	unsigned char	*step;
	int				i;

	tmp = NULL;
	if (!(tmp = (unsigned char *)malloc((size_t)sizebase)))
		return (NULL);
	i = -1;
	step = (unsigned char *)str;
	while (i <= sizebase)
		tmp[i] = step[i];
	free(str);
	if (!(str = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	i = -1;
	while (++i <= sizebase)
		step[i] = tmp[i];
	tmp[size] = 0;
	return (str);
}
