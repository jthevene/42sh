/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by apinho            #+#    #+#             */
/*   Updated: 2017/02/24 18:34:59 by apinho           ###   ########.fr       */
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
