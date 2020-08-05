/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 07:46:22 by craffate          #+#    #+#             */
/*   Updated: 2020/08/05 08:26:35 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

/*
** Prints a symbol list.
*/
void						print_symbols(t_symbol *s_lst)
{
	char					buf[256];
	char					type_buf[4];
	t_symbol				*s_idx;

	s_idx = s_lst;
	type_buf[0] = ' ';
	type_buf[2] = ' ';
	type_buf[3] = 0;
	while (s_idx)
	{
		ft_bzero(buf, 256);
		type_buf[1] = s_idx->type;
		ft_strcat(buf, s_idx->value);
		ft_strcat(buf, type_buf);
		ft_strcat(buf, s_idx->name);
		ft_strcat(buf, "\n");
		ft_putstr(buf);
		s_idx = s_idx->next;
	}
}

/*
** Appends a node to s_lst and returns a pointer to the appended node.
*/

t_symbol					*append_symbol_node(t_symbol **s_lst, t_symbol *node)
{
	t_symbol				*ret;

	ret = *s_lst;
	if (!ret)
	{
		*s_lst = node;
		ret = node;
	}
	else
	{
		while (ret->next)
			ret = ret->next;
		ret->next = node;
		ret = ret->next;
	}
	return (ret);
}

/*
** Allocates a t_symbol *, fills it and returns it.
*/

t_symbol					*create_symbol_node(char *name, unsigned char type, unsigned int value)
{
	t_symbol				*ret;

	if (!(ret = (t_symbol *)malloc(sizeof(t_symbol))))
		ret = NULL;
	if (ret)
	{
			if (!(ret->name = ft_strdup(name)))
				ret = NULL;
			ret->type = symbol_type(type);
			if (!(ret->value = ft_lltoa_base(value, 16)))
				ret = NULL;
			ret->next = NULL;
	}
	return (ret);
}
