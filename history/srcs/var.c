/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 12:05:57 by jules             #+#    #+#             */
/*   Updated: 2017/01/28 14:59:45 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/history.h"

char	*get_var(t_shell *g_shell, char *n_var)
{
	char	*str;
	t_var	*var;

	str = NULL;
	var = g_shell->vars;
	while (var)
	{
		if (!ft_strcmp(var->name, n_var))
		{
			str = ft_strdup(var->value);
			return (str);
		}
		var = var->next;
	}
	return (str);
}

t_var	*new_var(char *v_name, char *v_value)
{
	t_var	*var;

	var = (t_var *)malloc(sizeof(t_var));
	if (var)
	{
		var->name = ft_strdup(v_name);
		var->value = ft_strdup(v_value);
		var->next = NULL;
	}
	return (var);
}

void	ft_varappend(t_var *new_element)
{
	t_var	*tmp;

	if (!g_shell.vars)
		g_shell.vars = new_element;
	else
	{
		tmp = g_shell.vars;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_element;
	}
	
}