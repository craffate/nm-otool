/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 09:22:01 by craffate          #+#    #+#             */
/*   Updated: 2020/08/27 05:41:20 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int			nm(t_file *f_lst)
{
	int				ret;
	t_file			*idx;
	int				fname_switch;

	ret = ERR_UNKNOWNFT;
	idx = f_lst;
	while (idx)
	{
		if (idx->magic == MH_MAGIC || idx->magic == MH_MAGIC_64 ||
		idx->magic == MH_CIGAM || idx->magic == MH_CIGAM_64)
			ret = handle_macho(idx);
		idx = idx->next;
	}
	if (!ret)
	{
		idx = f_lst;
		fname_switch = idx->next ? 1 : 0;
		while (idx)
		{
			if (fname_switch)
			{
				ft_putstr(idx->name);
				ft_putendl(":");
			}
			print_symbols_sorted(idx->sym);
			if (idx->next)
				ft_putchar('\n');
			idx = idx->next;
		}
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
		ret = nm(f_lst);
	if (ret)
		print_error(ret);
	return (ret);
}
