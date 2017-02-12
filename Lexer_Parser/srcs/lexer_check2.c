/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 15:37:02 by sgaudin           #+#    #+#             */
/*   Updated: 2017/02/12 15:37:03 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void		print_tokens(t_token *token)
{
	int		i;

	i = 1;
	printf("\n***TOKEN_LIST***\n");
	while (token)
	{
		printf("TOKEN %d\n", i);
		printf("type : (%d)\n", token->type);
		printf("lexeme : (%s)\n", token->lexeme);
		token = token->next;
		i++;
	}
}

t_token		*init_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->next = NULL;
	return (token);
}
