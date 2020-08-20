/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 09:02:56 by craffate          #+#    #+#             */
/*   Updated: 2020/08/18 10:33:15 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

t_section				*append_section_node(t_section **s_lst, t_section *node)
{
	t_section			*ret;

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
		ret->align = se.align;
		ret->addr = se.addr;
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
		ret->align = se.align;
		ret->addr = se.addr;
		ret->next = NULL;
	}
	return (ret);
}