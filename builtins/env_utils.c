/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 14:26:30 by sgaudin           #+#    #+#             */
/*   Updated: 2017/03/14 14:57:53 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

void		print_env(char *to_exec, int is_opt)
{
	FT_INIT(t_var *, tmp_env, g_shell.tmp_env ? g_shell.tmp_env : g_shell.env);
	if (!tmp_env || is_opt)
		return ;
	else if (!is_opt && g_shell.env_opt == TRUE && !g_shell.tmp_env)
		return ;
	if (!to_exec && tmp_env)
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

void		free_env(int env, t_var **old_tmp_env)
{
	FT_INIT(t_var *, tmp, NULL);
	FT_INIT(t_var *, tmp_env, NULL);
	if (env == FALSE || (env == OTHER && (!old_tmp_env || !(*old_tmp_env))))
		return ;
	tmp_env = env == DEFAULT ? g_shell.env
			: FT_TER(env == TMP, g_shell.tmp_env, (*old_tmp_env));
	if (!tmp_env)
		return ;
	while (tmp_env)
	{
		tmp = tmp_env;
		ft_strdel(&tmp_env->name);
		ft_strdel(&tmp_env->value);
		if (!tmp_env->next)
			break ;
		tmp_env = tmp_env->next;
		free(tmp ? tmp : NULL);
	}
	free(tmp ? tmp : NULL);
	if (env == DEFAULT)
		g_shell.env = NULL;
	else if (env == TMP)
		g_shell.tmp_env = NULL;
	else if (env == OTHER)
		(*old_tmp_env) = NULL;
}

void		create_tmp_env(char **args, int is_opt)
{
	FT_INIT(int, i, 0);
	FT_INIT(char *, tmp, NULL);
	if (is_opt == 1)
	{
		free_env(TMP, NULL);
		g_shell.env = g_shell.null_env ? NULL : g_shell.env;
	}
	i = is_opt == 1 ? 2 : 1;
	if (i > ft_count_tab(args) || !args[i] || !ft_strchr(args[i], '='))
		return ;
	else if (!g_shell.tmp_env)
		init_tmp_env();
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

void		save_old_tmp_env(t_var **old_tmp_env)
{
	if (!g_shell.tmp_env)
		return ;
	FT_INIT(t_var *, tmp, g_shell.tmp_env);
	FT_INIT(t_var *, new, NULL);
	while (tmp)
	{
		new = new_var(tmp->name, tmp->value);
		ft_varappend(new, &(*old_tmp_env));
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
}

void		restore_new_env(t_var **old_tmp_env)
{
	if (!old_tmp_env || !(*old_tmp_env))
		return ;
	FT_INIT(t_var *, tmp_env, g_shell.tmp_env);
	FT_INIT(char *, name_to_recup, NULL);
	FT_INIT(char *, val_to_recup, NULL);
	FT_INIT(char *, to_set, NULL);
	FT_INIT(char *, tmp, NULL);
	while (tmp_env)
	{
		name_to_recup = ft_strdup(tmp_env->name);
		val_to_recup = get_var((*old_tmp_env), name_to_recup);
		if (val_to_recup && ft_strcmp(val_to_recup, tmp_env->value))
		{
			to_set = ft_strjoin("setenv ", name_to_recup);
			tmp = ft_strjoin(to_set, "=");
			ft_strdel(&to_set);
			to_set = ft_strjoin(tmp, tmp_env->value);
			ft_setenv(to_set, DEFAULT);
			ft_strdel(&to_set);
			ft_strdel(&tmp);
		}
		ft_strdel(&name_to_recup);
		ft_strdel(&val_to_recup);
		tmp_env = tmp_env->next;
	}
}
