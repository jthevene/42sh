/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:51:05 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char		*ft_str_replace(char *str, char *to_search, char *to_replace)
{
	FT_INIT(char*, str_replaced, NULL);
	FT_INIT(int, len_str, 0);
	FT_INIT(char*, strstr_match, NULL);
	if (!str || !to_replace || !to_search || !ft_strstr(str, to_search))
		return (NULL);
	len_str = ft_strlen(str) - ft_strlen(to_search);
	len_str = len_str < 0 ? -len_str : len_str;
	len_str += ft_strlen(to_replace);
	str_replaced = ft_strnew(len_str + 1);
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
