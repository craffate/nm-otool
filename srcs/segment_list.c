/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 02:57:21 by craffate          #+#    #+#             */
/*   Updated: 2021/02/07 09:20:14 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

t_segment				*find_segment(t_segment *s_lst, const char *seg_name)
{
	t_segment			*ret;

	ret = s_lst;
	while (ret && ft_strcmp(ret->name, seg_name))
		ret = ret->next;
	return (ret);
}

t_segment				*append_segment_node(t_segment **s_lst, t_segment *n)
{
	t_segment			*ret;

	ret = *s_lst;
	if (!ret)
	{
		*s_lst = n;
		ret = n;
	}
	else
	{
		while (ret->next)
			ret = ret->next;
		ret->next = n;
		ret = ret->next;
	}
	return (ret);
}

t_segment				*create_segment_node_32(struct segment_command sc)
{
	t_segment			*ret;

	if (!(ret = (t_segment *)malloc(sizeof(t_segment))))
		ret = NULL;
	if (ret)
	{
		ret->cmd = sc.cmd;
		ret->cmdsize = sc.cmdsize;
		ret->name = ft_strdup(sc.segname);
		ret->vmaddr.vmaddr_32 = sc.vmaddr;
		ret->vmsize.vmsize_32 = sc.vmsize;
		ret->offset.offset_32 = sc.fileoff;
		ret->size.size_32 = sc.filesize;
		ret->nsects = sc.nsects;
		ret->sec = NULL;
		ret->next = NULL;
	}
	return (ret);
}

t_segment				*create_segment_node_64(struct segment_command_64 sc)
{
	t_segment			*ret;

	if (!(ret = (t_segment *)malloc(sizeof(t_segment))))
		ret = NULL;
	if (ret)
	{
		ret->cmd = sc.cmd;
		ret->cmdsize = sc.cmdsize;
		ret->name = ft_strdup(sc.segname);
		ret->vmaddr.vmaddr_64 = sc.vmaddr;
		ret->vmsize.vmsize_64 = sc.vmsize;
		ret->offset.offset_64 = sc.fileoff;
		ret->size.size_64 = sc.filesize;
		ret->nsects = sc.nsects;
		ret->sec = NULL;
		ret->next = NULL;
	}
	return (ret);
}
