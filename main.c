/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:59:48 by ilya              #+#    #+#             */
/*   Updated: 2022/10/20 20:59:51 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	minishell = {NULL, NULL, NULL, NULL, NULL};

char	*my_getenv(char **env, char *key)
{
	char	*key_copy;
	char	*loc;
	int		count;

	key_copy = ft_strjoin(key, "=");
	count = 0;
	while (env[count])
	{
		loc = ft_strnstr(env[count], key_copy, ft_strlen(key_copy) + 1);
		if (loc)
		{
			free(key_copy);
			return (ft_strchr(env[count], '=') + 1);
		}
		count++;
	}
	free(key_copy);
	return (NULL);
}

void	handle_signals(int signo)
{
	(void)signo;
	write(1, "\n", 1); // Move to a new line
	rl_on_new_line(); // Regenerate the prompt on a newline
	rl_replace_line("", 0); // Clear the previous text
	rl_redisplay();
}

//placeholder
//to write actual version later
void	free_everything()
{
	t_cmd	*dbl_commands;

	free(minishell.command_line);
	minishell.command_line = NULL;
	dbl_commands = minishell.commands;
	while (dbl_commands)
	{
		dbl_commands = dbl_commands->next;
	}
}

int		cmd_len(t_cmd *commands)
{
	int	ret;

	ret = 0;
	while(commands)
	{
		ret++;
		commands = commands->next;
	}
	return (ret);
}

void	commute_pipes(int len, t_pipe *pipes, int pipe_pos)
{
	int	cls_pipes;

	cls_pipes = 0;
	if (pipe_pos != 0)
		dup2(pipes[pipe_pos - 1][0], 0);
	if (pipe_pos != len - 1)
		dup2(pipes[pipe_pos][1], 1);
	while (cls_pipes < len - 1)
	{
		if (cls_pipes != pipe_pos - 1)
			close(pipes[cls_pipes][0]);
		if (cls_pipes != pipe_pos)
			close(pipes[cls_pipes][1]);
		cls_pipes++;
	}
}

int	built_in_exit()
{
	exit(0);
}

int	built_in_env()
{
	int	count;

	count = 0;
	while (minishell.env[count])
	{
		printf("%s\n", minishell.env[count]);
		count++;
	}
	return (0);
}

int	built_in_echo(t_cmd *command)
{
	int		count;
	int		new_line;

	count = 1;
	new_line = 1;
	while (command->args[count])
	{
		if (count != 1 && !(count == 2 && new_line == 0))
			printf(" ");
		if (count == 1 && !ft_strncmp(command->args[count], "-n", 3))
			new_line = 0;
		else
			printf("%s", command->args[count]);
		count++;
	}
	if (new_line)
		printf("\n");
	return (0);
}

int	real_execution(t_cmd *command)
{
	if (command->type == e_simple_command)
		return(execve(command->cmd, command->args, minishell.env));
	else if (command->type == e_echo)
		return(built_in_echo(command));
	else if (command->type == e_cd)
		return(0);
	else if (command->type == e_pwd)
		return(0);
	else if (command->type == e_unset)
		return(0);
	else if (command->type == e_export)
		return(0);
	else if (command->type == e_env)
		return(built_in_env());
	else if (command->type == e_exit)
		return(built_in_exit());
	else
		return (-1);
}

void	exec_pipe(int len, t_pipe *pipes, int pipe_pos, t_cmd *command)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		commute_pipes(len, pipes, pipe_pos);
		// expand_command(command);
		if (real_execution(command))
			perror(command->cmd);
		exit(1);
	}
	else if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else
	{
		// printf("command %s with %d pid\n", command->cmd, pid);
		return ;
	}
}

void	init_pipes(t_pipe *pipes, t_pipe *trivial, int cmd_list_len)
{
	int	count;

	count = 0;
	if (pipes == trivial)
		return ;
	while (count < cmd_list_len)
	{
		if (pipe((int *)&(pipes[count])))
		{
			perror("pipe");
			exit(1);
		}
		count++;
	}
}

void	close_pipes(t_pipe *pipes_list, int len, t_pipe *trivial_pipe)
{
	int	count;

	count = 0;
	if (pipes_list == trivial_pipe)
		return ;
	while (count < len)
	{
		close(pipes_list[count][0]);
		close(pipes_list[count][1]);
		count++;
	}
	free(pipes_list);
}

void	fork_and_dup(int cmd_list_len)
{
	t_pipe	*pipes_list;
	t_pipe	trivial_pipe;
	t_cmd	*command;
	int	count;
	int	status;
	int	pid;

	count = 0;
	if (cmd_list_len == 1)
	{
		if (minishell.commands->type != e_simple_command && minishell.commands->type != e_echo)
		{
			real_execution(minishell.commands);
			return ;
		}
		trivial_pipe[0] = 0;
		trivial_pipe[1] = 1;
		pipes_list = &trivial_pipe;
	}
	else
		pipes_list = malloc(sizeof(t_pipe) * (cmd_list_len - 1));
	if (pipes_list == NULL)
		exit(1);
	init_pipes(pipes_list, &trivial_pipe, cmd_list_len - 1);
	command = minishell.commands;
	while (count < cmd_list_len)
	{
		exec_pipe(cmd_list_len, pipes_list, count, command);
		command = command->next;
		count++;
	}
	close_pipes(pipes_list, cmd_list_len - 1, &trivial_pipe);
	count = 0;
	while (count < cmd_list_len)
	{
		pid = wait(&status);
		// printf("process %d exits with %d\n", pid, WEXITSTATUS(status));
		(void)pid;
		count++;
	}
	return ;
}

// void	define_path(t_cmd *command, char **paths)
// {

// }

// void	expand_command(t_cmd *command)
// {
// 	char	**paths;
// 	char	**path_double;

// 	paths = ft_split(getenv("PATH"), ':');
// 	define_path(command, paths);
// 	path_double = paths;
// 	while (*paths)
// 	{
// 		free(*paths);
// 		paths++;
// 	}
// 	free(path_double);
// 	return ;
// }

void	execute_command_list(t_cmd *commands)
{
	int	cmd_list_len;

	cmd_list_len = cmd_len(commands);
	if (cmd_list_len > 0)
		fork_and_dup(cmd_list_len);
	//fork and dup here --------------
	return ;
}

void	print_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
	{
		printf("%s\n", args[count]);
		count++;
	}
	if (args[count] == NULL)
		printf("ok\n");
}

void	print_commands(t_cmd *list)
{
	while (list)
	{
		printf("%s\n", list->cmd);
		print_args(list->args);
		list = list->next;
	}
}

char	*output_prompt()
{
	static char	*prompt = NULL;
	char	*tmp;
	char	*sec_tmp;

	if (prompt != NULL)
		free(prompt);
	tmp = ft_strjoin(my_getenv(minishell.env, "USER"), ":");
	sec_tmp = ft_strjoin(tmp, my_getenv(minishell.env, "PWD"));
	free(tmp);
	prompt = ft_strjoin(sec_tmp, "$ ");
	free(sec_tmp);
	return (prompt);
}

void	set_labels(t_cmd *commands)
{
	while (commands)
	{
		if (!ft_strncmp(commands->cmd, "echo", sizeof("echo") + 1))
			commands->type = e_echo;
		else if (!ft_strncmp(commands->cmd, "cd", sizeof ("cd") + 1))
			commands->type = e_cd;
		else if (!ft_strncmp(commands->cmd, "pwd", sizeof ("pwd") + 1))
			commands->type = e_pwd;
		else if (!ft_strncmp(commands->cmd, "unset", sizeof ("unset") + 1))
			commands->type = e_unset;
		else if (!ft_strncmp(commands->cmd, "export", sizeof ("export") + 1))
			commands->type = e_export;
		else if (!ft_strncmp(commands->cmd, "env", sizeof ("env") + 1))
			commands->type = e_env;
		else if (!ft_strncmp(commands->cmd, "exit", sizeof ("exit") + 1))
			commands->type = e_exit;
		else
			commands->type = e_simple_command;
		commands = commands->next;
	}
}

void	manage_command()
{
	// char *name = ttyname(1);

	minishell.command_line = readline(output_prompt()); //USER should be in global context
	minishell.commands = string_run(minishell.command_line, minishell.env);
	set_labels(minishell.commands);
	execute_command_list(minishell.commands);
	free_everything();
}

char	**dup_env(char **environment)
{
	char	**dbl;
	int		count;
	int		sec_count;

	count = 0;
	if (environment == NULL)
	{
		perror("environment");
		exit(1);
	}
	while (environment[count])
		count++;
	dbl = malloc(sizeof(char *) * (count + 1));
	if (dbl == NULL)
	{
		perror("malloc");
		exit(1);
	}
	sec_count = 0;
	while (environment[sec_count])
	{
		dbl[sec_count] = ft_strdup(environment[sec_count]);
		if (!dbl[sec_count])
		{
			perror("ft_strdup");
			exit(1);
		}
		sec_count++;
	}
	dbl[sec_count] = NULL;
	return (dbl);
}

int	main(int argc, char **argv, char **environment)
{
	(void)argc;
	(void)argv;
	minishell.env = dup_env(environment);
	signal(SIGINT, handle_signals);
	while (1)
		manage_command();
	return (0);
}
