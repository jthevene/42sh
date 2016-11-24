#include "../includes/parse.h"

void	exec_tree(t_all *all, t_tree *tree)
{
	if (tree->type == COMMAND)
	{
		get_cmd(all, tree->content);
		get_path(all);
	}
	if (tree->left)
		exec_tree(all, tree->left);
	if (tree->right)
		exec_tree(all, tree->right);
}

void	get_path(t_all *all)
{
	int		i;
	char	*cmd;

	cmd = NULL;
	i = -1;
	if (getenv("PATH") == NULL)
		all->path = ft_strsplit(" : ", ':');
	else
		all->path = ft_strsplit(getenv("PATH"), ':');
	i = find_cmd_path(all, i, cmd);
	if (all->path[i] == NULL)
	{
		ft_putstr("21sh: command not found: ");
		ft_putendl(all->cmd);
	}
	free_tab(all->path);
	//free_tab(all->envcpy);
}

int		find_cmd_path(t_all *all, int i, char *cmd)
{
	struct stat	sb;

	while (all->path[++i])
	{
		if (ft_strncmp(all->cmd, "./", 2) == 0 || \
				(ft_strncmp(all->cmd, "/", 1) == 0))
			cmd = ft_strdup(all->cmd);
		else
			cmd = ft_strjoinchar(all->path[i], all->cmd, '/');
		stat(cmd, &sb);
		if (access(cmd, F_OK) == 0)
		{
			accessfork(all, sb, cmd);
			free(cmd);
			break ;
		}
		free(cmd);
	}
	return (i);
}

void	accessfork(t_all *all, struct stat sb, char *cmd)
{
	if (access(cmd, X_OK) == 0)
	{
		if (S_ISDIR(sb.st_mode))
		{
			ft_putstr(cmd);
			ft_putendl(" is a directory");
		}
		else
			exec_fork(all, cmd);
	}
	else
	{
		ft_putstr("21sh: permission denied: ");
		ft_putendl(all->cmd);
	}
}

void	exec_fork(t_all *all, char *cmd)
{
	pid_t papa;

	papa = fork();
	if (papa == -1)
	{
		ft_putstr("Fork Error");
		exit(EXIT_FAILURE);
	}
	if (papa == 0)
		execve(cmd, all->lines, all->envcpy);
	if (papa > 0)
		waitpid(papa, NULL, WCONTINUED);
}
