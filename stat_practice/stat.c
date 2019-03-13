#include <stdio.h>	// printf()
#include <sys/stat.h>	// stat()
#include <time.h>	// ctime()

int main(int argc, char * argv[]){
	struct stat sb;	// make a stat struct

	if(argc != 2){
		printf("Usage: %s <pathname>\n", argv[0]);
	}
	
	if(stat(argv[1], &sb) == -1){
			fprintf(stderr, "Error : stat()");
			return -1;
	}

	printf("=========================================\n");
	printf("File type : ");
	switch(sb.st_mode & S_IFMT){
			case S_IFBLK:	// kind of device is block device
					printf("block device\n"); break;
			case S_IFCHR:
					printf("character device\n"); break;
			case S_IFDIR:
					printf("directory\n"); break;
			case S_IFIFO:
					printf("FIFO device\n"); break;
			case S_IFLNK:
					printf("Symbolic link device\n"); break;
			case S_IFREG:
					printf("Regular file\n"); break;
			case S_IFSOCK:
					printf("Socket\n"); break;
			default:
					printf("unknown?\n"); break;
	}
	
	printf("I-node number:			%ld\n", (long) sb.st_ino);
	printf("Mode:				%lo (octal) \n", (unsigned long) sb.st_mode);
	printf("Link count:			%ld\n", (long) sb.st_nlink);
	printf("Ownership:			UID=%ld GID=%ld\n", (long) sb.st_uid, (long) sb.st_gid);
	printf("Preffered I/O block size:	%ld bytes\n", (long) sb.st_blksize);
	printf("File size: 			%lld bytes\n", (long long) sb.st_size);
	printf("Blocks allocated:		%lld\n", (long long) sb.st_blocks);
	printf("Last file change:		%s", ctime(&sb.st_ctime));
	printf("Last file access:		%s", ctime(&sb.st_atime));
	printf("Last file modification:		%s", ctime(&sb.st_mtime));

	return 0;
}
