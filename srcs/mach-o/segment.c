/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 08:49:57 by craffate          #+#    #+#             */
/*   Updated: 2021/02/07 09:46:58 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

t_segment						*get_segment_32(t_load_command *lc)
{
	t_segment					*ret;
	unsigned int				idx;
	t_segment_command			*sc;
	struct section				*se;

	ret = NULL;
	idx = -1u;
	sc = (t_segment_command *)lc;
	se = (struct section *)(((void *)sc) +
	sizeof(t_segment_command));
	ret = create_segment_node_32(*sc);
	ret->sec = get_section_32(lc);
	return (ret);
}

t_segment						*get_segment_64(t_load_command *lc)
{
	t_segment					*ret;
	unsigned int				idx;
	t_segment_command_64		*sc;
	struct section_64			*se;

	ret = NULL;
	idx = -1u;
	sc = (t_segment_command_64 *)lc;
	se = (struct section_64 *)(((void *)sc) +
	sizeof(t_segment_command_64));
	ret = create_segment_node_64(*sc);
	ret->sec = get_section_64(lc);
	return (ret);
}
