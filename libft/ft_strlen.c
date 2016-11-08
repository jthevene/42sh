/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 15:05:31 by jthevene          #+#    #+#             */
/*   Updated: 2016/11/08 12:36:28 by jules            ###   ########.fr       */
=======
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 15:02:40 by sgaudin           #+#    #+#             */
/*   Updated: 2016/02/03 10:30:58 by sgaudin          ###   ########.fr       */
>>>>>>> 6694b3e1eadb64e40e9b0e4df29760ea8067343f
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
<<<<<<< HEAD
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
=======
	if (!s)
		return (0);
	while (s[i])
>>>>>>> 6694b3e1eadb64e40e9b0e4df29760ea8067343f
		i++;
	return (i);
}
