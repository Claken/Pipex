#include "pipex.h"

char
	**ft_tab_of_path(char **envp)
{
	int	i;
	char**tab;

	i = 0;
	while (!(ft_strnstr(envp[i], "PATH", 4)))
		i++;
	tab = ft_split(envp[i], "=:");
	if (tab == NULL)
		return (NULL);
	return (tab);
}

void
	ft_print_and_free_tab(char **tab)
{
	int i;

	i = -1;
	while (tab[++i])
	{
		printf("%s\n", tab[i]);
		free(tab[i]);
	}
	free(tab);
}

char
	*ft_find_cmd(char **path, char *cmd)
{
	int	i;
	char*pathdebut;
	char*cmdpath;
	int	fd;

	i = 0;
	while (path[++i])
	{
		pathdebut = ft_strjoin(path[i], "/");
		if (!pathdebut)
			return (NULL);
		cmdpath = ft_strjoin(pathdebut, cmd);
		if (!cmdpath)
			return (NULL);
		free(pathdebut);
		fd = open(cmdpath, O_RDONLY);
		if (fd != -1)
		{
			close(fd);
			return (cmdpath);
		}
		close(fd);
		free(cmdpath);
	}
	return (NULL);
}

int
	main(int ac, char **av, char **envp)
{
	pid_t procid;
	pid_t procid2;
	int   pi[2];
	int   fd1;
	int   fd2;
	char **cmdn1;
	char **cmdn2;
	char **path;
	char *cmd1path;
	char *cmd2path;

	if (ac != 5)
		return (0);
	printf("Main program started\n");
	cmdn1 = ft_split(av[2], " ");
	cmdn2 = ft_split(av[3], " ");
	path = ft_tab_of_path(envp);

	cmd1path = ft_find_cmd(path, cmdn1[0]);
	cmd2path = ft_find_cmd(path, cmdn2[0]);
	printf("%s\n", cmd1path);
	printf("%s\n", cmd2path);

	char* cmd1[3] = { cmd1path, cmdn1[1], NULL };
	char* cmd2[3] = { cmd2path, cmdn2[1], NULL };



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
	ft_print_and_free_tab(cmdn1);
	ft_print_and_free_tab(cmdn2);
	ft_print_and_free_tab(path);
	free(cmd1path);
	free(cmd2path);
	return (0);
}
