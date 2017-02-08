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

char	*event_str(char *str, char *type)
{
	t_lst	*tmp;

	tmp = g_shell.hist;
	while (tmp && str)
	{
		if (ft_strstr(tmp->content, str))
			return (ft_strdup(tmp->content));
		tmp = tmp->prev;
	}
	ft_printf("\n42sh: %s: event not found", type);
	return (NULL);
}

char	*event_n(int n, char *type)
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
	ft_printf("\n42sh: %s: event not found", type);
	return (NULL);
}