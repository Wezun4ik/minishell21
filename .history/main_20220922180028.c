/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:59:48 by ilya              #+#    #+#             */
/*   Updated: 2022/09/22 18:00:28 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*args_one[] = {"bin/ls", "-al", "/", 0};

t_cmd	first_arg = {0, 0, "/bin/ls", };

t_cmd	*parse(char *line)
{

}

void	handle_signals(int signo)
{
	(void)signo;
	write(1, "\n", 1); // Move to a new line
	rl_on_new_line(); // Regenerate the prompt on a newline
	rl_replace_line("", 0); // Clear the previous text
	rl_redisplay();
}

void	manage_command()
{
	// char *name = ttyname(1);
	char *command_line;

	command_line = readline(getenv("USER")); //USER should be in global context
	parse(command_line);
	printf( "%s\n", command_line);
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
