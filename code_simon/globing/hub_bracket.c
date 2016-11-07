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

int				fill_bracket_tabs(int glob_case, char *line, t_glob *glob) // Fonciton qui choisit la méthode de remplissage de notre tableau de caractères
{
	FT_INIT(char *, tmp_error, NULL);
	FT_INIT(int, ret, 0);

	if (glob_case != MULT && glob_case != RNG && glob_case != NOMULT
		&& glob_case != NORNG && glob_case != MIX)
		glob_case = CATEGORY;
	sbracket_pushback(&glob->sbracket, glob_case);
	printf("pushback worked\n");
	ret = check_categories(g_shell.line, glob);
	if (ret == -1 || ret == 1)
		return (0);
	if (!check_rng(line))
	{
		tmp_error = ft_strjoin("42sh: no matches found: ", glob->command);
		ft_putendl_fd(tmp_error, 2);
		free(tmp_error);
		return (0);
	}
	if (glob_case == MULT)
	{
		printf("\033[32mmult\033[0m\n");
		glob->sbracket->bracket = clean_brackets(line);
		printf("\033[34mret mult :\033[0m %s\n", glob->sbracket->bracket);
	}
	if (glob_case == RNG)
	{
		printf("\033[32mrng\033[0m\n");
		glob->sbracket->bracket = fill_rng(line);
		printf("\033[34mret rng :\033[0m %s\n", glob->sbracket->bracket);
	}
	if (glob_case == NOMULT)
	{
		printf("\033[32mno mult\033[0m\n");
		glob->sbracket->bracket = fill_nomult(line);
		printf("\033[34mret no_mult :\033[0m %s\n", glob->sbracket->bracket);
	}
	if (glob_case == NORNG)
	{

		printf("\033[32mno rng\033[0m\n");
		glob->sbracket->bracket = fill_norng(line);
		printf("\033[34mret no_rng :\033[0m %s\n", glob->sbracket->bracket);
	}
	if (glob_case == MIX)
	{
		printf("\033[32mmix\033[0m\n");
		glob->sbracket->bracket = fill_mix(line);
		printf("\033[34mret mix :\033[0m %s\n", glob->sbracket->bracket);
	}
	return (1);
}

void			hub_bracket(t_glob *glob) // Gère les différents cas de figure, cf commentaires en dessous
{
	FT_INIT(int, i, 0);
	while (g_shell.line[i])
	{
		if (g_shell.line[i] == '[' && g_shell.line[i + 1]
			&& g_shell.line[i + 1] == '!')
		{
			fill_bracket_tabs(catch_dash(i) == 1 ? NORNG 
			: FT_TER(catch_dash(i) < 2, NOMULT, MIX), g_shell.line, glob);
			break ;
		}
		else if (g_shell.line[i] == '[' && g_shell.line[i + 1]
			&& g_shell.line[i + 1] != '!')
		{
			fill_bracket_tabs(catch_dash(i) == 1 ? RNG 
			: FT_TER(catch_dash(i) < 2, MULT, MIX), g_shell.line, glob);
			break ;
		}
		i++;
	}
}
