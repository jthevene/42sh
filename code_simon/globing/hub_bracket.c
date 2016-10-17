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

static int		catch_dash_mix(int i)
{
	FT_INIT(int, letters, 0);
	while (g_shell->line[i] == '!' || g_shell->line[i] == '[')
		i++;
	if (ft_strchr(g_shell->line, '-'))
	{
		while (g_shell->line[i] != '-')
		{
			letters++;
			i++;
		}
		if (letters >= 2 && g_shell->line[i + 1] != ']')
			return (2);
		i += 1;
		letters = 0;
		while (g_shell->line[i] != ']')
		{
			if (g_shell->line[i] == '-')
				letters += catch_dash_mix(i);
			letters++;
			i++;
		}
		if (letters >= 2)
			return (2);
	}
	return (0);
}

static int		catch_dash(int i)
{
	FT_INIT(int, nb, 0);
	nb = catch_dash_mix(i);
	while (g_shell->line[i] != ']')
	{
		if (g_shell->line[i] == '-' && g_shell->line[i - 1]
			&& g_shell->line[i + 1] && g_shell->line[i + 1] != ']')
		{
			nb++;
			i++;
		}
		i++;
	}
	return (nb);
}

void			fill_bracket_tabs(int glob_case, char *line, t_glob *glob)
{
	if (glob_case == MULT)
	{
		printf("\033[32mmult\033[0m\n");
		glob->mult = clean_brackets(line);
	}
	if (glob_case == RNG)
	{
		printf("\033[32mrng\033[0m\n");
		glob->rng = fill_rng(line);
	}
	if (glob_case == NOMULT)
	{
		printf("\033[32mno mult\033[0m\n");
		glob->no_mult = fill_nomult(line);
	}
	if (glob_case == NORNG)
	{
		printf("\033[32mno rng\033[0m\n");
		glob->no_rng = fill_norng(line);
	}
	if (glob_case == MIX)
	{
		printf("\033[32mmix\033[0m\n");
		glob->mix = fill_mix(line);
	}
}

void			hub_bracket(t_glob *glob)
{
	FT_INIT(int, i, 0);
	while (g_shell->line[i])
	{
		if (g_shell->line[i] == '[' && g_shell->line[i + 1]
			&& g_shell->line[i + 1] == '!')
		{
			if (catch_dash(i) == 1) /* [!.-.] */
				fill_bracket_tabs(NORNG, g_shell->line, glob);
			else if (catch_dash(i) == 0) /* [!...] */
				fill_bracket_tabs(NOMULT, g_shell->line, glob);
			if (catch_dash(i) >= 2) /* [..-..] || [...-...-...] || [!..-..] || [!...-...-...] */
//				fill_bracket_tabs(MIX, g_shell->line, glob);
				;
			break ;
		}
		else if (g_shell->line[i] == '[' && g_shell->line[i + 1]
			&& g_shell->line[i + 1] != '!')
		{
			if (catch_dash(i) == 1) /* [.-.] */
				fill_bracket_tabs(RNG, g_shell->line, glob);
			else if (catch_dash(i) == 0) /* [...] */
				fill_bracket_tabs(MULT, g_shell->line, glob);
			if (catch_dash(i) >= 2) /* [..-..] || [...-...-...] || [!..-..] || [!...-...-...] */
				fill_bracket_tabs(MIX, g_shell->line, glob);
			break ;
		}
		i++;
	}
}
