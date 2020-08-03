/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 09:00:16 by craffate          #+#    #+#             */
/*   Updated: 2020/08/03 09:14:55 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int							get_symtab_32(struct load_command *lc, char *ptr)
{
	int						ret;
	unsigned int			idx;
	struct symtab_command	*sc;
	struct nlist			*nl;
	char					*stable;

	ret = 0;
	idx = -1u;
	sc = (struct symtab_command *)lc;
	nl = (struct nlist *)(ptr + sc->symoff);
	stable = (char *)(ptr + sc->stroff);
	while (++idx < sc->nsyms)
	{
		ft_putendl(stable + nl[idx].n_un.n_strx);
	}
	return (ret);
}

int							get_symtab_64(struct load_command *lc, char *ptr)
{
	int						ret;
	unsigned int			idx;
	struct symtab_command	*sc;
	struct nlist_64			*nl;
	char					*stable;

	ret = 0;
	idx = -1u;
	sc = (struct symtab_command *)lc;
	nl = (struct nlist_64 *)(ptr + sc->symoff);
	stable = (char *)(ptr + sc->stroff);
	while (++idx < sc->nsyms)
	{
		ft_putendl(stable + nl[idx].n_un.n_strx);
	}
	return (ret);
}
