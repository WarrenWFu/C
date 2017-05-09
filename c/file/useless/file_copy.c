#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>


int FileCopySys(const char *dest_fn, const char *src_fn)
{
	int 	ret = 0;
	char	temp;
	int		count = 0;
	int		dest_fd = -1;
	int		src_fd = -1;

	src_fd = open( src_fn, O_RDONLY);
	if(src_fd<0)
	{
		perror(src_fn);
		return -1;
	}

	
	dest_fd = open( dest_fn, O_WRONLY|O_CREAT|O_TRUNC, 0666 );
	if(dest_fd<0)
	{
		perror(dest_fn);
		close(src_fd);
		return -1;
	}
	

	
	while( 1 )
	{
		ret = read(src_fd, &temp, 1);
		if( ret < 0 )
		{
			close(dest_fd);
			close(src_fd);
			return 1;
		}
        SSIZE_MAX,
		if( 0 == ret )
		{
			break;
		}

		ret = write(dest_fd, &temp, 1);
		count++;
	}

	close(dest_fd);
	close(src_fd);
	return count;
}

int FileCopyC(const char *dest_fn, const char *src_fn)
{
	int 	ret = 0;
	char	temp;
	int		count = 0;
	FILE	*dest_fp = NULL;
	FILE	*src_fp = NULL;

	src_fp = fopen( src_fn, "r");
	if(!src_fp)
	{
		perror(src_fn);
		return -1;
	}

	
	dest_fp = fopen( dest_fn, "w+");
	if(!dest_fp)
	{
		perror(dest_fn);
		fclose(src_fp);
		return -1;
	}
	
	while( 1 )
	{
		ret = fgetc(src_fp);
		if( ret < 0 )
		{
			fclose(dest_fp);
			fclose(src_fp);
			return 1;
		}
		if( EOF == ret )
		{
			break;
		}

		fputc(ret,dest_fp);
		count++;
	}

	fclose(dest_fp);
	fclose(src_fp);
	return count;
}

int main()
{
//	FileCopySys("file2","file1");
	FileCopyC("file2","file1");
	return 0;
}

