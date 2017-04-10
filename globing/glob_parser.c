/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 19:42:42 by sgaudin           #+#    #+#             */
/*   Updated: 2017/04/10 14:57:31 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/globing.h"

t_glob					*init_glob(void)
{
	t_glob				*glob;

	glob = (t_glob *)malloc(sizeof(t_glob));
	glob->sbracket = NULL;
	glob->cbracket = NULL;
	glob->args = NULL;
	glob->tmp_c = NULL;
	glob->c_touch = FALSE;
	glob->lastb_count = 1;
	glob->exp = NULL;
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
	init_tabs1(glob, 0, 0);
	init_tabs2(glob);
	init_tabs3(glob);
	return (glob);
}

static void				glob_parser_end(char **line, t_glob *glob)
{
	FT_INIT(char *, tmp, NULL);
	tmp = recreate_token_string(glob);
	if (tmp)
	{
		free((*line));
		(*line) = ft_strdup(tmp);
	}
	free(tmp);
}

int						glob_parser(char **line)
{
	static t_glob		*glob = NULL;

	if (!(*line))
		return (0);
	if (!verif_tokens(&(*line)))
		return (0);
	backslash_char_globing(&(*line));
	glob = !glob ? init_glob() : glob;
	glob->command = ft_strdup((*line));
	if (ft_strchr((*line), '{'))
	{
		if (!hub_cbracket(glob, (*line)))
		{
			free(glob->command ? glob->command : NULL);
			return (0);
		}
	}
	if (!hub_final(glob, (*line)))
	{
		free(glob->command ? glob->command : NULL);
		return (0);
	}
	glob_parser_end(&(*line), glob);
	free(glob->command ? glob->command : NULL);
	return (1);
}

int						send_token_to_glob(t_all *all)
{
	FT_INIT(t_token *, tmp, all->tokens_begin);
	FT_INIT(int, nb_error, 0);
	FT_INIT(int, nb_all, 0);
	if (tmp->next)
	{
		replace_env_var(&tmp->lexeme);
		tmp = tmp->next;
	}
	else
		return (replace_env_var(&tmp->lexeme));
	while (tmp)
	{
		if (tmp->lexeme)
		{
			replace_env_var(&tmp->lexeme);
			if (!glob_parser(&tmp->lexeme))
				nb_error++;
			nb_all++;
		}
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	return (0);
}
