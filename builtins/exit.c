/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <dvirgile@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 17:04:00 by sgaudin           #+#    #+#             */
/*   Updated: 2017/03/31 15:14:48 by dvirgile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

char		*get_tab_arguments(char **tabl, int len_tab)
{
	FT_INIT(char*, val, "0");
	FT_INIT(int, i, 0);
	if (tabl && len_tab == 2)
	{
		while (i >= 0 && tabl[1][i])
		{
			if (!ft_isdigit(tabl[1][i]) && tabl[1][i] != '-')
				i = -5;
			i++;
		}
		if (i > 0)
			val = tabl[1];
	}
	return (val);
}

char		*get_value_to_return(char *return_value)
{
	FT_INIT(int, len_tab_val, 0);
	FT_INIT(char*, val, "0");
	FT_INIT(char**, tabl, 0);
	if (return_value && ft_strchr(return_value, ' '))
	{
		tabl = ft_strsplit(return_value, ' ');
		len_tab_val = len_tab(tabl);
		if (tabl && len_tab_val == 2)
			val = ft_strdup(get_tab_arguments(tabl, len_tab_val));
		else if (tabl && len_tab_val == 1)
			val = ft_strdup("0");
		else if (tabl && len_tab_val > 2)
			val = NULL;
		else
			val = ft_strdup("0");
		if (tabl)
			free_tab(tabl);
	}
	else
		val = ft_strdup("0");
	return (val);
}

void		ft_exit(char *return_value)
{
	FT_INIT(int, int_return_value, 0);
	FT_INIT(char*, str_ret, NULL);
	if (!(str_ret = get_value_to_return(return_value)))
		return (ft_putstr_fd("42sh: exit: too many arguments", 2));
	go_to_end();
	ft_putstr("\n");
	ft_reset_termios(g_shell.t_back);
	update_history_file(get_histsize("HISTFILESIZE"));
	free(g_shell.save_list);
	free_hist();
	free_env(DEFAULT, NULL);
	int_return_value = ft_atoi(str_ret);
	if (str_ret)
		free(str_ret);
	exit(int_return_value);
}
