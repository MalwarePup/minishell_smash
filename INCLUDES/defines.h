/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:49:02 by annabrag          #+#    #+#             */
/*   Updated: 2024/09/23 19:21:47 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "colors.h"

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

/******************************************************************************\
 * EXIT STATUS
\******************************************************************************/

# define SUCCESS 0
# define FAILURE 1
# define MISUSE_CMD 2
# define CMD_CANNOT_EXEC 126
# define CMD_NOT_FOUND 127
# define CTRL_C_EXIT 130 // 128 + signal 2 (SIGINT)
# define KILL_EXIT 143 // 128 + signal 15 (SIGTERM)
# define OUT_OF_RANGE 255

/******************************************************************************\
 * ERROR
\******************************************************************************/

# define ERR_PREFIX (BOLD RED "smash: " RESET)
# define ERR_NEAR_PIPE "syntax error near unexpected token `|'"
# define ERR_MALLOC "cannot allocate memory"
# define ERR_QUOTES "failed to handle quotes"
# define ERR_BAD_FILE "No such file or directory"
# define ERR_CMD "command not found"

/******************************************************************************\
 * CUSTOM
\******************************************************************************/

# define WELCOME_BANNER "\e[96m╔══════════════════════════════════════════════════════════════════════════════════╗\n║                                                                                  ║\n║  \e[35m___________   __________                    ___________\t\t           \e[96m║\n║  \e[35m\\__    ___/   \\______   \\  ____  ___  ___   \\__    ___/____  _____     _____    \e[96m║\n║    \e[35m|    | ______|       _/_/ __ \\ \\  \\/  /     |    | _/ __ \\ \\__  \\   /     \\   \e[96m║\n║    \e[35m|    |/_____/|    |   \\\\  ___/  >    <      |    | \\  ___/  / __ \\_|  Y Y  \\  \e[96m║\n║    \e[35m|____|       |____|_  / \\___  >/__/\\_ \\     |____|  \\___  >(____  /|__|_|  /  \e[96m║\n║\t\t         \e[35m\\/      \\/       \\/                 \\/      \\/       \\/   \e[96m║\n║                                                                                  ║\n╚══════════════════════════════════════════════════════════════════════════════════╝\n\n\n"

# define BYE_MSG "Bye le sangreee"

#endif