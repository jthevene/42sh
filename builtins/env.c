/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:46:46 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

char		*get_var(t_shell *g_shell, char *n_var)
{
	char	*val;
	t_var	*tmp_env;

	if (!g_shell || !g_shell->env || !n_var)
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
		if (!v_value)
			var->value = ft_strdup("");
		else
			var->value = ft_strdup(v_value);
		var->next = NULL;
	}
	return (var);
}

char		*get_cmd_to_exec2(char *cmd, int i)
{
	FT_INIT(int, egal, 0);
	FT_INIT(int, j, 0);
	while (cmd[i])
	{
		j = i;
		while (cmd[i] && cmd[i] == ' ')
			i++;
		while (cmd[i] && cmd[i] != ' ')
		{
			if (cmd[i] == '=')
				egal = 1;
			i++;
		}
		if (!egal)
		{
			i = j;
			break ;
		}
		egal = 0;
	}
	if (!cmd[i])
		return (NULL);
	while (cmd[i] && cmd[i] == ' ')
		i++;
	return (ft_strsub(cmd, i, ft_strlen(cmd) - i));
}

char		*get_cmd_to_exec(char *cmd)
{
	FT_INIT(int, i, 0);
	while (cmd[i] && cmd[i] == ' ')
		i++;
	while (cmd[i] && cmd[i] != ' ')
		i++;
	while (cmd[i] && cmd[i] == ' ')
		i++;
	if (g_shell.env_opt)
	{
		while (cmd[i] && cmd[i] != ' ')
			i++;
		while (cmd[i] && cmd[i] == ' ')
			i++;
	}
	if (!cmd[i])
		return (NULL);
	return (get_cmd_to_exec2(cmd, i));
}

int			ft_env(char *cmd)
{
	if (!g_shell.env)
		return (1);
	FT_INIT(char **, tmp, ft_strsplit(cmd, ' '));
	if (tmp && tmp[1] && !ft_strcmp(tmp[1], "-i"))
		g_shell.env_opt = TRUE;
	if (!g_shell.tmp_env)
		create_tmp_env(tmp);
	FT_INIT(char *, to_exec, get_cmd_to_exec(cmd));
	FT_INIT(t_var *, tmp_env, g_shell.env);
	g_shell.env = g_shell.tmp_env ? g_shell.tmp_env : g_shell.env;
	if (to_exec != NULL)
		exec_function(&to_exec);
	print_env(to_exec);
	g_shell.env_opt = FALSE;
	free_tab(tmp);
	ft_strdel(&to_exec);
	g_shell.env = tmp_env;
	free_env(g_shell.tmp_env ? TMP : FALSE);
	return (0);
}
