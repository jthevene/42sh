/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 15:09:32 by sgaudin           #+#    #+#             */
/*   Updated: 2016/02/03 10:37:22 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*temp;
	unsigned int	i;

	i = 0;
	temp = s;
	if (n > 0)
	{
		while (i < n)
		{
			temp[i] = '\0';
			i++;
		}
	}
}
