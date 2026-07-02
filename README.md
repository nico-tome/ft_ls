# ft_ls
My own version of the 42 project ft_ls.

## Description

This project is about recreating the `ls` command from linux terminal, with some of the flags we can use.
The project can be split into three parts: reading, sorting and printing.

### Reading

To complete this project, we need to get some infos about the files and folders. We need:

- name
- path
- size
- uid
- gid
- inode
- permission
- type
- links
- date

We will use `lstat` and store the infos in a struct like the following:

```c
typedef struct  s_files
{
    char            *name;
    char            *path;
    struct  l_stat  stat;
    struct  l_file  *next;
}               t_file;
```
### Sorting

The sorting part is reading the flags given to the project:

-l long listing format
-R use recursive
-a not ignore files that start with .
-r reverse order while sorting
-t sort by time
-d list directories
-1 list one file per line
	int		d_flag;
	int		one_flag;

