/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 02:31:38 by craffate          #+#    #+#             */
/*   Updated: 2020/08/11 03:04:08 by craffate         ###   ########.fr       */
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
** Makes a buffer out of the symbol information and return it.
*/

static char				*get_symbol_buffer(t_symbol sym)
{
	char				*ret;
	char				type[4];

	if (!(ret = (char *)malloc(sizeof(char) * 1024)))
		ret = NULL;
	else
	{
		type[0] = ' ';
		type[1] = sym.type;
		type[2] = ' ';
		type[3] = 0;
		ft_bzero(ret, 1024);
		if (ft_strlen(sym.value) > 1 && *sym.value != '0')
		{
			ft_strncpy(ret, "0000000000000000", 16 - ft_strlen(sym.value));
			ft_strcat(ret, sym.value);
		}
		else
			ft_strncpy(ret, "                ", 16);
		ft_strcat(ret, type);
		ft_strcat(ret, sym.name);
		ft_strcat(ret, "\n");
	}
	return (ret);
}

/*
** Prints a symbol list in alphabetical order.
*/

void					print_symbols_sorted(t_symbol *s_lst)
{
	t_symbol			*s_idx;
	char				**s_arr;
	size_t				s_arr_si;

	s_idx = s_lst;
	if (!(s_arr = init_symbols_buffer(s_lst)))
		return ;
	s_arr_si = 0;
	while (s_idx)
	{
		s_arr[s_arr_si++] = get_symbol_buffer(*s_idx);
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
	t_symbol			*s_idx;
	char				**s_arr;
	size_t				s_arr_si;

	s_idx = s_lst;
	if (!(s_arr = init_symbols_buffer(s_lst)))
		return ;
	s_arr_si = 0;
	while (s_idx)
	{
		s_arr[s_arr_si++] = get_symbol_buffer(*s_idx);
		s_idx = s_idx->next;
	}
	print_symbol_array(s_arr);
}
