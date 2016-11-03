/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 10:54:10 by jules             #+#    #+#             */
/*   Updated: 2016/10/25 17:04:16 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

static int		which_arrow(char c)
{
	if (c == 'A')
		return (K_UP);
	else if (c == 'B')
		return (K_DOWN);
	else if (c == 'C')
		return (K_RIGHT);
	else
		return (K_LEFT);
}

static int		readkeyspecial(void)
{
	struct termios		t;
	char				c;
	int					n_lus;

	tcgetattr(STDIN_FILENO, &t);
	t.c_cc[VMIN] = 0; // pour retourner du read meme s'il n'y a aucun byte a lire apres le 
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
	n_lus = read(STDIN_FILENO, &c, 1);
	t.c_cc[VMIN] = 1;// on retablit le read bloquant dans tous les cas avant de return
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
	if (n_lus <= 0)
		return (K_ESCAPE);
	if (c != '[')
		return (K_UNKNOWN);
	read(STDIN_FILENO, &c, 1);
	if (c == 'A' || c == 'B' || c == 'C' || c == 'D')
		return (which_arrow(c));
	return (K_UNKNOWN);
}

int				readkey(void)
{
	char c;

	read(STDIN_FILENO, &c, 1);// on bloque ici en attendant au moins 1 byte
	if (c == 27)// caractere d'echappement recu
		return (readkeyspecial());// on doit donc traiter une touche speciale codee sur plusieurs bytes
	if (c > 31 && c < 126)
	{
		//ajouter c à g_shell.current_line
		fill_current_line(c);
		return (K_PRINT);
	}
	if (c == 127)
		return (K_BACKSP);
	if (c == 126)
		return (K_DEL);
	if (c == 10)
		return (K_RETURN);
	return (K_UNKNOWN);
}