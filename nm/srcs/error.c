/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 10:11:33 by craffate          #+#    #+#             */
/*   Updated: 2020/08/06 12:06:36 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void					print_error(int errcode)
{
	static char			*arr[ERR_UNKNOWN + 1];

	if (errcode)
	{
		arr[ERR_NOAV] = ERR_NOAV_S;
		arr[ERR_MALLOC] = ERR_MALLOC_S;
		arr[ERR_OPEN] = ERR_OPEN_S;
		arr[ERR_FSTAT] = ERR_FSTAT_S;
		arr[ERR_MMAP] = ERR_MMAP_S;
		arr[ERR_MUNMAP] = ERR_MUNMAP_S;
		arr[ERR_INTERNAL] = ERR_INTERNAL_S;
		arr[ERR_UNKNOWN] = ERR_UNKNOWN_S;
		ft_putendl_fd(arr[errcode], 2);
	}
}
