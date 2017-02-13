/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 14:20:42 by sgaudin           #+#    #+#             */
/*   Updated: 2017/02/13 12:38:56 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

char		*get_var(t_shell *g_shell, char *n_var)
{
	char	*val;
	t_var	*tmp_env;

	if (!g_shell || !n_var)
		return (NULL);
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

char		*get_cmd_to_exec(char *cmd)
{
	FT_INIT(int, i, 0);
	while (cmd[i] == ' ')
		i++;
	while (cmd[i] && cmd[i] != ' ')
		i++;
	while (cmd[i] && cmd[i] == ' ')
		i++;
	if (cmd[i] == '-' && cmd[i + 1] == 'i' && cmd[i + 2] == ' ')
	{
		while (cmd[i] != ' ')
			i++;
		while (cmd[i] == ' ')
			i++;
		return (ft_strsub(cmd, i, ft_strlen(cmd) - i));
	}
	else if (cmd[i] == '-' && cmd[i + 1] == 'i' && !cmd[i + 2])
		return (NULL);
	else if (cmd[i] && cmd[i] != ' ')
		return (ft_strsub(cmd, i, ft_strlen(cmd) - i));
	return (NULL);
}

int			ft_env(char *cmd)
{
	FT_INIT(char **, tmp, ft_strsplit(cmd, ' '));
	FT_INIT(t_var *, tmp_env, g_shell.env);
	FT_INIT(char *, to_exec, get_cmd_to_exec(cmd));
	if (!g_shell.env)
		return (1);
	if (tmp && tmp[1] && !ft_strcmp(tmp[1], "-i"))
		g_shell.env_opt = TRUE;
	if (to_exec != NULL)
		exec_function(to_exec);
	while (!to_exec && g_shell.env_opt == FALSE && tmp_env)
	{
		ft_putstr(tmp_env->name);
		ft_putchar('=');
		ft_putendl(tmp_env->value);
		tmp_env = tmp_env->next;
	}
	g_shell.env_opt = FALSE;
	free_tab(tmp);
	return (0);
}
