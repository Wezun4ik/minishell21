/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mproveme <mproveme@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 20:07:54 by ilya              #+#    #+#             */
/*   Updated: 2022/08/08 14:18:50 by mproveme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "./libft/libft.h"

# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>

typedef struct s_command_list
{
	int		type;
	char	*message;
}				t_command_list;

/* структура из результатов парсинга. из них нужно будет сделать склейку с переменными окружения для запуска в execve() */
typedef struct s_cmd
{
	int				str_len;	//длина строки команды. пригодится, когда нужно будет перебирать с вариантами окружения
	int				ind;		//индекс. пока не уверен, что понадобилтся, но проще его будет просто убрать
	char			*str_cmd;	//сама команда, с относительным/абсолютным/кратким путем
	struct s_cmd	*next;		
	struct s_cmd	*prev;		//пока список двусвязный. снова же, можно будет просто удалить обратный ход
}	t_cmd;

#endif