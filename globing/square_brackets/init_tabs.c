/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tabs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 18:40:11 by sgaudin           #+#    #+#             */
/*   Updated: 2017/04/10 14:57:54 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

void		init_tabs1(t_glob *glob, int i, int j)
{
	FT_INIT(char, c, 64);
	while (++c <= 'Z')
	{
		FT_MULTI4(glob->upper[i], glob->alpha[j], glob->alnum[j], c);
		i++;
		j++;
	}
	i = 0;
	c = 96;
	while (++c <= 'z')
	{
		FT_MULTI4(glob->lower[i], glob->alpha[j], glob->alnum[j], c);
		i++;
		j++;
	}
	i = 0;
	c = 47;
	while (++c <= '9')
	{
		FT_MULTI4(glob->digit[i], glob->alnum[j], glob->xdigit[i], c);
		i++;
		j++;
	}
}

void		init_tabs2(t_glob *glob)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, j, 0);
	FT_INIT(char, c, 32);
	while (++c <= 126)
	{
		if ((c >= 33 && c <= 47) || (c >= 58 && c <= 64) ||
			(c >= 91 && c <= 96) || (c >= 123 && c <= 126))
		{
			glob->punct[j] = c;
			j++;
		}
		FT_MULTI3(glob->graph[i], glob->print[i], c);
		i++;
	}
	glob->print[i] = 32;
	i = 0;
	c = 1;
	while (c <= 31)
	{
		glob->cntrl[i] = c;
		i++;
		c++;
	}
	glob->cntrl[i] = 127;
	glob->cntrl[++i] = 0;
}

void		init_tabs3(t_glob *glob)
{
	glob->space[0] = ' ';
	glob->space[1] = '\t';
	glob->space[2] = '\n';
	glob->space[3] = '\r';
	glob->space[4] = '\v';
	glob->space[5] = '\f';
	glob->space[6] = '\0';
	glob->xdigit[10] = 'A';
	glob->xdigit[11] = 'B';
	glob->xdigit[12] = 'C';
	glob->xdigit[13] = 'D';
	glob->xdigit[14] = 'E';
	glob->xdigit[15] = 'F';
}
