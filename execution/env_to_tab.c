/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by apinho            #+#    #+#             */
/*   Updated: 2017/02/24 18:36:46 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

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
