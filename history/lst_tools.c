/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:46:01 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/history.h"

t_lst		*ft_newlst(char *content)
{
	t_lst	*new;

	new = (t_lst*)ft_memalloc(sizeof(t_lst));
	if (new)
	{
		if (!content)
			new->content = NULL;
		else
			new->content = ft_strdup(content);
		new->next = NULL;
		new->prev = NULL;
		new->number = 1;
	}
	return (new);
}

void		ft_append_lst(t_lst **lst, t_lst *new_elem)
{
	t_lst	*tmp;

	if (!*lst)
	{
		*lst = new_elem;
	}
	else
	{
		tmp = *lst;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_elem;
		new_elem->prev = tmp;
		new_elem->number = tmp->number + 1;
	}
}

void		ft_print_list_content(t_lst *lst)
{
	t_lst	*tmp;
	int		i;

	tmp = lst;
	i = 1;
	if (tmp && tmp->content)
	{
		while (tmp->next && tmp->next->content)
		{
			ft_putnbr(i++);
			ft_putstr(" => ");
			ft_putendl(tmp->content);
			tmp = tmp->next;
		}
		ft_putnbr(i++);
		ft_putstr(" => ");
		ft_putendl(tmp->content);
	}
	else
		ft_putendl("Liste NULL");
}

void		ft_lst_rewind_n(t_lst **lst, int n)
{
	if ((*lst) != NULL)
	{
		while ((*lst)->prev)
		{
			(*lst) = (*lst)->prev;
			n--;
			if (n == 0)
				break ;
		}
	}
}

void		ft_lst_rewind(t_lst **lst)
{
	if ((*lst) != NULL)
	{
		while ((*lst)->prev)
			(*lst) = (*lst)->prev;
	}
}
