/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 10:54:10 by jules             #+#    #+#             */
/*   Updated: 2016/11/08 12:27:52 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/42sh.h"

 int		which_arrow(char c)
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

/* int		readkeyspecial(void)
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
	if (read(STDIN_FILENO, &c, 1))
		if (c == 'A' || c == 'B' || c == 'C' || c == 'D')
			return (which_arrow(c));
	return (K_UNKNOWN);
}
*/

int 			detect_arrow(char *key)
{
	if (key[0] == 27 && key[1] == 91 && key[2] == 67)
		return (K_RIGHT);
	if (key[0] == 27 && key[1] == 91 && key[2] == 68)
		return (K_LEFT);
	if (key[0] == 27 && key[1] == 91 && key[2] == 65)
		return (K_UP);
	if (key[0] == 27 && key[1] == 91 && key[2] == 66)
		return (K_DOWN);
	else 
		return (0);
}

int				readkey(void)
{
	char *c;

	c = ft_strnew(15);
	if (read(STDIN_FILENO, c, 15))// on bloque ici en attendant au moins 1 byte
	{
		FT_INIT(int, i, 0);
		while (c[i])
		{
		//	printf("c =%d\n", c[i]);
			i++;
		}
		ft_putstr("\n\n");
	//	if (c[0] == 27)// caractere d'echappement recu
	//		return (readkeyspecial());// on doit donc traiter une touche speciale codee sur plusieurs bytes
	}
	if (c[0] == 67)
			return (K_OW_RIGHT);
	else if (c[0] == 68)
			return (K_OW_LEFT);
	else if (c[0] == 65)
			return (K_OL_UP);
	else if (c[0] == 66)
			return (K_OL_DOWN);
	if (c[0] > 31 && c[0] < 126)
	{
		fill_current_line(c[0]);
		return (K_PRINT);
	}
	if (c[0] == 127)
		return (K_BACKSP);
	if (c[0] == 126)
		return (K_DEL);
	if (c[0] == 10)
		return (K_RETURN);
	return (K_UNKNOWN);
}
