/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/23 16:59:22 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

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

static void	ft_env2(char *cmd, int is_opt, char ***tmp, t_var **old_tmp_env)
{
	FT_INIT(char *, to_exec, get_cmd_to_exec(cmd));
	FT_INIT(t_var *, tmp_env, g_shell.env);
	if (g_shell.tmp_env)
	{
		g_shell.env = g_shell.tmp_env;
		g_shell.null_env = 1;
	}
	else
		g_shell.null_env = 0;
	if (is_opt == TRUE && !g_shell.tmp_env)
		g_shell.env = NULL;
	save_old_tmp_env(&(*old_tmp_env));
	if (to_exec != NULL)
		exec_function(&to_exec);
	print_env(to_exec, is_opt);
	g_shell.env_opt = FALSE;
	free_tab((*tmp));
	ft_strdel(&to_exec);
	g_shell.env = tmp_env;
}

int			ft_env(char *cmd)
{
	FT_INIT(t_var *, old_tmp_env, NULL);
	FT_INIT(char **, tmp, ft_strsplit(cmd, ' '));
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
	ft_env2(cmd, is_opt, &tmp, &old_tmp_env);
	restore_new_env(&old_tmp_env);
	free_env(old_tmp_env ? OTHER : FALSE, old_tmp_env ? &old_tmp_env : NULL);
	free_env(g_shell.tmp_env ? TMP : FALSE, NULL);
	g_shell.null_env = 0;
	return (1);
}
