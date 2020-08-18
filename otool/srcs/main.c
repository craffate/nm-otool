/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 07:55:24 by craffate          #+#    #+#             */
/*   Updated: 2020/08/18 10:31:28 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static int			otool(t_file *f_lst)
{
	int				ret;
	t_file			*idx;

	ret = ERR_UNKNOWNFT;
	idx = f_lst;
	while (ret && idx)
	{
		if (idx->magic == MH_MAGIC || idx->magic == MH_MAGIC_64 ||
		idx->magic == MH_CIGAM || idx->magic == MH_CIGAM_64)
			ret = handle_macho(idx);
		idx = idx->next;
	}
	return (ret);
}

int					main(int ac, char **av)
{
	int				ret;
	int				idx;
	char			*av_idx;
	t_file			*f_lst;

	ret = 0;
	idx = 0;
	av_idx = NULL;
	f_lst = NULL;
	while (++idx < ac)
	{
		av_idx = av[idx];
		if (!append_file_node(&f_lst, create_file_node(av_idx)))
			ret = ERR_INTERNAL;
	}
	if (!av_idx)
		if (!append_file_node(&f_lst, create_file_node(DEFAULT_FILE)))
			ret = ERR_INTERNAL;
	if (!ret)
		ret = otool(f_lst);
	if (ret)
		print_error(ret);
	return (ret);
}
