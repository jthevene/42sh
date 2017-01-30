#include "../includes/42sh.h"

char	**lst_to_tab(t_var *env)
{
	t_var	*tmp;
	char		**tab;
	int			i;

	i = 0;
	tmp = env;
	tab = (char**)malloc(sizeof(char*) * (lenght_list(env) + 1));
	while (tmp)
	{
		tab[i] = ft_strjoinchar(tmp->name, tmp->value, '=');
		i++;
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}

int		lenght_list(t_var *env)
{
	t_var	*tmp;
	int		lenght;

	lenght = 0;
	tmp = env;
	while (tmp)
	{
		lenght++;
		tmp = tmp->next;
	}
	return (lenght);
}
