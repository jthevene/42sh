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

# ifndef CHARS
#  define CHARS 1
# endif
# ifndef DIGIT
#  define DIGIT 2
# endif
# ifndef BOTH
#  define BOTH 3
# endif

# ifndef TRUE
#  define TRUE 1
# endif
# ifndef FALSE
#  define FALSE 0
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
	int					index;
	int					rewind;
	struct s_clist		*next;
	struct s_clist		*prev;
}						t_clist;

typedef struct			s_glob
{
	t_bracket			*sbracket;
	t_clist				*cbracket;

	t_bracket			*tmp_c;
	int					c_touch;
	int					lastb_count;
	char				**ext_args;

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

//FONCTIONS SQUARE BRACKETS
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
void					rewind_tbracket(t_bracket **list);
void					free_tbracket(t_bracket **list);

// FONCTIONS CURLY BRACKETS
// Initialisation et gestion de depart
int						hub_cbracket(t_glob *glob);
char					**recup_ext_args(char *str);
int						cbracket_errors(char *line, t_glob *glob);
int						fill_clist(char *line, t_glob *glob);

// Fonctions de liste chainee
int						clist_pushback(t_clist **clist);
int						clist_list_pushback(t_clist **clist);
void					rewind_tclist(t_clist **clist);
void					print_clist_list(t_clist **clist);
void					print_clist(t_clist **clist);
void					free_tclist(t_clist **list);
char					*next_expr(char *str, int i);

// Fonctions utilitaires "cbracket"
int						next_comma(char *str, int i);
int						end_bracket(char *str, int i);
int						is_bracket_in_exp(char *str, int i);
int						check_commas(char *line, int i);
int						detect_double_bracket(char *str);
int						last_bracket(char *str, int c);
int						count_imbric(char *str);
void					free_double_tab(char ***tabl);
char					*expand_pattern(char *pat, t_glob *glob);

// Fonctions utilitaires servant pour les algos imbriqués
int						i_recup_lastb(char *str, t_glob *glob);
int						i_get_arg_len(char *str, int i, int type, t_glob *glob);
void					i_algo_imbricated(char *str, t_glob *glob);
char					**i_get_arg_ext(char *str, t_glob *glob);
int						i_get_expr_end(char *str, int lastb_count);
char					*i_next_bracket(char *str);
int						i_detect_imbric(char *str);
t_clist					*i_create_multi_list(char *str);
char					*i_multi_patterns(t_clist **multi, int index);
void					rewind_index(t_clist **list, int index);

// Fonctions de gestion des algos imbriqués
void					i2_hub_imbric(char *str, t_glob *glob);
void					i_hub_patterns(char *str, t_glob *glob);

// Fonctions de gestion des expansions
void					hub_expansion(char *str, t_glob *glob);

// Fonctions utilitaires des expansions
int						exp_type(char *str);

#endif
