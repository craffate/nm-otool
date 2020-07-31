/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 09:18:07 by craffate          #+#    #+#             */
/*   Updated: 2020/07/31 12:18:34 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <sys/stat.h>
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

#endif
