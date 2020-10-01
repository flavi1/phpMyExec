 
#include < stdio.h >
#include < stdlib.h >
#include < unistd.h >
#include < sys/types.h >
#include < sys/stat.h >

main(int argc, char**argv)
{
    const char* php_exec = "/usr/bin/php ";
    char* command;
    int ok = 0;
    int uid,gid;
    struct stat statbuf;

    setuid(0);
    setgid(0);

    if (stat(argv[1],&statbuf))				{ fprintf(stderr,"cannot stat %s\n",argv[1]);			exit(-1); }
    if (statbuf.st_uid || statbuf.st_gid)	{ fprintf(stderr,"[%s] must be root root\n",argv[1]);	exit(-2); }
    if (!(statbuf.st_mode & S_ISGID))		{ fprintf(stderr,"[%s] must be sgid root\n",argv[1]);	exit(-3); }
    if (!(statbuf.st_mode & S_ISUID))		{ fprintf(stderr,"[%s] must be suid root\n",argv[1]);	exit(-4); }
    
    command = malloc(strlen(php_exec)+strlen(argv[1])+1);
    strcpy(command, php_exec);
    strcat(command, argv[1]);
    
    execv(command, argv+1);
}
