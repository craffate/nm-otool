/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 09:18:07 by craffate          #+#    #+#             */
/*   Updated: 2021/02/07 09:21:57 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include "nm_otool.h"

/*
** Sorting functions
*/

char					**init_symbols_buffer(t_symbol *s_lst);
void					bubblesort_symbols(char **s_arr, size_t s_arr_si);

/*
** Printing functions
*/

void					print_symbols(t_symbol *s_lst);
void					print_symbols_sorted(t_symbol *s_lst);

#endif
