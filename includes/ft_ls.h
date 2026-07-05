/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 13:19:34 by ntome             #+#    #+#             */
/*   Updated: 2026/07/05 19:52:50 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libs.h"

# define VALID_FLAGS "lRartd1DeU"

typedef struct s_arg
{
	char			*path;
	struct s_arg	*next;
}				t_arg;

typedef struct s_flags
{
	int		l_flag;			// -l use long fromat display
	int		ur_flag;		// -R recursive reading
	int		a_flag;			// -a read all files
	int		r_flag;			// -r reverse sorting
	int		t_flag;			// -t sort by time
	int		d_flag;			// -d list dir, not files
	int		one_flag;		// -1 one line per output
	int		e_flag;			// -e use emojies in ouput
	int		uu_flag;		// -U sort while keeping lowercase and uppercase
	int		debugg_flag;	// -D use debugg print (mine)
}			t_flags;

typedef struct s_file
{
	char			*name;
	char			*sorting_name;
	char			*path;
	struct stat		stat;

	struct s_file	*next;
}				t_file;

typedef struct s_dir
{
	char			*path;
	char			*sorting_path;
	struct stat		stat;

	struct s_file	*files;
	struct s_dir	*content;
	struct s_dir	*next;
}			t_dir;

typedef struct s_ctx
{
	int			exit_code;
	int			print_path;
	t_flags		flags;
	t_arg		*args;
}				t_ctx;

// free utils
void	free_args(t_arg *args);
void	free_elements(t_dir **elements);

// parsing utils
int		ft_init_flags(t_ctx *ctx, int ac, char **av);

// read utils
void	read_target(t_ctx *ctx, char *path, t_dir **elements);

// sort utils
void	insert_new_dir(t_ctx *ctx, t_dir **elements, t_dir *new_dir);
void	insert_new_file(t_ctx *ctx, t_dir **elements, t_file *new_file);

// print utils
void	print_help(void);
void	print_ls(t_ctx *ctx, t_dir **dir);
void	print_debugg_read_element(char *target, char *path);
void	print_debugg_file(t_file *file);
void	malloc_error(char *file, int line);

#endif
