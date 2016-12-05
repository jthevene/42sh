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
      	execve(output[0], output, all->envcpy);
		close(pipefd[1]);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		execve(input[0], input, all->envcpy);
		close(pipefd[0]);
	}
}
