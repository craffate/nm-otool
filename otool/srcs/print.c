/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 04:40:51 by craffate          #+#    #+#             */
/*   Updated: 2020/09/08 01:52:53 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static void				print_addr(unsigned int align, unsigned int addr)
{
	char				*s;
	char				*s2;
	char				*s3;
	unsigned int		idx;

	idx = -1u;
	s = (char *)malloc(sizeof(char) * 24);
	s2 = ft_lltoa_base((2 * 2) * align, 2);
	s3 = ft_lltoa_base(addr, 16);
	while (16 - ft_strlen(s2) - ft_strlen(s3) > ++idx)
		s[idx] = '0';
	ft_strcat(s, s2);
	ft_strcat(s, s3);
	ft_strcat(s, "\t");
	ft_putstr(s);
}

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
		if (!((idx) % 16 && (idx) != section->size))
			print_addr(section->align, section->addr + idx);
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

void					print_text_section(t_segment *s_lst, char *ptr)
{
	t_segment			*s_idx;
	t_section			*se_idx;
	char				buf[256];

	s_idx = s_lst;
	while (s_idx && ft_strcmp(s_idx->name, "__TEXT"))
		s_idx = s_idx->next;
	se_idx = s_idx->sec;
	while (se_idx && ft_strcmp(se_idx->name, "__text"))
		se_idx = se_idx->next;
	ft_bzero(buf, 256);
	ft_strcat(buf, "Contents of (");
	ft_strcat(buf, s_idx->name);
	ft_strcat(buf, ",");
	ft_strcat(buf, se_idx->name);
	ft_strcat(buf, ") section");
	ft_putendl(buf);
	hexdump_section(se_idx, ptr);
}
