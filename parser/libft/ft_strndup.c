/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/26 14:47:27 by apinho            #+#    #+#             */
/*   Updated: 2016/09/20 15:37:28 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strndup(char *str, int n)
{
	char	*result;
	int		i;

	if ((result = malloc(n + 1)) == NULL)
		return (NULL);
	i = -1;
	while (str[++i] && i < n)
		result[i] = str[i];
	result[i] = 0;
	return (result);
}
