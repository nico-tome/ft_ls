/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <nicolas@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:46:13 by ntome             #+#    #+#             */
/*   Updated: 2026/06/05 16:46:14 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// color.h

#ifndef COLOR_H
# define COLOR_H

/*
** ===================== TEXT COLORS =====================
*/

/* Regular */
# define BLACK          "\033[0;30m"
# define RED            "\033[0;31m"
# define GREEN          "\033[0;32m"
# define YELLOW         "\033[0;33m"
# define BLUE           "\033[0;34m"
# define PURPLE         "\033[0;35m"
# define CYAN           "\033[0;36m"
# define WHITE          "\033[0;37m"

/* Bright */
# define BRIGHT_BLACK   "\033[0;90m"
# define BRIGHT_RED     "\033[0;91m"
# define BRIGHT_GREEN   "\033[0;92m"
# define BRIGHT_YELLOW  "\033[0;93m"
# define BRIGHT_BLUE    "\033[0;94m"
# define BRIGHT_PURPLE  "\033[0;95m"
# define BRIGHT_CYAN    "\033[0;96m"
# define BRIGHT_WHITE   "\033[0;97m"

/*
** ===================== TEXT STYLES =====================
*/

# define BOLD           "\033[1m"
# define DIM            "\033[2m"
# define ITALIC         "\033[3m"
# define UNDERLINE      "\033[4m"
# define BLINK          "\033[5m"   // not widely supported
# define REVERSE        "\033[7m"
# define HIDDEN         "\033[8m"

/*
** ===================== BACKGROUND COLORS =====================
*/

/* Regular */
# define BG_BLACK       "\033[40m"
# define BG_RED         "\033[41m"
# define BG_GREEN       "\033[42m"
# define BG_YELLOW      "\033[43m"
# define BG_BLUE        "\033[44m"
# define BG_PURPLE      "\033[45m"
# define BG_CYAN        "\033[46m"
# define BG_WHITE       "\033[47m"

/* Bright */
# define BG_BRIGHT_BLACK   "\033[100m"
# define BG_BRIGHT_RED     "\033[101m"
# define BG_BRIGHT_GREEN   "\033[102m"
# define BG_BRIGHT_YELLOW  "\033[103m"
# define BG_BRIGHT_BLUE    "\033[104m"
# define BG_BRIGHT_PURPLE  "\033[105m"
# define BG_BRIGHT_CYAN    "\033[106m"
# define BG_BRIGHT_WHITE   "\033[107m"

/*
** ===================== RESET =====================
*/

# define RESET          "\033[0m"

#endif
