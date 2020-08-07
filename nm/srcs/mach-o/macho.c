/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 12:29:19 by craffate          #+#    #+#             */
/*   Updated: 2020/08/07 08:33:37 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

#ifdef __APPLE__

static int						handle_32(t_file *file)
{
	int							ret;
	unsigned int				idx;
	struct mach_header			*header;
	struct load_command			*lc;

	ret = 0;
	idx = -1u;
	header = (struct mach_header *)file->ptr;
	lc = (struct load_command *)((void *)file->ptr + sizeof(*header));
	while (!ret && ++idx < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
			if (!(file->sym = get_symtab_64(lc, file->ptr)))
				ret = ERR_INTERNAL;
		lc = (struct load_command *)((void *)lc + lc->cmdsize);
	}
	return (ret);
}

static int						handle_64(t_file *file)
{
	int							ret;
	unsigned int				idx;
	struct mach_header_64		*header;
	struct load_command			*lc;
	t_file						*f_idx;

	ret = 0;
	idx = -1u;
	header = (struct mach_header_64 *)file->ptr;
	lc = (struct load_command *)((void *)file->ptr + sizeof(*header));
	f_idx = file;
	while (!ret && ++idx < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
			if (!(file->sym = get_symtab_64(lc, file->ptr)))
				ret = ERR_INTERNAL;
		lc = (struct load_command *)((void *)lc + lc->cmdsize);
	}
	f_idx = NULL;
	return (ret);
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
