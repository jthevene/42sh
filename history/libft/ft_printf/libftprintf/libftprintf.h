/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 11:17:22 by sgaudin           #+#    #+#             */
/*   Updated: 2016/06/29 16:05:58 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include "../includes/ft_printf.h"
# include <wchar.h>

int			ftp_putbase(uintmax_t n, uint32_t base, uint8_t flag,
						t_docker *data);
int			ftp_putchar(uint32_t c);
int			ftp_putstr(uint8_t *str);
int			ftp_strlen(uint8_t *str);
int			ftp_putnbr(int64_t n, t_docker *data);
int			ftp_putnbr_long(int64_t n, t_docker *data);
int			ftp_putbase_long(uintmax_t n, uint32_t base, uint8_t flag,
							t_docker *data);
int			ftp_putwchar(wchar_t c, int count);
int			ftp_putwstr(wchar_t *str, int write);

#endif
