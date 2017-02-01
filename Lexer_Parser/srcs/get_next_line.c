#include "../includes/get_next_line.h"

int	get_next_line(int const fd, char **line)
{
  static char stck[BUFF_SIZE];
  char *buf;
  char *tmp;
  int i;
  
  if (BUFF_SIZE < 1 || !line)
    return (-1);
  if (!(buf = malloc(sizeof(char) * BUFF_SIZE + 1)))
    return (-1);
  if (!(tmp = ft_strncpy(ft_strnew(BUFF_SIZE), stck, BUFF_SIZE)))
    return (-1);
  while (ft_strchr(tmp, '\n') == 0)
    {
      if ((i = read(fd, buf, BUFF_SIZE)) == -1)
	return (-1);
      if (i == 0 && ft_strlen(tmp))
	{
	  *line = ft_strncpy(ft_strnew(ft_strlen(tmp)), tmp, ft_strlen(tmp));
	  free(tmp);
	  free(buf);
	  ft_bzero(stck, BUFF_SIZE);
	  i = 1;
          return (0);
	}
      else if (i == 0)
      {
            *line = NULL;
          return (0);
    }
    buf[i] = '\0';
    tmp = ft_strjoinfree(tmp, buf, 1);
    }
  free(buf);
  i = (size_t)(ft_strchr(tmp, '\n') - tmp);
  *line = ft_strncpy(ft_strnew(i), tmp, i);
  ft_bzero(stck, BUFF_SIZE);
  ft_strncpy(stck, ft_strchr(tmp, '\n') + 1, BUFF_SIZE);
  free(tmp);
  return (1);
}
