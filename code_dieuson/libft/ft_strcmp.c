/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/21 16:47:21 by sgaudin           #+#    #+#             */
/*   Updated: 2016/02/03 10:28:08 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int				i;
	unsigned char	*tmp1;
	unsigned char	*tmp2;

	i = 0;
	if (!s1 || !s2)
		return (0);
	tmp1 = (unsigned char *)s1;
	tmp2 = (unsigned char *)s2;
	while (tmp1[i] != '\0' && tmp2[i] != '\0' && tmp1[i] == tmp2[i])
		i++;
	return (tmp1[i] - tmp2[i]);
}
