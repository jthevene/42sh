/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:51:19 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char		*ft_strndup(char *str, int n)
{
	char	*result;
	int		i;

	if ((result = (char *)malloc(sizeof(char) * (n + 1))) == NULL)
		return (NULL);
	i = -1;
	while (str[++i] && i < n)
		result[i] = str[i];
	result[i] = 0;
	return (result);
}
