/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 09:41:44 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/19 12:44:49 by dmendelo         ###   ########.fr       */
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
		printf("%s\n", strings[p]);
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

char		*trip_join(const char *s1, const char c, const char *s2)
{
	WOW();
	char			*new;
	int				tmp;
	int				p;

	new = malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 2));
	tmp = 0;
	p = 0;
	while (s1[tmp])
	{
		new[p] = s1[tmp];
		p += 1;
		tmp += 1;
	}
	if (c)
	{
		new[p++] = c;
	}
	tmp = 0;
	while (s2[tmp])
	{
		new[p] = s2[tmp];
		p += 1;
		tmp += 1;
	}
	new[p] = '\0';
	return (new);
}

char		*replace_char(char *s, int old, int new)
{
	WOW();
	char			*ret;
	int				p;

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

int			get_pointer_len(char **env)
{
	WOW();
	int				p;

	p = 0;
	while (env[p])
	{
		printf("%s\n", env[p]);
		p += 1;
	}
	return (p);
}

int			get_arg_count(char *s)
{
	WOW();
	int				p;
	int				count;

	count = 0;
	p = 0;
	while (s[p])
	{
		if (s[p] == ' ' || s[p] == '\t')
		{
			while (s[p] && (s[p] == ' ' || s[p] == '\t'))
			{
				p += 1;
			}
		}
		else
		{
			count += 1;
			while (s[p] && s[p] != ' ' && s[p] != '\t')
			{
				p += 1;
			}
		}
	}
	return (count);
}

char		**split_stream(char *s)
{
	WOW();
	char			**strings;
	int				p;
	int				sp;
	int				arg_count;
	int				begin;

	arg_count = get_arg_count(s);
	printf("arg_count = %d\n", arg_count);
	strings = malloc(sizeof(*strings) * (arg_count + 1));
	p = 0;
	sp = 0;
	while (s[p])
	{
		if (s[p] == ' ' || s[p] == '\t')
		{
			while (s[p] && (s[p] == ' ' || s[p] == '\t'))
			{
				p += 1;
			}
		}
		else if (s[p] == '"')
		{
			begin = ++p;
			while (s[p] && s[p] != '"')
			{
				p += 1;
			}
			if (!s[p])
			{
				write(2, MISSING_P, sizeof(MISSING_P));
				g_err_num = PAREN;
				return (NULL);
			}
			strings[sp] = ft_strdup_range(s, begin, p - 1);
			sp += 1;
			p += 1;
		}
		else
		{
			begin = p;
			while (s[p] && s[p] != '"' && s[p] != ' ' && s[p] != '\t')
			{
				p += 1;
			}
			strings[sp] = ft_strdup_range(s, begin, p - 1);
			sp += 1;
		}
	}
	strings[sp] = NULL;
	return (strings);
}

char		**split_path(char *old)
{
	WOW();
	char			*tmp;
	int				p;
	char			**new;

	p = strchr_index(old, '=');
	tmp = ft_strdup_range(old, p + 1, strlen(tmp) - 1);
	new = split_stream(tmp);
	free(tmp);
	return (new);
}

void		init_env_path(void)
{
	WOW();
	char			**env;
	int				p;
	int				env_len;

	p = 0;
	env_len = get_pointer_len(environ);
	env = malloc(sizeof(*env) * (env_len + 1));
	while (environ[p])
	{
		env[p] = strdup(environ[p]);
		if (!strncmp(env[p], "PATH", 4))
		{
			g_PATH = env[p];
		}
		p += 1;
	}
	env[p] = NULL;
	g_env = env;
	printf("%p -> %p\n", env, g_env);
	printf("PATH:\n%s", g_PATH);
	printf("ENV:\n");
	print_strings(g_env, 0);
}

int			is_builtin(char *arg1)
{
	WOW();
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
	WOW();
	print_args(args, 1);
	printf("\n");
}

void		ft_cd(char **args)
{
	WOW();
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
/*
void		ft_set_path(char *value)
{
	WOW();
	char			*new;
	int				p;
	int				begin;
	char			*tmp;

	p = strchr_index(*g_PATH_addr, '=') - 1;
	tmp = ft_strdup_range(*g_PATH_addr, 0, p);
	new = trip_join(tmp, '=', value);
	free(tmp);
	free(*g_PATH_addr);
	g_PATH_addr = &new;
}
*/
void		free_2d_ptr(char **ptrs)
{
	WOW();
	int				p;
	int				len;

	len = get_pointer_len(ptrs);
	p = 0;
	while (ptrs[p] && p < len)
	{
		printf("%s\n", ptrs[p]);
		if (ptrs[p])
			free(ptrs[p]);
		p += 1;
	}
	printf("2\n");
	printf("%p\n", ptrs);
	free(ptrs);
}

void		ft_overwrite_env(char *name, char *value)
{
	WOW();
	char			**new;
	int				len;
	int				p;
	int				nlen;
	int				complete;

	len = get_pointer_len(g_env);
	nlen = strlen(name);
	new = malloc(sizeof(*new) * (len + 2));
	p = 0;
	complete = 0;
	while (g_env[p])
	{
		if (!strncmp(g_env[p], name, nlen))
		{
			new[p] = trip_join(name, '=', value);
			if (!strncmp(new[p], "PATH", 4))
				g_PATH = new[p];
			complete = 1;
		}
		else
		{
			new[p] = strdup(g_env[p]);
		}
		p += 1;
	}
	if (!complete)
	{
		new[p++] = trip_join(name, '=', value);
	}
	new[p] = NULL;
	free_2d_ptr(g_env);
	g_env = new;
}

void		ft_append_env(char *name, char *value)
{
	WOW();
	char			**new;
	int				len;
	int				nlen;
	int				p;

	p = 0;
	len = get_pointer_len(g_env);
	nlen = strlen(name);
	new = malloc(sizeof(*new) * (len + 2));
	while (g_env[p])
	{
		if (!strncmp(g_env[p], name, nlen))
		{
			free_2d_ptr(new);
			return ;
		}
		else
		{
			new[p] = strdup(g_env[p]);
		}
		p += 1;
	}
	new[p++] = trip_join(name, '=', value);
	new[p] = NULL;
	free_2d_ptr(g_env);
	g_env = new;
}

void		ft_setenv(char **args)
{
	WOW();
	if (get_pointer_len(args) > 4)
	{
		write(2, TOO_MANY_ARGS, sizeof(TOO_MANY_ARGS));
		g_err_num = SETENV;
		return ;
	}
	if (!strcmp(args[1], "PATH") && atoi(args[3]))
	{
		ft_overwrite_env(args[1], args[2]);
	}
	else if (atoi(args[3]))
	{
		ft_overwrite_env(args[1], args[2]);
	}
	else
	{
		ft_append_env(args[1], args[2]);
	}
}

void		ft_env(char **args)
{
	WOW();
	if (args[1])
	{
		write(2, TOO_MANY_ARGS, sizeof(TOO_MANY_ARGS));
		return ;
	}
	print_strings(g_env, 0);
}

void		ft_remove_env_var(char *name)
{
	char			**new;
	int				len;
	int				nlen;
	int				p;
	int				ep;

	nlen = strlen(name);
	len = get_pointer_len(g_env);
	printf("hmm\n");
	new = malloc(sizeof(*new) * (len + 1));
	p = 0;
	ep = 0;
	while (g_env[ep])
	{
		if (strncmp(g_env[ep], name, nlen))
		{
			new[p++] = strdup(g_env[ep]);
		}
		ep += 1;
	}
	new[p] = NULL;
	free_2d_ptr(g_env);
	g_env = new;
}

void		ft_unset_env(char **args)
{
	if (args[2])
	{
		write(2, TOO_MANY_ARGS, sizeof(TOO_MANY_ARGS));
		return ;
	}
	ft_remove_env_var(args[1]);
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
		ft_setenv(argv);
	}
	else if (command == UNSETENV)
	{
		ft_unset_env(argv);
	}
	else if (command == ENV)
	{
		ft_env(argv);
	}

}

char		*search_dir(char *command, char *dir)
{
	DIR				*dirp;
	struct dirent	*entry;
	char			*exe_path;

	exe_path = NULL;
	dirp = opendir(dir);
	if (!dirp)
		return (exe_path);
	while ((entry = readdir(dirp)))
	{
		if (!strcmp(command, entry->d_name))
		{
			exe_path = trip_join(dir, '/', entry->d_name);
		}
	}
	return (exe_path);
}

char		*search_directories(char *command, char **paths)
{
	int				p;
	char			*exe_path;

	p = 0;
	exe_path = NULL;
	while (paths[p] && !exe_path)
	{
		exe_path = search_dir(command, paths[p]);
		p += 1;
	}
	return (exe_path);
}

void 		execute(char *path, char **argv)
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

int			execute_path(char **args)
{
	char			*path;
	char			**paths;
	char			*tmp;

	tmp = replace_char(g_PATH, ':', ' ');
	paths = split_stream(tmp);
	print_strings(paths, 0);
	free(tmp);
	path = search_directories(args[0], paths);
	if (path)
	{
		printf("found! -> %s\n", path);
		execute(path, args);
		return (1);
	}
	return (0);
}

int			expand_arg(char **argv)
{
//	if (argv[0][0] == '~')
//	{
//		if (!tilde_expansion(arg
//	}
	return (1);
}

void		read_input(char *stream)
{
	WOW();
	char			**args;
	int				COMMAND;

	if (!(*stream))
		return ;
	args = split_stream(stream);
	if ((COMMAND = is_builtin(args[0])))
	{
		execute_builtin(COMMAND, args);
	}
	else
	{
		if (!execute_path(args) && !expand_arg(args))
		{
			g_err_num = INVALID;
			write(2, INVALID_COMMAND, sizeof(INVALID_COMMAND));
			return ;
		}
	}
}

void		read_line(void)
{
	WOW();
	char			buffer[1024];
	int				p;
	char			*input;

	write(1, "->", 2);
	bzero(buffer, 1024);
	p = 0;
	while (read(0, &buffer[p], 1))
	{
		if (buffer[p] == '\n')
		{
			buffer[p] = '\0';
			break ;
		}
		p += 1;
	}
	if (!strncmp(buffer, "quit", 4) || !strncmp(buffer, "exit", 4))
	{
		return ;
	}
	input = strdup(buffer);
	read_input(input);
	read_line();
}

int			main(void)
{
	init_env_path();
	read_line();
	return (0);
}
