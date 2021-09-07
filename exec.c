#include "pipex.h"

int
	main(int ac, char **av, char **envp)
{
	printf("Main program started\n");
	pid_t procid;
	pid_t procid2;
	int   pi[2];
	int   fd1;
	int   fd2;
	char* cmd1[3] = { "/bin/ls", "-l", NULL };
	char* cmd2[3] = { "/usr/bin/wc", "-l", NULL };

	char **cmdn1;
	char **cmdn2;

	cmdn1 = ft_split(av[2], " ");
	cmdn2 = ft_split(av[3], " ");

	int i;
	int j;

	i = -1;
	while (cmdn1[++i])
	{
		printf("%s\n", cmdn1[i]);
		free(cmdn1[i]);
	}
	free(cmdn1);

	i = -1;
	while (cmdn2[++i])
	{
		printf("%s\n", cmdn2[i]);
		free(cmdn2[i]);
	}
	free(cmdn2);

	i = -1;

	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH", 4))
		{
			printf("%s\n", envp[i]);
		}
	}

	if (pipe(pi) == -1)
		return (0);
	procid = fork();
	if (procid < 0)
		return (0);
	if (procid == 0)
	{
		fd1 = open(av[1], O_RDONLY);
		close(pi[0]);
		dup2(pi[1], 1);
		if (fd1 != -1)
		{
			dup2(fd1, 0);
			execve(cmd1[0], cmd1, envp);
		}
		perror("pipex");
		exit(0);
	}
	else
	{
		procid2 = fork();
		if (procid2 < 0)
			return (0);
		if (procid2 == 0)
		{
			fd2 = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 00644);
			close(pi[1]);
			dup2(pi[0], 0);
			if (fd2 != -1)
			{
				dup2(fd2, 1);
				execve(cmd2[0], cmd2, envp);
			}
			perror("pipex");
			exit(0);
		}
		else
		{
			close(pi[0]);
			close(pi[1]);
			while (wait(NULL) != -1);
		}
	}
	return (0);
}
