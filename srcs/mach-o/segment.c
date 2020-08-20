/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 08:49:57 by craffate          #+#    #+#             */
/*   Updated: 2020/08/20 03:58:18 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

t_section						*get_section_32(struct load_command *lc)
{
	t_section					*ret;
	unsigned int				idx;
	struct segment_command		*sc;
	struct section				*se;

	ret = NULL;
	idx = -1u;
	sc = (struct segment_command *)lc;
	se = (struct section *)(((void *)sc) + sizeof(struct segment_command));
	while (++idx < sc->nsects)
		append_section_node(&ret, create_section_node_32(se[idx]));
	return (ret);
}

t_section						*get_section_64(struct load_command *lc)
{
	t_section					*ret;
	unsigned int				idx;
	struct segment_command_64	*sc;
	struct section_64			*se;

	ret = NULL;
	idx = -1u;
	sc = (struct segment_command_64 *)lc;
	se = (struct section_64 *)(((void *)sc) + sizeof(struct segment_command_64));
	while (++idx < sc->nsects)
		append_section_node(&ret, create_section_node_64(se[idx]));
	return (ret);
}
