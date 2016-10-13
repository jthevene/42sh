/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_glob_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 11:39:09 by jules             #+#    #+#             */
/*   Updated: 2016/10/07 13:48:09 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/redir.h"
#include "../includes/globing.h"

char	*clean_brackets(char *str) // enleve les []
{
	int		i;
	int		len;
	int		start;
	char	*ret;
	
	i = 0;
	ret = NULL;
	len = 0;
	while (str[i] != '[')
		i++;
	start = i + 1;
	while (str[++i] != ']')
		len++;
	if (!(ret = (char *)malloc(sizeof(char)*len)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		ret[i] = str[start];
		i++;
		start++;
	}
	ret[i] = '\0';
	return (ret);
}

void	fill_glob_struct(int glob_case, char *line, t_glob *glob)//1=mult, 2=rng, 3=nomult 4=norng 5=mixed
{
	if (glob_case == MULT)
		glob->mult = clean_brackets(line);
	if (glob_case == RNG)
		glob->rng = fill_rng(line);
	if (glob_case == NOMULT)
		glob->no_mult = fill_nomult(line);
	if (glob_case == NORNG)
		glob->no_rng = fill_norng(line);
	if (glob_case == MIX)
		glob->mix = fill_mix(line);
}	