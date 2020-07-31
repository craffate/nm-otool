/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 09:22:01 by craffate          #+#    #+#             */
/*   Updated: 2020/07/31 12:19:12 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

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
		append_file_node(&f_lst, create_file_node(av_idx));
	}
	return (ret);
}
