/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/23 11:02:07 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

static void	create_safety_vars(void)
{
	FT_INIT(char *, pwd, ft_strnew(255));
	FT_INIT(t_var *, var, NULL);
	var = new_var("SHLVL", "1");
	ft_varappend(var, &g_shell.env);
	pwd = getcwd(pwd, 255);
	var = new_var("PWD", pwd);
	ft_varappend(var, &g_shell.env);
	var = new_var("HOME", pwd);
	ft_varappend(var, &g_shell.env);
	var = new_var("PATH", "/bin:/usr/bin");
	ft_varappend(var, &g_shell.env);
	var = new_var("TERM", "xterm-256color");
	ft_varappend(var, &g_shell.env);
	var = new_var("OLDPWD", pwd);
	ft_varappend(var, &g_shell.env);
	ft_strdel(&pwd);
}

void		increase_shlvl(void)
{
	FT_INIT(char *, tmp, NULL);
	FT_INIT(char *, tmp_setenv, NULL);
	FT_INIT(int, lvl_int, 0);
	if ((tmp = get_var(g_shell.env, "SHLVL")))
	{
		lvl_int = ft_atoi(tmp);
		ft_strdel(&tmp);
		tmp = ft_itoa(lvl_int + 1);
		tmp_setenv = ft_strjoin("setenv SHLVL=", tmp);
		ft_setenv(tmp_setenv, DEFAULT);
		ft_strdel(&tmp);
		ft_strdel(&tmp_setenv);
	}
}

void		init_tmp_env(void)
{
	FT_INIT(int, len, 0);
	FT_INIT(int, i, 0);
	FT_INIT(t_var *, tmp, g_shell.env);
	FT_INIT(t_var *, new, NULL);
	FT_INIT(t_var *, tmp_len, g_shell.env);
	if (g_shell.env_opt == TRUE)
		return ;
	while (tmp_len)
	{
		len++;
		tmp_len = tmp_len->next;
	}
	while (tmp && i < len)
	{
		new = new_var(tmp->name, tmp->value);
		ft_varappend(new, &g_shell.tmp_env);
		if (!tmp->next)
			break ;
		i++;
		tmp = tmp->next;
	}
}

int			init_env(char **envp)
{
	int				i;
	char			*v_name;
	char			*v_value;
	t_var			*var;

	i = 0;
	if (!envp[0])
	{
		create_safety_vars();
		g_shell.oldpwd = get_var(g_shell.env, "OLDPWD");
		return (1);
	}
	while (envp[i])
	{
		v_value = ft_strchr(envp[i], '=') + 1;
		v_name = ft_strsub(envp[i], 0, v_value - envp[i] - 1);
		var = new_var(v_name, v_value);
		ft_varappend(var, &g_shell.env);
		free(v_name);
		i++;
	}
	increase_shlvl();
	g_shell.oldpwd = get_var(g_shell.env, "OLDPWD");
	return (1);
}
