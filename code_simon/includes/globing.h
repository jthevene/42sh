/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 11:27:15 by sgaudin           #+#    #+#             */
/*   Updated: 2016/10/13 10:45:10 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBING_H
# define GLOBING_H

# include "../../includes/42sh.h"

# ifndef FT_INIT
#  define FT_INIT(t, n, v) t n = v
# endif

# ifndef FT_MULTI4
#  define FT_MULTI4(a, b, c, d) a = b = c = d
# endif

# ifndef FT_MULTI3
#  define FT_MULTI3(a, b, c) a = b = c
# endif

# define MULT 1
# define RNG 2
# define NOMULT 3
# define NORNG 4
# define MIX 5

typedef struct			s_glob
{
	char				*mult;
	char				*rng;
	char				*no_mult;
	char				*no_rng;
	char				*mix;
	char				upper[27];
	char				lower[27];
	char				alpha[53];
	char				digit[11];
	char				alnum[63];
	char				space[7];
	char				graph[95];
	char				print[96];
	char				punct[33];
	char				cntrl[34];
	char				xdigit[17];
}						t_glob;

int						glob_parser(void);

void					hub_bracket(t_glob *glob);
void					init_tabs1(t_glob *glob, int i, int j);
void					init_tabs2(t_glob *glob);
void					init_tabs3(t_glob *glob);

char					*fill_mult(char *str);
char					*fill_rng(char *str);
char					*fill_nomult(char *str);
char					*fill_norng(char *str);
char					*fill_mix(char *str);
char					*clean_brackets(char *str);
void					fill_glob_struct(int glob_case, char *line, t_glob *glob);

#endif
