/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 20:07:54 by ilya              #+#    #+#             */
/*   Updated: 2022/10/25 15:37:29 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "./libft/libft.h"
# include "./lexer/header/header.h"

# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_minishell
{
	char			*command_line;
	char			*pwd;
	char			**env;
	t_cmd			*commands;
	pid_t			*processes_pids;
}					t_minishell;

typedef int	t_pipe[2];

void	expand_command(t_cmd *command);

#endif
