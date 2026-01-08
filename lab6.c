#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

pid_t child_pid = 0;
int n = 0;

void process_a_ends(int sig)
{
  int status;

  if (kill(child_pid, SIGUSR2) < 0)
    {
      printf("Error sending SIGUSR2 to child\n");
      exit(2);
    }

  /* waiting for the child to end */

  wait(&status);
  printf("Child ended with code %d\n", WEXITSTATUS(status));

  printf("Process ends.\n");
  exit(0);
}

void process_a()
{
  int i;

  if (signal(SIGINT, process_a_ends) == SIG_ERR)
    {
      printf("Error setting handler for SIGINT\n");
      exit(1);
    }
  for (i = 0;;i++)
    {
      usleep(1000);
      if (i%10 == 0)
	if (kill(child_pid, SIGUSR1) < 0)
	  {
	    printf("Error sending SIGUSR1 to child\n");
	    exit(2);
	  }
    }
}

void process_b_writes(int sig)
{
  printf("Process b received SIGUSR1: %d\n", ++n);
}

void process_b_ends(int sig)
{
  printf("Process b ends.\n");
  exit(0);
}

void process_b()
{
  /* Ignoring SIGINT. Process b will end only when receives SIGUSR2 */

  if (signal(SIGINT, SIG_IGN) == SIG_ERR)
    {
      printf("Error ignoring SIGINT in process b\n");
      exit(3);
    }

  /* Setting the signal handlers */

  if (signal(SIGUSR1, process_b_writes) == SIG_ERR)
    {
      printf("Error setting handler for SIGUSR1\n");
      exit(4);
    }
  if (signal(SIGUSR2, process_b_ends) == SIG_ERR)
    {
      printf("Error setting handler for SIGUSR2\n");
      exit(5);
    }

  /* Infinite loop;
     process b only responds to signals */

  while(1)
    ;
}

int main()
{
  int status;

  /* First, ignore the user signals,
   to prevent interrupting the child
   process before setting the
   appropriate handlers */

  signal(SIGUSR1, SIG_IGN);
  signal(SIGUSR2, SIG_IGN);

  /* Creating the child process.
    A global variable
    is used to store the child process ID
    in order to be able to use it from the
    signal handlers */

  if ((child_pid = fork()) < 0)
    {
      printf("Error creating child process\n");
      exit(1);
    }

  if (child_pid == 0) /* the child process */
    {
      process_b();
      exit(0);
    }
  else /* the parent process */
    {
      process_a();
    }

  /* this is still the parent code */
  
  return 0;
}