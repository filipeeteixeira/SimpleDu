#include "regfile.h"

void initRegister(){
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    regfile = getenv("LOG_FILENAME");
    
    if (regfile==NULL){ 
        regfile = "log.txt";
        setenv("LOG_FILENAME",regfile,1);
    }
    fp=fopen(regfile,"w");
    if(fp == NULL) {
        perror("Error opening file");
        exit(1);
    }
}

void regCommand(int argc,char const *argv[]){
    struct timespec action_time;
    char command[100] = "";

    clock_gettime(CLOCK_MONOTONIC, &action_time);

    for(int i = 1; i < argc;i++){
		strcat(command,argv[i]);
        if(i!=argc-1)
            strcat(command," ");
	}
    fprintf(fp, "%.2f - %.8d - CREATE - %s\n", getTimefromBeggining(action_time), getpid(), command);
    fflush(fp);
}

void regNewProcess(flags *flags){
    struct timespec action_time;
    clock_gettime(CLOCK_MONOTONIC, &action_time);

    char outflags[100]="";
    char depth[20],blocksize[20];

    if (flags->countLinks) strcat(outflags,"-l ");
    strcat(outflags,flags->dir);
    if (flags->all) strcat(outflags," -a");
    if(flags->bytes) strcat(outflags," -b");
    sprintf(blocksize," --block-size=%d",flags->blockSizeValue);
    if (flags->blockSize) strcat(outflags,blocksize);
    if(flags->dereference) strcat(outflags," -L");
    if(flags->separateDirs) strcat(outflags," -S");
    sprintf(depth," --max-depth=%d",flags->maxDepthValue);
    if(flags->maxDepth) strcat(outflags,depth);
    
    fprintf(fp, "%.2f - %.8d - CREATE - %s\n", getTimefromBeggining(action_time), getpid(),outflags);
    fflush(fp);
}

void regExit(int status){
    struct timespec action_time;
    clock_gettime(CLOCK_MONOTONIC, &action_time);

    fprintf(fp, "%.2f - %.8d - EXIT - %d\n", getTimefromBeggining(action_time), getpid(),status);
    fflush(fp);
    exit(status);
}

int regSendSignal(pid_t dpid, int signo){
    struct timespec action_time;
    clock_gettime(CLOCK_MONOTONIC, &action_time);

    fprintf(fp, "%.2f - %.8d - SEND_SIGNAL - %d to process: %d\n", getTimefromBeggining(action_time), getpid(),signo, dpid);
    fflush(fp);
    return kill(dpid,signo);
}

void regReceiveSignal(int signal){ //handler dos sinais
    struct timespec action_time;
    clock_gettime(CLOCK_MONOTONIC, &action_time);

    fprintf(fp, "%.2f - %.8d - RECV_SIGNAL - %d\n", getTimefromBeggining(action_time), getpid(),signal);
    fflush(fp);
}

void regSendMessage(int fd, long int *size, size_t n){
    struct timespec action_time;
    clock_gettime(CLOCK_MONOTONIC, &action_time);
    write(fd,size,n);
    fprintf(fp, "%.2f - %.8d - SEND_PIPE - %ld\n", getTimefromBeggining(action_time), getpid(),*size);
    fflush(fp);
}

void regReceiveMessage(int fd, long int *size, size_t n){
    struct timespec action_time;
    clock_gettime(CLOCK_MONOTONIC, &action_time);
    read(fd,size,n);
    fprintf(fp, "%.2f - %.8d - RECV_PIPE - %ld\n", getTimefromBeggining(action_time), getpid(), *size); 
    fflush(fp);
}

void regEntry(int size, char *path){
    struct timespec action_time;
    clock_gettime(CLOCK_MONOTONIC, &action_time);
    
    fprintf(fp, "%.2f - %.8d - ENTRY - size: %d\tpath: %s\n", getTimefromBeggining(action_time), getpid(), size, path); 
    
    fflush(fp);
}

double getTimefromBeggining(struct timespec action_time){
    return (action_time.tv_sec-start_time.tv_sec)*1000+((action_time.tv_nsec-start_time.tv_nsec)/10e6);
}
