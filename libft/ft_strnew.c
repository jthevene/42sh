/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 11:55:16 by sgaudin           #+#    #+#             */
/*   Updated: 2016/02/03 10:32:26 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strnew(size_t size)
{
	char *string;

	string = (char*)malloc(sizeof(*string) * size + 1);
	if (string != NULL)
		ft_bzero(string, size + 1);
	else
		return (NULL);
	return (string);
}
