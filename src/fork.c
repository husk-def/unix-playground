#include 	<sys/wait.h>
#include 	<stdlib.h>
#include 	<stdio.h>
#include 	<string.h>
#include 	<unistd.h>
#include	<stdarg.h>

#define		MAXLINE 50

void	err_sys(const char *, ...);

int
main(void)
{
	char	buf[MAXLINE];
	pid_t	pid;
	int		status;

	printf("%% ");
	while (fgets(buf, MAXLINE, stdin) != NULL) {
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = 0;

		if ((pid = fork()) < 0) {
			err_sys("fork error");
		} else if (pid == 0) {
			execlp(buf, buf, (char *)0);
			err_sys("couldnt execute: %s", buf);
			exit(127);
		}

		if ((pid = waitpid(pid, &status, 0)) < 0) {
			err_sys("waitpid error");
		}
		printf("%% ");
	}
	exit(0);
}

void
err_sys(const char *fmt, ...)
{
	/* variables */
	char		buf[200];
	va_list		ap;
	/* implementation */
	va_start(ap, fmt);
	vsnprintf(buf, 199, fmt, ap);
	va_end(ap);

	strcat(buf, "\n");
	fflush(stdout);						/* in case stdout and stderr are the same */
	fputs(buf, stderr);
	fflush(NULL);						/* flushes all stdio output streams */
	
}
