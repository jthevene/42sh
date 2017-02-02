/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 14:01:40 by jules             #+#    #+#             */
/*   Updated: 2017/02/02 21:01:39 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/history.h"

int		ft_strisnum(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '-' && str[1])
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

char	*event_str(char *str)
{
	t_lst	*tmp;

	tmp = g_shell.hist;
	while (tmp && str)
	{
		if (ft_strstr(tmp->content, str))
			return (ft_strdup(tmp->content));
		tmp = tmp->prev;
	}
	ft_putendl("event not found");
	return (NULL);
}

char	*event_n(int n)
{
	t_lst	*tmp;
	int		i;

	tmp = g_shell.hist;
	i = n;
	if (n < 0)
	{
		while (tmp && ++i < 0)
			tmp = tmp->prev;
		if (tmp)
			return (ft_strdup(tmp->content));
	}
	else
	{
		while (tmp && tmp->number != n)
			tmp = tmp->prev;
		if (tmp)
			return (ft_strdup(tmp->content));
	}
	ft_putendl("event not found");
	return (NULL);
}

void	check_pattern_event(char *event)
{
	char	*str;
	int		len;

	str = NULL;
	len = ft_strlen(event);
	ft_putchar(10);
	if (event[0] == '!' && len > 1)
	{
		str = ft_strsub(event, 1, --len);
		if (str[0] == '!' && len == 1)
			event_n(-1);
		else if (ft_strisnum(str))
			event_n(ft_atoi(str));
		else
			event_str(str);
	}
	free(str);
}
