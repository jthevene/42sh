/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 12:05:57 by jules             #+#    #+#             */
/*   Updated: 2016/10/11 12:07:25 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42shsh.h"

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

void	ft_varappend(t_var **alst, t_var *new_element)
{
	t_var	*it;

	if (!*alst)
		*alst = new_element;
	else
	{
		it = *alst;
		while (it->next)
			it = it->next;
		it->next = new_element;
	}
}