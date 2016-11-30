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

int				count_imbric(char *str)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, count, 0);
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '{')
			count++;
		i++;
	}
	return (count);
}

int				i_recup_lastb(char *str, t_glob *glob)
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
//		printf("TMP_C->content = %s\n", glob->tmp_c->content);
	}
	return (1);
}

t_bracket		*i_create_new_args(char **ext, t_glob *glob)
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
//		printf("new_arg created : %s\n", new_args->content);
		if (!glob->tmp_c->next)
			break ;
		glob->tmp_c = glob->tmp_c->next;
	}
	free_tbracket(&glob->tmp_c);
	return (new_args);
}

char			*recreate_string(char *str, t_bracket *new_args, t_glob *glob)
{
	FT_INIT(int, i, last_bracket(str, glob->lastb_count) - 1);
	FT_INIT(char *, new_str, NULL);
	FT_INIT(char *, tmp, NULL);
	FT_INIT(char *, tmp2, NULL);
	while (str[i] != '\0' && str[i] != ',' && str[i] != '{' && str[i] != '}')
		i--;
	new_str = i > 0 ? ft_strsub(str, 0, i + 1) : NULL;
	if (glob->c_touch == TRUE)
	{
		tmp = new_str;
		new_str = tmp ? ft_strjoin(new_str, "{") : ft_strdup("{");
		if (tmp)
			free(tmp);
	}
	while (new_args->next)
	{
		tmp = new_str;
		new_str = !new_str ? ft_strdup(new_args->content)
		: ft_strjoin(new_str, new_args->content);
		if (tmp)
			free(tmp);
		tmp = new_str;
		new_str = ft_strjoin(new_str, ",");
		free(tmp);
		new_args = new_args->next;
	}
	tmp = new_str;
	new_str = ft_strjoin(new_str, new_args->content);
	free(tmp);
	if (glob->c_touch == TRUE)
	{
		tmp = new_str;
		new_str = ft_strjoin(new_str, "}");
		free(tmp);
	}
	i = i_get_expr_end(str, glob->lastb_count);
	if (i != (int)ft_strlen(str))
	{
		tmp = new_str;
		tmp2 = ft_strsub(str, i, ft_strlen(str) - i);
		new_str = ft_strjoin(new_str, tmp2);
		free(tmp);
		free(tmp2);
	}
	return (new_str);
}

void			i_algo_imbricated(char *str, t_glob *glob)
{
	FT_INIT(char **, arg_ext, NULL);
	FT_INIT(t_bracket *, new_args, NULL);
	FT_INIT(char *, tmp, NULL);
	FT_INIT(int, count, count_imbric(str));
	FT_INIT(int, i, 0);
	while (count > 0)
	{
		i = 0;
		i_recup_lastb(str, glob);
		arg_ext = i_get_arg_ext(str, glob);
		new_args = i_create_new_args(arg_ext, glob);
		rewind_tbracket(&new_args);
		tmp = recreate_string(str, new_args, glob);
		printf("NEW STR = %s\n", tmp);
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
	i_hub_patterns(str, glob);
}

// l {a,{bcd,e{,g}h,lol}}
// l {a,{bcd,cou{f,g}cou}}
// l {b{aba,obo}s,co{llier,lliers},LOL}
// l jk{lm{no,p}q{r,s}bw{eh,ah}cl{ef,ou},t}uv
// l jk{lm{no,p}q{r,s,wak}bw{eh,ah}cl{ef,ou,ang},t}uv