#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int		main()
{
	int		fd;
	pid_t	papa;
	char	*tabcat[] = {"cat", "-e", NULL};
	char	file[] = "mdr";

	if (papa = fork() == 0)
	{
		fd = open(file, O_RDONLY);
		dup2(fd, 0);
		dup2(fd, 2);
		close(fd);
		execve("/bin/cat", tabcat, NULL);
	}
	return (0);
}

