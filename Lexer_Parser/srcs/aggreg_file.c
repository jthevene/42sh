/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aggreg_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by apinho            #+#    #+#             */
/*   Updated: 2017/02/24 18:35:24 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int		check_for_aggreg_fd(t_token *token, char *line, int pos)
{
	FT_INIT(int, i, 1);
	FT_INIT(int, x, pos);
	while (ft_isdigit((unsigned char)line[pos + i]))
		i++;
	if (line[pos + i] == '<')
		if (line[pos + i + 1] == '&')
			if (line[pos + i + 2] == '-'
				|| ft_isdigit((unsigned char)line[pos + i + 2]))
			{
				pos = pos + i + 3;
				token->type = AGGREG_LEFT;
				add_lexeme(token, line, pos, x);
				return (pos);
			}
	if (line[pos + i] == '>')
		if (line[pos + i + 1] == '&')
			if (line[pos + i + 2] == '-'
				|| ft_isdigit((unsigned char)line[pos + i + 2]))
			{
				pos = pos + i + 3;
				token->type = AGGREG_RIGHT;
				add_lexeme(token, line, pos, x);
				return (pos);
			}
	return (pos);
}

int		check_for_aggreg(t_token *token, char *line, int pos)
{
	FT_INIT(int, i, pos);
	if (line[pos] == '<')
		if (line[pos + 1] == '&')
			if (line[pos + 2] == '-'
				|| ft_isdigit((unsigned char)line[pos + 2]))
			{
				pos = pos + 3;
				token->type = AGGREG_LEFT;
				add_lexeme(token, line, pos, i);
				return (pos);
			}
	if (line[pos] == '>')
		if (line[pos + 1] == '&')
			if (line[pos + 2] == '-'
				|| ft_isdigit((unsigned char)line[pos + 2]))
			{
				pos = pos + 3;
				token->type = AGGREG_RIGHT;
				add_lexeme(token, line, pos, i);
				return (pos);
			}
	return (pos);
}
