/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_dash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:46:21 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/globing.h"
#include "../../../includes/redir.h"

static int		catch_dash_mix(int i)
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

int				catch_dash(int i)
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
