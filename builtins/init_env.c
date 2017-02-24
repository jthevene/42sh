/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 16:55:03 by sgaudin           #+#    #+#             */
/*   Updated: 2017/02/22 08:58:06 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

/*
static void	create_safety_vars(void)
{
	FT_INIT(char *, pwd, ft_strnew(255));
	FT_INIT(char *, tmp, NULL);
	ft_setenv("SHLVL=1");
	tmp = getcwd(tmp, 255);
	pwd = ft_strjoin("PWD=", tmp);
	ft_setenv(pwd);
	ft_strdel(&pwd);
	pwd = ft_strjoin("HOME=", tmp);
	ft_setenv(pwd);
	ft_strdel(&tmp);
	ft_strdel(&pwd);
	ft_setenv("PATH=/bin:/usr/bin");
}
*/

void		increase_shlvl(void)
{
	FT_INIT(char *, tmp, NULL);
	FT_INIT(char *, tmp_setenv, NULL);
	FT_INIT(int, lvl_int, 0);
	if ((tmp = get_var(&g_shell, "SHLVL")))
	{
		lvl_int = ft_atoi(tmp);
		ft_strdel(&tmp);
		tmp = ft_itoa(lvl_int + 1);
		tmp_setenv = ft_strjoin("setenv SHLVL=", tmp);
		ft_setenv(tmp_setenv);
		ft_strdel(&tmp);
		ft_strdel(&tmp_setenv);
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
		ft_putstr_fd("Environment not found.\n", 2);
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
	increase_shlvl();
	g_shell.oldpwd = get_var(&g_shell, "OLDPWD");
	return (1);
}
