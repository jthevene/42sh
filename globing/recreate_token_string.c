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
	FT_INIT(int, i, 0);
	FT_INIT(char *, tmp, NULL);
	FT_INIT(char *, tmp2, NULL);
	if (!str || !glob->args)
		return (NULL);
	while (str[i] && str[i] != ' ')
		i++;
	rewind_tbracket(&glob->args);
	tmp = ft_strndup(str, i);
	while (glob->args)
	{
		tmp = !tmp ? ft_strdup(str) : tmp;
		free(str);
		tmp2 = ft_strjoin(tmp, " ");
		free(tmp);
		str = ft_strjoin(tmp2, glob->args->content);
		free(tmp2);
		tmp = NULL;
		if (!glob->args->next)
			break ;
		glob->args = glob->args->next;
	}
	printf("\033[31mg_shell.line after globing =\033[0m \n%s\n", str);
	free_tbracket(&glob->args);
	return (str);
}