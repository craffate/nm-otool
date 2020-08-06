/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 09:18:07 by craffate          #+#    #+#             */
/*   Updated: 2020/08/06 12:03:14 by craffate         ###   ########.fr       */
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
** General constants
*/

# define DEFAULT_FILE	"a.out"

/*
** Magic numbers
*/

# define MH_MAGIC		0xfeedface
# define MH_CIGAM		0xcefaedfe
# define MH_MAGIC_64	0xfeedfacf
# define MH_CIGAM_64	0xcffaedfe

/*
** Error strings
*/

# define ERR_NOAV_S			"No argument provided"
# define ERR_MALLOC_S		"Memory allocation error"
# define ERR_OPEN_S			"Error opening file"
# define ERR_FSTAT_S		"Error gathering file information"
# define ERR_MMAP_S			"Error mapping file to memory"
# define ERR_MUNMAP_S		"Error unmapping file from memory"
# define ERR_INTERNAL_S		"Internal error"
# define ERR_UNKNOWN_S		"Unknown error"

/*
** Error codes
*/

typedef enum			e_error
{
	ERR_NOAV = 1,
	ERR_MALLOC,
	ERR_OPEN,
	ERR_FSTAT,
	ERR_MMAP,
	ERR_MUNMAP,
	ERR_INTERNAL,
	ERR_UNKNOWN
}						t_error;

/*
** Symbol data structure
*/

typedef struct			s_symbol
{
	char				*name;
	unsigned int		section;
	unsigned char		type;
	char				*value;
	struct s_symbol		*next;
}						t_symbol;

/*
** File data structure
*/

typedef struct			s_file
{
	char				*name;
	unsigned int		magic;
	int					fd;
	struct stat			stat;
	char				*ptr;
	struct s_symbol		*sym;
	struct s_file		*next;
}						t_file;

/*
** File list functions
*/

t_file					*create_file_node(const char *name);
t_file					*append_file_node(t_file **f_lst, t_file *node);

/*
** Symbol list functions
*/

void					print_symbols(t_symbol *s_lst);
t_symbol				*create_symbol_node_32(char *st, struct nlist nl);
t_symbol				*create_symbol_node_64(char *st, struct nlist_64 nl);
t_symbol				*append_symbol_node(t_symbol **s_lst, t_symbol *node);

/*
** Mach-O functions
*/

int						handle_macho(t_file *file);

# ifdef __APPLE__

/*
** Mach-O symtab functions
*/

t_symbol				*get_symtab_64(struct load_command *lc, char *ptr);
t_symbol				*get_symtab_32(struct load_command *lc, char *ptr);
unsigned char			symbol_type(uint8_t n_type, uint8_t n_sect);

# endif

/*
** Error functions
*/

void					print_error(int errcode);

#endif
