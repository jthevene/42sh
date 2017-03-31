/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tools2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:46:47 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

char				*ft_rescue_directory(void)
{
	if (!g_shell.line)
		return (NULL);
	FT_INIT(char*, path_rescue, ft_strdup(g_shell.line));
	FT_INIT(char*, tmp, NULL);
	if (!verif_access_bin_directory_(path_rescue))
	{
		if (path_rescue && ft_strrchr(path_rescue, '/'))
		{
			tmp = ft_strsub(path_rescue, 0, ft_strlen(path_rescue) -
				ft_strlen(ft_strrchr(path_rescue, '/')));
			ft_strdel(&path_rescue);
			path_rescue = ft_strjoin(tmp, "/");
			free(tmp);
		}
	}
	return (path_rescue);
}
