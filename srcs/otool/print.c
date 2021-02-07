/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 04:40:51 by craffate          #+#    #+#             */
/*   Updated: 2020/09/12 12:02:45 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static void				print_addr_32(uint32_t addr)
{
	char				*s;
	char				*s2;
	unsigned int		idx;

	idx = -1u;
	s = (char *)malloc(sizeof(char) * 24);
	s2 = ft_lltoa_base(addr, 16);
	ft_bzero(s, 24);
	while (16 - ft_strlen(s2) > ++idx)
		s[idx] = '0';
	ft_strcat(s, s2);
	ft_strcat(s, "\t");
	ft_putstr(s);
	free(s2);
	free(s);
}

static void				print_addr_64(uint64_t addr)
{
	char				*s;
	char				*s2;
	unsigned int		idx;

	idx = -1u;
	s = (char *)malloc(sizeof(char) * 24);
	s2 = ft_lltoa_base(addr, 16);
	ft_bzero(s, 24);
	while (16 - ft_strlen(s2) > ++idx)
		s[idx] = '0';
	ft_strcat(s, s2);
	ft_strcat(s, "\t");
	ft_putstr(s);
	free(s2);
	free(s);
}

static void				hexdump_section_32(t_section *section, char *ptr)
{
	char				*ptr_idx;
	unsigned int		idx;
	char				byte[2];
	unsigned char		c;
	char				buffer[1024];

	idx = -1u;
	ptr_idx = (char *)(ptr + section->offset);
	while (++idx < section->size.size_32)
	{
		ft_bzero(buffer, 1024);
		c = ptr_idx[idx];
		if (!((idx) % 16 && (idx) != section->size.size_32))
			print_addr_32(section->addr.addr_32 + idx);
		byte[1] = ("0123456789abcdef")[c % 16];
		byte[0] = ("0123456789abcdef")[c / 16];
		ft_strncat(buffer, byte, 2);
		if ((idx + 1) % 16 && (idx + 1) != section->size.size_32)
			ft_strcat(buffer, " ");
		else
			ft_strcat(buffer, "\n");
		ft_putstr(buffer);
	}
}

static void				hexdump_section_64(t_section *section, char *ptr)
{
	char				*ptr_idx;
	unsigned int		idx;
	char				byte[2];
	unsigned char		c;
	char				buffer[1024];

	idx = -1u;
	ptr_idx = (char *)(ptr + section->offset);
	while (++idx < section->size.size_64)
	{
		ft_bzero(buffer, 1024);
		c = ptr_idx[idx];
		if (!((idx) % 16 && (idx) != section->size.size_64))
			print_addr_64(section->addr.addr_64 + idx);
		byte[1] = ("0123456789abcdef")[c % 16];
		byte[0] = ("0123456789abcdef")[c / 16];
		ft_strncat(buffer, byte, 2);
		if ((idx + 1) % 16 && (idx + 1) != section->size.size_64)
			ft_strcat(buffer, " ");
		else
			ft_strcat(buffer, "\n");
		ft_putstr(buffer);
	}
}

void					print_text_section(t_file *file)
{
	t_segment			*s_idx;
	t_section			*se_idx;
	char				buf[64];

	if (!(s_idx = find_segment(file->seg, "__TEXT")))
		s_idx = file->seg;
	if (!(se_idx = find_section(s_idx->sec, "__text")))
		return ;
	ft_bzero(buf, 64);
	ft_strcat(buf, "Contents of (__TEXT,__text) section");
	ft_putendl(buf);
	if (file->magic == MH_MAGIC || file->magic == MH_CIGAM)
		hexdump_section_32(se_idx, file->ptr);
	else if (file->magic == MH_MAGIC_64 || file->magic == MH_CIGAM_64)
		hexdump_section_64(se_idx, file->ptr);
}
