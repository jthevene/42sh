/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 14:42:31 by apinho            #+#    #+#             */
/*   Updated: 2016/10/05 19:38:28 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_tablen(char **tableau)
{
	int	i;

	i = 0;
	if (tableau == NULL)
		return (0);
	while (tableau[i])
		i++;
	return (i);
}

char	**ft_tabdup(char **tableau)
{
	char	**ret;
	int		i;

	i = 0;
	ret = (char**)malloc(sizeof(char*) * (ft_tablen(tableau) + 1));
	while (tableau && tableau[i])
	{
		ret[i] = ft_strdup(tableau[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
