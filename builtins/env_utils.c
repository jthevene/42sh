/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 14:26:30 by sgaudin           #+#    #+#             */
/*   Updated: 2017/03/11 14:26:31 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

static void	init_tmp_env(void)
{
	FT_INIT(t_var *, tmp, g_shell.env);
	FT_INIT(t_var *, new, NULL);
	if (g_shell.env_opt == TRUE)
		return ;
	while (tmp)
	{
		new = new_var(tmp->name, tmp->value);
		ft_varappend(new, &g_shell.tmp_env);
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
}

void		print_env(char *to_exec)
{
	FT_INIT(t_var *, tmp_env, g_shell.tmp_env ? g_shell.tmp_env : g_shell.env);
	if ((!to_exec && g_shell.env_opt == FALSE)
		|| (!to_exec && g_shell.env_opt == TRUE && g_shell.tmp_env))
	{
		while (tmp_env)
		{
			ft_putstr(tmp_env->name);
			ft_putchar('=');
			ft_putendl(tmp_env->value);
			tmp_env = tmp_env->next;
		}
	}
}

void		free_env(int env)
{
	FT_INIT(t_var *, tmp, NULL);
	FT_INIT(t_var *, tmp_env, NULL);
	if (env == FALSE)
		return ;
	tmp_env = env == DEFAULT ? g_shell.env : g_shell.tmp_env;
	while (tmp_env)
	{
		tmp = tmp_env;
		free(tmp_env->name ? tmp_env->name : NULL);
		free(tmp_env->value ? tmp_env->value : NULL);
		if (!tmp_env->next)
			break ;
		tmp_env = tmp_env->next;
		free(tmp);
	}
	free(tmp);
	if (env == DEFAULT)
		g_shell.env = NULL;
	if (env == TMP)
		g_shell.tmp_env = NULL;
}

void		create_tmp_env(char **args)
{
	FT_INIT(int, i, 0);
	FT_INIT(char *, tmp, NULL);
	if (g_shell.env_opt == TRUE)
	{
		i = 2;
		g_shell.tmp_env = NULL;
	}
	else
		i = 1;
	if (args[i] && ft_strchr(args[i], '='))
		init_tmp_env();
	else
		return ;
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
		{
			tmp = ft_strjoin("setenv ", args[i]);
			ft_setenv(tmp, TMP);
			ft_strdel(&tmp);
		}
		else
			break ;
		i++;
	}
}
