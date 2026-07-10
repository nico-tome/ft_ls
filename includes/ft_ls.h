/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 13:19:34 by ntome             #+#    #+#             */
/*   Updated: 2026/07/10 13:36:56 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libs.h"

# define VALID_FLAGS "lRartAdgGmnps1QeUD"

typedef struct s_arg
{
	char			*path;
	struct s_arg	*next;
}				t_arg;

typedef struct s_flags
{
	// manda flags
	int		l_flag;			// -l use long fromat display
	int		ur_flag;		// -R recursive reading
	int		a_flag;			// -a --all read all files
	int		r_flag;			// -r reverse sorting
	int		t_flag;			// -t sort by time
	// bonus flags
	int		ua_flag;		// -A --almost-all dont show . and ..
	int		auth_flag;		// --author with -l show the author of the file
	int		d_flag;			// -d --directory list dir, not files
	int		g_flag;			// -g like -l but without owner
	int		ug_flag;		// -G --no-group with -l or -g but without groups
	int		m_flag;			// -m put a comma after each file
	int		n_flag;			// -n --numeric-uid-gid like -l but use numeric uid and gid
	int		p_flag;			// -p --directory-indicator aapend / after each dir
	int		uq_flag;		// -Q put names in quotes
	int		s_flag;			// -s show the size of the file in block
	int		one_flag;		// -1 one line per output
	// custom flags
	int		e_flag;			// -e --emojies use emojies in ouput
	int		uu_flag;		// -U --keep-uppercase sort while keeping lowercase and uppercase
	int		only_dir_flag;	// --only-dir show only directorys
	int		no_color_flag;	// --no-color disable color
}			t_flags;

typedef struct s_padding
{
	int	block;
	int	link;
	int	name;
	int	group;
	int	size;
	int	date;
	int	total_size;
}				t_padding;

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
void	read_target(t_ctx *ctx, char *path, t_dir **elements, t_dir **files);

// sort utils
void	insert_new_dir(t_ctx *ctx, t_dir **elements, t_dir *new_dir);
void	insert_new_file(t_ctx *ctx, t_dir **elements, t_file *new_file);

// print utils
void		print_help(void);
void		print_ls(t_ctx *ctx, t_dir **files, t_dir **dir);
void		malloc_error(char *file, int line);
int			check_print(t_file *file, t_flags *flags);
int			check_long_format(t_flags *flags);
void		get_long_value(t_flags *flags, t_file *file, char **name, char **group);
char		get_file_type(t_file *file);
void		get_color(t_flags *flags, t_file *file, char **color);
void		print_permission(t_file *file);
t_padding	get_padding(t_ctx *ctx, t_file *files);

#endif
