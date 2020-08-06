/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 09:32:26 by craffate          #+#    #+#             */
/*   Updated: 2020/08/06 12:05:25 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

/*
** Appends node to f_lst and returns a pointer to the appended node
*/

t_file					*append_file_node(t_file **f_lst, t_file *node)
{
	t_file				*ret;

	ret = *f_lst;
	if (!ret)
	{
		*f_lst = node;
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
** Allocates a t_file *, fills it and returns it
*/

t_file					*create_file_node(const char *name)
{
	t_file				*ret;

	if (!(ret = (t_file *)malloc(sizeof(t_file))))
		ret = NULL;
	if (ret)
	{
		if (!(ret->name = ft_strdup(name)))
			ret = NULL;
		if (ret && (ret->fd = open(ret->name, O_RDONLY)) == -1)
			ret = NULL;
		if (ret && fstat(ret->fd, &ret->stat) == -1)
			ret = NULL;
		if (ret && (ret->ptr = (char *)mmap(0, ret->stat.st_size, PROT_READ,
		MAP_PRIVATE, ret->fd, 0)) == MAP_FAILED)
			ret = NULL;
		if (ret)
		{
			ret->magic = *(unsigned int *)ret->ptr;
			ret->next = NULL;
		}
	}
	return (ret);
}
