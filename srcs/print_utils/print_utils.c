/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 11:34:09 by ntome             #+#    #+#             */
/*   Updated: 2026/07/09 21:35:37 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

void	print_help(void)
{
	ft_printf("Usage: ls [%sOPTION%s]... [%sFILES%s]...\n",
		YELLOW, RESET, YELLOW, RESET);
	ft_printf("Show informations about [%sFILES%s].\n\n", YELLOW, RESET);
	ft_printf("%s -a%s, %s--all%s\t\tdon't ignore entries that start with .\n", GREEN, RESET, GREEN, RESET);
	ft_printf("%s -A%s, %s--almost-all%s\tdon't include . and .. in the list\n", GREEN, RESET, GREEN, RESET);
	ft_printf("%s     --author%s\t\twith -l, display the author of each files\n", GREEN, RESET);
	ft_printf("%s -d%s, %s--directory%s\tdisplay the name of directories, not their content\n", GREEN, RESET, GREEN, RESET);
	ft_printf("%s -g%s\t\t\tlike -l but display the owner\n", GREEN, RESET);
	ft_printf("%s -G%s, %s--no-group%s\t\tin a long display format, don't show the group\n", GREEN, RESET, GREEN, RESET);
	ft_printf("%s -l%s\t\t\tuse long format display\n", GREEN, RESET);
	ft_printf("%s -m%s\t\t\tput a comma after each entrie\n", GREEN, RESET);
	ft_printf("%s -n%s, %s--numeric-uid-gid%s\tlike -l but display numeric value of uid and gid\n", GREEN, RESET, GREEN, RESET);
	ft_printf("%s -p%s\t\t\tadd / after each directories\n", GREEN, RESET);
	ft_printf("%s -Q%s, %s--quote-names%s\tput name between quotes\n", GREEN, RESET, GREEN, RESET);
	ft_printf("%s -r%s, %s--reverse%s\t\treverse sort order\n", GREEN, RESET, GREEN, RESET);
	ft_printf("%s -R%s, %s--recursive%s\tuse recursive subdirectories\n", GREEN, RESET, GREEN, RESET);
	ft_printf("%s -s%s, %s--size%s\t\tdisplay the size allocated for each files in block\n", GREEN, RESET, GREEN, RESET);
	ft_printf("%s -t%s\t\t\tsort by date, newest first\n", GREEN, RESET);
	ft_printf("%s -1%s\t\t\tshow one file per line\n", GREEN, RESET);
	ft_printf("%s     --help%s\t\tshow this help\n", GREEN, RESET);
	ft_printf("\nCustome flags:\n");
	ft_printf("%s -e%s, %s--emojies%s\t\tuse emojies 🤌 (may not work on every terminal)\n", GREEN, RESET, GREEN, RESET);
	ft_printf("%s -U%s, %s--keep-uppercase%s\tkeep uppercase when sorting by name\n", GREEN, RESET, GREEN, RESET);
	ft_printf("%s     --only-dir%s\t\tshow only directories\n", GREEN, RESET);
	ft_printf("%s     --no-color%s\t\tdisable colors\n", GREEN, RESET);
}

void	get_long_value(t_flags *flags, t_file *file, char **name, char **group)
{
	if (flags->n_flag)
	{
		*name = ft_itoa(getpwuid(file->stat.st_uid)->pw_uid);
		*group = ft_itoa(getpwuid(file->stat.st_gid)->pw_gid);

	}
	else
	{
		*name = getpwuid(file->stat.st_uid)->pw_name;
		*group = getgrgid(file->stat.st_gid)->gr_name;
	}
}

int	check_long_format(t_flags *flags)
{
	if (flags->l_flag ||
		flags->n_flag ||
		flags->g_flag)
		return (1);
	return (0);
}

int	check_print(t_file *file, t_flags *flags)
{
	char	type;

	type = get_file_type(file);
	if (file->name[0] == '.' && !flags->a_flag && !flags->d_flag && !flags->ua_flag)
		return (0);
	if (flags->only_dir_flag && type != 'd')
		return (0);
	if (file->name[ft_strlen(file->name) - 1] == '.' && flags->ua_flag)
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

void	get_color(t_flags *flags, t_file *file, char **color)
{
	char	type;

	if (flags->no_color_flag)
	{
		*color = RESET;
		return ;
	}
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
	char		*name;
	char		*group;

	ft_bzero(&padd, sizeof(t_padding));
	if (!check_long_format(&ctx->flags) && !ctx->flags.s_flag)
		return (padd);
	while (files)
	{
		if (!check_print(files, &ctx->flags))
		{
			files = files->next;
			continue ;
		}
		get_long_value(&ctx->flags, files, &name, &group);
		date = ctime(&files->stat.st_mtim.tv_sec);
		date[ft_strlen(date) - 9] = '\0';
		tmp.block = ft_get_int_size(files->stat.st_blocks / 2);
		tmp.link = ft_get_int_size(files->stat.st_nlink);
		tmp.name = ft_strlen(name);
		tmp.group = ft_strlen(group);
		tmp.size = ft_get_long_long_size(files->stat.st_size);
		tmp.date = ft_strlen(date);
		padd.block = tmp.block > padd.block ? tmp.block : padd.block;
		padd.link = tmp.link > padd.link ? tmp.link : padd.link;
		padd.name = tmp.name > padd.name ? tmp.name : padd.name;
		padd.group = tmp.group > padd.group ? tmp.group : padd.group;
		padd.size = tmp.size > padd.size ? tmp.size : padd.size;
		padd.date = tmp.date > padd.date ? tmp.date : padd.date;
		padd.total_size += files->stat.st_blocks / 2;
		if (ctx->flags.n_flag)
		{
			free(name);
			free(group);
		}
		files = files->next;
	}
	return (padd);
}
