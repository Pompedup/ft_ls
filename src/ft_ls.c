/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:43:16 by abezanni          #+#    #+#             */
/*   Updated: 2019/03/03 00:27:15 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	simple_print(t_container *contain)
{
	char *test;

	while (contain)
	{
		test = ctime(&contain->time);
		*(ft_strchr(test, '\n')) = '\0';
		ft_printf("\033[32m%s - %s - %p\n", test, contain->name, contain->dir);
		contain = contain->next;
	}
}

int		main(int ac, char **av)
{
	t_data	data;
	int		i;

	init(&data, &i);
	if (i < ac && *av[i] == '-')
	{
		if ((data.options = options(av[i] + 1)) == -1)
			return (0);
		i++;
	}
	if (i < ac)
		args(&data, ac - i, av + i);
	else
		test_link(&data, ".");
	del_t_errors(&(data.errors));
	display_folder(&data, data.files);
	// if (data.files)//to protect
	// 	display_files(&data.files, data.files->len_max, data.files->nb_files);
	get_folders(&data, &data.folders);
	return (0);
}

// #include <sys/ioctl.h>
    // struct winsize w;
    // ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    // printf ("lines %d\n", w.ws_row);
    // printf ("columns %d\n", w.ws_col);


// ◦ write
// Ecrire sur le terminal


// ◦ DIR *opendir(const char *filename)
// Ouvre le dossier filename et retourne un poiteur qui identifie le directory stream
// Retourne NULL si filename est innacessible (errno explique l'erreur)

// ◦ struct dirent *readdir(DIR *)
// struct dirent { /* when _DARWIN_FEATURE_64_BIT_INODE is NOT defined */
//              ino_t      d_ino;                /* file number of entry */
//              __uint16_t d_reclen;             /* length of this record */
//              __uint8_t  d_type;               /* file type, see below */
//              __uint8_t  d_namlen;             /* length of string in d_name */
//              char    d_name[255 + 1];   /* name must be no longer than this */
//      };
// Retourne un pointeur contenant les infos du prochain fichier/dossier
// Retourne NULL a la fin de la lecture ou si une erreur se produit

// ◦ int closedir(DIR *)
// Ferme un fichier ouvert avec opendir et free la structure
// Retourne 0 si tout est bon
//  -1 en cas d'erreur ->errno
// ◦ int stat(const char *restrict path, struct stat *restrict buf)
// Recupere les informations du fichier pointe par path
//   printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
//     printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
//     printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
//     printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
//     printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
//     printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
//     printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
//     printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
//     printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
// ◦ int lstat(const char *restrict path, struct stat *restrict buf)
// Comme stat mais avec un lien symbolic,
// The lstat() function is like stat() except in the case where the named file is a symbolic link; lstat() returns information about the link, while stat() returns information about the file the link
    //  references.  For symbolic links, the st_mode member contains meaningful information when used with the file type macros, and the st_size member contains the length of the pathname contained in the
    //  symbolic link. File mode bits and the contents of the remaining members of the stat structure are unspecified. The value returned in the st_size member is the length of the contents of the sym-
    //  bolic link, and does not count any trailing null.


// ◦ struct passwd *getpwuid(uid_t uid)
//
// struct passwd {
//                    char    *pw_name;       /* user name */
//                    char    *pw_passwd;     /* encrypted password */
//                    uid_t   pw_uid;         /* user uid */
//                    gid_t   pw_gid;         /* user gid */
//                    time_t  pw_change;      /* password change time */
//                    char    *pw_class;      /* user access class */
//                    char    *pw_gecos;      /* Honeywell login info */
//                    char    *pw_dir;        /* home directory */
//                    char    *pw_shell;      /* default shell */
//                    time_t  pw_expire;      /* account expiration */
//                    int     pw_fields;      /* internal: fields filled in */
// };
// ◦ getgrgid
// These functions obtain information from opendirectoryd(8), including records in /etc/group which is described in group(5).  Each line of the database is defined by the structure group found in the
//      include file <grp.h>:

//            struct group {
//                    char    *gr_name;       /* group name */
//                    char    *gr_passwd;     /* group password */
//                    gid_t   gr_gid;         /* group id */
//                    char    **gr_mem;       /* group members */
//            };
// ◦ ssize_t listxattr(const char *path, char *namebuf, size_t size, int options);
// ◦ ssize_t getxattr(const char *path, const char *name, void *value, size_t size, u_int32_t position, int options);
// ◦ time_t time(time_t *tloc)
// ◦ char * ctime(const time_t *clock)

// ◦ ssize_t readlink(const char *restrict path, char *restrict buf, size_t bufsize)


// ◦ void perror(const char *s)
// ◦ char * strerror(int errnum)

// ◦ malloc
// ◦ free
// ◦ exit


// struct stat
        //  dev_t           st_dev;           /* ID of device containing file */
        //  mode_t          st_mode;          /* Mode of file (see below) */
        //  nlink_t         st_nlink;         /* Number of hard links */
        //  ino_t           st_ino;           /* File serial number */
        //  uid_t           st_uid;           /* User ID of the file */
        //  gid_t           st_gid;           /* Group ID of the file */
        //  dev_t           st_rdev;          /* Device ID */
        //  struct timespec st_atimespec;     /* time of last access */
        //  struct timespec st_mtimespec;     /* time of last data modification */
        //  struct timespec st_ctimespec;     /* time of last status change */
        //  struct timespec st_birthtimespec; /* time of file creation(birth) */
        //  off_t           st_size;          /* file size, in bytes */
        //  blkcnt_t        st_blocks;        /* blocks allocated for file */
        //  blksize_t       st_blksize;       /* optimal blocksize for I/O */
        //  uint32_t        st_flags;         /* user defined flags for file */
        //  uint32_t        st_gen;           /* file generation number */
        //  int32_t         st_lspare;        /* RESERVED: DO NOT USE! */
        //  int64_t         st_qspare[2];     /* RESERVED: DO NOT USE! */

//ls -lRart (-l droits ?)
