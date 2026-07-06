/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 11:34:09 by ntome             #+#    #+#             */
/*   Updated: 2026/07/06 22:36:25 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

void	print_help(void)
{
	ft_printf("Usage: ls [%sOPTION%s]... [%sFILES%s]...\n",
		YELLOW, RESET, YELLOW, RESET);
	ft_printf("Show informations about [%sFILES%s].\n\n", YELLOW, RESET);
	ft_printf("%s-l%s\tuse long format display\n", GREEN, RESET);
	ft_printf("%s-R%s\tuse recursive subdirectories\n", GREEN, RESET);
	ft_printf("%s-r%s\treverse sort order\n", GREEN, RESET);
	ft_printf("%s-a%s\tdon't ignore entries that start with .\n", GREEN, RESET);
	ft_printf("%s-t%s\tsort by date, newest first\n", GREEN, RESET);
	ft_printf("%s-d%s\tonly show directory names\n", GREEN, RESET);
	ft_printf("%s-1%s\tshow one file per line\n", GREEN, RESET);
	ft_printf("%s-D%s\tuse debugg mode\n", GREEN, RESET);
	ft_printf("%s--help%s\tshow this help\n", GREEN, RESET);
}

int	check_print(t_file *file, t_flags *flags)
{
	if (file->name[0] == '.' && !flags->a_flag && !flags->d_flag)
		return (0);
	return (1);
}

char	get_file_type(t_file *file)
{
	mode_t	mode;

	mode = file->stat.st_mode;
	if (S_ISDIR(mode))
		return ('d');
	else if (S_ISREG(mode))
		return ('-');
	else if (S_ISLNK(mode))
		return ('l');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISBLK(mode))
		return ('b');
	else if (S_ISFIFO(mode))
		return ('p');
	else if (S_ISSOCK(mode))
		return ('s');
	return ('-');
}

void	get_color(t_file *file, char **color)
{
	char	type;

	type = get_file_type(file);
	*color = RESET;
	if (type == 'd')
		*color = BLUE;
	else if (type == '-')
	{
		if (file->stat.st_mode & ((S_IXUSR | S_IXGRP | S_IXOTH)))
			*color = GREEN;
		else
			*color = RESET;
	}
}

void	print_permission(t_file *file)
{
	ft_printf("%c", (file->stat.st_mode & S_IRUSR) ? 'r' : '-');
	ft_printf("%c", (file->stat.st_mode & S_IWUSR) ? 'w' : '-');
	ft_printf("%c", (file->stat.st_mode & S_IXUSR) ? 'x' : '-');

	ft_printf("%c", (file->stat.st_mode & S_IRGRP) ? 'r' : '-');
	ft_printf("%c", (file->stat.st_mode & S_IWGRP) ? 'w' : '-');
	ft_printf("%c", (file->stat.st_mode & S_IXGRP) ? 'x' : '-');

	ft_printf("%c", (file->stat.st_mode & S_IROTH) ? 'r' : '-');
	ft_printf("%c", (file->stat.st_mode & S_IWOTH) ? 'w' : '-');
	ft_printf("%c", (file->stat.st_mode & S_IXOTH) ? 'x' : '-');

	ft_printf(" ");
}

t_padding	get_padding(t_ctx *ctx, t_file *files)
{
	t_padding	padd;
	t_padding	tmp;
	char		*date;

	ft_bzero(&padd, sizeof(t_padding));
	if (!ctx->flags.l_flag && !ctx->flags.s_flag)
		return (padd);
	while (files)
	{
		if (!check_print(files, &ctx->flags))
		{
			files = files->next;
			continue ;
		}
		date = ctime(&files->stat.st_mtim.tv_sec);
		date[ft_strlen(date) - 9] = '\0';
		tmp.block = ft_get_int_size(files->stat.st_blocks / 2);
		tmp.link = ft_get_int_size(files->stat.st_nlink);
		tmp.name = ft_strlen(getpwuid(files->stat.st_uid)->pw_name);
		tmp.group = ft_strlen(getgrgid(files->stat.st_gid)->gr_name);
		tmp.size = ft_get_long_long_size(files->stat.st_size);
		tmp.date = ft_strlen(date);
		padd.block = tmp.block > padd.block ? tmp.block : padd.block;
		padd.link = tmp.link > padd.link ? tmp.link : padd.link;
		padd.name = tmp.name > padd.name ? tmp.name : padd.name;
		padd.group = tmp.group > padd.group ? tmp.group : padd.group;
		padd.size = tmp.size > padd.size ? tmp.size : padd.size;
		padd.date = tmp.date > padd.date ? tmp.date : padd.date;
		padd.total_size += files->stat.st_blocks / 2;
		files = files->next;
	}
	return (padd);
}
