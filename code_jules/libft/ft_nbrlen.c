/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthevene <jthevene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/16 15:39:09 by jthevene          #+#    #+#             */
/*   Updated: 2015/10/30 15:07:05 by jthevene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_nbrlen(int i)
{
	int		len;
	char	*ret;

	len = 0;
	ret = ft_itoa(i);
	len = ft_strlen(ret);
	free(ret);
	return (len);
}
