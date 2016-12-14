#include "../includes/parse.h"

void	try_pipe(t_all *all, t_tree *tree)
{
	char	**output;
	char	**input;

	if (tree->left->type == COMMAND && tree->right->type == COMMAND)
	{
		output = ft_strsplit(tree->left->content, ' ');
		input = ft_strsplit(tree->right->content, ' ');
		exec_pipe(output, input, all);
	}
}

void	exec_pipe(char **output, char **input, t_all *all)
{
	pid_t	pid1;
	int		pipefd[2];

	pipe(pipefd);
	pid1 = fork();
	if (pid1 == -1)
	{
		ft_putstr("Fork Error");
		exit(EXIT_FAILURE);
	}
	if (pid1 == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
      	execve(all->cmd1_path, output, all->envcpy);
		close(pipefd[1]);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		execve(all->cmd2_path, input, all->envcpy);
		close(pipefd[0]);
	}
}

int	get_path_for_pipe(t_all *all, t_tree *tree)
{
	int		i;
	struct stat	sb1;
	struct stat sb2;

	i = -1;
	printf("allcmd1 : %s\n", all->cmd1);
	printf("allcmd2 : %s\n", all->cmd2);
	if (getenv("PATH") == NULL)
		all->path = ft_strsplit(" : ", ':');
	else
		all->path = ft_strsplit(getenv("PATH"), ':');
	while (all->path[++i])
	{
		if (ft_strncmp(all->cmd1, "./", 2) == 0 || \
				(ft_strncmp(all->cmd1, "/", 1) == 0))
			all->cmd1_path = ft_strdup(all->cmd1);
		else
			all->cmd1_path = ft_strjoinchar(all->path[i], all->cmd1, '/');
		stat(all->cmd1_path, &sb1);
		if (access(all->cmd1_path, F_OK) == 0)
			break ;
	}
	if (all->path[i] == NULL)
	{
		ft_putstr("21sh: command not found: ");
		ft_putendl(all->cmd1);
		return (-1);
	}
	i = -1;
	while (all->path[++i])
	{
		if (ft_strncmp(all->cmd2, "./", 2) == 0 || \
				(ft_strncmp(all->cmd2, "/", 1) == 0))
			all->cmd2_path = ft_strdup(all->cmd2);
		else
			all->cmd2_path = ft_strjoinchar(all->path[i], all->cmd2, '/');
		stat(all->cmd2_path, &sb2);
		if (access(all->cmd2_path, F_OK) == 0)
			break ;
	}
	if (all->path[i] == NULL)
	{
		ft_putstr("21sh: command not found: ");
		ft_putendl(all->cmd2);
		return (-1);
	}
	if (access(all->cmd1_path, F_OK) == 0 && access(all->cmd2_path, F_OK) == 0)
	{
		if(access(all->cmd1_path, X_OK) == 0 && access(all->cmd2_path, X_OK) == 0)
		{
			if (S_ISDIR(sb1.st_mode))
			{
				ft_putstr(all->cmd1_path);
				ft_putendl(" is a directory");
			}
			else if (S_ISDIR(sb2.st_mode))
			{
				ft_putstr(all->cmd2_path);
				ft_putendl(" is a directory");
			}
			else
				try_pipe(all, tree);
		}
	}
	else
	{
		ft_putstr("21sh: permission denied: ");
		ft_putendl(all->cmd1);
		ft_putstr("21sh: permission denied: ");
		ft_putendl(all->cmd2);
	}
	free_tab(all->path);
	//free_tab(all->envcpy);
	return (0);
}