/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/02 14:38:14 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/23 18:44:31 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>
# include <wchar.h>
# include <locale.h>
# include "../../includes/libft.h"

# define DIEZ 0
# define ZERO 1
# define MINUS 2
# define PLUS 3
# define SPACE 4
# define CHAMP 5
# define PRECISION 6
# define HH 8
# define H 7
# define L 9
# define LL 10
# define J 11
# define Z 12

typedef struct		s_printf
{
	char			c;
	int				(*ptr)(va_list *ap, int *state);
}					t_printf;

int					shortf(int ret, int *state);
int					printf_call(const char *str, int *i, va_list *ap);
int					conv(const char *format, int *i, va_list *ap);
int					indexof(const char *str, const char c);
void				range(int *state, const char *str, int *p, int *i);
int					ft_witoa(char *dest, wint_t src);
size_t				ft_wcharlen(wchar_t *s);
int					*ft_wctoa(char **dest, wchar_t *src);
int					ft_printf(const char *format, ...);
int					printf_pourcent(va_list *ap, int *state);
int					printf_s(va_list *ap, int *state);
int					printf_d(va_list *ap, int *state);
int					printf_gd(va_list *ap, int *state);
int					printf_gs(va_list *ap, int *state);
int					printf_o(va_list *ap, int *state);
int					printf_go(va_list *ap, int *state);
int					printf_u(va_list *ap, int *state);
int					printf_gu(va_list *ap, int *state);
int					printf_x(va_list *ap, int *state);
int					printf_gx(va_list *ap, int *state);
int					printf_i(va_list *ap, int *state);
int					printf_p(va_list *ap, int *state);
int					printf_c(va_list *ap, int *state);
int					printf_gc(va_list *ap, int *state);
long long			get_arg(va_list *ap, int *state);
unsigned long long	get_uarg(va_list *ap, int *state);

#endif
