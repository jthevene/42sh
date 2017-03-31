/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:46:35 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

char			**lst_to_tab(t_var *env)
{
	t_var		*tmp;
	char		**tableau;
	int			i;

	i = 0;
	tmp = env;
	tableau = (char**)malloc(sizeof(char*) * (lenght_list(env) + 1));
	while (tmp)
	{
		tableau[i] = ft_strjoinchar(tmp->name, tmp->value, '=');
		i++;
		tmp = tmp->next;
	}
	tableau[i] = NULL;
	return (tableau);
}

int				lenght_list(t_var *env)
{
	t_var		*tmp;
	int			lenght;

	lenght = 0;
	tmp = env;
	while (tmp)
	{
		lenght++;
		tmp = tmp->next;
	}
	return (lenght);
}
