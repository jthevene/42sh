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
	printf("NO TOKEN\n");
	glob->args->content = ft_strdup(str);
	return (1);
}

int			only_qmark(char *str, t_glob *glob)
{
	FT_INIT(int, len, ft_strlen(str));
	printf("LEN ARG QMARK : %d\n", len);
	if (glob)
		return (1);
	return (0);
}

int			only_star(char *str, t_glob *glob)
{
	printf("STAR\n");
	if (str && glob)
		return (1);
	return (0);
}

int			only_cbrkt(char *str, t_glob *glob)
{
	FT_INIT(int, len, get_len_token(str));
	printf("LEN ARG CBRKT : %d\n", len);
	if (str && glob)
		return (1);
	return (0);
}

int			mix_token(char *str, t_glob *glob)
{
	FT_INIT(int, len, get_len_token(str));
	FT_INIT(char *, path, get_cmd_path(str));
	printf("LEN ARG MIX: %d\n", len);
	printf("PATH = %s\n", path);
	free(path);
	if (glob)
		return (1);
	return (0);
}