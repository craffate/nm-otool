/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 08:13:33 by craffate          #+#    #+#             */
/*   Updated: 2021/02/07 09:20:33 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int					validate_range(void *p, void *start, void *end)
{
	int				ret;

	ret = 1;
	if (p < start || p > end)
		ret = 0;
	return (ret);
}
