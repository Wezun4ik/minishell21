/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 20:07:54 by ilya              #+#    #+#             */
/*   Updated: 2022/10/26 14:16:01 by ilya             ###   ########.fr       */
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
int		built_in_pwd(t_cmd *command);
int		valid_key_value(char *arg);
void	export_one(char ***prev_env, char *env_var);
int		built_in_export(char ***prev_env, t_cmd *command);
int		built_in_cd(t_cmd *command);
int		built_in_unset(char ***prev_env, t_cmd *command);
int		unset_one(char ***prev_env, char *env_var);
char	*my_special_getenv(char **env, char *key);
int		valid_arg(char *arg);
int		built_in_echo(t_cmd *command);
char	*my_getenv(char **env, char *key);
int		built_in_exit(void);
int		built_in_env(void);
#endif
