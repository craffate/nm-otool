/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 08:49:57 by craffate          #+#    #+#             */
/*   Updated: 2020/08/18 11:16:48 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

t_section						*get_section_32(struct load_command *lc, char *ptr)
{
	t_section					*ret;
	unsigned int				idx;
	struct segment_command		*sc;
	struct section				*se;

	ret = NULL;
	idx = -1u;
	sc = (struct segment_command *)lc;
	se = (struct section *)(ptr + sc->fileoff);
	while (++idx < sc->nsects)
		append_section_node(&ret, create_section_node_32(se[idx]));
	return (ret);
}

t_section						*get_section_64(struct load_command *lc, char *ptr)
{
	t_section					*ret;
	unsigned int				idx;
	struct segment_command_64	*sc;
	struct section_64			*se;

	ret = NULL;
	idx = -1u;
	sc = (struct segment_command_64 *)lc;
	se = (struct section_64 *)(ptr + sc->fileoff);
	while (++idx < sc->nsects)
		append_section_node(&ret, create_section_node_64(se[idx]));
	return (ret);
}
