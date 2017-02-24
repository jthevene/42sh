/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by apinho            #+#    #+#             */
/*   Updated: 2017/02/24 18:33:20 by apinho           ###   ########.fr       */
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
