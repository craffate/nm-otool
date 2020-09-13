/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 09:02:56 by craffate          #+#    #+#             */
/*   Updated: 2020/09/13 09:11:50 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

t_section				*find_section_id(t_file *file, unsigned int id)
{
	t_segment			*seg_idx;
	t_section			*se_idx;

	seg_idx = file->seg->next;
	se_idx = seg_idx->sec;
	while (--id && seg_idx)
	{
		se_idx = se_idx->next;
		if (!se_idx)
		{
			seg_idx = seg_idx->next;
			se_idx = seg_idx->sec;
		}
	}
	return (se_idx);
}

t_section				*find_section(t_section *se_lst, const char *name)
{
	t_section			*ret;

	ret = se_lst;
	while (ret && ft_strcmp(ret->name, name))
		ret = ret->next;
	return (ret);
}

t_section				*append_section_node(t_section **s_lst, t_section *n)
{
	t_section			*ret;

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

t_section				*create_section_node_32(struct section se)
{
	t_section			*ret;

	if (!(ret = (t_section *)malloc(sizeof(t_section))))
		ret = NULL;
	if (ret)
	{
		if (!(ret->name = ft_strdup(se.sectname)))
			ret = NULL;
		if (!(ret->seg_name = ft_strdup(se.segname)))
			ret = NULL;
		ret->addr.addr_32 = se.addr;
		ret->size.size_32 = se.size;
		ret->offset = se.offset;
		ret->align = se.align;
		ret->next = NULL;
	}
	return (ret);
}

t_section				*create_section_node_64(struct section_64 se)
{
	t_section			*ret;

	if (!(ret = (t_section *)malloc(sizeof(t_section))))
		ret = NULL;
	if (ret)
	{
		if (!(ret->name = ft_strdup(se.sectname)))
			ret = NULL;
		if (!(ret->seg_name = ft_strdup(se.segname)))
			ret = NULL;
		ret->addr.addr_64 = se.addr;
		ret->size.size_64 = se.size;
		ret->offset = se.offset;
		ret->align = se.align;
		ret->next = NULL;
	}
	return (ret);
}
