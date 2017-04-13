/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 10:49:30 by sgaudin           #+#    #+#             */
/*   Updated: 2017/04/11 11:40:10 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/globing.h"

static char	*recup_varname(char **line, int i)
{
	FT_INIT(int, j, i);
	FT_INIT(char *, varname, NULL);
	FT_INIT(char *, value, NULL);
	while ((*line)[j])
	{
		if ((*line)[j] == '\\' || (*line)[j] == '\'' || (*line)[j] == '\"'
			|| (*line)[j] == '$')
			break ;
		j++;
	}
	varname = ft_strsub((*line), i, j - i);
	value = get_var(g_shell.env, varname);
	free(varname);
	return (value);
}

static void	reform3(char **line, char *tmp_end)
{
	FT_INIT(char *, tmp2, NULL);
	tmp2 = ft_strdup((*line));
	free((*line));
	(*line) = ft_strjoin(tmp2, tmp_end);
	free(tmp2);
}

static void	reform2(char **line, char *tmp_begin, char *tmp_mid, char *tmp_end)
{
	free((*line));
	(*line) = NULL;
	if (tmp_begin)
	{
		if (tmp_mid)
		{
			(*line) = ft_strjoin(tmp_begin, tmp_mid);
			if (tmp_end)
			{
				reform3(line, tmp_end);
				return ;
			}
		}
		else if (tmp_end)
			(*line) = ft_strjoin(tmp_begin, tmp_end);
		else
			(*line) = ft_strdup(tmp_begin);
		return ;
	}
	else if (tmp_mid)
		(*line) = tmp_end ? ft_strjoin(tmp_mid, tmp_end) : ft_strdup(tmp_mid);
	else if (tmp_end)
		(*line) = ft_strdup(tmp_end);
	else
		(*line) = NULL;
}

static void	reform_line_var(char **line, char *value, int i)
{
	FT_INIT(char *, tmp_begin, i > 0 ? ft_strsub((*line), 0, i) : NULL);
	FT_INIT(char *, tmp_mid, NULL);
	FT_INIT(char *, tmp_end, NULL);
	i++;
	while ((*line)[i] && (*line)[i] != '\\' && (*line)[i] != '\''
		&& (*line)[i] != '\"' && (*line)[i] != '$')
		i++;
	if ((*line)[i] != '\0')
		tmp_end = ft_strsub((*line), i, ft_strlen((*line)) - i);
	if (value != NULL)
		tmp_mid = ft_strdup(value);
	reform2(line, tmp_begin, tmp_mid, tmp_end);
	free(tmp_begin ? tmp_begin : NULL);
	free(tmp_mid ? tmp_mid : NULL);
	free(tmp_end ? tmp_end : NULL);
}

int			replace_env_var(char **line)
{
	FT_INIT(int, i, -1);
	FT_INIT(char *, tmp, NULL);
	while (++i < (int)ft_strlen((*line)) && (*line)[i])
	{
		if ((*line)[i] == '\\')
			i++;
		else if ((*line)[i] == '\'')
			while ((*line)[i] && (*line)[i] != '\'')
				i++;
		else if ((*line)[i] == '\"')
			while ((*line)[i] && (*line)[i] != '\"')
				i++;
		else if ((*line)[i] == '$')
		{
			tmp = recup_varname(line, i + 1);
			reform_line_var(line, tmp, i);
			free(tmp ? tmp : NULL);
			if (!(*line))
				break ;
		}
	}
	(*line) = !(*line) ? ft_strdup("") : (*line);
	return (0);
}
