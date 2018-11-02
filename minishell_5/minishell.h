/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 09:42:38 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/22 15:47:09 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <signal.h>
#include <strings.h>
#include <string.h>
#include <assert.h>

#define WOW() printf("->%s\n", __func__)

extern char	**environ;

char		*g_PATH;
char		**g_env;


typedef enum
{
	ZERO,
	ECHO,
	CD,
	SETENV,
	UNSETENV,
	ENV
}		t_builtins;

unsigned int g_err_num;

typedef enum
{
	CLEAN,
	PAREN,
	INVALID,
	CD_ERR,
	SETENV_ERR,
	ARG_ERR,
	SETENV_INVAL
}		t_errors;

#define INVALID_P "Error! -> Invalid Parameteres\n"
#define MISSING_P "Error! -> missing parenthesis\n"
#define INVALID_COMMAND "Error! -> Invalid Command\n"
#define CD_NOTINPWD "cd: string not in pwd: "
#define INVALID_DIR "cd: no such file or directory: "
#define ARGS "Error! -> invalid number of arguments\n"
#define NULL_ARG "Error -> can't take empty argument\n"
