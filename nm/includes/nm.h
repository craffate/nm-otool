/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 09:18:07 by craffate          #+#    #+#             */
/*   Updated: 2020/08/05 09:16:17 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <sys/stat.h>
# ifdef __APPLE__
#  include <mach-o/loader.h>
#  include <mach-o/nlist.h>
# endif
# ifdef __linux__
#  include <elf.h>
# endif
# include "libft.h"

/*
** Magic numbers
*/
# define MH_MAGIC		0xfeedface
# define MH_CIGAM		0xcefaedfe
# define MH_MAGIC_64	0xfeedfacf
# define MH_CIGAM_64	0xcffaedfe

typedef struct					s_symbol
{
	char						*name;
	unsigned int				section;
	unsigned char				type;
	char						*value;
	struct s_symbol				*next;
}								t_symbol;

typedef struct					s_file
{
	char						*name;
	unsigned int				magic;
	int							fd;
	struct stat					stat;
	char						*ptr;
	struct s_symbol				*sym;
	struct s_file				*next;
}								t_file;

/*
** File list functions
*/
t_file							*create_file_node(const char *name);
t_file							*append_file_node(t_file **f_lst, t_file *node);

/*
** Symbol list functions
*/
void							print_symbols(t_symbol *s_lst);
t_symbol						*create_symbol_node_32(char *stable, struct nlist nl);
t_symbol						*create_symbol_node_64(char *stable, struct nlist_64 nl);
t_symbol						*append_symbol_node(t_symbol **s_lst, t_symbol *node);

/*
** Mach-O functions
*/
int								handle_macho(t_file *file);

# ifdef __APPLE__
/*
** Mach-O symtab functions
*/
t_symbol						*get_symtab_64(struct load_command *lc, char *ptr);
t_symbol						*get_symtab_32(struct load_command *lc, char *ptr);
unsigned char					symbol_type(uint8_t n_type);
# endif

#endif
