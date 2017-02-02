/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recreate_token_string.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 15:59:09 by sgaudin           #+#    #+#             */
/*   Updated: 2017/01/30 15:59:09 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/globing.h"

static int		start_recreate(char **str, t_glob *glob)
{
	rewind_tbracket(&glob->args);
	free((*str));
	(*str) = ft_strdup(glob->args->content);
	if (glob->args->next)
	{
		glob->args = glob->args->next ? glob->args->next : glob->args;
		return (1);
	}
	else
		return (0);
}

char			*recreate_token_string(char *str, t_glob *glob)
{
	FT_INIT(char *, tmp, NULL);
	FT_INIT(char *, tmp2, NULL);
	if (!str || !glob->args)
		return (NULL);
	if (!start_recreate(&str, glob))
	{
		free_tbracket(&glob->args);
		return (str);
	}
	while (glob->args)
	{
		tmp = ft_strdup(str);
		free(str);
		tmp2 = ft_strjoin(tmp, " ");
		free(tmp);
		str = ft_strjoin(tmp2, glob->args->content);
		free(tmp2);
		if (!glob->args->next)
			break ;
		glob->args = glob->args->next;
	}
	free_tbracket(&glob->args);
	return (str);
}
