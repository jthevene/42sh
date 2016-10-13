/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square_brackets.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/06 15:37:04 by sgaudin           #+#    #+#             */
/*   Updated: 2016/10/06 15:37:18 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/globing.h"

static int 		catch_dash(int i)
{
	int 		nb;

	nb = 0;
	while (g_shell->line[i] != ']')
	{
		if (g_shell->line[i] == '-')
			nb++;
		i++;
	}
	return (nb);
}

void 			hub_bracket(void)
{
	FT_INIT(int, i, 0);
	while (g_shell->line[i])
	{
		if (g_shell->line[i] == '[' && g_shell->line[i + 1] == '!')
		{
			if (catch_dash(i) >= 1) /* [!..-..] */
				fill_norng(g_shell->line);
			else if (catch_dash(i) == 0) /* [!...] */
				fill_nomult(g_shell->line);
		}
		else
		{
			if (catch_dash(i) == 1) /* [..-..] */
				fill_rng(g_shell->line);
			else if (catch_dash(i) == 0) /* [...] */
				//fill_mult(g_shell->line, glob);
				;
		}
		i++;
	}
}