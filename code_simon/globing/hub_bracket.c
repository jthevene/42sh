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

static int		catch_dash_mix(int i) // Cette fonction est la pour ce genre de cas de figure : [a-dfg-hjkl-vbn]
{
	FT_INIT(int, letters, 0);
	while (g_shell.line[i] == '!' || g_shell.line[i] == '[')
		i++;
	if (ft_strchr(g_shell.line, '-'))
	{
		while (g_shell.line[i] != '-')
		{
			letters += g_shell.line[i - 1] == '[' ? 0 : 1;
			i++;
		}
		if (letters >= 2 && g_shell.line[i + 1] != ']')
			return (2);
		i += 1;
		letters = 0;
		while (g_shell.line[i] != ']')
		{
			if (g_shell.line[i] == '-')
				letters += catch_dash_mix(i);
			letters++;
			i++;
		}
		if (letters >= 2)
			return (2);
	}
	return (0);
}

static int		catch_dash(int i) // Fonction qui vérifie la validité de l'expression en regardant le dash dans cette dernière
{
	FT_INIT(int, nb, 0);
	nb = catch_dash_mix(i);
	while (g_shell.line[i] != ']')
	{
		if (g_shell.line[i] == '-' && g_shell.line[i - 1]
			&& g_shell.line[i + 1] && g_shell.line[i + 1] != ']')
		{
			nb++;
			i++;
		}
		i++;
	}
	return (nb);
}

int				fill_bracket_tabs(int glob_case, char *line, t_glob *glob) // Fonciton qui choisit la méthode de remplissage de notre tableau de caractères
{
	FT_INIT(char *, tmp_error, NULL);
	FT_INIT(int, ret, check_categories(g_shell.line, glob));

	glob->type = glob_case;
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
		glob->bracket = clean_brackets(line);
		printf("\033[34mret mult :\033[0m %s\n", glob->bracket);
	}
	if (glob_case == RNG)
	{
		printf("\033[32mrng\033[0m\n");
		glob->bracket = fill_rng(line);
		printf("\033[34mret rng :\033[0m %s\n", glob->bracket);
	}
	if (glob_case == NOMULT)
	{
		printf("\033[32mno mult\033[0m\n");
		glob->bracket = fill_nomult(line);
		printf("\033[34mret no_mult :\033[0m %s\n", glob->bracket);
	}
	if (glob_case == NORNG)
	{

		printf("\033[32mno rng\033[0m\n");
		glob->bracket = fill_norng(line);
		printf("\033[34mret no_rng :\033[0m %s\n", glob->bracket);
	}
	if (glob_case == MIX)
	{
		printf("\033[32mmix\033[0m\n");
		glob->bracket = fill_mix(line);
		printf("\033[34mret mix :\033[0m %s\n", glob->bracket);
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
			if (catch_dash(i) == 1) /* [!.-.] */
				fill_bracket_tabs(NORNG, g_shell.line, glob);
			else if (catch_dash(i) == 0) /* [!...] */
				fill_bracket_tabs(NOMULT, g_shell.line, glob);
			if (catch_dash(i) >= 2) /* [..-..] || [...-...-...] || [!..-..] || [!...-...-...] */
				fill_bracket_tabs(MIX, g_shell.line, glob);
			break ;
		}
		else if (g_shell.line[i] == '[' && g_shell.line[i + 1]
			&& g_shell.line[i + 1] != '!')
		{
			if (catch_dash(i) == 1) /* [.-.] */
				fill_bracket_tabs(RNG, g_shell.line, glob);
			else if (catch_dash(i) == 0) /* [...] */
				fill_bracket_tabs(MULT, g_shell.line, glob);
			if (catch_dash(i) >= 2) /* [..-..] || [...-...-...] || [!..-..] || [!...-...-...] */
				fill_bracket_tabs(MIX, g_shell.line, glob);
			break ;
		}
		i++;
	}
}
