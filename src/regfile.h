#ifndef REGFILE_H
#define REGFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <inttypes.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include "flags.h"
#include <math.h>

struct timespec start_time;
char *regfile;
FILE *fp;

void initRegister();

/*
function to log the command in the file
*/
void regCommand(int argc,char const *argv[]);

/*
function to make a new process and log it in the file
*/
void regNewProcess(flags *flags);

/*
function to exit a process and log it in the file
*/
void regExit(int status);

/*
function to receive a signal and log it in the file
this function will be the signal_handler
*/
void regReceiveSignal(int signal);

/*
function to send a signal and log it in the file
*/
int regSendSignal(pid_t dpid,int signo);

/*
function to send a message using pipe and log it in the file
*/
void regSendMessage(int fd, long int *size, size_t n);

/*
function to receive a message using pipe and log it in the file
*/
void regReceiveMessage(int fd, long int *size, size_t n);

void regEntry(int size, char *path);

double getTimefromBeggining(struct timespec action_time);

#endif /*REGFILE_H*/