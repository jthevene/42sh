/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_imbricated.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 09:54:32 by sgaudin           #+#    #+#             */
/*   Updated: 2016/11/23 09:54:33 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/globing.h"

int				i_recup_lastb(char *str, t_glob *glob)
{
	FT_INIT(int, i, last_bracket(str) + 1);
	FT_INIT(int, arg_len, 0);
	while (str[i] != '}')
	{
		if (!(bracket_pushback(&glob->tmp_c)))
			return (0);
		arg_len = i_get_arg_len(str, i, ARG);
		if (!(glob->tmp_c->content = ft_strsub(str, i, arg_len)))
			return (0);
		i += arg_len;
		i += str[i] == ',' ? 1 : 0;
		printf("TMP_C->content = %s\n", glob->tmp_c->content);
	}
	return (1);
}

t_bracket		*i_create_new_args(char **arg_ext, t_glob *glob)
{
	FT_INIT(t_bracket *, new_args, NULL);
	FT_INIT(char *, tmp, NULL);
	while (glob->tmp_c->prev)
		glob->tmp_c = glob->tmp_c->prev;
	while (1)
	{
		bracket_pushback(&new_args);
		if (!arg_ext[0] && !arg_ext[1])
			new_args->content = ft_strdup(glob->tmp_c->content);
		if (arg_ext[0])
			tmp = ft_strjoin(arg_ext[0], glob->tmp_c->content);
		if (arg_ext[1])
			new_args->content = tmp ? ft_strjoin(tmp, arg_ext[1])
			: ft_strjoin(glob->tmp_c->content, arg_ext[1]);
		if (tmp)
			free(tmp);
		printf("new_arg created : %s\n", new_args->content);
		if (!glob->tmp_c->next)
			break ;
		else
			glob->tmp_c = glob->tmp_c->next;
	}
	free_tbracket(&glob->tmp_c);
	glob->tmp_c = NULL;
	return (new_args);
}

char			*recreate_string(char *str, t_bracket *new_args)
{
	FT_INIT(int, i, last_bracket(str) - 1);
	FT_INIT(char *, new_str, NULL);
	FT_INIT(char *, tmp, NULL);
	FT_INIT(char *, tmp2, NULL);
	while (str[i] != ',' && str[i] != '{')
		i--;
	new_str = ft_strsub(str, 0, i + 1);
	while (new_args->next)
	{
		tmp = new_str;
		new_str = ft_strjoin(new_str, new_args->content);
		free(tmp);
		tmp = new_str;
		new_str = ft_strjoin(new_str, ",");
		free(tmp);
		new_args = new_args->next;
	}
	tmp = new_str;
	new_str = ft_strjoin(new_str, new_args->content);
	free(tmp);
	i = i_get_expr_end(str);
	tmp = new_str;
	tmp2 = ft_strsub(str, i, ft_strlen(str) - i);
	new_str = ft_strjoin(new_str, tmp2);
	free(tmp);
	free(tmp2);
	return (new_str);
}

int				i_algo_imbricated(char *str, t_glob *glob)
{
	FT_INIT(char **, arg_ext, i_get_arg_ext(str));
	FT_INIT(t_bracket *, new_args, NULL);
	FT_INIT(char *, tmp, NULL);
	i_recup_lastb(str, glob);
	new_args = i_create_new_args(arg_ext, glob);
	rewind_tbracket(&new_args);
	tmp = recreate_string(str, new_args);
	free(str);
	str = ft_strdup(tmp);
	free(tmp);
	printf("new_str = %s\n", str);
// PENSER A FREE ARG_EXT ET NEW_ARGS
	return (1);
}

// l {a,{bcd,e{f,g}h,lol}}
// l {a,{bcd,cou{f,g}cou}}