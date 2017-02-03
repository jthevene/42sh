#ifndef SH_H
# define SH_H

# ifndef _42SH_H
#  include "42sh.h"
# endif

# define WORDS		0
# define DQUOTE		1
# define SQUOTE		2
# define OR			3
# define AND		4
# define PIPE		5
# define DLESS		6
# define DMORE		7
# define LESS		8
# define MORE		9
# define SEMICOLON	10
# define END_LINE	11

typedef struct			s_token
{
	int					type;
	char				*lexeme;
	struct s_token		*next;
}						t_token;

typedef struct			s_all
{
	char				*line;
	t_token				*tokens_begin;
}						t_all;

typedef struct			s_tree
{
	int					type;
	char				*content;
	struct s_tree		*left;
	struct s_tree		*right;
}						t_tree;

int		execute_or_and(t_tree *tree);
char	*finish_line_backslash(char *line);
void	lexer_parser(char *line);
int		check_ope(t_token *token, char *line, int pos, int i);
int		ft_isprintnotope(char c);
void	print_tokens(t_token *token);
void	analise_line(t_all *all);
int		lire_lexeme(t_token *token, char *line, int pos);
void	add_lexeme(t_token *token, char *line, int pos, int i);
int		ft_isope(char c);
int		isallspace(char *str);
char	*epur_str(char *str);
t_token	*init_token(void);
void	backslash_char(t_token *token);
int		quote_in_word(char *line, int pos);
int		get_lexeme_pos(char *line, int pos);
int		unfinished_quote(char *line);
char	*finish_the_squote(char *line);
char	*finish_the_dquote(char *line);
void	free_tree(t_tree *tree);
void	free_tab(char **tabl);
void	parse(t_tree *tree, t_token *token);
int		dotcoma(t_tree *tree, t_token *token);
t_tree	*create_node(void);
int		and_or(t_tree *tree, t_token *token);
int		redirections(t_tree *tree, t_token *token);
void	start_parse(t_token *token);
t_token	*get_token(t_token *token, int type);
t_token	*get_token_and_or(t_token *token);
t_token	*get_token_redirections(t_token *token);
t_token	*copy_token_left(t_token *begin, t_token *ope);
t_token	*copy_token_right(t_token *ope);
char	*commands_leaf(t_token *token);
char	*trim_end(char *line);
int		token_squote(t_token *token, char *line, int pos, int i);
int		token_dquote(t_token *token, char *line, int pos, int i);
char	*finish_quotes(char *line);
int		left_redir_token(t_token *token, char *line, int pos, int i);
int		right_redir_token(t_token *token, char *line, int pos, int i);
int		pipe_or_token(t_token *token, char *line, int pos, int i);
int		supp_squote(t_token *token, int pos, int s);
int		supp_dquote(t_token *token, int pos, int d);
int		unfinished_squote(char *line, int i);
int		unfinished_dquote(char *line, int i);
char	*prompt_dquote(char *quote_type);
int		send_token_to_glob(t_all *all);
void	free_token(t_token *token);

#endif
