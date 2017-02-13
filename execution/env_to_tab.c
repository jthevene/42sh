/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 17:06:30 by sgaudin           #+#    #+#             */
/*   Updated: 2017/02/13 12:38:38 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

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
