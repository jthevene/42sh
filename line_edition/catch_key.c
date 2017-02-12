/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 17:16:00 by dvirgile          #+#    #+#             */
/*   Updated: 2017/01/16 17:16:00 by dvirgile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/42sh.h"

int				is_arrow(char *key)
{
	if (key[0] == 27 && key[1] == 91 && key[2] == 49
		&& key[3] == 59 && key[4] == 53)
		return (1);
	if ((key[0] == 27 && key[1] == 91 && (key[2] != 51
		&& key[2] != 70 && key[2] != 72)))
		return (1);
	return (0);
}

int				readkeyspecial(char *key)
{
//	readkeyspecial2();
	if (key[0] == 27 && key[1] == 99) // ALT + C
	{
//		ft_putendl("COPY");
		return (K_COPY);
	}
	else if (key[0] == 27 && key[1] == 0) // ECHAP
	{
//		ft_putendl("ECHAP");
		return (K_ESCAPE);
	}
	else if (key[0] == 27 && key[1] == 118) // ALT + V
		return (K_PAST);
	else if (is_arrow(key))
		return (detect_arrow(key));
	else if (key[0] == 27 && key[1] == 91 && key[2] == 51 && key[3] == 126)
		return (K_DEL);
	else if (key[0] == 27 && key[1] == 91 && key[2] == 72)
		return (K_GO_START);
	else if (key[0] == 27 && key[1] == 91 && key[2] == 70)
		return (K_GO_END);
	return (K_UNKNOWN);
}

int				readkey(void)
{
	FT_INIT(char*, c, g_shell.c);
	ft_bzero(c, 16);
	if (read(STDIN_FILENO, c, 15))// on bloque ici en attendant au moins 1 byte
	{
		if (c[0] == 27)// caractere d'echappement recu
			return (readkeyspecial(c));// on doit donc traiter une touche speciale codee sur plusieurs bytes
	}
	if (c[0] == 4 && c[1] == 0) // CTRL + D
		return (K_ESCAPE);
	else if (c[0] > 31 && c[0] < 127)
		return (K_PRINT);
	else if (c[0] == 5) // CTRL + E
		return (K_COPY);
	else if (c[0] == 9) // TAB
		return (K_TAB);
	else if (c[0] == 18) // CTRL + R
		return (K_CUT);
	else if (c[0] == 20) // PAST CTRL + T
		past_line(g_shell.clipboard);
	else if (c[0] == 127)
		return (K_BACKSP);
	else if (c[0] == 10)
		return (K_RETURN);
	return (K_UNKNOWN);
}
