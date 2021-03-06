#define MVM_FILE_FLOCK_SHARED        1       /* Shared lock. Read lock */
#define MVM_FILE_FLOCK_EXCLUSIVE     2       /* Exclusive lock. Write lock. */
#define MVM_FILE_FLOCK_TYPEMASK      0x000F  /* a mask of lock type */
#define MVM_FILE_FLOCK_NONBLOCK      0x0010  /* asynchronous block during
                                              * locking the file */
#define MVM_stat_exists              0
#define MVM_stat_filesize            1
#define MVM_stat_isdir               2
#define MVM_stat_isreg               3
#define MVM_stat_isdev               4
#define MVM_stat_createtime          5
#define MVM_stat_accesstime          6
#define MVM_stat_modifytime          7
#define MVM_stat_changetime          8
#define MVM_stat_backuptime          9
#define MVM_stat_uid                10
#define MVM_stat_gid                11
#define MVM_stat_islnk              12
#define MVM_stat_platform_dev       -1
#define MVM_stat_platform_inode     -2
#define MVM_stat_platform_mode      -3
#define MVM_stat_platform_nlinks    -4
#define MVM_stat_platform_devtype   -5
#define MVM_stat_platform_blocksize -6
#define MVM_stat_platform_blocks    -7

MVMint64 MVM_file_stat(MVMThreadContext *tc, MVMString *filename, MVMint64 status);
void MVM_file_copy(MVMThreadContext *tc, MVMString *src, MVMString *dest);
void MVM_file_rename(MVMThreadContext *tc, MVMString *src, MVMString *dest);
void MVM_file_delete(MVMThreadContext *tc, MVMString *f);
void MVM_file_chmod(MVMThreadContext *tc, MVMString *f, MVMint64 flag);
MVMint64 MVM_file_exists(MVMThreadContext *tc, MVMString *f);
MVMint64 MVM_file_isreadable(MVMThreadContext *tc, MVMString *filename);
MVMint64 MVM_file_iswritable(MVMThreadContext *tc, MVMString *filename);
MVMint64 MVM_file_isexecutable(MVMThreadContext *tc, MVMString *filename);
MVMString * MVM_file_readline_interactive_fh(MVMThreadContext *tc, MVMObject *oshandle, MVMString *prompt);
MVMString * MVM_file_slurp(MVMThreadContext *tc, MVMString *filename, MVMString *encoding);
void MVM_file_spew(MVMThreadContext *tc, MVMString *output, MVMString *filename, MVMString *encoding);
MVMObject * MVM_file_get_stdstream(MVMThreadContext *tc, MVMuint8 type, MVMuint8 readable);
MVMString * MVM_file_in_libpath(MVMThreadContext *tc, MVMString *orig);
void MVM_file_link(MVMThreadContext *tc, MVMString *oldpath, MVMString *newpath);
void MVM_file_symlink(MVMThreadContext *tc, MVMString *oldpath, MVMString *newpath);
