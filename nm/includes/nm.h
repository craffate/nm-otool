/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 09:18:07 by craffate          #+#    #+#             */
/*   Updated: 2020/08/03 09:13:32 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include "libft.h"

typedef struct					s_file
{
	char						*name;
	unsigned int				magic;
	int							fd;
	struct stat					stat;
	char						*ptr;
	struct s_file				*next;
}								t_file;

/*
** File list functions
*/
t_file							*create_file_node(const char *name);
t_file							*append_file_node(t_file **f_lst, t_file *node);

/*
** Mach-O functions
*/
int								handle_macho(t_file *file);

/*
** Symtab functions
*/
int								get_symtab_64(struct load_command *lc, char *ptr);
int								get_symtab_32(struct load_command *lc, char *ptr);

#endif
