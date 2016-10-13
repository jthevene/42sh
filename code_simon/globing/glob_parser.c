/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 11:43:43 by sgaudin           #+#    #+#             */
/*   Updated: 2016/10/05 11:44:49 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/globing.h"

static int 		verif_tokens(char *str)
{
	int 		nb;

	nb = 0;
	if (ft_strchr(str, '[') && !ft_strchr(str, ']'))
		return (0);
	else
		nb++;
	if (ft_strchr(str, '{') && !ft_strchr(str, '}'))
		return (0);
	else
		nb++;
	if (ft_strchr(str, '*') || ft_strchr(str, '?'))
		nb++;
	if (!nb)
		return (0);
	return (1);
}

t_glob			*init_glob(void)
{
	t_glob		*glob;

	glob = (t_glob *)malloc(sizeof(t_glob));
	ft_bzero(glob->upper, 27);
	ft_bzero(glob->lower, 27);
	ft_bzero(glob->alpha, 53);
	ft_bzero(glob->digit, 11);
	ft_bzero(glob->alnum, 63);
	ft_bzero(glob->space, 7);
	ft_bzero(glob->graph, 95);
	ft_bzero(glob->print, 96);
	ft_bzero(glob->punct, 33);
	ft_bzero(glob->cntrl, 34);
	ft_bzero(glob->xdigit, 17);
	init_tabs1(glob, 0, 0);
	init_tabs2(glob);
	init_tabs3(glob);
	return (glob);
}

int 			glob_parser(void)
{
	t_glob		*glob;

	if (!g_shell->line)
		return (0);
	if (!verif_tokens(g_shell->line))
		return (0);
	glob = init_glob();
//	ft_printf("upper : |%s|\nlower : |%s|\nalpha : |%s|\ndigit : |%s|\nalnum : |%s|\nspace : |%s|\ngraph : |%s|\nprint : |%s|\npunct : |%s|\ncntrl : |%s|\nxdigit : |%s|\n",
//		glob->upper, glob->lower, glob->alpha, glob->digit, glob->alnum, glob->space, glob->graph, glob->print, glob->punct, glob->cntrl, glob->xdigit);
//	if (ft_strchr(g_shell->line, '['))
//		hub_bracket(&glob);
	free(glob);
	return (1);
}