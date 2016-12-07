/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 21:03:02 by sgaudin           #+#    #+#             */
/*   Updated: 2016/12/07 21:03:03 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

int			g_no_token(char *str, t_glob *glob)
{
	if (!bracket_pushback(&glob->args))
		return (0);
	glob->args->content = ft_strdup(str);
	return (1);
}

int			only_qmark(char *str, t_glob *glob)
{
	if (str && glob)
		return (1);
}

int			only_star(char *str, t_glob glob)
{
	if (str && glob)
		return (1);
}

int			only_cbrkt(char *str, t_glob *glob)
{
	if (str && glob)
		return (1);
}

int			mix_token(char *str, t_glob *glob)
{
	if (str && glob)
		return (1);
}