/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:59:48 by ilya              #+#    #+#             */
/*   Updated: 2022/09/23 17:24:55 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*args_one[] = {"/bin/ls", "-al", "/", NULL};

t_cmd	first_arg = {0, 0, "/bin/ls", args_one, NULL, NULL};

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

void	fork_and_dup(int cmd_list_len)
{
	int	(*pipes_list)[2];


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
