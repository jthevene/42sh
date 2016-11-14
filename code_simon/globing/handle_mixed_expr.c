/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mixed_expr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 14:32:12 by sgaudin           #+#    #+#             */
/*   Updated: 2016/11/10 14:32:24 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/globing.h"

/*
int 			detect_mixed_expr(char *str)
{
	FT_INIT(int, i, 0);
	while (str[i] && str[i] != '[')
		i++;
	if (str[i + 1] == '[' && str[i + 2] == ':')
	{
		while (str[i - 2 != ':'] && str[i - 1] != ']')
			i++;
		if (str[i] && str[i] != ']')
			return (FIN);
	}
	else
		return (DEBUT);
	return (0);
}

char			*separate_chars(char *line, int pos)
{
	FT_INIT(char *, ret, NULL);
	if (pos == DEBUT)
		ret = separate_chars_debut(line, pos);
	else if (pos == FIN)
		ret = separate_chars_fin(line, pos);
	printf("ret = %s\n", ret);
	return (ret);
}

void			handle_mixed_expr(int glob_case, char *line, t_glob *glob)
{
	FT_INIT(int, pos, 0);
	FT_INIT(char *, chars, NULL);
	if (glob_case && glob)
		ft_putchar('\n');
	if (!detect_category(line))
	{
		printf("\033[33mCategory not detected\033[0m\n");
		fill_bracket_tabs(glob_case, line, glob);
	}
	else
	{
		printf("\033[33mCategory detected\033[0m\n");
		if (!(pos = detect_mixed_expr(line)))
		{
			printf("fill_bracket_tabs\n");
			fill_bracket_tabs(glob_case, line, glob);
		}
		else
		{
			printf("\033[33mMixed expr detected\033[0m\n");
			chars = separate_chars(line, pos);
		}
	}
}
*/