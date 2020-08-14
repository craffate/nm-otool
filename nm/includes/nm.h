/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 09:18:07 by craffate          #+#    #+#             */
/*   Updated: 2020/08/13 08:11:52 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include "shared.h"

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
