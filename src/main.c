/*
 * Project 2 - Advanced Operating System
 * CAUSAL MESSAGE ORDERING IN DISTRIBUTED SYSTEM
 * Using Schiper-Eggli-Sandoz Algorithm
 *
 * 1512284 - Ha Tan Linh
 * Email: hatanlinh13@gmail.com
 *
 * Module: Main Routine
 */
#include "defs.h"
#include "config.h"
#include "threads.h"
#include "ses.h"

#include <stdio.h>
#include <string.h>
#include <pthread.h>

int           n;  /* number of processes in system */
int           id; /* index of current process */
sentvec_t     vect_curr; /* sent message vector of current process */
vectorclock_t time_curr; /* time vector clock of current process */
host_t       *proc_list; /* addresses of all processes in the system */
int           nmsg;      /* number of messages to send to each other process */
int           rmin;      /* min send rate (messages per minute) */
int           rmax;      /* max send rate (messages per minute) */
char          log_fname[255]; /* logs file name */
int           lport;     /* listening port   */
int           servfd;    /* listening socket */
pthread_t        trr[1024]; /* thread id array */
pthread_rwlock_t lock_n    = PTHREAD_RWLOCK_INITIALIZER;
pthread_rwlock_t lock_id   = PTHREAD_RWLOCK_INITIALIZER;
pthread_rwlock_t lock_vect = PTHREAD_RWLOCK_INITIALIZER;
pthread_rwlock_t lock_time = PTHREAD_RWLOCK_INITIALIZER;
pthread_mutex_t  lock_log  = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char **argv)
{
	config_default();
	if (argc == 2)
		config_get_from_file(argv[1]);

	/* Initialize SES enviroments and setting up listen socket */
	ses_init();

	/* wait for user type *start* to begin */
	char buf[255];
	while (1) {
		printf("Type \"start\" to begin: ");
		scanf("%s", buf);
		if (strncmp(buf, "start", 5) == 0)
			break;
	}

	/* Spawn threads to send messages */
	threads_init();

	/* receiving messages */
	ses_loop();

	return 0;
}
