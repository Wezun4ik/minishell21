/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:59:48 by ilya              #+#    #+#             */
/*   Updated: 2022/10/26 14:16:19 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	minishell = {NULL, NULL, NULL, NULL, NULL};

void	handle_signals(int signo)
{
	(void)signo;
	write(1, "\n", 1); // Move to a new line
	rl_on_new_line(); // Regenerate the prompt on a newline
	rl_replace_line("", 0); // Clear the previous text
	rl_redisplay();
}

void	unlink_heredocs(t_cmd *commands)
{
	while (commands)
	{
		if (commands->heredoc)
			unlink(commands->heredoc);
		commands = commands->next;
	}
}

//placeholder
//to write actual version later
void	free_everything(void)
{
	t_cmd	*dbl_commands;
	t_cmd	*dbl_dbl_commands;
	int		count;
	t_red	*all_reds;
	t_red	*all_reds_dbl;

	free(minishell.command_line);
	minishell.command_line = NULL;
	unlink_heredocs(minishell.commands);
	dbl_commands = minishell.commands;
	while (dbl_commands)
	{
		if (dbl_commands->cmd != dbl_commands->args[0])
			free(dbl_commands->cmd);
		count = 0;
		while (dbl_commands->args[count])
		{
			free(dbl_commands->args[count]);
			count++;
		}
		free(dbl_commands->args);
		if (dbl_commands->red)
		{
			all_reds = dbl_commands->red;
			while (all_reds)
			{
				free(all_reds->word);
				all_reds_dbl = all_reds->next;
				free(all_reds);
				all_reds = all_reds_dbl;
			}
		}
		dbl_dbl_commands = dbl_commands->next;
		free(dbl_commands);
		dbl_commands = dbl_dbl_commands;
	}
}

int	cmd_len(t_cmd *commands)
{
	int	ret;

	ret = 0;
	while (commands)
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

int	open_files(t_cmd *command)
{
	t_red	*cur_red;

	command->input = 0;
	command->output = 1;
	cur_red = command->red;
	while (cur_red)
	{
		if (cur_red->type == REDGINT || cur_red->type == REDGGINT)
		{
			if (command->output != 1)
				close(command->output);
			if (cur_red->type == REDGINT)
				command->output = open(cur_red->word, O_WRONLY | O_TRUNC | O_CREAT,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
			else
				command->output = open(cur_red->word, O_WRONLY | O_APPEND | O_CREAT,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
			if (command->output == -1)
			{
				perror(cur_red->word);
				command->output = 1;
				return (1);
			}
		}
		if (cur_red->type == REDLINT || cur_red->type == REDLLINT)
		{
			if (command->input != 0)
				close(command->output);
			if (cur_red->type == REDLLINT)
				command->input = open(command->heredoc, O_RDONLY);
			else
				command->input = open(cur_red->word, O_RDONLY);
			if (command->input == -1)
			{
				perror(cur_red->word);
				command->input = 1;
				return (1);
			}
		}
		cur_red = cur_red->next;
	}
	return (0);
}

void	close_files(t_cmd *command)
{
	if (command->input != 0)
		close(command->input);
	if (command->output != 1)
		close(command->output);
}

int	real_execution(t_cmd *command)
{
	int	ret;

	ret = open_files(command);
	if (!ret)
	{
		if (command->type == e_simple_command)
		{
			dup2(command->input, 0);
			dup2(command->output, 1);
			ret = (execve(command->cmd, command->args, minishell.env));
		}
		else if (command->type == e_echo)
			ret = (built_in_echo(command));
		else if (command->type == e_cd)
			ret = (built_in_cd(command));
		else if (command->type == e_pwd)
			ret = (built_in_pwd(command));
		else if (command->type == e_unset)
			ret = (built_in_unset(&minishell.env, command));
		else if (command->type == e_export)
			ret = (built_in_export(&minishell.env, command));
		else if (command->type == e_env)
			ret = (built_in_env());
		else if (command->type == e_exit)
			ret = (built_in_exit());
		else
			ret = (1);
	}
	close_files(command);
	return (ret);
}

void	exec_pipe(int len, t_pipe *pipes, int pipe_pos, t_cmd *command)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		commute_pipes(len, pipes, pipe_pos);
		expand_command(command);
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
	int		count;
	int		status;
	int		pid;

	count = 0;
	if (cmd_list_len == 1)
	{
		if (minishell.commands->type != e_simple_command
			&& minishell.commands->type != e_echo)
		{
			if (minishell.commands->type == e_exit)
				unlink_heredocs(minishell.commands);
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

void	define_path(t_cmd *command, char **paths)
{
	int		count;
	char	*buf;
	char	*filename;
	int		ret_code;

	count = 0;
	while (paths[count])
	{
		buf = ft_strjoin(paths[count], "/");
		filename = ft_strjoin(buf, command->cmd);
		free(buf);
		if (filename == NULL)
		{
			perror("strjoin");
			exit (1);
		}
		ret_code = access(filename, F_OK | X_OK);
		if (ret_code == 0)
		{
			if (command->cmd != command->args[0])
				free(command->cmd);
			command->cmd = filename;
			return ;
		}
		free(filename);
		count++;
	}
	perror(command->cmd);
	exit(1);
}

void	expand_command(t_cmd *command)
{
	char	**paths;
	char	**path_double;

	if (command->type != e_simple_command || command->cmd == NULL)
		return ;
	if (command->cmd[0] == '/' || (command->cmd[0] != '\0'
			&& command->cmd[1] != '\0'
			&& command->cmd[0] == '.' && command->cmd[1] == '/'))
		return ;
	paths = ft_split(getenv("PATH"), ':');
	define_path(command, paths);
	path_double = paths;
	while (*paths)
	{
		free(*paths);
		paths++;
	}
	free(path_double);
	return ;
}

void	execute_command_list(t_cmd *commands)
{
	int	cmd_list_len;

	cmd_list_len = cmd_len(commands);
	if (cmd_list_len > 0)
		fork_and_dup(cmd_list_len);
	//fork and dup here --------------
	return ;
}

char	*output_prompt(void)
{
	static char	*prompt = NULL;
	char		*tmp;
	char		*sec_tmp;

	if (prompt != NULL)
		free(prompt);
	tmp = ft_strjoin(my_getenv(minishell.env, "USER"), ":");
	sec_tmp = ft_strjoin(tmp, my_getenv(minishell.env, "PWD"));
	free(tmp);
	prompt = ft_strjoin(sec_tmp, "$ ");
	free(sec_tmp);
	if (prompt == NULL)
		return ("$");
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

int		read_heredocs(t_cmd *commands)
{
	static int	file_counter = 0;
	t_red		*reds;
	char		*str_misc;
	int			fd;

	while (commands)
	{
		commands->heredoc = NULL;
		reds = commands->red;
		while (reds)
		{
			if (reds->type == REDLLINT)
			{
				if (commands->heredoc)
				{
					unlink(commands->heredoc);
					free(commands->heredoc);
					commands->heredoc = NULL;
				}
				str_misc = ft_itoa(file_counter);
				commands->heredoc = ft_strjoin("/tmp/minishell_tmp-", str_misc);
				free(str_misc);
				fd = open(commands->heredoc, O_WRONLY | O_CREAT,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
				if (fd == -1)
				{
					perror("heredoc");
					return (0);
				}
				while (1)
				{
					// write(1, "\n", 1);
					rl_on_new_line();
					str_misc = readline(">");
					if (str_misc == NULL)
						return (0);
					if (!ft_strncmp(str_misc, reds->word, ft_strlen(str_misc) + 1))
					{
						free(str_misc);
						break ;
					}
					write(fd, str_misc, ft_strlen(str_misc));
					free(str_misc);
				}
				close(fd);
			}
			reds = reds->next;
		}
		commands = commands->next;
	}
	return (1);
}

void	manage_command(void)
{
	rl_on_new_line();
	minishell.command_line = readline(output_prompt()); //USER should be in global context
	if (minishell.command_line == NULL)
	{
		printf("\n");
		return ;
	}
	add_history(minishell.command_line);
	minishell.commands = string_run(minishell.command_line, minishell.env);
	set_labels(minishell.commands);
	if (read_heredocs(minishell.commands))
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
	signal(SIGQUIT, SIG_IGN);
	rl_getc_function = getc;
	while (1)
		manage_command();
	return (0);
}
