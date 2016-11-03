/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_right.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 14:35:45 by sgaudin           #+#    #+#             */
/*   Updated: 2016/10/13 10:55:21 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
		     					.i;;;;i.                                  
                               iYcviii;vXY:                                
                             .YXi       .i1c.                              
                            .YC.     .    in7.                             
                           .vc.   ......   ;1c.                            
                           i7,   ..        .;1;                            
                          i7,   .. ...      .Y1i                           
                         ,7v     .6MMM@;     .YX,                          
                        .7;.   ..IMMMMMM1     :t7.                         
                       .;Y.     ;$MMMMMM9.     :tc.                        
                       vY.   .. .nMMM@MMU.      ;1v.                       
                      i7i   ...  .#MM@M@C. .....:71i                       
                     it:   ....   $MMM@9;.,i;;;i,;tti                      
                    :t7.  .....   0MMMWv.,iii:::,,;St.                     
                   .nC.   .....   IMMMQ..,::::::,.,czX.                    
                  .ct:   ....... .ZMMMI..,:::::::,,:76Y.                   
                  c2:   ......,i..Y$M@t..:::::::,,..inZY                   Unfinished, still under contruction, step away visitor :3
                 vov   ......:ii..c$MBc..,,,,,,,,,,..iI9i                  
                i9Y   ......iii:..7@MA,..,,,,,,,,,....;AA:                 
               iIS.  ......:ii::..;@MI....,............;Ez.                
              .I9.  ......:i::::...8M1..................C0z.               
             .z9;  ......:i::::,.. .i:...................zWX.              
             vbv  ......,i::::,,.      ................. :AQY              
            c6Y.  .,...,::::,,..:t0@@QY. ................ :8bi             
           :6S. ..,,...,:::,,,..EMMMMMMI. ............... .;bZ,            
          :6o,  .,,,,..:::,,,..i#MMMMMM#v.................  YW2.           
         .n8i ..,,,,,,,::,,,,.. tMMMMM@C:.................. .1Wn           
         7Uc. .:::,,,,,::,,,,..   i1t;,..................... .UEi          
         7C...::::::::::::,,,,..        ....................  vSi.         
         ;1;...,,::::::,.........       ..................    Yz:          
          v97,.........                                     .voC.          
           izAotX7777777777777777777777777777777777777777Y7n92:            
             .;CoIIIIIUAA666666699999ZZZZZZZZZZZZZZZZZZZZ6ov.   
*/

#include "../includes/redir.h"

static int	get_filename_double(int i, int last_fd)
{
	FT_INIT(int, j, 0);
	while (g_shell.line[i] && g_shell.line[i - 1] != '>')
		i++;
	if (g_shell.line[i - 1] == '>' && g_shell.line[i] != '>')
		return (0);
	if (!g_shell.line[++i])
		return (last_fd);
	while (g_shell.line[i] && ft_isspace(g_shell.line[i]))
		i++;
	if (!g_shell.line[i])
		return (0);
	FT_INIT(int, tmp, i);
	while (g_shell.line[tmp] && !ft_isspace(g_shell.line[tmp]))
		tmp++;
	FT_INIT(char *, filename, ft_strnew(tmp - i + 1));
	while (g_shell.line[i] && !ft_isspace(g_shell.line[i]))
	{
		filename[j] = g_shell.line[i];
		i++;
		j++;
	}
	filename[j] = '\0';
	FT_INIT(int, fd, open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644));
	printf("FD créé : %d\n", fd);
	free(filename);
	return (get_filename_double(i, fd));
}

int			double_right(void)
{
	int		fd;
	int		fd_out;

	printf("Entrée dans double_right\n");
	if (!ft_strchr(g_shell.line, '>'))
		return (0); /* Pas de redirection(s) droite */
	printf("Redirection détectée\n");
	fd_out = detect_out();
	printf("Detect_out OK : %d\n", fd_out);
	if (!(fd = get_filename_double(1, 0)))
		return (0); /* Pas de fichier spécifié pour la redirection ou pas de double redir */
	printf("Test 2 OK, fichier créé, on a récup le fd %d\n", fd);
	printf("Prêt pour fork la commande et dup la sortie dans le fichier\n");
	close(fd);
//	exec_redir_right(fd);
	return (1);
}
