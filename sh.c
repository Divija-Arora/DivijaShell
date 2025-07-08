#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "linkedlist.h"
#include <signal.h>
#include "linkedListForHistory.h"
#include <pthread.h>

char *shell_Name = "shell@divija > ";
char *shell_temp_Name = "shell@divija > ";

int sh_cd(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "sh: expected argument to \"cd\"\n");
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("Invalid Call");
		}
	}
	return 1;
}

int sh_exit(char **args)
{
	printf(ANSI_COLOR_CYAN "\n!See you again :)\n\n" ANSI_COLOR_RESET);
	return 0;
}

process *headProcess = NULL;
int sh_bg(char **args)
{
	//args -- bg echo "hello"
	++args;
	//args -- echo "hello"
	char *firstCmd = args[0]; //echo
	int childpid = fork();
	if (childpid >= 0)
	{
		if (childpid == 0)
		{
			if (execvp(firstCmd, args) < 0)
			{
				perror("Error on execvp\n");
				exit(0);
			}
		}
		else
		{
			if (headProcess == NULL)
			{
				headProcess = create_list(childpid, firstCmd);
			}
			else
			{
				add_to_list(childpid, firstCmd, true);
			}
		}
	}
	else
	{
		perror("fork() error");
	}
	return 1;
}
int sh_bglist(char **args)
{
	print_list();
	return 1;
}

int sh_kill(char **args)
{
	// kill 1575
	char *pidCmd = args[1];
	if (!pidCmd) //kill
	{
		printf("Please specify a pid\n");
	}
	else
	{
		int pid = atoi(pidCmd);
		process *target = search_in_list(pid, &headProcess);
		if (target != NULL)
		{
			if (kill(target->pid, SIGTERM) >= 0)
			{
				delete_from_list(pid);
			}
			else
			{
				perror("Could not kill pid specified\n");
			}
		}
		else
		{
			printf("Specify a pid which is present in the list.\nType \"bglist\" to see active processes\n");
		}
	}
	return 1;
}

historyList *head_of_historylist = NULL;
int sh_history(char **args)
{
	print_list_of_history(head_of_historylist);
	return 1;
}

int sh_prompt(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "sh: expected argument to \"prompt\"\n");
		return 1;
	}
	char* temp_Line = "";
	int i = 2;
	temp_Line = strAppend(temp_Line, args[1]);

	while (args[i] != NULL)
	{
		temp_Line = strAppend(temp_Line, " ");
		temp_Line = strAppend(temp_Line, args[i]);
		i++;
	}
	
	shell_temp_Name = (char *)malloc(sizeof(char *) * (strlen(temp_Line)));
	strcpy(shell_temp_Name, temp_Line);
	shell_temp_Name = strAppend(shell_temp_Name, " > ");
	return 1;
}

int sh_reset_prompt(char **args)
{
	shell_temp_Name = "";
	shell_temp_Name = strAppend(shell_temp_Name, shell_Name);
	return 1;
}

char *builtin_str[] = {
	"cd",
	"exit",
	"bg",
	"bglist",
	"kill",
	"history",
	"prompt",
	"reset-prompt",
	"help",
};

int sh_help(char **args)
{
  int i;
  printf("---------------------Shell @ Pranaw---------------------\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");

  for (i = 0; i < 9; i++) {
    printf(" %d  %s\n", i+1, builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  printf("--------------------------------------------------------\n");
  return 1;
}

//bg echo "hello"
//bglist ->jobs
//kill
int (*builtin_func[])(char **) = {
	&sh_cd,
	&sh_exit,
	&sh_bg,
	&sh_bglist,
	&sh_kill,
	&sh_history,
	&sh_prompt,
	&sh_reset_prompt,
	&sh_help,
};

char *sh_read_line()
{

	char *line = NULL;
	ssize_t bufsize = 0;
	if (getline(&line, &bufsize, stdin) == -1)
	{
		if (feof(stdin))
		{
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("acm-sh: getline\n");
			exit(EXIT_FAILURE);
		}
	}
	FILE *log = fopen("log.txt", "a");
	if (log != NULL) {
		fprintf(log, "%s", line);
		fclose(log);
	}
	return line;
}

#define SH_TOKEN_BUFSIZE 64
#define SH_TOK_DELIM " \t\r\n"

char **sh_split_line(char *line)
{
	int bufsize = SH_TOKEN_BUFSIZE, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!token)
	{
		fprintf(stderr, "acm-sh: allocation error\n");
		exit(EXIT_FAILURE);
	}

	//strtok :- Library Function
	token = strtok(line, SH_TOK_DELIM);
	while (token != NULL)
	{
		tokens[position] = token;
		token = strtok(NULL, SH_TOK_DELIM);

		position++;
	}
	tokens[position] = NULL;
	return tokens;
}

int sh_launch(char **args, char *line)
{
	pid_t pid;
	int status;
	int fd[2];
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		int val = 1;
		if (execvp(args[0], args) == -1)
		{
			val = 0;
			// no need to use the read end of pipe here so close it
			close(fd[0]);
			write(fd[1], &val, sizeof(val));
			printf("Invalid Command\n");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("acm-sh");
	}
	else
	{
		// wait(NULL);
		sleep(1);
		close(fd[1]);
		int val=1;
		read(fd[0], &val, sizeof(val));
		do
		{
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));

		bool *validate = (bool *)malloc(sizeof(bool));
		if (val == 1)
		{
			*validate = true;
		}
		else
		{
			*validate = false;
		}
		
		// add to list of history
		if (head_of_historylist == NULL)
		{

			head_of_historylist = create_list_of_history(line, *validate);
		}
		else
		{
			add_to_list_of_history(line, *validate);
		}
	}
	return 1;
}

int sh_execute(char **args, char *line)
{
	int i;
	if (args[0] == NULL)
	{
		return 1;
	}

	for (int i = 0; i < 9; i++)
	{
		if (strcmp(args[0], builtin_str[i]) == 0)
		{
			if (head_of_historylist == NULL)
			{
				head_of_historylist = create_list_of_history(line, true);
			}
			else
			{
				add_to_list_of_history(line, true);
			}

			return (*builtin_func[i])(args);
		}
	}

	return sh_launch(args, line);
}

void broadcastTermination(int pid, int status)
{
	if (WIFEXITED(status))
	{
		printf("exited, status=%d\n", WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
		printf("killed by signal %d\n", WTERMSIG(status));
	}
	else if (WIFSTOPPED(status))
	{
		printf("stopped by signal %d\n", WSTOPSIG(status));
	}
	else if (WIFCONTINUED(status))
	{
		printf("continued\n");
	}
	delete_from_list(pid);
}

static void signalHandler(int sig)
{
	int pid;
	int status;
	pid = waitpid(-1, &status, WNOHANG);
	broadcastTermination(pid, status);
}

int main(int argc, char **argv)
{
	char *line;
	char *test;
	char **args;
	int status;
	signal(SIGCHLD, signalHandler);
	do
	{
		int v = 1;
		printf(ANSI_COLOR_MAGENTA);
		printf("%s", shell_temp_Name);
		printf(ANSI_COLOR_RESET);

		line = sh_read_line();
		test = (char *)malloc(sizeof(char *) * (strlen(line)));

		strcpy(test, line);
		
		args = sh_split_line(line);
		status = sh_execute(args, test);

		free(line);
		free(args);
	} while (status);

	return 0;
}
