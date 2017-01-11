#include "../includes/42sh.h"

int 			prev_sentence_value(char *sentence)
{
	FT_INIT(int, val, 0);
	FT_INIT(int, poid, 0);
	while (sentence && sentence[poid])
	{
		val += sentence[poid] + poid;
		poid++;
	}
	return (val);
}

int 			arrondi(float val)
{
	FT_INIT(int, val2, val);
	FT_INIT(float, result, val - val2);
	if (result >= 0.5)
		return (val2);
	return (val2);
}

int 			ft_nb_elem_lst(int nb_elem, int nb_col)
{
	FT_INIT(float, result, 0);
	while (result * nb_col < nb_elem)
		result++;
	return (result);
}