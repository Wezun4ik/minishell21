/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 03:03:26 by ilya              #+#    #+#             */
/*   Updated: 2022/10/26 14:17:55 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell minishell;

int	built_in_echo(t_cmd *command)
{
	int		count;
	int		new_line;

	count = 1;
	new_line = 1;
	while (command->args[count])
	{
		if (count != 1 && !(count == 2 && new_line == 0))
			write(command->output, " ", 1);
		if (count == 1 && !ft_strncmp(command->args[count], "-n", 3))
			new_line = 0;
		else
			write(command->output, command->args[count], ft_strlen(command->args[count]));
		count++;
	}
	if (new_line)
		write(command->output, "\n", 1);
	return (0);
}

int	valid_arg(char *arg)
{
	while (*arg)
	{
		if (!ft_isalnum(*arg) && *arg != '_')
			return (0);
		arg++;
	}
	return (1);
}

char	*my_special_getenv(char **env, char *key)
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
			return (env[count]);
		}
		count++;
	}
	free(key_copy);
	return (NULL);
}

int	unset_one(char ***prev_env, char *env_var)
{
	int		count;
	char	**new_env;
	char	*to_unset;
	int		sec_count;

	count = 0;
	sec_count = 0;
	to_unset = my_special_getenv(*prev_env, env_var);
	while ((*prev_env)[count])
		count++;
	if (!to_unset || count == 0)
		return (0);
	new_env = malloc(sizeof(char *) * (count));
	new_env[count - 1] = NULL;
	if (!new_env)
	{
		perror("malloc unset_one");
		exit (1);
	}
	count = 0;
	while ((*prev_env)[count])
	{
		if ((*prev_env)[count] != to_unset)
		{
			new_env[sec_count] = (*prev_env)[count];
			sec_count++;
		}
		else
			free((*prev_env)[count]);
		count++;
	}
	count = 0;
	free(*prev_env);
	*prev_env = new_env;
	return (0);
}

int	built_in_unset(char ***prev_env, t_cmd *command)
{
	int	count;

	count = 1;
	while (command->args[count])
	{
		if (valid_arg(command->args[count]))
			unset_one(prev_env, command->args[count]);
		else
			perror("unset");
		count++;
	}
	return (0);
}
