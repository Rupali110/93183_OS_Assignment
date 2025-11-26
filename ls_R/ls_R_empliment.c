#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>




void list_Print(char *path){
		DIR *DP=opendir(path);
		if(DP==NULL){
				printf("Error to open path");
				return;
		}
		printf("\n %s \n",path);
		struct dirent *ent;
		struct stat point;
		 chdir(path);
		while((ent=readdir(DP))!=0){
				if(strcmp(ent->d_name,".")==0||strcmp(ent->d_name,"..")==0)
								continue;
						if(stat(ent->d_name,&point)==0){
						printf("%-20s | mode: %d | links: %ld | uid: %d | gid: %d | size: %ld bytes\n",ent->d_name, point.st_mode, point.st_nlink,point.st_uid, point.st_gid, point.st_size);
						}else {
            perror(ent->d_name);
        }
    }
rewinddir(DP);
while((ent=readdir(DP))!=0){
                 if(strcmp(ent->d_name,".")==0||strcmp(ent->d_name,"..")==0)
                                 continue;
                        if(stat(ent->d_name,&point)==0&&S_ISDIR(point.st_mode)){
				list_Print(ent->d_name);
 }
 
 }
 chdir("..");
 closedir(DP);
}
int main(int argc,char *argv[]){
		char *path;
		if(argc!=2){
				printf("Path not given:\n");
				printf("Run as %s <Path> \n",argv[0]);
		}
		path=argv[1];
		list_Print(path);
		return 0;

				
}
