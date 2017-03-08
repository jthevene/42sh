/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:50:48 by hjacque          ###   ########.fr       */
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
