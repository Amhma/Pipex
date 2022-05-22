#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "libft.h"


//===================================================================//
//						PARSE.C
//===================================================================//

void	clear_lst(t_list **cmd, int	*fd_file)
{
	close(fd_file[0]);
	close(fd_file[1]);
	ft_lstclear(cmd, &free);
	exit(EXIT_FAILURE);
}	

void	open_file(int ac, char **av, int *fd_in, int *fd_out)
{
	if (ft_strcmp(av[1], "here_doc") != 0)
	{
		*fd_in = open(av[1], O_RDONLY, 0644);	
		if (*fd_in == -1)
		{
			perror("open ");
			exit(EXIT_FAILURE);
		}
	}
	else
		*fd_in = 0;
	if (ft_strcmp(av[1], "here_doc") == 0)
		*fd_out = open(av[ac - 1], O_CREAT | O_RDWR | O_APPEND, 0644);
	else
	{
		unlink(av[ac - 1]);
		*fd_out = open(av[ac - 1], O_CREAT | O_RDWR, 0644);
	}
	if (*fd_out == -1)
	{
		if (ft_strcmp(av[1], "here_doc") != 0)
			close(*fd_in);
		perror("open ");
		exit(EXIT_FAILURE);
	}	
}

void	parse(int ac, char **av, t_list **cmd, int *fd_file)
{
	int	i;
	int	y;

	i = 2;
	y = 1;
	if (ft_strcmp(av[1], "here_doc") == 0)
		i++;
	open_file(ac, av, fd_file, fd_file + 1);
	while (i < ac - 1)
	{
		if ((ft_strcmp(av[1], "here_doc") == 0 && i == 3) || i == 2)
			ft_lstadd_back(cmd, ft_lstnew(ft_split(av[i], ' '), fd_file[0], 0));
		else if (i == ac - 2)
			ft_lstadd_back(cmd, ft_lstnew(ft_split(av[i], ' '), 0, fd_file[1]));
		else
			ft_lstadd_back(cmd, ft_lstnew(ft_split(av[i], ' '), 0, 0));
		if (ft_lstsize(*cmd) != y++)
			clear_lst(cmd, fd_file);
		i++;
	}
}

//==================================================================//
//					PROCESS.C
//==================================================================//

void	free_array(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		free(arg[i++]);
	free(arg);
}

char	*find_cmd(t_list *elem, char **env)
{
	char	*path;
	char	*temp;
	char	**env_pth;
	int		i;
	int		y;

	i = -1;
	if (ft_strstr(elem->arg[0], "/"))
	{
		path = ft_strjoin("", elem->arg[0]);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
	}
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			y = -1;
			env_pth = ft_split(env[i] + 5, ':');
			while (env_pth[++y])
			{	
				temp = ft_strjoin(env_pth[y], "/");
				path = ft_strjoin(temp, elem->arg[0]);
				free(temp);
				if (access(path, F_OK) == 0)
				{
					free_array(env_pth);
					return (path);
				}
				free(path);
			}
			free(env_pth);
		}
	}
	return (NULL);
}

void	child_process(t_list *elem, int *fd_file, int *fds, char **env)
{
	char	*path;
	
	path = find_cmd(elem, env);
	dup2(fd_file[0], 0);
	if (!elem->next)
		dup2(fd_file[1], 1);
	else
		dup2(fds[1], 1);
	close(fds[0]);
	close(fds[1]);
	close(fd_file[0]);
	close(fd_file[1]);
	execve(path, elem->arg, env);
	perror("execve :");
	exit(EXIT_FAILURE);
}

void	parent_process(t_list *elem, int pid, int *fd_file, int *fds)
{
	int	status;

	waitpid(pid, &status, 0);
	close(fd_file[0]);
	if (!elem->next)
	{
		close(fd_file[0]);
		close(fd_file[1]);
		close(fds[0]);
		close(fds[1]);
	}
	else
	{
		close(fd_file[0]);	
		fd_file[0] = dup(fds[0]);
		close(fds[0]);
		close(fds[1]);
	}
}

void	process_pipex(t_list **cmd, int *fd_file, char **env)
{
	int		fds[2];
	int		pid;
	t_list	*elem;

	elem = *cmd;
	while (elem)
	{
		pipe(fds);
		pid = fork();
		if (pid == -1)
		{
			close(fds[0]);
			close(fds[1]);
			perror("fork :");
			clear_lst(cmd, fd_file);
		}
		if (pid == 0)
			child_process(elem, fd_file, fds, env);
		else
			parent_process(elem, pid, fd_file, fds);
		elem = elem->next;
	}
}

//================================================================//
//							PIPEX.C	
//================================================================//

int	main(int ac, char **av, char **env)
{
	t_list	*cmd;
//	t_list	*elem;
	int		fd_file[2];

	parse(ac, av, &cmd, fd_file);
	process_pipex(&cmd, fd_file, env);
/*	for (elem = cmd; elem; elem = elem->next)
	{
		for (int i = 0; elem->arg[i]; i++)
			ft_putendl_fd(elem->arg[i], 1);
		ft_printf("fd_in : %d\n", elem->fd_in);
		ft_printf("fd_out : %d\n", elem->fd_out);
	}
*/	return (0);
}
