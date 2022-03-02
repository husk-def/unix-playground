#include <dirent.h>
#include <limits,h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int Myfunc(const char *, const struct stat *, int);

static	Myfunc	myfunc;
static	char*	path_alloc(int *);
static	int		myftw(char *, Myfunc *);
static	int		dopath(Myfunc *); 

static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

int
main(int argc, char *argv[])
{
	int		ret;

	assert(argc == 2);

	ret = myftw(argv[1], myfunc); /* does it all */
	ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
	if (ntot == 0)
		ntot = 1;	/* avoid division by 0 */
	printf("regular files 	= %7ld, %5.2f %%\n", nreg,
		nreg * 100.0 / ntot);
	printf("directories 	= %7ld, %5.2f %%\n", ndir,
		ndir * 100.0 / ntot);
	printf("block special	= %7ld, %5.2f %%\n", nblk,
		nblk * 100.0 / ntot);
	printf("char special	= %7ld, %5.2f %%\n", nchr,
		nchr * 100.0 / ntot);
	printf("fifos			= %7ld, %5.2f %%\n", nfifo,
		nfifo * 100 / ntot);
	printf("symbolic links	= %7ld, %5.2f %%\n", nslink,
		nslink * 100 / ntot);
	printf("sockets			= %7ld, %5.2f %%\n", nsock,
		nsock * 100 / ntot);

	exit(ret);
}

#ifdef PATH_MAX
static int pathmax = PATH_MAX;
#else
static int pathmax = 0;
#endif

char  *
path_alloc(int *size) 
{
    char	*ptr;

    if (pathmax == 0) {
        errno = 0;
        if ( ( pathmax = pathconf("/", _PC_PATH_MAX) ) < 0 ) {
            if ( errno == 0 )
                pathmax = PATH_MAX_GUESS;
            else
               perror("pathconf error for _PC_PATH_MAX");
        }
        else
            pathmax++;
    }

    if ( ( ptr = malloc(pathmax + 1) ) == NULL )
        perror("malloc error for pathname");

    if ( size != NULL )
        *size = pathmax + 1;

    return(ptr);
}


/*
 * descend through the hierarchy, starting at "pathname".
 * the caller's func() is called for every file.
 */
#define	FTW_F	1 	/* file other that directory */
#define FTW_D	2 	/* directory */
#define	FTW_DNR	3	/* directory that can't be read */
#define	FTW_NS	4	/* file that we can't stat */

static char		*fullpath;		/*full pathname for every file */
static size_t	pathlen;

static int
myftw(char *pathname, Myfunc *func)
{
	fullpath = path_alloc(&pathlen);		/* malloc PATH_MAX + 1 bytes */
	if (pathlen <= strlen(pathname)) {
		pathlen = strlen(pathname) << 1;
		assert((fullpath = realloc(fullpath, pathlen) != NULL);
	}
	strcpy(fullpath, pathname);
	return(dopath(func));
}

/*
 * descend through the hierarchy, starting at "fullpath"
 * if "fullpath is anything other than a directory, we lstat() it,
 * call func(), and return. For a directory, we call ourself
 * recursively for each name in the directory.
 */
 static int
 dopath(Myfunc *func)
 {
 	struct stat	statbuf;
 	struct dirent	*dirp;
 	DIR			*dp;
 	int			ret, n;
 	
 	if (lstat(fullpath, &statbuf) < 0) 		/* stat error */
 		return(func(fullpath, &statbuf, FTW_NS));
 	if (S_ISDIR(statbuf.st_mode) == 0)	/* not a directory */
 		return(func(fullpath, &statbuf, FTW_F));
 		
 	/*
 	 * it's a directory. First call func() for the directory,
 	 * then process each filename in the directory.
 	 */
 	if ((ret = func(fullpath, &statbud, FTW_D) != 0)
 		return(ret);
	n = strlen(fullpath);
	if (n + NAME_MAX + 2 > pathlen) { /* expand path buffer */
		pathlen <<= 1;
		assert((fullpath = realloc(fullpath, pathlen)) != NULL);
	}
	fullpath[n++] = '/';
	fullpath[n] = 0;
	if ((dp = opendir(fullpath)) == NULL)
		return(func(fullpath, &statbuf, FTW_DNR));
		
	while ((dirp = readdir(dp)) != NULL) {
		if (strcmp(dirp->d_name, ".") == 0 ||
			strcmp(dirp->d_name, "..") == 0)
			continue;			/* ignore . and .. */
		strcpy(&fullpath[n], dirp->d_name);
		if ((ret = dopath(func)) != 0)	/* recursive */
			break;				/* time to leave */
	}	
	fullpath[n-1] = 0;				/* erase everything from / onward */
	assert(closedir(dp) >= 0);
	return(ret);
}

static int
myfunc(const char *pathname, const struct stat *statptr, int type)
{
	switch (type) {
	case FTW_F:
		switch (statprt->st_mode & S_IFMT) {
		case S_IFREG:	++nreg;		break;
		case S_IFBLK:	++nblik;		break;
		case S_IFCHR:	++nchr;		break;
		case S_IFIFO:		++nfifo;		break;
		case S_IFLINK:	++nslink;	break;
		case S_IFSOCK:	++nsock;	break;
		case S_IFDIR:		/* directories should have type FTW_D */
			perror("for S_IFDIR");
		}
		break;
	case FTW_D:		++ndir;	break;
	case FTW_DNR:	perror("cant read directory");	break;
	case FTW_NS:	perror("stat error"); break;
	default: perror("unknown type");
	}
	return(0);


