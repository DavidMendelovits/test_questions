/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishel.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 08:16:15 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/15 08:55:59 by dmendelo         ###   ########.fr       */
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

#define WOW() printf("->%s\n", __func__)

typedef	enum
{
	MISSING_PAREN, 
	INVALID_COMMAND,
	ETC,
	GOOD
}			errnum;

char		*errors[4] = 
{
	"Error -> Missing Parenthesis/brackets\n",
	"Error -> Invalid Command\n",
	"etc\n",
	(NULL)
};
