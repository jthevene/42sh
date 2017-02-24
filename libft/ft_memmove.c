/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by apinho            #+#    #+#             */
/*   Updated: 2017/02/24 18:34:00 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*transfert;

	if (dst != NULL && src != NULL && len > 0)
	{
		transfert = (char*)malloc(sizeof(transfert) * (len + 1));
		ft_memcpy(transfert, (char*)src, len);
		ft_memcpy(dst, transfert, len);
		free(transfert);
		return (dst);
	}
	return (NULL);
}
