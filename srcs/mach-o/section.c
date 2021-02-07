/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 03:18:33 by craffate          #+#    #+#             */
/*   Updated: 2021/02/07 09:46:26 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

t_section						*get_section_32(t_load_command *lc)
{
	t_section					*ret;
	unsigned int				idx;
	t_segment_command			*sc;
	struct section				*se;

	ret = NULL;
	idx = -1u;
	sc = (t_segment_command *)lc;
	se = (struct section *)(((void *)sc) + sizeof(t_segment_command));
	while (++idx < sc->nsects)
		append_section_node(&ret, create_section_node_32(se[idx]));
	return (ret);
}

t_section						*get_section_64(t_load_command *lc)
{
	t_section					*ret;
	unsigned int				idx;
	t_segment_command_64		*sc;
	struct section_64			*se;

	ret = NULL;
	idx = -1u;
	sc = (t_segment_command_64 *)lc;
	se = (struct section_64 *)(((void *)sc) +
	sizeof(t_segment_command_64));
	while (++idx < sc->nsects)
		append_section_node(&ret, create_section_node_64(se[idx]));
	return (ret);
}
