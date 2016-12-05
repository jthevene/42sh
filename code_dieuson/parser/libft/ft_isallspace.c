/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isallspace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/03 11:24:37 by hjacque           #+#    #+#             */
/*   Updated: 2016/11/10 12:09:54 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isallspace(char *str)
{
	unsigned int i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (i == (ft_strlen(str)))
		return (1);
	else
		return (0);
}