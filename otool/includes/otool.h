/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 07:58:45 by craffate          #+#    #+#             */
/*   Updated: 2020/09/04 23:29:36 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTOOL_H
# define OTOOL_H

# include "shared.h"

/*
** Printing functions
*/

void					print_text_section(t_segment *s_lst, char *ptr);

#endif
