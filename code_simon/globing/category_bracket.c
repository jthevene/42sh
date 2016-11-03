/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   category_bracket.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 15:35:08 by sgaudin           #+#    #+#             */
/*   Updated: 2016/10/25 15:35:10 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/globing.h"

// Cette fonction gère les entrées de ce type : [[:upper:]]
static int 		category_choice(char *category, t_glob *glob)
{
	if (!ft_strcmp(category, "upper"))
		glob->bracket = ft_strdup(glob->upper);
	else if (!ft_strcmp(category, "lower"))
		glob->bracket = ft_strdup(glob->lower);
	else if (!ft_strcmp(category, "alpha"))
		glob->bracket = ft_strdup(glob->alpha);
	else if (!ft_strcmp(category, "digit"))
		glob->bracket = ft_strdup(glob->digit);
	else if (!ft_strcmp(category, "alnum"))
		glob->bracket = ft_strdup(glob->alnum);
	else if (!ft_strcmp(category, "space"))
		glob->bracket = ft_strdup(glob->space);
	else if (!ft_strcmp(category, "graph"))
		glob->bracket = ft_strdup(glob->graph);
	else if (!ft_strcmp(category, "print"))
		glob->bracket = ft_strdup(glob->print);
	else if (!ft_strcmp(category, "punct"))
		glob->bracket = ft_strdup(glob->punct);
	else if (!ft_strcmp(category, "cntrl"))
		glob->bracket = ft_strdup(glob->cntrl);
	else if (!ft_strcmp(category, "xdigit"))
		glob->bracket = ft_strdup(glob->xdigit);
	else
		printf("No match found /// Category choice\n");
	return (0);
}

// Fonction qui check si l'entrée est correcte, sinon imprime un message d'erreur
int 			check_categories(char *str, t_glob *glob)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, j, 0);
	FT_INIT(char *, category, NULL);

	while (str[i] != '[')
		i++;
	if (str[i + 1] && str[i + 2] && str[i + 1] == '[' && str[i + 2] == ':')
	{
		j = i + 2;
		while (str[i] && str[i] != ' ')
			i++;
		if (str[i - 1] == ']' && str[i - 2] == ']' && str[i - 3] == ':')
		{
			category = ft_strsub(str, j + 1, i - j - 4);
			printf("category = %s\n", category);
			category_choice(category, glob);
		}
		else
		{
			printf("Bad pattern check categories\n");
			free(category);
			return (-1);
		}
	}
	free(category);
	if (!glob->bracket)
		return (0);
	else
		printf("glob->bracket = %s\n", glob->bracket);
	return (1);
}