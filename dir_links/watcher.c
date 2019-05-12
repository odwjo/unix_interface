#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <ftw.h>
#include "tlpi_hdr.h"

#define BUF_SIZE 500
#define BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))

struct node{
    int fd;
    struct node *next;
    char pathname[BUF_SIZE];
};

struct list{
    struct node *head;
};

void initlist(struct list *plist)
{
    plist->head = NULL;
}

int addnode(struct list *plist, const char *pathname, int fd)
{
    struct node *pnode;
    struct node *tnode;
    
    tnode = (struct node *)malloc(sizeof(struct node));
    strcpy(tnode->pathname, pathname);
    tnode->fd = fd;
    tnode->next = NULL;

    if (NULL == plist->head)
        plist->head = tnode;
    else {
        pnode = plist->head;
        while(pnode->next)
            pnode = pnode->next;
        pnode->next = tnode;
    }

    printf("adding ... path:%s, wd:%d\n", pathname, fd);
}

int delnodebyfd(struct list *plist, int fd)
{
    struct node *pnode = plist->head;
    struct node *tnode;
    while (pnode) {
        if (pnode->fd == fd)
        {
            if (pnode == plist->head) {
                plist->head = pnode->next;
            } else {
                tnode->next = pnode->next;
            }
            free(pnode);
        }
        tnode = pnode;
        pnode = pnode->next;
    }
    if (pnode)
        return 0;
    return 1;
}

int delnodebypathnm(struct list *plist, char *pathname)
{
    struct node *pnode = plist->head;
    struct node *tnode;
    while (pnode) {
        if (strncmp(pnode->pathname, pathname, BUF_SIZE) == 0)
        {
            printf("del : %s\n", pathname);
            if (pnode == plist->head) {
                plist->head = pnode->next;
            } else {
                tnode->next = pnode->next;
            }
            free(pnode);
            return 0;
        }
        tnode = pnode;
        pnode = pnode->next;
    }
    return 1;
}

struct node* searchlistbyfd(struct list *plist, int fd)
{
    struct node *head = plist->head;
    while (head && head->fd != fd)
    {
        head = head->next;
    }
    return head;
}

void freelist(struct list *plist)
{
    struct node *ptemp = plist->head;
    plist->head = NULL;
    struct node *pftemp;
    while(ptemp)
    {
        pftemp = ptemp->next;
        free(ptemp);
        ptemp = pftemp;
    }
}

struct list *getlist()
{
    static struct list glist;
    static int i = 1;
    if (i)
        initlist(&glist);
    i = 0;
    return &glist;
}

int getInotiFd()
{
    static int inotifyFd = -1;
    if (inotifyFd == -1)
        inotifyFd = inotify_init();
    return inotifyFd;
}

int nftw_aux(const char *dirpath, const struct stat *sb, int typeflag,
        struct FTW *fwtbuf)
{
    int initFd, wd;
    struct list *plist;
    if (typeflag == FTW_D)
    {
        initFd = getInotiFd();
        if (-1 == initFd)
            errExit("getInotiFD");
        wd = inotify_add_watch(initFd, dirpath, IN_ALL_EVENTS);
        if (-1 == wd)
            errExit("inotify_add_watch");
        plist = getlist();
        if (NULL == plist)
            errExit("getlist");
        addnode(plist, dirpath, wd);
    }
    return 0;
}

int is_path(const char *pathname)
{
    struct stat statbuf;
    if (-1 == stat(pathname, &statbuf))
        errExit("stat");
    if (S_IFDIR == (statbuf.st_mode & S_IFMT))
    {
        printf("dir: %s\n", pathname);
        return 1;
    }
    printf("not dir: %s\n", pathname);
    return 0;
}

void dealInotifyEvent(struct inotify_event *i)
{
    int fd, wd;
    char *pathname;
    char pathBUF[BUF_SIZE] = {0};
    struct list *plist;
    struct node *pnode;
    printf("wd =%2d; ", i->wd);
    if (i->cookie > 0)
        printf("cookie =%4d; ", i->cookie);
    
    printf("mask =  ");
    if (i->mask & IN_ACCESS) printf("%22s","IN_ACCESS ");
    if (i->mask & IN_ATTRIB) printf("%22s","IN_ATTRIB ");
    if (i->mask & IN_CLOSE_NOWRITE) printf("%22s","IN_CLOSE_NOWRITE ");
    if (i->mask & IN_CLOSE_WRITE) printf("%22s","IN_CLOSE_WRITE ");
    if (i->mask & IN_CREATE) printf("%22s","IN_CREATE ");
    if (i->mask & IN_DELETE) printf("%22s","IN_DELETE ");
    if (i->mask & IN_DELETE_SELF) printf("%22s","IN_DELETE_SELF ");
    if (i->mask & IN_IGNORED) printf("%22s","IN_IGNORED ");
    if (i->mask & IN_ISDIR) printf("%22s","IN_ISDIR ");
    if (i->mask & IN_MODIFY) printf("%22s","IN_MODIFY ");
    if (i->mask & IN_MOVE_SELF) printf("%22s","IN_MOVE_SELF ");
    if (i->mask & IN_MOVED_FROM) printf("%22s","IN_MOVED_FROM ");
    if (i->mask & IN_MOVED_TO) printf("%22s","IN_MOVED_TO ");
    if (i->mask & IN_OPEN) printf("%22s","IN_OPEN ");
    if (i->mask & IN_Q_OVERFLOW) printf("%22s","IN_Q_OVERFLOW ");
    if (i->mask & IN_UNMOUNT) printf("%22s","IN_UNMOUNT ");
    printf("\n");

    plist = getlist();
    if (plist == NULL)
        errExit("getlist");
    pnode = searchlistbyfd(plist, i->wd);
    if (NULL == pnode)
        printf("wd: %d is not in the list.\n", i->wd);
    else {
        pathname = pnode->pathname;
        strncpy(pathBUF, pathname, BUF_SIZE);
        strncat(pathBUF, "/", BUF_SIZE);
        strncat(pathBUF, i->name, BUF_SIZE);
    
        fd = getInotiFd();
        if (-1 == fd)
            errExit("getInotiFd");
    
        if (i->mask & IN_ISDIR && (i->mask & IN_MOVED_TO || i->mask & IN_CREATE))
        {
            wd = inotify_add_watch(fd, pathBUF, IN_ALL_EVENTS);
            if (-1 == wd)
                errExit("inotify_add_watch");
            printf("%d for %s added\n", wd, pathBUF);
            addnode(plist, pathBUF, wd);
        } else if (i->mask & IN_DELETE_SELF) 
        {
            if (delnodebypathnm(plist, pathname))
                errExit("delnodebypathnm");
        } else if (((i->mask & IN_DELETE) || (i->mask & IN_MOVED_FROM)) && (i->mask & IN_ISDIR))
        {
            //if (delnodebypathnm(plist, pathBUF))
            //    errExit("delnodebypathnm");
        }
    }

    if (i->len > 0)
        printf("      name = %s\n", i->name);
}

void  addwatch(const char *pathname)
{
    int inotifyFd, wd, j;
    char buf[BUF_LEN];
    ssize_t numRead;
    char *p;
    struct inotify_event *event;
    struct list *plist;

    plist = getlist();
    if (NULL == plist)
        errExit("getlist");

    inotifyFd = getInotiFd();
    if (inotifyFd == -1)
        errExit("inotify_init");

    if (!is_path(pathname)) {
        wd = inotify_add_watch(inotifyFd, pathname, IN_ALL_EVENTS);
        if (wd == -1)
            errExit("inotify_add_watch");
    } else {
        wd = nftw(pathname, nftw_aux, 20, 0);
        if (wd == -1)
            errExit("nftw");
    }

    for (;;) {
        numRead = read(inotifyFd, buf, BUF_LEN);
        if (numRead == 0)
            fatal("read() from inotify fd return 0");
        if (numRead == -1)
            errExit("read");

        printf("Read %ld bytes from inotify fd\n", (long) numRead);

        for (p = buf; p < buf + numRead; ) {
            event = (struct inotify_event *)p;
            dealInotifyEvent(event);

            p += sizeof(struct inotify_event) + event->len;
        }
    }
    exit(EXIT_SUCCESS);
}


int main(int argc, char *argv[])
{
    int i = 0;
    if(argc > 1 && strcmp(argv[1], "--help") == 0)
        usageErr("%s [file|dir ...]", argv[0]);
    if (argc == 1)
        addwatch(".");
    else
        for (i = 1; i != argc; ++i){
            addwatch(argv[i]);
        }
    exit(EXIT_SUCCESS);
}
