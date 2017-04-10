/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_imbricated.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 19:33:41 by sgaudin           #+#    #+#             */
/*   Updated: 2017/04/10 14:58:38 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/globing.h"

int			i_recup_lastb(char *str, t_glob *glob)
{
	FT_INIT(int, i, last_bracket(str, glob->lastb_count) + 1);
	FT_INIT(int, arg_len, 0);
	while (str[i] && str[i] != '}')
	{
		if (!(bracket_pushback(&glob->tmp_c)))
			return (0);
		arg_len = i_get_arg_len(str, i, ARG, glob);
		if (!(glob->tmp_c->content = ft_strsub(str, i, arg_len)))
			return (0);
		i += arg_len;
		i += str[i] == ',' ? 1 : 0;
	}
	return (1);
}

t_bracket	*i_create_new_args(char **ext, t_glob *glob)
{
	FT_INIT(t_bracket *, new_args, NULL);
	FT_INIT(char *, tmp, NULL);
	rewind_tbracket(&glob->tmp_c);
	while (1)
	{
		bracket_pushback(&new_args);
		if (!ext[0] && !ext[1])
			new_args->content = ft_strdup(glob->tmp_c->content);
		else
		{
			tmp = ext[0] ? ft_strjoin(ext[0], glob->tmp_c->content) : NULL;
			if (ext[1])
				new_args->content = tmp ? ft_strjoin(tmp, ext[1])
				: ft_strjoin(glob->tmp_c->content, ext[1]);
			else
				new_args->content = ft_strdup(tmp);
		}
		if (tmp)
			free(tmp);
		if (!glob->tmp_c->next)
			break ;
		glob->tmp_c = glob->tmp_c->next;
	}
	free_tbracket(&glob->tmp_c);
	return (new_args);
}

char		*recreate_2(char *s, char *new_s, t_bracket *new_a, t_glob *g)
{
	FT_INIT(char *, tmp, new_s);
	FT_INIT(char *, tmp2, NULL);
	FT_INIT(int, i, 0);
	new_s = ft_strjoin(new_s, new_a->content);
	free(tmp);
	if (g->c_touch == TRUE)
	{
		tmp = new_s;
		new_s = ft_strjoin(new_s, "}");
		free(tmp);
	}
	i = i_get_expr_end(s, g->lastb_count);
	if (i != (int)ft_strlen(s))
	{
		tmp = new_s;
		tmp2 = ft_strsub(s, i, ft_strlen(s) - i);
		new_s = ft_strjoin(new_s, tmp2);
		free(tmp);
		free(tmp2);
	}
	return (new_s);
}

char		*recreate_string(char *str, t_bracket *new_args, t_glob *glob)
{
	FT_INIT(int, i, last_bracket(str, glob->lastb_count) - 1);
	FT_INIT(char *, new_s, NULL);
	FT_INIT(char *, tmp, NULL);
	while (str[i] != '\0' && str[i] != ',' && str[i] != '{' && str[i] != '}')
		i--;
	new_s = i > 0 ? ft_strsub(str, 0, i + 1) : NULL;
	if (glob->c_touch == TRUE)
	{
		tmp = new_s;
		new_s = tmp ? ft_strjoin(new_s, "{") : ft_strdup("{");
		free(tmp ? tmp : NULL);
	}
	while (new_args->next)
	{
		tmp = new_s;
		new_s = !new_s ? ft_strdup(new_args->content)
		: ft_strjoin(new_s, new_args->content);
		free(tmp ? tmp : NULL);
		tmp = new_s;
		new_s = ft_strjoin(new_s, ",");
		free(tmp);
		new_args = new_args->next;
	}
	return (recreate_2(str, new_s, new_args, glob));
}

int			i_algo_imbricated(char *str, t_glob *glob)
{
	FT_INIT(char **, arg_ext, NULL);
	FT_INIT(t_bracket *, new_args, NULL);
	FT_INIT(char *, tmp, NULL);
	FT_INIT(int, count, count_imbric(str));
	while (count > 0)
	{
		i_recup_lastb(str, glob);
		arg_ext = i_get_arg_ext(str, glob);
		new_args = i_create_new_args(arg_ext, glob);
		rewind_tbracket(&new_args);
		tmp = recreate_string(str, new_args, glob);
		free(str);
		str = ft_strdup(tmp);
		free(tmp);
		free_double_tab(&arg_ext);
		free_tbracket(&new_args);
		glob->lastb_count = glob->c_touch == TRUE
		? glob->lastb_count + 1 : glob->lastb_count;
		if (detect_double_bracket(str) || i_detect_imbric(str) > 0)
			count--;
		count--;
	}
	glob->lastb_count = 1;
	i_hub_patterns(str, glob);
	return (1);
}
