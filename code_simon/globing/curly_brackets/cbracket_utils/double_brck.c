/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_brck.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 09:03:03 by sgaudin           #+#    #+#             */
/*   Updated: 2016/11/30 09:03:04 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/globing.h"

// 1 ---> Recup la partie a traiter (next_comma) --->>>>> OK
// 2 ---> Recup le 'i' de cette partie --->>>>> OK
// 3 ---> Créer la liste chainée qui va contenir toutes les possibilités --->>>>> IN PROGRESS
// 4 ---> Recréer la chaine de caractères avec les nouveaux arguments
// 5 ---> Renvoyer tout ce joyeux bordel au début (algo_imbricated)

void		i2_recup_patterns(char *str, char *tmp, int i, t_glob *glob)
{
	if (str && glob && i)
		printf("\n/~~~~~ RECUP PATTERNS ~~~~~/ tmp = %s\n\n", tmp);
}

void		i2_hub_imbric(char *str, t_glob *glob)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, ret, 0);
	FT_INIT(char *, tmp, NULL);
	while (str[i] != '{')
		i++;
	while (str[++i])
	{
		if ((ret = next_comma(str, i)) == -1)
		{
			tmp = ft_strsub(str, i, ft_strlen(str) - i - 1);
			printf("/##### HUB IMBRIC #####/ tmp = %s\n", tmp);
			if (ft_strchr(tmp, '{'))
				i2_recup_patterns(str, tmp, i, glob);
			break ;
		}
		else
		{
			tmp = ft_strsub(str, i, ret);
			printf("/##### HUB IMBRIC #####/ tmp = %s\n", tmp);
			i += next_comma(str, i);
			if (ft_strchr(tmp, '{'))
				i2_recup_patterns(str, tmp, i, glob);
		}
		free(tmp);
	}
}