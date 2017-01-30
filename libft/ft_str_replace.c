/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 16:24:25 by dvirgile          #+#    #+#             */
/*   Updated: 2017/01/30 16:24:44 by dvirgile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char 	*ft_str_replace(char *str, char *to_search, char *to_replace)
{
	FT_INIT(char*, str_replaced, NULL);
	FT_INIT(int, len_str, 0);
	FT_INIT(char*, strstr_match, NULL);
	if (!str || !to_replace || !to_search || !ft_strstr(str, to_search))
		return (NULL);
	len_str = ft_strlen(str) - ft_strlen(to_search);
	len_str = len_str < 0 ? -len_str : len_str;
	len_str += ft_strlen(to_replace);
	str_replaced = ft_strnew(len_str);
	strstr_match = ft_strstr(str, to_search);
	if (!ft_strcmp(strstr_match, str))
		len_str = 0;
	else
		len_str = ft_strlen(str) - ft_strlen(ft_strstr(str, to_search));
	str_replaced = ft_strncat(str_replaced, str, len_str);
	if (!ft_strcmp(strstr_match, str))
		len_str = ft_strlen(to_search);
	else
		len_str = ft_strlen(str) - ft_strlen(ft_strstr(str, to_search))
					+ ft_strlen(to_search);
	str_replaced = ft_strcat(str_replaced, to_replace);
	str_replaced = ft_strcat(str_replaced, str + len_str);
	return (str_replaced);
}
