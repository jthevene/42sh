/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 10:07:32 by sgaudin           #+#    #+#             */
/*   Updated: 2016/02/03 10:25:26 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*transfert;

	if (dst != NULL && src != NULL && len > 0)
	{
		transfert = (char*)malloc(sizeof(transfert) * len + 1);
		ft_memcpy(transfert, (char*)src, len);
		ft_memcpy(dst, transfert, len);
		free(transfert);
		return (dst);
	}
	return (NULL);
}
