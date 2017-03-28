/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/23 18:45:16 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdint.h>
# include <wchar.h>

# include "get_next_line.h"

# ifndef FT_INIT
#  define FT_INIT(t, n, v) t n = v
# endif

void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);

size_t				ft_strlen(const char *s);

int					ft_nbrlen(int i);

char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t n);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_str_replace(char *str, char *to_search,
					char *to_replace);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);

int					ft_atoi(const char *str);
int					ft_atoibase(char *nb, int base);

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_isspace(int c);

int					ft_toupper(int c);
int					ft_tolower(int c);

void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);

char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);

void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);

char				*ft_itoa(int n);
char				*ft_itoa_base(int n, int base);

int					ft_recursive_pow(int n, int power);

void				ft_putchar(char c);
int					ft_putchar_int(int i);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putnbrendl(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);

typedef struct		s_list
{
	char			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstaddend(t_list **alst, t_list *new_elem);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_lstadd_bottom(t_list **alst, t_list *new);
void				ft_print_list(t_list **alst);

int					ft_sqrt(int n);
int					ft_abs(int n);
void				ft_printbase(unsigned char n, int base);
void				ft_printhex(unsigned char n);
char				*ft_strtolower(char *str);
char				*ft_strtoupper(char *str);

int					ft_putwchar(wchar_t c);
int					ft_putwstr(wchar_t *str);

void				ft_puttab(char **array);
void				ft_putendl_fd_exit(char const *src, int fd, int exit_code);
int					ft_isallspace(char *str);
char				*ft_epurstr(char *str);
char				*ft_strjoinfree(char *s1, char *s2, int flag_str_to_free);
void				ft_putstrtimespace(char const *s);
void				ft_putstrspace(char const *s);
void				ft_putstrtime(char const *s);
char				*ft_strjoinchar(char const *s1, char const *s2, char c);
int					ft_unbrlen(unsigned long long nbr, unsigned int base);
char				*ft_ltoa(long int nb);
char				*ft_realloc(void *str, int sizebase, int size);
int					size_bin(unsigned int nbr);
void				ft_putunbrprec(unsigned long long nbr, int *state,
						unsigned int base, int caps);
void				ft_putnbrprec(long long nbr, int *state,
						int caps);
void				ft_putnbr_ftprintf(long long nbr, int caps);

int					ft_count_tab(char **array);
int					get_nb(const char *str, int *i);
void				ft_lstaddback(t_list *alst, t_list *new);
char				**ft_tabdup(char **tableau);
int					ft_tablen(char **tableau);
char				*ft_strdupfree(char *s1);
char				*ft_strndup(char *str, int n);

#endif
