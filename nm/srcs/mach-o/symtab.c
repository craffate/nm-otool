/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 09:00:16 by craffate          #+#    #+#             */
/*   Updated: 2020/08/06 08:33:40 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

unsigned char				symbol_type(uint8_t n_type, uint8_t n_sect)
{
	unsigned char			ret;

	ret = '?';
	if (n_sect == NO_SECT)
		ret = n_type & ~N_UNDF ? 'u' : 'a';
	else
	{
		if (n_type & ~N_INDR)
			ret = 'i';
		if (n_sect == 1)
			ret = 't';
		if (n_sect == 9)
			ret = 'b';
	}
	if (n_type & N_EXT || n_type & N_PEXT)
		ret = ft_toupper(ret);
	return (ret);
}

t_symbol					*get_symtab_32(struct load_command *lc, char *ptr)
{
	t_symbol				*ret;
	unsigned int			idx;
	struct symtab_command	*sc;
	struct nlist			*nl;
	char					*stable;

	ret = NULL;
	idx = -1u;
	sc = (struct symtab_command *)lc;
	nl = (struct nlist *)(ptr + sc->symoff);
	stable = (char *)(ptr + sc->stroff);
	while (++idx < sc->nsyms)
		append_symbol_node(&ret, create_symbol_node_32(stable, nl[idx]));
	return (ret);
}

t_symbol					*get_symtab_64(struct load_command *lc, char *ptr)
{
	t_symbol				*ret;
	unsigned int			idx;
	struct symtab_command	*sc;
	struct nlist_64			*nl;
	char					*stable;

	ret = NULL;
	idx = -1u;
	sc = (struct symtab_command *)lc;
	nl = (struct nlist_64 *)(ptr + sc->symoff);
	stable = (char *)(ptr + sc->stroff);
	while (++idx < sc->nsyms)
		append_symbol_node(&ret, create_symbol_node_64(stable, nl[idx]));
	return (ret);
}
