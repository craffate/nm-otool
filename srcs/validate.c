/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 08:13:33 by craffate          #+#    #+#             */
/*   Updated: 2020/09/12 08:15:33 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"

int					validate_range(void *p, void *start, void *end)
{
	int				ret;

	ret = 1;
	if (p < start || p > end)
		ret = 0;
	return (ret);
}
