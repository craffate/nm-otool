/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 07:46:22 by craffate          #+#    #+#             */
/*   Updated: 2020/08/13 08:08:10 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

/*
** Appends a node to s_lst and returns a pointer to the appended node.
*/

t_symbol				*append_symbol_node(t_symbol **s_lst, t_symbol *node)
{
	t_symbol			*ret;

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
** Allocates a t_symbol *, fills it with 32-bit data and returns it.
*/

t_symbol				*create_symbol_node_32(char *st, struct nlist nl)
{
	t_symbol			*ret;

	if (!(ret = (t_symbol *)malloc(sizeof(t_symbol))))
		ret = NULL;
	if (ret)
	{
		if (!(ret->name = ft_strdup(st + nl.n_un.n_strx)))
			ret = NULL;
		ret->section = nl.n_sect;
		ret->type = symbol_type(nl.n_type, nl.n_sect);
		if (!(ret->value = ft_lltoa_base(nl.n_value, 16)))
			ret = NULL;
		ret->next = NULL;
	}
	return (ret);
}

/*
** Allocates a t_symbol *, fills it with 64-bit data and returns it.
*/

t_symbol				*create_symbol_node_64(char *st, struct nlist_64 nl)
{
	t_symbol			*ret;

	if (!(ret = (t_symbol *)malloc(sizeof(t_symbol))))
		ret = NULL;
	if (ret)
	{
		if (!(ret->name = ft_strdup(st + nl.n_un.n_strx)))
			ret = NULL;
		ret->section = nl.n_sect;
		ret->type = symbol_type(nl.n_type, nl.n_sect);
		if (!(ret->value = ft_lltoa_base(nl.n_value, 16)))
			ret = NULL;
		ret->next = NULL;
	}
	return (ret);
}
