/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 08:03:38 by craffate          #+#    #+#             */
/*   Updated: 2020/09/12 11:12:12 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H

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
# define FAT_MAGIC		0xcafebabe
# define FAT_CIGAM		0xbebafeca
# define FAT_MAGIC_64	0xcafebabf
# define FAT_CIGAM_64	0xbfbafeca

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
# define ERR_CORRUPT_S		"Corrupt binary"
# define ERR_UNKNOWNFT_S	"Unknown filetype"
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
	ERR_CORRUPT,
	ERR_UNKNOWNFT,
	ERR_UNKNOWN
}						t_error;

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
	char				*ptr_end;
	int					errno;
	struct s_segment	*seg;
	struct s_symbol		*sym;
	struct s_file		*next;
}						t_file;

/*
** Segment data structure
*/

typedef struct			s_segment
{
	uint32_t			cmd;
	uint32_t			cmdsize;
	char				*name;
	union
	{
		uint32_t		vmsize_32;
		uint64_t		vmsize_64;
	}					vmsize;
	union
	{
		uint32_t		vmaddr_32;
		uint64_t		vmaddr_64;
	}					vmaddr;
	union
	{
		uint32_t		offset_32;
		uint64_t		offset_64;
	}					offset;
	union
	{
		uint32_t		size_32;
		uint64_t		size_64;
	}					size;
	uint32_t			nsects;
	struct s_section	*sec;
	struct s_segment	*next;
}						t_segment;

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
** Section data structure
*/

typedef struct			s_section
{
	char				*name;
	char				*seg_name;
	union
	{
		uint32_t		addr_32;
		uint64_t		addr_64;
	}					addr;
	union
	{
		uint32_t		size_32;
		uint64_t		size_64;
	}					size;
	uint32_t			offset;
	uint32_t			align;
	struct s_section	*next;
}						t_section;

/*
** File list functions
*/

t_file					*create_file_node(const char *name);
t_file					*append_file_node(t_file **f_lst, t_file *n);

/*
** Segment list functions
*/

t_segment				*append_segment_node(t_segment **s_lst, t_segment *n);
t_segment				*create_segment_node_32(struct segment_command sc);
t_segment				*create_segment_node_64(struct segment_command_64 sc);
t_segment				*find_segment(t_segment *s_lst, const char *seg_name);

/*
** Symbol list functions
*/

t_symbol				*create_symbol_node_32(char *st, struct nlist nl);
t_symbol				*create_symbol_node_64(char *st, struct nlist_64 nl);
t_symbol				*append_symbol_node(t_symbol **s_lst, t_symbol *n);

/*
** Section list functions
*/

t_section				*create_section_node_32(struct section se);
t_section				*create_section_node_64(struct section_64 se);
t_section				*append_section_node(t_section **s_lst, t_section *n);
t_section				*find_section(t_section *se_lst, const char *name);

/*
** Mach-O functions
*/

int						handle_macho(t_file *file);
int						handle_macho_sections(t_file *file);

/*
** Error checking functions
*/

int						validate_range(void *p, void *start, void *end);

# ifdef __APPLE__

/*
** Mach-O symtab functions
*/

t_symbol				*get_symtab_64(struct load_command *lc, char *ptr);
t_symbol				*get_symtab_32(struct load_command *lc, char *ptr);
unsigned char			symbol_type(uint8_t n_type, uint8_t n_sect);

/*
** Mach-O section functions
*/

t_section				*get_section_64(struct load_command *lc);
t_section				*get_section_32(struct load_command *lc);

/*
** Mach-O segment functions
*/

t_segment				*get_segment_32(struct load_command *lc);
t_segment				*get_segment_64(struct load_command *lc);

# endif

/*
** Error functions
*/

void					print_error(int errcode);

#endif
