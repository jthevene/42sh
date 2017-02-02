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

char			*recreate_token_string(char *str, t_glob *glob)
{
	FT_INIT(char *, tmp, NULL);
	FT_INIT(char *, tmp2, NULL);
	if (!str || !glob->args)
		return (NULL);
	rewind_tbracket(&glob->args);
	free(str);
	str = ft_strdup(glob->args->content);
	if (glob->args->next)
		glob->args = glob->args->next;
	else
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
//	printf("\033[31mLine after globing = \n%s\033[0m\n", str);
	free_tbracket(&glob->args);
	return (str);
}