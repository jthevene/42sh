/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 02:09:03 by hjacque           #+#    #+#             */
/*   Updated: 2016/11/10 12:10:09 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# include <wchar.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

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
void				ft_putunbrprec(unsigned long long nbr, int *state, \
					unsigned int base, int caps);
void				ft_putunbrchelou(unsigned long long nbr, \
					unsigned int base, int caps);
void				ft_putnbrprec(long long nbr, int *state, \
					int base, int caps);
void				ft_putnbrchelou(long long nbr, int base, int caps);
int					ft_nbrlen(long long nbr, int base);
int					get_nb(const char *str, int *i);
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
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
char				*ft_strcpy(char *dest, char const *src);
char				*ft_strncpy(char *dest, char const *src, size_t n);
char				*ft_strstr(char const *str, char const *to_find);
int					ft_strcmp(char const *s1, char const *s2);
int					ft_strncmp(char const *s1, char const *s2, size_t n);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isprint(int c);
int					ft_isascii(int c);
int					ft_isspace(int c);
size_t				ft_strlen(char const *s);
char				*ft_strdup(char const *s1);
char				*ft_strcat(char *s1, char const *s2);
char				*ft_strncat(char *s1, char const *s2, size_t n);
char				*ft_strchr(char const *s, int c);
char				*ft_strrchr(char const *s, int c);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strnstr(char const *str, char const *to_find, size_t n);
void				ft_bzero(void *b, size_t len);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
int					ft_atoi(const char *str);
void				*ft_memmove(void *dst, const void *src, size_t len);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_itoa(int nb);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_lstaddback(t_list *alst, t_list *new);
char				**ft_tabdup(char **tab);
int					ft_tablen(char **tab);
char				*ft_strdupfree(char *s1);
char				*ft_strndup(char *str, int n);

#endif
