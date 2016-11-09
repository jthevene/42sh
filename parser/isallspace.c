/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isallspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 14:31:22 by apinho            #+#    #+#             */
/*   Updated: 2016/09/26 14:11:45 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parse.h"

int		isallspace(char *str)
{
	unsigned int i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (i == (ft_strlen(str)))
		return (1);
	else
		return (0);
}

char	*epur_str(char *str)
{
	char	*tmp;
	int		i;
	int		k;

	i = 0;
	k = 0;
	tmp = malloc(sizeof(*tmp) * (ft_strlen(str) + 1));
	while ((str[i] == ' ') || (str[i] == '\t'))
		i++;
	while (str[i])
	{
		tmp[k++] = str[i++];
		while ((str[i] == ' ') || (str[i] == '\t'))
			i++;
		if (((str[i - 1] == ' ') || (str[i - 1] == '\t')) && (str[i]))
		{
			tmp[k] = ' ';
			k++;
		}
	}
	tmp[k] = '\0';
	free(str);
	return (tmp);
}

char	*search(char *src, char *str1, char *str2)
{
   int i;
   int j;
   int	firstOcc;

   i = 0;
   j = 0;
   while (src[i] != '\0')
   {
      while ((src[i] != str1[0] && src[i] != str2[0]) && src[i] != '\0')
         i++;
      if (src[i] == '\0')
         return (NULL);
      firstOcc = i;
      while (src[i] == str1[j] && src[i] != '\0' && str1[j] != '\0')
      {
         i++;
         j++;
      }
      while (src[i] == str2[j] && src[i] != '\0' && str2[j] != '\0')
      {
         i++;
         j++;
      }
      if (str1[j] == '\0')
         return ((char*)&str1[firstOcc]);
      if (str2[j] == '\0')
         return ((char*)&str2[firstOcc]);
      if (src[i] == '\0')
         return (NULL);
      i = firstOcc + 1;
      j = 0;
   }
   return (NULL);
}
