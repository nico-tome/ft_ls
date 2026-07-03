/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 13:19:34 by ntome             #+#    #+#             */
/*   Updated: 2026/07/03 15:06:19 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "../lib/libft/libft.h"
# include "color.h"

# define VALID_FLAGS "lRartd1D"

typedef struct s_arg
{
	char			*path;
	struct s_arg	*next;
}				t_arg;

typedef struct s_flags
{
	int		l_flag;
	int		ur_flag;
	int		a_flag;
	int		r_flag;
	int		t_flag;
	int		d_flag;
	int		one_flag;
	int		debugg_flag;
}			t_flags;

typedef struct s_element
{
	char				*path;
	char				*name;
	int					is_dir;
	int					type;

	struct stat			stat;
	struct s_element	*content;
	struct s_element	*next;
}				t_element;

typedef struct s_ctx
{
	int			exit_code;
	t_flags		*flags;
	t_arg		*args;
	t_element	*elements;
}				t_ctx;

// free utils
void	free_args(t_arg *args);
void	free_elements(t_element *elements);

int		ft_init_flags(t_flags *flags, int ac, char **av);
int		read_element(t_element *elements, char *target, t_flags *flags, char *path);

// print utils
void	print_help(void);
void	print_ls(t_element *element, t_flags *flags);
void	print_debugg_read_element(char *target, char *path);

#endif
