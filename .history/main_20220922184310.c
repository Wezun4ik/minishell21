/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:59:48 by ilya              #+#    #+#             */
/*   Updated: 2022/09/22 18:43:10 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*args_one[] = {"/bin/ls", "-al", "/", NULL};

t_cmd	first_arg = {0, 0, "/bin/ls", args_one, NULL, NULL};

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
void	free_commands(t_cmd *commands)
{
	commands = commands;
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
}

void	execute_command_list(t_cmd *commands)
{
	int	cmd_list_len;

	cmd_list_len = cmd_len(commands);
}

void	manage_command()
{
	// char *name = ttyname(1);
	char	*command_line;
	t_cmd	*commands;

	command_line = readline(getenv("USER")); //USER should be in global context
	commands = parse(command_line);
	execute_command_list(commands);
	printf( "%s\n", command_line);
	free(command_line);
	free_commands(commands);
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
