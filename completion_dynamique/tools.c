/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 17:20:11 by dvirgile          #+#    #+#             */
/*   Updated: 2017/02/22 08:57:57 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

int				prev_sentence_value(char *sentence)
{
	FT_INIT(int, val, 0);
	FT_INIT(int, poid, 0);
	while (sentence && sentence[poid])
	{
		val += sentence[poid] + poid;
		poid++;
	}
	return (val);
}

char			*set_copy_sentence(char *sentence)
{
	FT_INIT(char*, copy_sentence, NULL);
	FT_INIT(int, nb_char, 0);
	nb_char = g_shell.cursor_x - g_shell.prompt_len;
	copy_sentence = ft_strnew(nb_char);
	ft_strncpy(copy_sentence, sentence, nb_char);
	return (copy_sentence);
}

int				verif_sentence(char *sentence)
{
	if (!ft_strchr(sentence, ' '))
		return (1);
	FT_INIT(char**, sentence_tab, ft_strsplit(sentence, ' '));
	FT_INIT(int, i, 0);
	while (sentence_tab[i])
		i++;
	free_auto_tab(sentence_tab);
	return (i);
}

int				arrondi(float val)
{
	FT_INIT(int, val2, val);
	FT_INIT(float, result, val - val2);
	if (result >= 0.5)
		return (val2);
	return (val2);
}

int				ft_nb_elem_lst(int nb_elem, int nb_col)
{
	FT_INIT(float, result, 0);
	while (result * nb_col < nb_elem)
		result++;
	return (result);
}
