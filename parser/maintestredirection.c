#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int		main()
{
	int		fd;
	pid_t	papa;
	char	*tabls[] = {"ls", "-la", NULL};
	char	file[] = "mdr";

	if (papa = fork() == 0)
	{
		fd = open(file, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
		dup2(fd, 1);
		dup2(fd, 2);
		close(fd);
		execve("/bin/ls", tabls, NULL);
	}
	return (0);
}

