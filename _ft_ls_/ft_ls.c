#include "ft_ls.h"
#define WOW() printf("->%s\n",__func__)

void                init_options(t_opt *o)
{
    WOW();
    o->l = 0;
    o->a = 0;
    o->r = 0;
    o->R = 0;
    o->t = 0;
}

void                add_path_front(t_list **head, char *path)
{
    WOW();
    t_list          *new;

    new = malloc(sizeof(t_list));
    new->path = strdup(path);
    new->prev = NULL;
    if (!(*head))
    {
        new->next = NULL;
        *head = new;
    }
    else
    {
        new->next = *head;
        (*head)->prev = new;
        *head = new;
    }
}

void                print_paths(t_list *paths)
{
    WOW();
    if (!paths)
    {
        return ;
    }
    if (paths->path)
    {
        printf("%s\n", paths->path);
    }
    if (paths->next)
    {
        print_paths(paths->next);
    }
}

int                 opt_check(t_opt *o, char *arg)
{
    WOW();
    int             i;

    i = 1;
    while (arg[i])
    {
        if (arg[i] == 'l')
        {
            o->l = 1;
        }
        else if (arg[i] == 'a')
        {
            o->a = 1;
        }
        else if (arg[i] == 'r')
        {
            o->r = 1;
        }
        else if (arg[i] == 'R')
        {
            o->R = 1;
        }
        else if (arg[i] == 't')
        {
            o->t = 1;
        }
        else
        {
            return (0);
        
		}
        i += 1;
    }
    return (1);
}

t_list              *split_options(t_opt *o, int argc, char **argv)
{
    WOW();
    t_list          *paths;
    int             i;

    i = 1;
    paths = NULL;
    while (i < argc)
    {
        if (argv[i][0] == '-')
        {
            if (!opt_check(o, argv[i]))
            {
				printf("invalid opt\n");
                return (NULL);
            }
        }
        else
        {
            add_path_front(&paths, argv[i]);
        }
        i += 1;
    }
	if (!paths)
	{
		add_path_front(&paths, ".");
	}
    return (paths);
}

void                add_entry_front(t_dir **head, char *filename)
{
    t_dir           *new;
    
    new = malloc(sizeof(t_dir));
    new->file = malloc(sizeof(t_file));
    new->prev = NULL;
    new->file->name = strdup(filename);
    if (!(*head))
    {
        new->next = NULL;
        *head = new;
    }
    else
    {
        new->next = *head;
        (*head)->prev = new;
        *head = new;
    }
}

t_dir               *read_entries(DIR *dirp, char *path, t_opt *o)
{
    struct dirent   *entry;
    t_dir           *dir;

    dir = NULL;
    while ((entry = readdir(dirp)))
    {
        if (entry->d_name[0] != '.' || o->a)
            add_entry_front(&dir, entry->d_name);
    }
    return (dir);
}

t_dir				*read_dir(char *path, t_opt *o)
{
	DIR				*dirp;
	t_dir			*dir;

	dir = NULL;
	dirp = opendir(path);
	if (!dirp && errno == ENOENT)
	{
		printf("invalid path!\n");
		return (NULL);
	}
	else if (!dirp && errno == ENOTDIR)
	{
		printf("%s is file, not dir\n", path);
		add_entry_front(&dir, path);
		return (dir);
	}
	else if (dirp)
	{
		dir = read_entries(dirp, path, o);
	}
    return (dir);
}

void                print_entries(t_dir *dir)
{
    if (!dir)
    {
        return ;
    }
    if (dir->file->name)
    {
        printf("%s\n", dir->file->name);
    }
    if (dir->next)
    {
        print_entries(dir->next);
    }
}

char                *path_join(char *path, char *filename)
{
    WOW();
    char            *ret;
    int             i;
    int             j;

    ret = malloc(sizeof(char) * (strlen(path) + strlen(filename) + 2));
    i = 0;
    j = 0;
    while (path[j])
    {
        ret[i] = path[j];
        i += 1;
        j += 1;
    }
    ret[i++] = '/';
    j = 0;
    while (filename[j])
    {
        ret[i] = filename[j];
        i += 1;
        j += 1;
    }
    ret[i] = '\0';
    return (ret);
}


void                read_mode(t_dir **entry, struct stat buf)
{
    WOW();
    memset((*entry)->file->permissions, '-', 10);
    (*entry)->file->permissions[10] = '\0';
    if (S_ISDIR(buf.st_mode))
    {
        (*entry)->file->permissions[0] = 'd';
    }
    if (buf.st_mode & S_IRUSR)
    {
        (*entry)->file->permissions[1] = 'r';
    }
    if (buf.st_mode & S_IWUSR)
    {
        (*entry)->file->permissions[2] = 'w';
    }
    if (buf.st_mode & S_IXUSR)
    {
        (*entry)->file->permissions[3] = 'x';
    }
    if (buf.st_mode &  S_IRGRP)
    {
        (*entry)->file->permissions[4] = 'r';
    }
    if (buf.st_mode & S_IWGRP)
    {
        (*entry)->file->permissions[5] = 'w';
    }
    if (buf.st_mode & S_IXGRP)
    {
        (*entry)->file->permissions[6] = 'x';
    }
    if (buf.st_mode & S_IROTH)
    {
        (*entry)->file->permissions[7] = 'r';
    }
    if (buf.st_mode & S_IWOTH)
    {
        (*entry)->file->permissions[8] = 'w';
    }
    if (buf.st_mode & S_IXOTH)
    {
        (*entry)->file->permissions[9] = 'x';
    }
}

void                read_uid_gid(t_dir **entry, struct stat buf)
{
    WOW();
    struct passwd   *uid;
    struct group    *gid;

    uid = getpwuid(buf.st_uid);
    (*entry)->file->uid = strdup(uid->pw_name);
    gid = getgrgid(buf.st_gid);
    (*entry)->file->gid = strdup(gid->gr_name);
}

void                read_size(t_dir **entry, struct stat buf)
{
    WOW();
    (*entry)->file->size = (size_t)buf.st_size;
}

void                read_time(t_dir **entry, struct stat buf)
{
    WOW();
    (*entry)->file->time = buf.st_mtime;
    (*entry)->file->formatted_time = strndup(ctime(&buf.st_mtime), 16);
}


void                read_links(t_dir **entry, struct stat buf)
{
    (*entry)->file->links = buf.st_nlink;
}

void                read_details(char *path, t_dir **dir, t_opt *o)
{
    WOW();
    char            *complete_path;
    t_dir           *tmp;
    struct stat     buf;

    tmp = *dir;
    while (tmp)
    {
        complete_path = path_join(path, tmp->file->name);
        printf("complete path: %s\n", complete_path);
        lstat(complete_path, &buf);
        read_mode(&tmp, buf);
        read_links(&tmp, buf);
        read_uid_gid(&tmp, buf);
        read_size(&tmp, buf);
        read_time(&tmp, buf);
        tmp = tmp->next;
    }
}

void            print_long(t_dir *entries)
{
    static int start = 1;
    if (start)
    {
        WOW();
        start = 0;
    }
    printf("%s ", entries->file->permissions);
    printf("%ld ", entries->file->links);
    printf("%s ", entries->file->uid);
    printf("%s ", entries->file->gid);
    printf("%ld ", entries->file->size);
    printf("%s ", entries->file->formatted_time);
    printf("%s\n", entries->file->name);
    if (entries->next)
    {
        print_long(entries->next);
    }
}
void                swap_nodes(t_file **a, t_file **b)
{
    WOW();
    t_file          *tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

void                sort_lex(t_dir **head, t_opt *o)
{
    WOW();
    t_dir           *tmp;
    int             sorted;


    sorted = 0;
    while (!sorted)
    {
        sorted = 1;
        tmp = *head;
        while (tmp->next)
        {
            if (strcmp(tmp->file->name, tmp->next->file->name) > 0 && !o->r)
            {
                swap_nodes(&tmp->file, &tmp->next->file);
                sorted = 0;
            }
            else if (strcmp(tmp->file->name, tmp->next->file->name) < 0 && o->r)
            {
                swap_nodes(&tmp->file, &tmp->next->file);
                sorted = 0;
            }
            tmp = tmp->next;
        }
    }
}

void                sort_time(t_dir **head, t_opt *o)
{
    WOW();
    t_dir           *tmp;
    int             sorted;

    sorted = 0;
    while (!sorted)
    {
        sorted = 1;
        tmp = *head;
        while (tmp->next)
        {
            if (tmp->file->time < tmp->next->file->time && !o->r)
            {
                swap_nodes(&tmp->file, &tmp->next->file);
                sorted = 0;
            }
            else if (tmp->file->time > tmp->next->file->time && o->r)
            {
                swap_nodes(&tmp->file, &tmp->next->file);
                sorted = 0;
            }
            tmp = tmp->next;
        }
    }
}

void                sort_dir(t_dir **head, t_opt *o)
{
    WOW();
    if (o->t)
    {
        sort_time(head, o);
    }
    else
    {
        sort_lex(head, o);
    }

}


void                do_recursion(t_dir *dir, t_opt *o, char *path)
{
    WOW();
    char        *_path;

    while (dir)
    {
        if (dir->file->permissions[0] == 'd')
        {
            _path = path_join(path, dir->file->name);
            ft_ls(_path, o);
        }
        dir = dir->next;
    }
}

int					ft_ls(char *path, t_opt *o)
{
    WOW();
    printf("path: %s\n", path);
	t_dir			*dir;

	dir = read_dir(path, o);
    sort_dir(&dir, o);
    if (o->l)
    {
        read_details(path, &dir, o);
        print_long(dir);
    }
    else
        print_entries(dir);
    if (o->R)
    {
        do_recursion(dir, o, path);
    }
    return (1);
}

void				queue_paths(t_list *paths, t_opt *o)
{
	WOW();
	if (!paths)
	{
		return ;
	}
	if (paths->path)
	{
		ft_ls(paths->path, o);
	}
	if (paths->next)
	{
		queue_paths(paths->next, o);
	}
}

int                 main(int argc, char **argv)
{
    t_opt           options;
    t_list          *paths;

    init_options(&options);
    printf("argc: %d\n", argc);
    if (argc == 1)
    {
        ft_ls(".", &options);
    }
    else
    {
        paths = split_options(&options, argc, argv);
        print_paths(paths);
		if (paths)
		{
			queue_paths(paths, &options);
		}
		else
		{
			return (1);
		}
    }
    return (0);
}
