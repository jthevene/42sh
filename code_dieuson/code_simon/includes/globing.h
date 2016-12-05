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

# ifndef I_42SH_H
#  define I_42SH_H
#  include "../../includes/42sh.h"
# endif

# ifndef FT_INIT
#  define FT_INIT(t, n, v) t n = v // Macro d'initialisation de variable
# endif

# ifndef FT_MULTI4
#  define FT_MULTI4(a, b, c, d) a = b = c = d // Macro de multi assignation
# endif

# ifndef FT_MULTI3
#  define FT_MULTI3(a, b, c) a = b = c // Macro de multi assignation
# endif

# ifndef FT_TER
#  define FT_TER(si, alors, sinon) si ? alors : sinon
# endif

# define MULT 1 // [abc]
# define RNG 2 // [a-c]
# define NOMULT 3 // [!abc]
# define NORNG 4 // [!a-c]
# define MIX 5 // [abc-fE-W] || [!abc-fE-W]

typedef struct 			s_sbracket
{
	char 				*bracket;
	int 				type;
	struct s_sbracket	*next;
	struct s_sbracket	*prev;
}						t_sbracket;

typedef struct			s_glob
{
	t_sbracket			*sbracket;

	char				*command;
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

int 					check_categories(char *str, t_glob *glob);

char					*fill_mult(char *str);
char					*fill_rng(char *str);
char					*fill_nomult(char *str);
char					*fill_norng(char *str);
char					*fill_mix(char *str);

int 					next_bracket(char *str, int i);
int 					count_brackets(char *str, char bracket);

char					*clean_brackets(char *str);

int						get_len_mix(char *str);
int						get_letters(char **ret, char *str);
char					*get_rng_str(char *str, int i);

int						check_rng(char *str);
int						catch_dash(int i);

char					*strjoin_nodouble(char *s1, char *s2);
char 					*strdup_nodouble(char *str);
char					*mult_nodouble(char *str);

int 					sbracket_pushback(t_sbracket **list, int type);
void					print_sbracket(t_sbracket *list);

#endif
