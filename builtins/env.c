/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 14:20:42 by sgaudin           #+#    #+#             */
/*   Updated: 2017/01/23 14:20:42 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/42sh.h"

char		*get_var(t_shell *g_shell, char *n_var)
{
	char	*val;
	t_var	*tmp_env;

	val = NULL;
	tmp_env = g_shell->env;
	while (tmp_env)
	{
		if (!ft_strcmp(tmp_env->name, n_var))
		{
			val = ft_strdup(tmp_env->value);
			return (val);
		}
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
		var->value = ft_strdup(v_value);
		var->next = NULL;
	}
	return (var);
}

void		ft_varappend(t_var *new_element)
{
	t_var	*tmp;

	if (!g_shell.env)
		g_shell.env = new_element;
	else
	{
		tmp = g_shell.env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_element;
	}
}

int			init_env(void)
{
	int				i;
	char			*v_name;
	char			*v_value;
	t_var			*var;
	extern char		**environ;

	i = 0;
	if (!environ[0])
	{
		ft_putendl("error : no environ");
		return (0);
	}
	while (environ[i])
	{
		v_value = ft_strchr(environ[i], '=') + 1;
		v_name = ft_strsub(environ[i], 0, v_value - environ[i] - 1);
		var = new_var(v_name, v_value);
		ft_varappend(var);
		free(v_name);
		i++;
	}
	g_shell.oldpwd = get_var(&g_shell, "OLDPWD");
	g_shell.hist = (t_lst*)ft_memalloc(sizeof(t_lst));
	return (1);
}

int			_42sh_env(void)
{
	FT_INIT(t_var *, tmp_env, g_shell.env);
	if (!g_shell.env)
		return (1);
	while (tmp_env)
	{
		ft_putstr(tmp_env->name);
		ft_putchar('=');
		ft_putendl(tmp_env->value);
		tmp_env = tmp_env->next;
	}
	return (0);
}
