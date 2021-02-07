/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 09:00:16 by craffate          #+#    #+#             */
/*   Updated: 2021/02/07 09:33:23 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

unsigned char				symbol_type(uint8_t n_type)
{
	unsigned char			ret;

	ret = '?';
	if (n_type & N_STAB)
		ret = '-';
	else if ((n_type & N_TYPE) == N_UNDF)
	{
		if (n_type & N_EXT)
			ret = 'U';
		else
			ret = 'C';
	}
	else if ((n_type & N_TYPE) == N_ABS)
		ret = 'A';
	else if ((n_type & N_TYPE) == N_INDR)
		ret = 'I';
	else if ((n_type & N_TYPE) == N_SECT)
		ret = '0';
	return (ret);
}

t_symbol					*get_symtab_32(t_load_command *lc, char *ptr)
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

t_symbol					*get_symtab_64(t_load_command *lc, char *ptr)
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
