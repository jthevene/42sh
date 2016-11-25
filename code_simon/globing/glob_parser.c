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

static int				verif_tokens(char *str)
{
	FT_INIT(int, nb, 0);
	if (ft_strchr(str, '[') && !ft_strchr(str, ']'))
		return (0);
	else if (!count_brackets(str, '[') || !count_brackets(str, '{'))
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

static int				get_command(char *str, t_glob *glob) // Fonction qui recupere la commande pour le message d'erreur
{
	FT_INIT(int, i, 0);
	FT_INIT(int, j, 0);
	while (str[i] && str[i] != ' ')
		i++;
	i++;
	j = i;
	while (str[j] && str[j] != ' ')
		j++;
	if (!(glob->command = ft_strnew(j - i)))
		return (-1);
	j = 0;
	while (str[i] && str[i] != ' ')
	{
		glob->command[j] = str[i];
		j++;
		i++;
	}
	return (0);
}

t_glob					*init_glob(void)
{
	t_glob				*glob;

	glob = (t_glob *)malloc(sizeof(t_glob));
	glob->sbracket = NULL;
	glob->cbracket = NULL;
	glob->tmp_c = NULL;
	glob->c_touch = FALSE;
	glob->lastb_count = 1;
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
	init_tabs1(glob, 0, 0); // Les 3 fonctions init_tabs servent à remplir les tableaux pour [[:upper:]], [[:xdigit:]] etc...
	init_tabs2(glob);
	init_tabs3(glob);
	return (glob);
}

/*
void			free_glob(t_glob *glob)
{
	if (glob->bracket)
		free(glob->bracket);
	if (glob->command)
		free(glob->command);
	free(glob);
}
*/

int						glob_parser(void)
{
	static t_glob		*glob = NULL;

	if (!g_shell.line)
		return (0);
	if (!verif_tokens(g_shell.line))
		return (0);
	glob = glob == NULL ? init_glob() : glob;
	get_command(g_shell.line, glob);
	if (ft_strchr(g_shell.line, '['))
		hub_sbracket(glob); // Hub bracket est le hub de fonctions qui va gérer tous les cas possibles pour les expression de globing contenant des brackets de ce type : '[]'
	if (glob->command)
		free(glob->command);
	if (ft_strchr(g_shell.line, '{'))
		hub_cbracket(glob);
//	free_glob(glob);
	return (1);
}
