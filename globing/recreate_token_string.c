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

static int		start_recreate(char **ret, t_glob *glob)
{
	rewind_tbracket(&glob->args);
	(*ret) = ft_strdup(glob->args->content);
	if (glob->args->next)
	{
		glob->args = glob->args->next ? glob->args->next : glob->args;
		return (1);
	}
	else
		return (0);
}

char			*recreate_token_string(t_glob *glob)
{
	FT_INIT(char *, ret, NULL);
	FT_INIT(char *, tmp, NULL);
	FT_INIT(char *, tmp2, NULL);
	if (!glob->args)
		return (NULL);
	if (!start_recreate(&ret, glob))
	{
		free_tbracket(&glob->args);
		return (ret);
	}
	while (glob->args)
	{
		tmp = ft_strdup(ret);
		free(ret);
		tmp2 = ft_strjoin(tmp, " ");
		free(tmp);
		ret = ft_strjoin(tmp2, glob->args->content);
		free(tmp2);
		if (!glob->args->next)
			break ;
		glob->args = glob->args->next;
	}
	free_tbracket(&glob->args);
	return (ret);
}
