/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 11:31:52 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/19 09:13:27 by dmendelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			print_args(char **strings, int p)
{
	if (!strings)
		return ;
	if (strings[p])
	{
		printf("%s ", strings[p]);
	}
	if (strings[p + 1])
	{
		print_args(strings, p + 1);
	}
}

void			print_strings(char **strings, int p)
{
	if (!strings)
		return ;
	if (strings[p])
	{
		printf("[%d] -> %s\n", p, strings[p]);
	}
	if (strings[p + 1])
	{
		print_strings(strings, p + 1);
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

char		*replace_char(char *s, int old, int new)
{
	WOW();
	char		*ret;
	int			p;

	ret = strdup(s);
	p = 0;
	while (s[p])
	{
		if (s[p] == old)
		{
			ret[p] = new;
		}
		p += 1;
	}
	return (ret);
}

int			count_args(char *s)
{
	WOW();
	int			count;
	int			p;
	int			len;

	len = strlen(s);
	printf("len = %d\n", len);
	p = 0;
	count = 0;
	while (s[p] && p < len)
	{
	//	printf("s[%d] = %c\n", p, s[p]);
		assert(p < len);
		if (s[p] == ' ' || s[p] == '\t')
		{
			while (s[p] && (s[p] == ' ' || s[p] == '\t'))
			{
				p += 1;
			}
		}
		else if (s[p] != ' ' && s[p] != '\t')
		{
			count += 1;
			while (s[p] && s[p] != ' ' && s[p] != '\t')
			{
				p += 1;
			}
		}
		else
			p += 1;
	}
	return (count);
}

char		**split_stream(char *s)
{
	WOW();
	char		**strings;
	int			p;
	int			sp;
	int			arg_count;
	int			begin;

	arg_count = count_args(s);
	printf("arg count = %d\n", arg_count);
	strings = malloc(sizeof(char *) * (arg_count + 1));
	p = 0;
	sp = 0;
	while (s[p])
	{
		if (s[p] == ' '|| s[p] == '\t')
		{
			while (s[p] && (s[p] == ' ' || s[p] == '\t'))
			{
				p += 1;
			}
		}
		else if (s[p] == '"')
		{
			p += 1;
			begin = p;
			while (s[p] && s[p] != '"')
			{
				p += 1;
			}
			if (!s[p])
			{
				write(2, MISSING_P, sizeof(MISSING_P));
			}
		}
		else
		{
			begin = p;
			while (s[p] && s[p] != ' ' && s[p] != '\t')
			{
				p += 1;
			}
			strings[sp] = ft_strdup_range(s, begin, p - 1);
			printf("strings[%d] = %s\n", sp, strings[sp]);
			sp += 1;
		}
	}
	strings[sp] = NULL;
	return (strings);
}

char		*strcharstr_join(char *parent, char *child, int _char)
{
	char			*path;
	int				p;
	int				tmp;

	printf("parent = %s\nchild = %s\n", parent, child);
	path = malloc(sizeof(char) * strlen(parent) + strlen(child) + 2);
	p = 0;
	tmp = 0;
	while (parent[tmp])
	{
		path[p] = parent[tmp];
		tmp += 1;
		p += 1;
	}
	path[p++] = _char;
	tmp = 0;
	while (child[tmp])
	{
		path[p] = child[tmp];
		p += 1;
		tmp += 1;
	}
	path[p] = '\0';
	return (path);
}
int			is_builtin(char *arg1)
{
	if (!strcmp(arg1, "echo"))
	{
		return (ECHO);
	}
	else if (!strcmp(arg1, "cd"))
	{
		return (CD);
	}
	else if (!strcmp(arg1, "setenv"))
	{
		return (SETENV);
	}
	else if (!strcmp(arg1, "unsetenv"))
	{
		return (UNSETENV);
	}
	else if (!strcmp(arg1, "env"))
	{
		return (ENV);
	}
	return (0);
}

void		ft_echo(char **args)
{
	print_args(args, 1);
	printf("\n");
}

void		ft_cd(char **args)
{
	if (args[2])
	{
		write(2, CD_NOTINPWD, sizeof(CD_NOTINPWD));
		printf("%s\n", args[2]);
		g_err_num = CD_ERR;
		return ;
	}
	if (chdir(args[1]))
	{
		write(2, INVALID_DIR, sizeof(INVALID_DIR));
		printf("%s\n", args[1]);
		g_err_num = CD_ERR;
	}
	return ;
}

int			get_env_len(char **env)
{
	int			p;

	while (env[p])
	{
		p += 1;
	}
	return (p);
}

char		**copy_replace_env(char **env, char *name, char *value)
{
	int			p;
	char		**new;
	char		*tmp;
	int			env_len;

	env_len = get_env_len(env);
	new = malloc(sizeof(char *) * (env_len + 1));
	p = 0;
	while (env[p])
	{
		if (!strncmp(env[p], name, strlen(name)))
		{
			new[p] = strndup(env[p], strlen(name));
			tmp = strcharstr_join(new[p], value, '=');
			free(new[p]);
			new[p] = strdup(tmp);
			free(tmp);
		}
		else
			new[p] = strdup(env[p]);
		p += 1;
	}
	new[p] = NULL;
	return (new);
}

char		**append_var_env(char **env, char *name, char *value)
{
	int			p;
	char		**new;
	char		*tmp;
	int			env_len;

	env_len = get_env_len(env);
	new = malloc(sizeof(char *) * (env_len + 2));
	p = 0;
	while (env[p])
	{
		new[p] = strdup(env[p]);
		p += 1;
	}
	new[p++] = strcharstr_join(name, value, '=');
	new[p] = NULL;
	return (new);
}

int			check_env(char *name)
{
	int			p;

	p = 0;
	while (environ[p])
	{
		if (strncmp(environ[p], name, strlen(name)))
		{
			return (1);
		}
		p += 1;
	}
	return (0);
}

void		ft_setenv(char **argv)
{
	int			env_len;
	char		**new_env;
	int			overwrite;

	if (argv[4])
	{
		write(2, TOO_MANY_ARGS, sizeof(TOO_MANY_ARGS));
		g_err_num = SETENV_ERR;
		return ;
	}

	overwrite = atoi(argv[3]);
	if (check_env(argv[1]) && overwrite)
	{
		new_env = copy_replace_env(environ, argv[1], argv[2]);
	}
	else
	{
		new_env = append_var_env(environ, argv[1], argv[2]);
	}
	print_strings(new_env, 0);
}

void		execute_builtin(int command, char **argv)
{
	WOW();
	if (command == ECHO)
	{
		ft_echo(argv);
	}
	else if (command == CD)
	{
		ft_cd(argv);
	}
	else if (command == SETENV)
	{
//		ft_setenv(argv);
	}
	else if (command == UNSETENV)
	{
//		ft_unset_env(argv);
	}
	else if (command == ENV)
	{
//		ft_env(argv);
	}
}

char		*search_dir(char *dir, char *command)
{
	DIR				*dirp;
	struct dirent	*entry;
	char			*ret;

	ret = NULL;
	dirp = opendir(dir);
	printf("searching %s...\n", dir);
	while ((entry = readdir(dirp)))
	{
		printf("%s ? %s\n", entry->d_name, command);
		if (!strcmp(entry->d_name, command))
		{
			ret = strcharstr_join(dir, entry->d_name, '/');
			break ;
		}
	}
	closedir(dirp);
	return (ret);
}

char		*search_directories(char *command)
{
	int			p;
	char		*exe_path;

	exe_path = NULL;
	p = 0;
	while (g_path[p] && !exe_path)
	{
		exe_path = search_dir(g_path[p], command);
		p += 1;
	}
	return (exe_path);
}

void		execute(char *path, char **argv)
{
	int			pid;
	int			status;

	pid = fork();
	if (pid == 0)
	{
		execve(path, argv, environ);
		_exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		status = -1;
	}
	else
	{
		if (waitpid(pid, &status, 0) != pid)
		{
			status = 1;
		}
		return ;
	}
}

int			execute_PATH(char **argv)
{
	char		*exe_path;

	exe_path = search_directories(argv[0]);
	if (!exe_path)
	{
		return (0);
	}
	else
		printf("found -> %s\n", exe_path);
	execute(exe_path, argv);
	return (1);
}

void		execute_input(char *input)
{
	WOW();
	printf("input = %s\n", input);

	char		**args;
	int			command;

	args = split_stream(input);
	if ((command = is_builtin(args[0])))
	{
		execute_builtin(command, args);
	}
	else
	{
		if (!execute_PATH(args))
		{
			write(2, INVALID_COMMAND, sizeof(INVALID_COMMAND));
			g_err_num = INVALID;
			return ;
		}
	}
}

void		read_line(void)
{
	char		buffer[1024];
	int			p;
	char		*input;

	bzero(buffer, 1024);
	p = 0;
	write(1, "->", 2);
	while (read(0, &buffer[p], 1))
	{
		if (buffer[p] == '\n')
		{
			buffer[p] = '\0';
			break ;
		}
		p += 1;
	}
	input = strdup(buffer);
	if (!strncmp(input, "quit", 4) || !strncmp(input, "exit", 4))
	{
		return ;
	}
	execute_input(input);
	read_line();
}

void		get_path(void)
{
	WOW();
	char		**path;
	int			ep;
	char		*_path;
	char		*tmp;

	ep = 0;
	while (environ[ep])
	{
		printf("environ[%d] = %s\n", ep, environ[ep]);
		if (!strncmp(environ[ep], "PATH", 4))
		{
			break ;
		}
		ep += 1;
	}
	_path = ft_strdup_range(environ[ep], strchr_index(environ[ep], '=') + 1, strlen(environ[ep]) - 1);
	printf("_path = %s\n", _path);
	tmp = replace_char(_path, ':', ' ');
	printf("_path = %s\n", tmp);
	path = split_stream(tmp);
	printf("PATH:\n\n");
//	print_strings(path);
	free(tmp);
	free(_path);
	g_path = path;
}

int			main(void)
{
	get_path();
	printf("g_PATH\n\n");
	print_strings(g_path, 0);
	read_line();
	return (0);
}
