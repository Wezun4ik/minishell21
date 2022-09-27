/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:59:48 by ilya              #+#    #+#             */
/*   Updated: 2022/09/25 17:55:11 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*args_one[] = {"/bin/ls", "-al", "/", NULL};

t_cmd	first_arg = {0, 0, "/bin/ls", args_one, 0, 1, NULL, NULL};

t_minishell	minishell = {NULL, NULL, NULL, NULL};

t_cmd	*parse(char *line)
{
	line = line;
	return (&first_arg);
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
	free(minishell.command_line);
	minishell.command_line = NULL;
	// free(commands);
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

void	exec_pipe(int len, t_pipe *pipes, int pipe_pos)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (pipe_pos != 0)
			close(pipes[pipe_pos - 1][0]);
		if (pipe_pos == len - 1 && len != 1)
			close(pipes[pipe_pos][1]);
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
		if (!pipe((int *)&(pipes[count])))
		{
			perror("pipe");
			exit(1);
		}
		count++;
	}
}

void	fork_and_dup(int cmd_list_len)
{
	t_pipe	*pipes_list;
	t_pipe	trivial_pipe;
	int	count;

	count = 0;
	if (cmd_list_len == 1)
	{
		trivial_pipe[0] = 0;
		trivial_pipe[1] = 1;
		pipes_list = &trivial_pipe;
	}
	else
		pipes_list = malloc(sizeof(t_pipe) * (cmd_list_len - 1));
	if (pipes_list == NULL)
		exit(1);
	init_pipes(pipes_list, &trivial_pipe, cmd_list_len - 1);
	while (count < cmd_list_len)
	{
		exec_pipe(cmd_list_len, pipes_list, count);
		count++;
	}
}

void	execute_command_list(t_cmd *commands)
{
	int	cmd_list_len;

	cmd_list_len = cmd_len(commands);
	printf("%d\n", cmd_list_len);
	if (cmd_list_len > 0)
		fork_and_dup(cmd_list_len);
	//fork and dup here --------------
	return ;
}

void	manage_command()
{
	// char *name = ttyname(1);

	minishell.command_line = readline(getenv("USER")); //USER should be in global context
	minishell.commands = parse(minishell.command_line);
	execute_command_list(minishell.commands);
	printf( "%s\n", minishell.command_line);
	free_everything();
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	signal(SIGINT, handle_signals);
	while (1)
		manage_command();
	return (0);
}
