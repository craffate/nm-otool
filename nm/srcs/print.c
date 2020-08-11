/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 02:31:38 by craffate          #+#    #+#             */
/*   Updated: 2020/08/11 02:33:02 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

/*
** Prints a symbol array.
*/

static void				print_symbol_array(char **s_arr)
{
	unsigned int		idx;

	idx = 0;
	while (s_arr[idx])
	{
		ft_putstr(s_arr[idx]);
		++idx;
	}
}

/*
** Prints a symbol list in alphabetical order.
*/

void					print_symbols_sorted(t_symbol *s_lst)
{
	char				buf[256];
	char				type_buf[4];
	t_symbol			*s_idx;
	char				**s_arr;
	size_t				s_arr_si;

	s_idx = s_lst;
	if (!(s_arr = init_symbols_buffer(s_lst)))
		return ;
	s_arr_si = 0;
	type_buf[0] = ' ';
	type_buf[2] = ' ';
	type_buf[3] = 0;
	while (s_idx)
	{
		ft_bzero(buf, 256);
		type_buf[1] = s_idx->type;
		if (ft_strlen(s_idx->value) > 1 && *s_idx->value != '0')
		{
			ft_strncpy(buf, "0000000000000000", 16 - ft_strlen(s_idx->value));
			ft_strcat(buf, s_idx->value);
		}
		else
			ft_strncpy(buf, "                ", 16);
		ft_strcat(buf, type_buf);
		ft_strcat(buf, s_idx->name);
		ft_strcat(buf, "\n");
		s_arr[s_arr_si++] = ft_strdup(buf);
		s_idx = s_idx->next;
	}
	bubblesort_symbols(s_arr, s_arr_si);
	print_symbol_array(s_arr);
}

/*
** Prints a symbol list.
*/

void					print_symbols(t_symbol *s_lst)
{
	char				buf[256];
	char				type_buf[4];
	t_symbol			*s_idx;

	s_idx = s_lst;
	type_buf[0] = ' ';
	type_buf[2] = ' ';
	type_buf[3] = 0;
	while (s_idx)
	{
		ft_bzero(buf, 256);
		type_buf[1] = s_idx->type;
		if (ft_strlen(s_idx->value) > 1 && *s_idx->value != '0')
		{
			ft_strncpy(buf, "0000000000000000", 16 - ft_strlen(s_idx->value));
			ft_strcat(buf, s_idx->value);
		}
		else
			ft_strncpy(buf, "                ", 16);
		ft_strcat(buf, type_buf);
		ft_strcat(buf, s_idx->name);
		ft_strcat(buf, "\n");
		ft_putstr(buf);
		s_idx = s_idx->next;
	}
}
