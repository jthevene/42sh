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
		ft_putendl("error : extern char **environ does not exist");
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
	return (1);
}
