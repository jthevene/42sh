/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/31 17:33:19 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBING_H
# define GLOBING_H

# ifndef SH42_H
#  include "sh42.h"
# endif

# ifndef FT_INIT
#  define FT_INIT(t, n, v) t n = v
# endif

# ifndef FT_MULTI4
#  define FT_MULTI4(a, b, c, d) a = b = c = d
# endif

# ifndef FT_MULTI3
#  define FT_MULTI3(a, b, c) a = b = c
# endif

# ifndef FT_TER
#  define FT_TER(si, alors, sinon) si ? alors : sinon
# endif

# ifndef MULTI
#  define MULTI(val_a, val_b, val_c) val_a = val_b = val_c
# endif

# ifndef MULT
#  define MULT 1
# endif
# ifndef RNG
#  define RNG 2
# endif
# ifndef NOMULT
#  define NOMULT 3
# endif
# ifndef NORNG
#  define NORNG 4
# endif
# ifndef MIX
#  define MIX 5
# endif

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

typedef struct			s_bracket
{
	char				*content;
	struct s_bracket	*next;
	struct s_bracket	*prev;
}						t_bracket;

typedef struct			s_clist
{
	t_bracket			*list;
	int					index;
	int					rewind;
	struct s_clist		*next;
	struct s_clist		*prev;
}						t_clist;

typedef	struct			s_checkfile
{
	int					*i;
	int					*j;
	int					len;
	char				*s;
	char				*file;
}						t_checkfile;

typedef struct			s_glob
{
	t_bracket			*sbracket;

	t_clist				*cbracket;

	t_bracket			*tmp_c;
	int					c_touch;
	int					lastb_count;
	char				**ext_args;
	char				*exp;

	char				*command;

	t_bracket			*args;
	char				*f_path;
	char				*l_path;

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

int						glob_parser(char **line);
int						replace_env_var(char **line);
int						ft_strchr_bslash(char *s, int c);
int						verif_tokens(char **str);
int						backslash_char_globing(char **line);
char					*recreate_token_string(t_glob *glob);
void					free_glob(t_glob *glob);

void					hub_sbracket(t_glob *glob, char *line);
void					init_tabs1(t_glob *glob, int i, int j);
void					init_tabs2(t_glob *glob);
void					init_tabs3(t_glob *glob);

char					*fill_mult(char *str);
char					*fill_rng(char *str);
char					*fill_nomult(char *str);
char					*fill_norng(char *str);
char					*fill_mix(char *str);
char					*handle_categories(char *str, t_glob *glob);
int						detect_category(char *str);

char					*clean_brackets(char *str);
int						get_len_mix(char *str);
int						get_letters(char **ret, char *str);
char					*get_rng_str(char *str, int i);
char					*get_category(char *str);
int						check_rng(char *str);
int						catch_dash(int i);
int						count_brackets(char *str, char bracket);
int						next_bracket(char *str, char c, int i);

char					*strjoin_nodouble(char *s1, char *s2);
char					*strdup_nodouble(char *str);
char					*mult_nodouble(char *str);

int						bracket_pushback(t_bracket **list);
int						pushback_content(t_bracket **list, char *content);
void					rewind_tbracket(t_bracket **list);
int						free_tbracket(t_bracket **list);
void					copy_list(t_bracket **src, t_bracket **dest);

int						hub_cbracket(t_glob *glob, char *line);
int						is_expansion(char *line);
char					**recup_ext_args(char *str);
int						cbracket_errors(char *line, t_glob *glob);
int						fill_clist(char *line, t_glob *glob);

int						clist_pushback(t_clist **clist);
int						clist_list_pushback(t_clist **clist);
void					rewind_tclist(t_clist **clist);
void					print_clist_list(t_clist **clist);
void					print_clist(t_clist **clist);
void					free_tclist(t_clist **list);
char					*next_expr(char *str, int i);

int						next_comma(char *str, int i);
int						end_bracket(char *str, int i);
int						is_bracket_in_exp(char *str, int i);
int						check_commas(char *line, int i);
int						detect_double_bracket(char *str);
int						last_bracket(char *str, int c);
int						count_imbric(char *str);
void					free_double_tab(char ***tabl);
char					*expand_pattern(char *pat, t_glob *glob);

int						i_recup_lastb(char *str, t_glob *glob);
int						i_get_arg_len(char *str, int i, int type, t_glob *glob);
int						i_algo_imbricated(char *str, t_glob *glob);
char					**i_get_arg_ext(char *str, t_glob *glob);
int						i_get_expr_end(char *str, int lastb_count);
char					*i_next_bracket(char *str);
int						i_detect_imbric(char *str);
t_clist					*i_create_multi_list(char *str);
t_clist					*i_recup_multi_patterns(char *str, int i, int j);
char					*i_multi_patterns(t_clist **multi, int index);
void					rewind_index(t_clist **list, int index);

void					i2_hub_imbric(char *str, int i, t_glob *glob);
void					i_hub_patterns(char *str, t_glob *glob);

int						hub_expansion(char *str, t_glob *glob);

int						exp_type(char *str);
char					*ft_cdup(char c);
int						is_solo_arg(t_bracket *args);
int						free_triple_str(char **s, char **s2, char **s3);

int						secured_call_to_sbracket(t_glob *g, char *s, t_lst **f
												, char **token);
int						hub_final(t_glob *glob, char *line);
int						is_only_token(char token, char *str);
int						only_star(char *str, t_glob *glob);
int						g_parse_expr(char *str, t_glob *glob);
int						g_no_token(char *str, t_glob *glob);
int						only_qmark(char *str, int star, t_glob *glob);
int						only_cbrkt(char *str, t_glob *glob);
int						mix_with_star(char *str, t_glob *glob);
int						mix_token(char *str, t_glob *glob);

int						get_len_token(char *str);
char					*wild_get_token(char *str);

t_lst					*get_dir_content(char *dir);
char					*ft_strpathjoin(const char *s1, const char *s2);
char					*get_cmd_path(char *str);

t_lst					*only_qmark2(t_lst *dir_content, char *target);

int						ft_check_bracket(char *s1, int i, int stop, t_glob *g);
void					check_file(int len, char *s, char *file, t_glob **glob);
char					*get_next_star(char *str, int i);

int						ft_istrstr(char *s1, char *s2, int i, t_glob *g);
char					*ft_istrchr(const char *s, int c, int i);

int						push_content_path(t_bracket **l, char *s, t_glob *g);
char					*get_cmd_last_path(char *str);

t_lst					*ft_newlst(char *content);
void					ft_append_lst(t_lst **lst, t_lst *new_elem);
void					ft_print_list_content(t_lst *lst);
void					ft_lst_rewind(t_lst **lst);
void					ft_lst_free(t_lst **list);

#endif
