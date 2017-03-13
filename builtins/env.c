/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/13 16:43:43 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

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
	while (i < (int)ft_strlen(cmd) && cmd[i])
	{
		j = i;
		while (i < (int)ft_strlen(cmd) && cmd[i] && cmd[i] == ' ')
			i++;
		while (i < (int)ft_strlen(cmd) && cmd[i] && cmd[i] != ' ')
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
	while (i < (int)ft_strlen(cmd) && cmd[i] && cmd[i] == ' ')
		i++;
	return (ft_strsub(cmd, i, ft_strlen(cmd) - i));
}

char		*get_cmd_to_exec(char *cmd)
{
	FT_INIT(int, i, 0);
	while (i < (int)ft_strlen(cmd) && cmd[i] && cmd[i] == ' ')
		i++;
	while (i < (int)ft_strlen(cmd) && cmd[i] && cmd[i] != ' ')
		i++;
	while (i < (int)ft_strlen(cmd) && cmd[i] && cmd[i] == ' ')
		i++;
	if (g_shell.env_opt)
	{
		while (i < (int)ft_strlen(cmd) && cmd[i] && cmd[i] != ' ')
			i++;
		while (i < (int)ft_strlen(cmd) && cmd[i] && cmd[i] == ' ')
			i++;
	}
	if (i > (int)ft_strlen(cmd) || !cmd[i])
		return (NULL);
	return (get_cmd_to_exec2(cmd, i));
}

int			ft_env(char *cmd)
{
	FT_INIT(char **, tmp, ft_strsplit(cmd, ' '));
	FT_INIT(t_var *, old_tmp_env, NULL);
	FT_INIT(int, is_opt, tmp && tmp[1] && !ft_strcmp(tmp[1], "-i") ? 1 : 0);
	if (tmp && tmp[1] && !ft_strcmp(tmp[1], "-i"))
		g_shell.env_opt = TRUE;
	if (!g_shell.tmp_env)
	{
		create_tmp_env(tmp, is_opt);
		is_opt = g_shell.tmp_env ? 0 : is_opt;
	}
	else
	{
		create_tmp_env(tmp, is_opt);
		is_opt = g_shell.tmp_env ? 0 : is_opt;
	}
	FT_INIT(char *, to_exec, get_cmd_to_exec(cmd));
	FT_INIT(t_var *, tmp_env, g_shell.env);
	g_shell.env = g_shell.tmp_env ? g_shell.tmp_env : g_shell.env;
	save_old_tmp_env(&old_tmp_env);
	if (to_exec != NULL)
		exec_function(&to_exec);
	print_env(to_exec, is_opt);
	g_shell.env_opt = FALSE;
	free_tab(tmp);
	ft_strdel(&to_exec);
	g_shell.env = tmp_env;
	restore_new_env(&old_tmp_env);
	free_env(old_tmp_env ? OTHER : FALSE, old_tmp_env ? &old_tmp_env : NULL);
	free_env(g_shell.tmp_env ? TMP : FALSE, NULL);
	return (0);
}
