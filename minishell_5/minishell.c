/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmendelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 09:47:07 by dmendelo          #+#    #+#             */
/*   Updated: 2018/10/22 21:41:09 by dmendelo         ###   ########.fr       */
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


void			*write_error(char *err, size_t size)
{
	write(2, err, size);
	return (NULL);
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
//		printf("%s\n", env[p]);
		p += 1;
	}
	return (p);
}

void		free_2d(char **ptrs)
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
void		init_env(void)
{
	WOW();
	char			**env;
	int				len;
	int				p;

	p = 0;
	len = get_pointer_len(environ);
	env = malloc(sizeof(*env) * (len + 1));
	while (environ[p])
	{
		env[p] = strdup(environ[p]);
		if (!strncmp(env[p], "PATH", 4))
			g_PATH = env[p];
		p += 1;
	}
	env[p] = NULL;
	g_env = env;
	printf("g_env:\n");
	print_strings(g_env, 0);
	printf("path @ %s\n", g_PATH);
}

int			count_args(char *s)
{
	int				p;
	int				count;

	p = 0;
	count = 0;
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
			count += 1;
			p += 1;
			while (s[p] && s[p] != '"')
			{
				p += 1;
			}
			p += 1;
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

char		*search_env(char *name)
{
	WOW();
	int				p;

	p = 0;
	while (g_env[p])
	{
		printf("checking...\n%s->\n%s\n", name, g_env[p]);
		if (!strncmp(name, g_env[p], strlen(name)))
		{
			return (ft_strdup_range(g_env[p], strchr_index(g_env[p], '=') + 1, strlen(g_env[p]) - 1));
		}
		p += 1;
	}
	return (NULL);
}

void		expand_tilde(char **tilde)
{
	WOW();
	char			*tmp;
	char			*local;
	char			*new;
	int				p;

	if (!strncmp(*tilde, "~+", 2))
	{
		new = search_env("PWD");
		p = 2;
	}
	else if (!strncmp(*tilde, "~-", 2))
	{
		new = search_env("OLDPWD");
		p = 2;
	}
	else
	{
		new = search_env("HOME");
		p = 1;
	}
	printf("home = %s\n", new);
	printf("p = %d\n", p);
	printf("tilde = %s\n", *tilde);
	if (!(*tilde)[p])
	{
		printf("simple\n\n");
		free(*tilde);
		*tilde = new;
	}
	else if (strlen(*tilde) > p && (*tilde)[p] == '/')
	{
		printf("hum\n\n");
		tmp = ft_strdup_range(*tilde, strchr_index(*tilde, '/'), strlen(*tilde) - 1);
		printf("hum\n\n");
		free(*tilde);
		*tilde = trip_join(new, 0, tmp);
		free(new);
		free(tmp);
	}
	else
	{
		free(new);
	}
	printf("--------expansion = %s\n", *tilde);
}

char		**split_stream(char *s)
{
	WOW();
	char			**strings;
	int				p;
	int				sp;
	int				arg_count;
	int				begin;

	arg_count = count_args(s);
	printf("arg_count = %d\n", arg_count);
	strings = malloc(sizeof(*strings) * (arg_count + 1));
	p = 0;
	sp = 0;
	while (s[p])
	{
		printf("%s\n%*c\n", s, p - 1, s[p]);
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
				g_err_num = PAREN;
				return (write_error(MISSING_P, sizeof(MISSING_P)));
			}
			strings[sp] = ft_strdup_range(s, begin, p - 1);
			printf("strings[%d] = %s\n", sp, strings[sp]);
			sp += 1;
			p += 1;
		}
		else
		{
			begin = p;
			while (s[p] && s[p] != ' ' && s[p] != '\t')
			{
				p += 1;
			}
			strings[sp] = ft_strdup_range(s, begin, p - 1);
			if (strings[sp][0] == '~')
				expand_tilde(&strings[sp]);
			printf("strings[%d] = %s\n", sp, strings[sp]);
			sp += 1;
		}
	}
	strings[sp] = NULL;
	return (strings);
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
	if (args[1])
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

void		overwrite_env(char *name, char *value)
{
	WOW();
	char			**new;
	int				len;
	int				p;
	int				complete;

	complete = 0;
	len = get_pointer_len(g_env);
	new = malloc(sizeof(*new) * (len + 2));
	p = 0;
	while (g_env[p])
	{
		if (!strncmp(name, g_env[p], strlen(name)))
		{
			new[p] = trip_join(name, '=', value);
			complete = 1;
		}
		else
			new[p] = strdup(g_env[p]);
		if (!strncmp(new[p], "PATH", 4))
			g_PATH = new[p];
		p += 1;
	}
	if (!complete)
		new[p++] = trip_join(name, '=', value);
	new[p] = NULL;
	print_strings(new, 0);
	free_2d(g_env);
	g_env = new;
}

void		append_env(char *name, char *value)
{
	WOW();
	char			**new;
	int				len;
	int				p;
	int				path;

	p = 0;
	len = get_pointer_len(g_env);
	new = malloc(sizeof(*new) * (len + 2));
	while (g_env[p])
	{
		if (!strncmp(name, g_env[p], strlen(name)))
		{
			free(new);
			return ;
		}
		new[p] = strdup(g_env[p]);
		if (!strncmp(new[p], "PATH", 4))
			path = p;
		p += 1;
	}
	new[p++] = trip_join(name, '=', value);
	new[p] = NULL;
	print_strings(new, 0);
	free_2d(g_env);
	g_PATH = new[path];
	g_env = new;

}

void		ft_setenv(char **argv)
{
	int				argc;

	argc = get_pointer_len(argv);
	if (argc != 4)
	{
		g_err_num = ARG_ERR;
		return ;
	}
	if (strchr(argv[1], '=') || !strlen(argv[1]))
	{
		g_err_num = SETENV_INVAL;
		return ;
	}
	if (atoi(argv[3]))
	{
		overwrite_env(argv[1], argv[2]);
	}
	else
	{
		append_env(argv[1], argv[2]);
	}
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
	free_2d(g_env);
	g_env = new;
}

void		ft_unset_env(char **args)
{
	if (args[2])
	{
		write(2, ARGS, sizeof(ARGS));
		return ;
	}
	ft_remove_env_var(args[1]);
}

void		ft_env(char **args)
{
	WOW();
	if (args[1])
	{
		write(2, ARGS, sizeof(ARGS));
		return ;
	}
	print_strings(g_env, 0);
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

void		print_error(void)
{
	if (g_err_num == SETENV_INVAL)
		write_error(ARGS, sizeof(ARGS));
	else if (g_err_num == CD_ERR)
		return ;		
	else if (g_err_num == INVALID)
		write_error(INVALID_COMMAND, sizeof(INVALID_COMMAND));
	else if (g_err_num == SETENV_ERR)
		write_error(NULL_ARG, sizeof(NULL_ARG));
}

char		*search_dir(char *dir, char *command)
{
	DIR				*dirp;
	struct dirent	*entry;
	char			*path;

	dirp = opendir(dir);
	path = NULL;
	if (!dirp)
	{
//		closedir(dirp);
		return (path);
	}
	while ((entry = readdir(dirp)))
	{
		if (!strcmp(entry->d_name, command))
		{
			path = trip_join(dir, '/', entry->d_name);
		}
	}
	closedir(dirp);
	if (path)
		printf("found! -> %s\n", path);
	return (path);
}

char		*search_path_directories(char *command)
{
	int				p;
	char			**path_dirs;
	char			*tmp;
	char			*command_path;

	tmp = replace_char(g_PATH, ':', ' ');
	path_dirs = split_stream(tmp);
	print_strings(path_dirs, 0);
	free(tmp);
	p = 0;
	while (path_dirs[p])
	{
		if ((command_path = search_dir(path_dirs[p], command)))
			break ;
		p += 1;
	}
	free_2d(path_dirs);
	return (command_path);
}

void		search_path(char **argv)
{
	char			*command_path;

	command_path = search_path_directories(argv[0]);
	if (!command_path)
		g_err_num = INVALID;
	if (!access(command_path, X_OK))
	{
		execute(command_path, argv);
	}
	else
		g_err_num = INVALID;
	free(command_path);
}

void		parse(char *input)
{
	char			**args;
	int				command;

	args = split_stream(input);
	print_strings(args, 0);
	if (!access(args[0], X_OK))
 		execute(args[0], args);
	else if ((command = is_builtin(args[0])))
	{
		execute_builtin(command, args);
	}
	else
	{
		search_path(args);
	}
	free_2d(args);
}

void		read_line(void)
{
	char			buffer[1024];
	int				p;
	char			*input;

	p = 0;
	bzero(buffer, 1024);
	write(1, "?>", 2);
	while (read(0, &buffer[p], 1))
	{
		if (buffer[p] == '\n')
		{
			buffer[p] = '\0';
			break ;
		}
		p += 1;
	}
	if (p > 0)
	{
		if (!strncmp(buffer, "quit", 4) || !strncmp(buffer, "exit", 4))
			return ;
		input = strdup(buffer);
		parse(input);
		free(input);
	}
	read_line();
}

int			main(void)
{
	DIR				*dirp;
	struct dirent 	*entry;

	dirp = opendir(".");
	entry = readdir(dirp);
	printf("%s\n", entry->d_name);
	init_env();
	read_line();
	free_2d(g_env);
}
