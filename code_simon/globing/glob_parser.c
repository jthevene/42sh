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

static int		verif_tokens(char *str)
{
	int			nb;

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

static void		get_command(char *str)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, len, 0);
//	FT_INIT(char *, str, NULL);

	while (str[i] && str[i] != ' ')
		i++;
	i++;
	while (str[i] && str[i] != ' ')
	{
		i++;
		len++;
	}
	printf("len = %d\n", len);
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
	glob->mult = NULL;
	glob->no_mult = NULL;
	glob->rng = NULL;
	glob->no_rng = NULL;
	glob->mix = NULL;
	return (glob);
}

void			free_glob(t_glob *glob)
{
	if (glob->mult)
		free(glob->mult);
	if (glob->no_mult)
		free(glob->no_mult);
	if (glob->rng)
		free(glob->rng);
	if (glob->no_rng)
		free(glob->no_rng);
	if (glob->mix)
		free(glob->mix);
	free(glob);
}

int				glob_parser(void)
{
	t_glob		*glob;

	if (!g_shell->line)
		return (0);
	if (!verif_tokens(g_shell->line))
		return (0);
	glob = init_glob();
	get_command(g_shell->line);
//	printf("upper : |%s|\nlower : |%s|\nalpha : |%s|\ndigit : |%s|\nalnum : |%s|\nspace : |%s|\ngraph : |%s|\nprint : |%s|\npunct : |%s|\ncntrl : |%s|\nxdigit : |%s|\n",
//		glob->upper, glob->lower, glob->alpha, glob->digit, glob->alnum, glob->space, glob->graph, glob->print, glob->punct, glob->cntrl, glob->xdigit);
	if (ft_strchr(g_shell->line, '['))
		hub_bracket(glob);
	free_glob(glob);
	printf("Glob freed\n");
	return (1);
}
