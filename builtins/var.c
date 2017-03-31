/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 14:55:58 by sgaudin           #+#    #+#             */
/*   Updated: 2017/03/14 15:29:08 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

char		*get_var(t_var *env, char *n_var)
{
	char	*val;
	t_var	*tmp_env;

	if (!env || !n_var)
		return (NULL);
	val = NULL;
	tmp_env = env;
	while (tmp_env)
	{
		if (tmp_env->name && n_var && !ft_strcmp(tmp_env->name, n_var))
		{
			val = tmp_env->value ? ft_strdup(tmp_env->value) : NULL;
			return (val);
		}
		if (!tmp_env->next)
			break ;
		tmp_env = tmp_env->next;
	}
	return (val);
}

t_var		*new_var(char *v_name, char *v_value)
{
	t_var	*var;

	var = (t_var *)malloc(sizeof(t_var));
	if (var)
	{
		var->name = ft_strdup(v_name);
		if (!v_value)
			var->value = ft_strdup("");
		else
			var->value = ft_strdup(v_value);
		var->next = NULL;
	}
	return (var);
}

void		ft_varappend(t_var *new_element, t_var **env)
{
	t_var	*tmp;

	if (!(*env))
		(*env) = new_element;
	else
	{
		tmp = (*env);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_element;
	}
}
