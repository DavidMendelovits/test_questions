/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 08:18:33 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/15 09:57:46 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char		**environ;
int				g_error_num = GOOD;

void			print_strings(char **strings)
{
	int				p;

	p = 0;
	while (strings[p])
	{
		printf("[%d] -> %s\n", p, strings[p]);
		p += 1;
	}
}

int				strchr_index(const char *s, int c)
{
	WOW();
	int				i;

	while (s[i])
	{
		if (s[i] == c)
		{
			return (i);
		}
		i += 1;
	}
	return (0);	
}

char			*ft_strdup_range(const char *str, int begin, int end)
{
	WOW();
	int				p;
	char			*dup;
	int				dp;

	if (begin > end)
		return (NULL);
	p = begin;
	dup = malloc(sizeof(char) * (end - begin + 2));
	bzero(dup, end - begin + 2);
	dp = 0;
	while (p <= end)
	{
		dup[dp] = str[p];
		dp += 1;
		p += 1;
	}
	printf("dup = %s\n", dup);
	return (dup);
}

int				skip_whitespaces(const char *str, int p)
{
	WOW();
	while (str[p] && (str[p] == '\t' || str[p] == ' '))
	{
		p += 1;
		printf("%d\n", p);
		printf("stream[%d] = %c\n", p, str[p]);
	}
	printf("returns (%d) = %c\n", p, str[p]);
	return (p);
}

int				count_args(const char *stream)
{
	WOW();
	int				p;
	int				count;

	p = 0;
	count = 0;
	while (stream[p])
	{
		if (stream[p] == '"')
		{
			count += 1;
			p += 1;
			while (stream[p] && stream[p] != '"')
			{
				printf("etc\n");
				printf("%c\n", stream[p]);
				p += 1;
			}
			if (!stream[p])
			{
				g_error_num = MISSING_PAREN;
				return (0);
			}
			p += 1;
		}
		else if (stream[p] != ' ' && stream[p] != '\t')
		{
			count += 1;
			while (stream[p] && stream[p] != ' ' && stream[p] != '\t')
			{
				printf("lol\n");
				p += 1;
			}
		}
		else if (stream[p] == ' ' || stream[p] == '\t')
		{
			p = skip_whitespaces(stream, p);
		}
	}
	printf("returns (%d)\n", count);
	return (count);
}

char			**split_stream(const char *stream)
{
	WOW();
	char			**args;
	int				sp;
	int				ap;
	int				arg_count;
	int				begin;

	sp = 0;
	ap = 0;
	arg_count = count_args(stream);
	if (!arg_count)
		return (NULL);
	printf("arg count = %d\n", arg_count);
	args = malloc(sizeof(*args) * (arg_count + 1));
	while (stream[sp])
	{
		if (stream[sp] == '"')
		{
			begin = sp +1;
			sp += 1;
			while (stream[sp] && stream[sp] != '"')
			{
				sp += 1;
			}
			args[ap] = ft_strdup_range(stream, begin, sp - 1);
			ap += 1;
			sp += 1;
		}
		else if (stream[sp] != ' ' && stream[sp] != '\t')
		{
			begin = sp;
			while (stream[sp] && stream[sp] != ' ' && stream[sp] != '\t')
			{
				sp += 1;
			}
			args[ap] = ft_strdup_range(stream, begin, sp - 1);
			ap += 1;
		}
		else if (stream[sp] == ' ' || stream[sp] == '\t')
		{
			sp = skip_whitespaces(stream, sp);
		}
	}
	args[ap] = NULL;
	printf("end split stream\n");
	return (args);
	
}

char			*replace_char(char *str, int old, int new)
{
	WOW();
	int				p;
	char			*dup;

	dup = strdup(str);
	while (str[p])
	{
		if (str[p] == old)
		{
			dup[p] = new;
		}
		p += 1;
	}
	return (dup);
}

char			**isolate_path_dirs(void)
{
	WOW();
	int				ep;
	char			**path_dirs;
	char			*PATH;
	char			*tmp;

	ep = 0;
	while (environ[ep])
	{
		if (!strncmp(environ[ep], "PATH=", 5))
		{
			printf("hm\n");
			PATH = ft_strdup_range(environ[ep], 5, strlen(environ[ep]) - 1);
		}
		printf(" = %s\n", environ[ep]);
		ep += 1;
	}
	tmp = replace_char(PATH, ':', ' ');
	path_dirs = split_stream(tmp);
	free(tmp);
	free(PATH);
	return (path_dirs);
}

char			*str_join(char *a, char *b)
{
	WOW();
	char			*join;
	int				tmp;
	int				p;

	p = 0;
	tmp = 0;
	join = malloc(sizeof(char) * (strlen(a) + strlen(b) + 1));
	while (a[tmp])
	{
		join[p] = a[tmp];
		tmp += 1;
		p += 1;
	}
	tmp = 0;
	while (b[tmp])
	{
		join[p] = b[tmp];
		tmp += 1;
		p += 1;
	}
	join[p] = '\0';
	return (join);
}

char			*search_dir(char *dir, char *command)
{
	WOW();
	DIR				*dirp;
	struct dirent	*entry;
	char			*exe_path;
	char			*tmp;

	printf("searching %s\n", dir);
	dirp = opendir(dir);
	while ((entry = readdir(dirp)))
	{
		printf("%s ? %s\n", entry->d_name, command);
		if (!strcmp(command, entry->d_name))
		{
			tmp = str_join(dir, "/");
			exe_path = str_join(tmp, entry->d_name);
			free(tmp);
			closedir(dirp);
			return(exe_path);
		}
	}
	closedir(dirp);
	return (NULL);
}

char			*search_directories(char **dirs, char *command)
{
	WOW();
	int				p;
	char			*exe_path;

	p = 0;
	while (dirs[p])
	{
		exe_path = search_dir(dirs[p], command);
		if (exe_path)
			break ;
		p += 1;
	}
	if (exe_path)
		printf("exe_path = %s\n", exe_path);
	return (exe_path);
}

char			*find_executable(char *command)
{
	char			**path_dirs;
	char			*exe_path;

	path_dirs = isolate_path_dirs();
	print_strings(path_dirs);
	exe_path = search_directories(path_dirs, command);
	return ("placeholder");
}

void			execute_file(char *exe_path, char **args)
{
	int				pid;

	pid 
}

void			find_execute_command(char **arguments)
{
	char			*command_path;

	command_path = find_executable(arguments[0]);
	printf("exe_path = %s\n");
	execute_file(command_path, arguments);
}

void			parse_input(char *input)
{
	WOW();
	char			**arguments;

	arguments = split_stream(input);
	printf("split stream = \n");
	print_strings(arguments);
	find_execute_command(arguments);
}

void			read_line(void)
{
	char			buffer[1024];
	int				bp;
	char			*input;

	bzero(buffer, 1024);
	bp = 0;
	write(1, "-->", 3);
	while (read(0, &buffer[bp], 1))
	{
		if (buffer[bp] == '\n')
		{
			buffer[bp] = '\0';
			break;
		}
		bp += 1;
	}
	if (strstr(buffer, "exit"))
		return ;
	printf("input %s\n", buffer);
	input = strdup(buffer);
	parse_input(input);
	read_line();
}

int				main()
{
	read_line();
	return (0);
}
