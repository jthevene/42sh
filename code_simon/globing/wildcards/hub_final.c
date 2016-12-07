/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub_final.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 09:37:08 by sgaudin           #+#    #+#             */
/*   Updated: 2016/12/07 09:37:09 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

void		hub_final(t_glob *glob) // Hub final du traitement globing
{
	FT_INIT(int, i, 0);
	FT_INIT(char *, tmp, NULL);
	while (g_shell.line[i] != ' ')
		i++;
	i++;
	while (g_shell.line[i])
	{
		tmp = next_expr(g_shell.line, i);
		i += ft_strlen(tmp);
		printf("tmp = %s\n", tmp);
	}
}