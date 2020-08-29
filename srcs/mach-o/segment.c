/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 08:49:57 by craffate          #+#    #+#             */
/*   Updated: 2020/08/29 03:25:44 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

t_segment						*get_segment_32(struct load_command *lc)
{
	t_segment					*ret;
	struct segment_command		*sc;

	ret = NULL;
	sc = (struct segment_command *)lc;
	append_segment_node(&ret, create_segment_node_32(*sc));
	return (ret);
}

t_segment						*get_segment_64(struct load_command *lc)
{
	t_segment					*ret;
	struct segment_command_64	*sc;

	ret = NULL;
	sc = (struct segment_command_64 *)lc;
	append_segment_node(&ret, create_segment_node_64(*sc));
	return (ret);
}
