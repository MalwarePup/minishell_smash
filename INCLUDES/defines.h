/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:07:16 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/22 21:18:11 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "libraries.h"

/******************************************************************************\
 * GENERAL
\******************************************************************************/

# define _XOPEN_SOURCE 700
# define PATH_MAX 4096
# define IS_REDIR(t) ((t == REDIR_IN) || (t == HERE_DOC) \
						|| (t == REDIR_OUT_TRUNC) || (t == REDIR_OUT_APPEND))

/******************************************************************************\
 * YAMA'S FLAGS
\******************************************************************************/

# define CREATE 0
# define CREATE_TAB 1
# define ADD 2
# define ADD_TAB 3
# define REMOVE -1
# define CLEAN_ALL -2

/******************************************************************************\
 * EXIT STATUS
\******************************************************************************/

# define SUCCESS 0
# define FAILURE 1

# define BAD_USAGE 2
# define CMD_CANNOT_EXEC 126
# define CMD_NOT_FOUND 127
# define OUT_OF_RANGE 255

# define CTRL_C_EXIT 130 // 128 + signal 2 (SIGINT)
# define CTRL_SL_EXIT 143 // 128 + signal 15 (SIGTERM)

/******************************************************************************\
 * ERROR
\******************************************************************************/

# define ERR_PREFIX (BOLD RED "smash: " R)

// syntax / user error
# define ERR_PIPE "syntax error near unexpected token `"
# define ERR_QUOTES "failed to handle quotes"
# define ERR_ENV_VAR "not a valid identifier"
# define ERR_ARG "too many arguments"
# define ERR_ARG_TYPE "numeric argument required"

// creation
# define ERR_MALLOC "cannot allocate memory"

// exec
# define ERR_CMD "command not found"
# define ERR_BAD_PERM "Permission denied"
# define ERR_BAD_FILE "No such file or directory"
# define ERR_NO_ENV "$PATH doesn't exist, please specify absolute path"
# define ERR_MAX_HD "maximum here-document count exceeded"

/******************************************************************************\
 * CUSTOM
\******************************************************************************/

# define BP BOLD PINK
# define BPP BOLD PURPLE

# define WELCOME_BANNER "\e[38;2;255;234;150m╔═════════════════════════════════════════════════════════════════════════╗\n║                                                                         ║\n║\t\t\e[31m░██████╗███╗░░░███╗░█████╗░░██████╗██╗░░██╗\t\t  \e[38;2;255;234;150m║\n║\t\t\e[31m██╔════╝████╗░████║██╔══██╗██╔════╝██║░░██║\t\t  \e[38;2;255;234;150m║\n║\t\t\e[31m╚█████╗░██╔████╔██║███████║╚█████╗░███████║\t\t  \e[38;2;255;234;150m║\n║\t\t\e[31m░╚═══██╗██║╚██╔╝██║██╔══██║░╚═══██╗██╔══██║\t\t  \e[38;2;255;234;150m║\n║\t\t\e[31m██████╔╝██║░╚═╝░██║██║░░██║██████╔╝██║░░██║\t\t  \e[38;2;255;234;150m║\n║\t\t\e[31m╚═════╝░╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═════╝░╚═╝░░╚═╝\t\t  \e[38;2;255;234;150m║\n║                 \e[38;2;173;165;165m―――――――  Simple Mateo Anna SHell ―――――――                \e[38;2;255;234;150m║\n║                                                                         ║\n╚═════════════════════════════════════════════════════════════════════════╝\n\n\n"

# define LIM "=================================="
# define LIM2 "================================"
# define LIM3 "================================="

# define BYE_MSG "XOXO 💋"

#endif