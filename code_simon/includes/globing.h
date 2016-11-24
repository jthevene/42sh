/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 18:56:07 by sgaudin           #+#    #+#             */
/*   Updated: 2016/11/17 11:26:34 by sgaudin          ###   ########.fr       */
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

# ifndef MULT
#  define MULT 1 // [abc]
# endif
# ifndef RNG
#  define RNG 2 // [a-c]
# endif
# ifndef NOMULT
#  define NOMULT 3 // [!abc]
# endif
# ifndef NORNG
#  define NORNG 4 // [!a-c]
# endif
# ifndef MIX
#  define MIX 5 // [abc-fE-W] || [!abc-fE-W]
# endif

// Macros pour algo_imbricated, dans c_bracket
# ifndef ARG
#  define ARG 1
# endif
# ifndef BEGIN
#  define BEGIN 2
# endif
# ifndef END
#  define END 3
# endif

// Struct qui stocke le resultat d'une commande avec des []
typedef struct			s_bracket
{
	char				*content;
	struct s_bracket	*next;
	struct s_bracket	*prev;
}						t_bracket;

//Struct qui stocke le resultat d'une commande avec des {}
typedef struct			s_clist
{
	t_bracket			*list;
	struct s_clist		*next;
	struct s_clist		*prev;
}						t_clist;

typedef struct			s_glob
{
	t_bracket			*sbracket;
	t_clist				*cbracket;
	t_bracket			*tmp_c;

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

// Initialisation et gestion de depart
void					hub_sbracket(t_glob *glob);
void					init_tabs1(t_glob *glob, int i, int j);
void					init_tabs2(t_glob *glob);
void					init_tabs3(t_glob *glob);

// Traitement de la commande
char					*fill_mult(char *str);
char					*fill_rng(char *str);
char					*fill_nomult(char *str);
char					*fill_norng(char *str);
char					*fill_mix(char *str);
char					*handle_categories(char *str, t_glob *glob);

// Fonctions utilitaires
char					*clean_brackets(char *str);
int						get_len_mix(char *str);
int						get_letters(char **ret, char *str);
char					*get_rng_str(char *str, int i);
char					*get_category(char *str);
int						check_rng(char *str);
int						catch_dash(int i);
int						count_brackets(char *str, char bracket);
int						next_bracket(char *str, char c, int i);

// Fonctions enlevant les doublons d'une chaine
char					*strjoin_nodouble(char *s1, char *s2);
char					*strdup_nodouble(char *str);
char					*mult_nodouble(char *str);

// Fonctions de liste chainee
int						bracket_pushback(t_bracket **list);

// FONCTIONS CURLY BRACKETS
int						hub_cbracket(t_glob *glob);
int						clist_pushback(t_clist **clist);
int						clist_list_pushback(t_clist **clist);
int						fill_clist(char *line, t_glob *glob);
int						cbracket_errors(char *line, t_glob *glob);

int						next_comma(char *str, int i);
int						check_commas(char *line, int i);

int						i_recup_lastb(char *str, t_glob *glob);
int						i_get_arg_len(char *str, int i, int type);
int						i_algo_imbricated(char *str, t_glob *glob);
char					**i_get_arg_ext(char *str);

int						last_bracket(char *str);

#endif
