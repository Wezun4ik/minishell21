/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 02:54:50 by ilya              #+#    #+#             */
/*   Updated: 2022/10/26 14:15:44 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell minishell;

int	built_in_pwd(t_cmd *command)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (1);
	write(command->output, cwd, ft_strlen(cwd));
	free(cwd);
	return (0);
}

int	valid_key_value(char *arg)
{
	int	count;
	int	num_of_equals;

	count = 0;
	num_of_equals = 0;
	while (arg[count])
	{
		if (arg[count] == '=')
			num_of_equals++;
		count++;
	}
	if (num_of_equals != 1)
		return (0);
	count = 0;
	while (arg[count] && arg[count] != '=')
	{
		if (!(ft_isalnum(arg[count])) && arg[count] != '_' && arg[count] != '=')
			return (0);
		count++;
	}
	return (1);
}

void	export_one(char ***prev_env, char *env_var)
{
	char	*key;
	char	*pos;
	int		count;
	char	**new_env;
	int		sec_count;

	sec_count = 0;
	key = ft_strdup(env_var);
	pos = ft_strchr(key, '=');
	*pos = '\0';
	unset_one(prev_env, key);
	*pos = '=';
	count = 0;
	while ((*prev_env)[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (new_env == NULL)
	{
		perror("malloc");
		exit (1);
	}
	new_env[count + 1] = NULL;
	while (sec_count < count)
	{
		new_env[sec_count] = (*prev_env)[sec_count];
		sec_count++;
	}
	new_env[count] = key;
	free(*prev_env);
	*prev_env = new_env;
}

int	built_in_export(char ***prev_env, t_cmd *command)
{
	int	count;

	count = 1;
	while (command->args[count])
	{
		if (valid_key_value(command->args[count]))
			export_one(prev_env, command->args[count]);
		else
			perror("export");
		count++;
	}
	return (0);
}

int	built_in_cd(t_cmd *command)
{
	int		count;
	char	*arg;
	char	*dbl;

	count = 1;
	while (command->args[count])
		count++;
	if (count > 2)
	{
		perror("cd: invalid number of arguments");
		return (1);
	}
	if (count == 1)
	{
		arg = my_getenv(minishell.env, "HOME");
		if (!arg)
		{
			perror("cd: HOME is not set");
			return (1);
		}
	}
	else
		arg = command->args[1];
	if (chdir(arg))
	{
		perror("cd");
		return (1);
	}
	unset_one(&minishell.env, "OLDPWD");
	if (my_getenv(minishell.env, "PWD"))
	{
		arg = ft_strjoin("OLDPWD=", my_getenv(minishell.env, "PWD"));
		export_one(&minishell.env, arg);
		free(arg);
	}
	unset_one(&minishell.env, "PWD");
	arg = getcwd(NULL, 0);
	dbl = ft_strjoin("PWD=", arg);
	free(arg);
	export_one(&minishell.env, dbl);
	free(dbl);
	return (0);
}
