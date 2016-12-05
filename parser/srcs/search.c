#include "../includes/parse.h"

char	*search(char *src, char *str1, char *str2)
{
	int	i;
	int	u;

	i = 0;
	u = 0;
	while (src[i])
	{
		u = 0;
		while (src[i] == str1[u] || src[i] == str2[u])
		{
			i++;
			u++;
			if (str1[u] == '\0' || str2[u] == '\0')
				return ((char*)src + i - u);
		}
		i++;
	}
	return (NULL);
}

char	*search2(char *src, char *str1, char *str2, char *str3)
{
	int	i;
	int	u;

	i = 0;
	u = 0;
	while (src[i])
	{
		u = 0;
		while (src[i] == str1[u] || src[i] == str2[u] || src[i] == str3[u])
		{
			i++;
			u++;
			if (str1[u] == '\0' || str2[u] == '\0' || str3[u] == '\0')
				return ((char*)src + i - u);
		}
		i++;
	}
	return (NULL);
}