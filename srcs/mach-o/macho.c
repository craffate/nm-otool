/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 12:29:19 by craffate          #+#    #+#             */
/*   Updated: 2021/02/07 09:33:56 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

#ifdef __APPLE__

static int						handle_32(t_file *file)
{
	int							ret;
	unsigned int				idx;
	struct mach_header			*header;
	t_load_command				*lc;

	ret = 0;
	idx = -1u;
	header = (struct mach_header *)file->ptr;
	lc = (t_load_command *)((void *)file->ptr + sizeof(*header));
	file->filetype = header->filetype;
	if (!validate_range(lc, file->ptr, file->ptr_end))
		file->errno = ERR_CORRUPT;
	while (!ret && ++idx < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			if (!(file->sym = get_symtab_32(lc, file->ptr)))
				file->errno = ERR_INTERNAL;
		}
		else if (lc->cmd == LC_SEGMENT)
		{
			if (!(append_segment_node(&file->seg, get_segment_32(lc))))
				file->errno = ERR_INTERNAL;
		}
		lc = (t_load_command *)((void *)lc + lc->cmdsize);
	}
	return (file->errno);
}

static int						handle_64(t_file *file)
{
	unsigned int				idx;
	struct mach_header_64		*header;
	t_load_command				*lc;

	idx = -1u;
	header = (struct mach_header_64 *)file->ptr;
	lc = (t_load_command *)((void *)file->ptr + sizeof(*header));
	file->filetype = header->filetype;
	if (!validate_range(lc, file->ptr, file->ptr_end))
		file->errno = ERR_CORRUPT;
	while (!file->errno && ++idx < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			if (!(file->sym = get_symtab_64(lc, file->ptr)))
				file->errno = ERR_INTERNAL;
		}
		else if (lc->cmd == LC_SEGMENT_64)
		{
			if (!(append_segment_node(&file->seg, get_segment_64(lc))))
				file->errno = ERR_INTERNAL;
		}
		lc = (t_load_command *)((void *)lc + lc->cmdsize);
	}
	return (file->errno);
}

static void						sanitize_symbols(t_file *file)
{
	t_symbol					*s_idx;
	t_section					*se_idx;

	s_idx = file->sym;
	while (s_idx)
	{
		if (s_idx->type == '0')
		{
			se_idx = find_section_id(file, s_idx->section);
			if (!ft_strcmp(se_idx->name, SECT_TEXT))
				s_idx->type = 'T';
			else if (!ft_strcmp(se_idx->name, SECT_DATA))
				s_idx->type = 'D';
			else if (!ft_strcmp(se_idx->name, SECT_BSS))
				s_idx->type = 'B';
			else
				s_idx->type = 'S';
		}
		if (!(s_idx->type & N_EXT))
			ft_tolower(s_idx->type);
		s_idx = s_idx->next;
	}
}

int								handle_macho(t_file *file)
{
	int							ret;

	ret = 0;
	if (file->magic == MH_MAGIC)
		ret = handle_32(file);
	else if (file->magic == MH_MAGIC_64)
		ret = handle_64(file);
	else
		ret = -1;
	if (!ret)
		sanitize_symbols(file);
	return (ret);
}

#elif __linux__

int								handle_macho(t_file *file)
{
	int							ret;

	ret = -1;
	(void)file;
	ft_putendl_fd("Mach-O file format is not supported on Linux", 2);
	return (ret);
}

#endif
