/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 01:45:57 by craffate          #+#    #+#             */
/*   Updated: 2020/08/11 02:31:00 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

/*
** Performs a bubblesort on a symbol array.
*/

void					bubblesort_symbols(char **s_arr, size_t s_arr_si)
{
	unsigned int		idx;
	char				*tmp;

	idx = -1u;
	if (s_arr_si == 1)
		return ;
	while (++idx < s_arr_si - 1)
	{
		if (ft_strcmp(s_arr[idx] + 19, s_arr[idx + 1] + 19) > 0)
		{
			tmp = s_arr[idx];
			s_arr[idx] = s_arr[idx + 1];
			s_arr[idx + 1] = tmp;
		}
	}
	bubblesort_symbols(s_arr, s_arr_si - 1);
}

/*
** Creates a buffer capable of holding all symbol strings and returns it.
*/

char					**init_symbols_buffer(t_symbol *s_lst)
{
	char				**ret;
	size_t				ret_si;
	t_symbol			*s_idx;

	ret_si = 0;
	s_idx = s_lst;
	while (s_idx)
	{
		++ret_si;
		s_idx = s_idx->next;
	}
	if (!(ret = (char **)malloc(sizeof(char *) * (ret_si + 1))))
		ret = NULL;
	if (ret)
		ret[ret_si] = NULL;
	return (ret);
}
