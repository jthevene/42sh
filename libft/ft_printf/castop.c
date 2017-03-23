/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   castop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/06 13:44:10 by hjacque           #+#    #+#             */
/*   Updated: 2016/01/22 14:50:23 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

long long				get_arg(va_list *ap, int *state)
{
	long long			nbr;

	if (state[L])
		nbr = va_arg(*ap, long int);
	else if (state[HH])
		nbr = (signed char)va_arg(*ap, int);
	else if (state[H])
		nbr = (short)va_arg(*ap, int);
	else if (state[LL])
		nbr = va_arg(*ap, long long int);
	else if (state[J])
		nbr = va_arg(*ap, intmax_t);
	else if (state[Z])
		nbr = va_arg(*ap, size_t);
	else
		nbr = va_arg(*ap, int);
	return (nbr);
}

unsigned long long		get_uarg(va_list *ap, int *state)
{
	unsigned long long	nbr;

	if (state[L])
		nbr = va_arg(*ap, unsigned long int);
	else if (state[HH])
		nbr = (unsigned char)va_arg(*ap, unsigned int);
	else if (state[H])
		nbr = (unsigned short)va_arg(*ap, unsigned int);
	else if (state[LL])
		nbr = va_arg(*ap, unsigned long long int);
	else if (state[J])
		nbr = va_arg(*ap, uintmax_t);
	else if (state[Z])
		nbr = va_arg(*ap, size_t);
	else
		nbr = va_arg(*ap, unsigned int);
	return (nbr);
}
