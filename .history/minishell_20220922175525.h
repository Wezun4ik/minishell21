/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 20:07:54 by ilya              #+#    #+#             */
/*   Updated: 2022/09/22 17:55:25 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "./libft/libft.h"

# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

enum e_type
{
	simple_command,
	built_in_command
};

/* структура из результатов парсинга. из них нужно будет сделать склейку с переменными окружения для запуска в execve() */
typedef struct		s_cmd
{
	int				str_len;	//длина строки команды. пригодится, когда нужно будет перебирать с вариантами окружения
	int				ind;		//индекс. пока не уверен, что понадобилтся, но проще его будет просто убрать
	char			*str_cmd;	//сама команда, с относительным/абсолютным/кратким путем
	char			**args;
	struct s_cmd	*next;
	struct s_cmd	*prev;		//пока список двусвязный. снова же, можно будет просто удалить обратный ход
}					t_cmd;

typedef struct		s_minishell
{
	char			*pwd;				//директория
	t_cmd			*commands;			//список команд
	pid_t			*processes_pids;	//набор pid_t запущенных процессов; тип скорее всего изменится
}					t_minishell;


#endif
