/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 04:40:51 by craffate          #+#    #+#             */
/*   Updated: 2020/08/20 05:19:54 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static void				hexdump_section(t_section *section, char *ptr)
{
	char				*ptr_idx;
	unsigned int		idx;
	char				byte[2];
	unsigned char		c;
	char				buffer[1024];

	idx = -1u;
	ptr_idx = (char *)(ptr + section->offset);
	while (++idx < section->size)
	{
		ft_bzero(buffer, 1024);
		c = ptr_idx[idx];
		byte[1] = ("0123456789abcdef")[c % 16];
		byte[0] = ("0123456789abcdef")[c / 16];
		ft_strncat(buffer, byte, 2);
		if ((idx + 1) % 16 && (idx + 1) != section->size)
			ft_strcat(buffer, " ");
		else
			ft_strcat(buffer, "\n");
		ft_putstr(buffer);
	}
}

void					print_text_section(t_section *s_lst, char *ptr)
{
	t_section			*s_idx;

	s_idx = s_lst;
	while (s_idx)
	{
		if (!ft_strcmp(s_idx->name, "__text"))
			hexdump_section(s_idx, ptr);
		s_idx = s_idx->next;
	}
}