/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 02:04:21 by apinho            #+#    #+#             */
/*   Updated: 2016/09/20 15:36:34 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char const *s1)
{
	char	*s2;
	int		x;

	x = ft_strlen(s1);
	s2 = malloc(sizeof(*s1) * (x + 1));
	if (s2 == '\0')
		return (0);
	s2 = ft_strcpy(s2, s1);
	return (s2);
}
