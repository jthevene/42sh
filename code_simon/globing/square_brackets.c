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

static int 		catch_dash_mix(int i)
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
		if (letters >= 2 && g_shell->line[i] != ']')
			return (2);
	}
	return (0);
}

static int 		catch_dash(int i)
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

void 			hub_bracket(t_glob *glob)
{
	FT_INIT(int, i, 0);
	while (g_shell->line[i])
	{
		if (g_shell->line[i] == '[' && g_shell->line[i + 1]
			&& g_shell->line[i + 1] == '!')
		{
			if (catch_dash(i) == 1) /* [!.-.] */
				fill_glob_struct(NORNG, g_shell->line, glob);
			else if (catch_dash(i) == 0) /* [!...] */
				fill_glob_struct(NOMULT, g_shell->line, glob);
			if (catch_dash(i) >= 2) /* [..-..] || [...-...-...] || [!..-..] || [!...-...-...] */
				fill_glob_struct(MIX, g_shell->line, glob);
			break ;
		}
		else if (g_shell->line[i] == '[' && g_shell->line[i + 1]
			&& g_shell->line[i + 1] != '!')
		{
			if (catch_dash(i) == 1) /* [.-.] */
				fill_glob_struct(RNG, g_shell->line, glob);
			else if (catch_dash(i) == 0) /* [...] */
				fill_glob_struct(MULT, g_shell->line, glob);
			if (catch_dash(i) >= 2) /* [..-..] || [...-...-...] || [!..-..] || [!...-...-...] */
				fill_glob_struct(MIX, g_shell->line, glob);
			break ;
		}
		i++;
	}
}