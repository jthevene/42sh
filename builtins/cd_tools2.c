/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tools2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 16:29:05 by sgaudin           #+#    #+#             */
/*   Updated: 2017/03/06 16:39:19 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

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
