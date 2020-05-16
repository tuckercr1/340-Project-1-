// Alex Laughlin
// Chris Tucker
// CSCI 340 Project 1

#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h> 
#include <unistd.h>
#include <libgen.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/stat.h>

   // The main function
   int main(int argc, char *argv[])
   {
	
	// This is the pointer for the stat.txt files
	FILE *pf;
	
	// These arrays are used for storing information from the stat.txt files in /proc
	int pid[1024]; //1
      	char name[1024][100]; //2
      	int ppid[1024]; //4
      	int vsize[1024]; //23 

	// These 3 arrays are needed to form a string for scanning the /proc directories for the stat.txt files
	char start[] = "/proc/";
	char middle[10];
	char end[] = "/stat";
	char dirString[4096];
	int count = 0;
	


	struct dirent *de;  // Pointer for directory entry 
  
    	// opendir() returns a pointer of DIR type.  
   	 DIR *dr = opendir("/proc"); 
  
    	if (dr == NULL)  // opendir returns NULL if couldn't open directory 
    	{ 
        	printf("Could not open current directory\n"); 
       		return 0; 
   	}	 

	 
	
    	// Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html 
    	// for readdir() 
    	while ((de = readdir(dr)) != NULL) {
		if (de->d_type == DT_DIR) {
		    	
			// These 3 strcat() will form the string "/proc/%s/stat.txt" where %s is the name of the Directory
			strcat(dirString, start);
			strcat(dirString, de->d_name);
			strcat(dirString, end);
			
			// Have to scan
			pf = fopen(dirString, "r");

			// If dirString (/proc/%s/stat.txt) does not exist
			if(pf == NULL){
	 			//printf("Unable to open the file.\n"); // Test to make sure the if/else loop is working
			}

			// If dirString (/proc/%s/stat.txt) does exist
			else{
				
				int temp_pid; //1
      				char temp_name[15]; //2
      				int temp_ppid; //4
      				int temp_vsize; //23 

	 			//printf("Opened the file.\n"); // Test to make sure the file is opening
	 			fscanf(pf, "%d %s %*c %d %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %d", 					&temp_pid, temp_name, &temp_ppid, &temp_vsize);

				// This will print the pid, name, ppid, and vsize in the order that it is read from the /proc filesystem
	 			//printf("(%d) %s, ppid = %d, %d\n", temp_pid, temp_name, temp_ppid, temp_vsize);
				
				
				pid[count] = temp_pid;
				ppid[count] = temp_ppid;
				vsize[count] = temp_vsize/100;
				strcpy(name[count], temp_name);
				
				count++;
	 			fclose(pf);
			} 

			strcpy(dirString, ""); // This clears dirString so it doesn't keep adding additional strings going into the next 							  iteration
			   
		}}
	
	// Test prints ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//printf("count = %d\n", count);
	//printf("pid[5] = %d\n", pid[5]);
	//printf("pid[count-1] = %d\n", pid[count-1]);
	//printf("pid[0] = %d, ppid[0] = %d, vsize[0] = %dkb\n", pid[0], ppid[0], vsize[0]);
	//printf("pid[5] = %d, ppid[5] = %d, vsize[5] = %dkb\n", pid[5], ppid[5], vsize[5]);
	//printf("pid[count-1] = %d, ppid[count-1] = %d, vsize[count-1] = %dkb\n", pid[count-1], ppid[count-1], vsize[count-1]);
	//printf("%s\n", name[0]);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
	// This loop goes through the list of ppids and if a ppid matches another process' pid then the index process gets printed
	// tabbed over.

	int i = 0;
	while(i < count){
	  if(ppid[i] == 0){
	    printf("%d %s, ppid: %d, %d kb\n", pid[i], name[i], ppid[i], vsize[i]);
	      int j = 0;
	        while(j < count){
		  if(ppid[j] == pid[i]){
		    printf("    %d %s, ppid: %d, %d kb\n", pid[j], name[j], ppid[j], vsize[j]);
		      int k = 0;
			while(k < count){
			   if(ppid[k] == pid[j]){
			    printf("      %d %s, ppid: %d, %d kb\n", pid[k], name[k], ppid[k], vsize[k]);
			      int l = 0;
				while(l < count){
				  if(ppid[l] == pid[k]){
				    printf("        %d %s, ppid: %d, %d kb\n", pid[l], name[l], ppid[l], vsize[l]);
				      int m = 0;
				       while(m < count){
					 if(ppid[m] == pid[l]){
					   printf("          %d %s, ppid: %d, %d kb\n", pid[m], name[m], ppid[m], vsize[m]);
				 	   int n = 0;
					   while(n < count){
					     if(ppid[n] == pid[m]){
						printf("            %d %s, ppid: %d, %d kb\n", pid[n], name[n], ppid[n], vsize[n]);
						int x = 0;
						while(x < count){
						  if(ppid[x] == pid[n]){
						    printf("              %d %s, ppid: %d, %d kb\n", pid[x], name[x], ppid[x], vsize[x]);
						  }
						x++;
						}
					     }
					   n++;
					   }
					 }
				       m++;
				       }
				   }
				l++;
			   	}
			   }
			 k++;
			 }
		   }
		 j++;
		 }
	    }
	i++;
	}

	
	
		
    	closedir(dr);     
    	return 0;
    }// end of main
