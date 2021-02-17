LEVEL2 {}

Sets the magic(4) file(1) substring used to detect this type of
archiver (eg "gzip compressed data"). The search type is
case-sensitive substring (strstr()). Look in /etc/magic for
more information on the detected types.

STRING1 {Zip archive} S 39 Archiver 1, detection string

A description of the archiver.

NAME1 {PKZIP 2.04g} S 39 Archiver 1, description

Short file type description (eg "ZIP", "TAR/GZIP", etc).

TYPE1 {ZIP} S 15 Archiver 1, file type (extension)

Used by the file libraries to stamp archives with the BBS's ASCII/ANSI
logo. This specifies a command that will add a comment to the archive
(the kind that appears while the archive is uncompressed. Some archivers
don't have this feature -- do not include a comment command for
them. One %s is needed and replaced by the name of the archive. The
actual comment comes from the standard input. YOU have to take care to
terminate it properly (some archivers like infozip need a period to end
the comment).

COMMENT1 {zip -z %s} S 256 Archiver 1, command to add comment

Shell command that creates a compressed file. Accepts two arguments. The
first is the name of the archive to be created. The second is a space
separated list of files to be included (wildcards are possible). You
HAVE to add two %s specifiers in your command.

NB: set up the command line so that any subdirectories ARE recursed into
and included in the generated archive. Go for behaviour similar to that
of tar(1).

COMPRESS1 {zip -9r %s %s} S 256 Archiver 1, compression

Like compress, only decompresses an archive. Two %s are needed here; the
first is the archive name, the second the list of files to be retrieved
from the archive.  The second argument may be blank, in which case all
of the files should be retrieved. Any directories should be created,
like tar(1) does.

UNCOMPRESS1 {unzip %s %s} S 256 Archiver 1, decompression

Shell command that views the contents of an archive file.  The command
is called with one argument, the name of the file whose contents are to
be viewed. You HAVE to add a %s somewhere in the command (it will be
replaced by the filename).

VIEW1 {~unzip -v %s|awk -- '/^ Length  Method/ {a=1~}{if(a)print~}'} S 256 Archiver 1, view contents






Sets the magic(4) file(1) substring used to detect this type of
archiver (eg "gzip compressed data"). The search type is
case-sensitive substring (strstr()). Look in /etc/magic for
more information on the detected types.

STRING2 {ARJ archive} S 39 Archiver 2, detection string

A description of the archiver.

NAME2 {ARJ 2.30} S 39 Archiver 2, description

Short file type description (eg "ZIP", "TAR/GZIP", etc).

TYPE2 {ARJ} S 15 Archiver 2, file type (extension)

Used by the file libraries to stamp archives with the BBS's ASCII/ANSI
logo. This specifies a command that will add a comment to the archive
(the kind that appears while the archive is uncompressed. Some archivers
don't have this feature -- do not include a comment command for
them. One %s is needed and replaced by the name of the archive. The
actual comment comes from the standard input. YOU have to take care to
terminate it properly (some archivers like infozip need a period to end
the comment).

COMMENT2 {} S 256 Archiver 2, command to add comment

Shell command that creates a compressed file. Accepts two arguments. The
first is the name of the archive to be created. The second is a space
separated list of files to be included (wildcards are possible). You
HAVE to add two %s specifiers in your command.

NB: set up the command line so that any subdirectories ARE recursed into
and included in the generated archive. Go for behaviour similar to that
of tar(1).

COMPRESS2 {} S 256 Archiver 2, compression

Like compress, only decompresses an archive. Two %s are needed here; the
first is the archive name, the second the list of files to be retrieved
from the archive.  The second argument may be blank, in which case all
of the files should be retrieved. Any directories should be created,
like tar(1) does.

UNCOMPRESS2 {(unarj x %s && a=`\echo '%s'|\tr " " "|"`&&\rm `\ls *|egrep -v $a`)} S 256 Archiver 2, decompression

Shell command that views the contents of an archive file.  The command
is called with one argument, the name of the file whose contents are to
be viewed. You HAVE to add a %s somewhere in the command (it will be
replaced by the filename).

VIEW2 {unarj l %s|awk -- '/^Archive date/ {a=1~}{if(a)print~}'} S 256 Archiver 2, view contents






Sets the magic(4) file(1) substring used to detect this type of
archiver (eg "gzip compressed data"). The search type is
case-sensitive substring (strstr()). Look in /etc/magic for
more information on the detected types.

STRING3 {LHarc archive} S 39 Archiver 3, detection string

A description of the archiver.

NAME3 {LHARC 1.02} S 39 Archiver 3, description

Short file type description (eg "ZIP", "TAR/GZIP", etc).

TYPE3 {LZH} S 15 Archiver 3, file type (extension)

Used by the file libraries to stamp archives with the BBS's ASCII/ANSI
logo. This specifies a command that will add a comment to the archive
(the kind that appears while the archive is uncompressed. Some archivers
don't have this feature -- do not include a comment command for
them. One %s is needed and replaced by the name of the archive. The
actual comment comes from the standard input. YOU have to take care to
terminate it properly (some archivers like infozip need a period to end
the comment).

COMMENT3 {} S 256 Archiver 3, command to add comment

Shell command that creates a compressed file. Accepts two arguments. The
first is the name of the archive to be created. The second is a space
separated list of files to be included (wildcards are possible). You
HAVE to add two %s specifiers in your command.

NB: set up the command line so that any subdirectories ARE recursed into
and included in the generated archive. Go for behaviour similar to that
of tar(1).

COMPRESS3 {lha ao %s %s} S 256 Archiver 3, compression

Like compress, only decompresses an archive. Two %s are needed here; the
first is the archive name, the second the list of files to be retrieved
from the archive.  The second argument may be blank, in which case all
of the files should be retrieved. Any directories should be created,
like tar(1) does.

UNCOMPRESS3 {lha xvf %s %s} S 256 Archiver 3, decompression

Shell command that views the contents of an archive file.  The command
is called with one argument, the name of the file whose contents are to
be viewed. You HAVE to add a %s somewhere in the command (it will be
replaced by the filename).

VIEW3 {lha v %s} S 256 Archiver 3, view contents






Sets the magic(4) file(1) substring used to detect this type of
archiver (eg "gzip compressed data"). The search type is
case-sensitive substring (strstr()). Look in /etc/magic for
more information on the detected types.

STRING4 {ZOO archive} S 39 Archiver 4, detection string

A description of the archiver.

NAME4 {ZOO 2.1} S 39 Archiver 4, description

Short file type description (eg "ZIP", "TAR/GZIP", etc).

TYPE4 {ZOO} S 15 Archiver 4, file type (extension)

Used by the file libraries to stamp archives with the BBS's ASCII/ANSI
logo. This specifies a command that will add a comment to the archive
(the kind that appears while the archive is uncompressed. Some archivers
don't have this feature -- do not include a comment command for
them. One %s is needed and replaced by the name of the archive. The
actual comment comes from the standard input. YOU have to take care to
terminate it properly (some archivers like infozip need a period to end
the comment).

COMMENT4 {zoo cA %s} S 256 Archiver 4, command to add comment

Shell command that creates a compressed file. Accepts two arguments. The
first is the name of the archive to be created. The second is a space
separated list of files to be included (wildcards are possible). You
HAVE to add two %s specifiers in your command.

NB: set up the command line so that any subdirectories ARE recursed into
and included in the generated archive. Go for behaviour similar to that
of tar(1).

COMPRESS4 {zoo ahPP %s %s} S 256 Archiver 4, compression

Like compress, only decompresses an archive. Two %s are needed here; the
first is the archive name, the second the list of files to be retrieved
from the archive.  The second argument may be blank, in which case all
of the files should be retrieved. Any directories should be created,
like tar(1) does.

UNCOMPRESS4 {zoo e. %s %s} S 256 Archiver 4, decompression

Shell command that views the contents of an archive file.  The command
is called with one argument, the name of the file whose contents are to
be viewed. You HAVE to add a %s somewhere in the command (it will be
replaced by the filename).

VIEW4 {zoo v %s|awk -- '/^Length/ {a=1~}{if(a)print~}'} S 256 Archiver 4, view contents






Sets the magic(4) file(1) substring used to detect this type of
archiver (eg "gzip compressed data"). The search type is
case-sensitive substring (strstr()). Look in /etc/magic for
more information on the detected types.

STRING5 {gzip compressed data} S 39 Archiver 5, detection string

A description of the archiver.

NAME5 {Tar & GNUZip (Unix)} S 39 Archiver 5, description

Short file type description (eg "ZIP", "TAR/GZIP", etc).

TYPE5 {TAR/GZIP} S 15 Archiver 5, file type (extension)

Used by the file libraries to stamp archives with the BBS's ASCII/ANSI
logo. This specifies a command that will add a comment to the archive
(the kind that appears while the archive is uncompressed. Some archivers
don't have this feature -- do not include a comment command for
them. One %s is needed and replaced by the name of the archive. The
actual comment comes from the standard input. YOU have to take care to
terminate it properly (some archivers like infozip need a period to end
the comment).

COMMENT5 {} S 256 Archiver 5, command to add comment

Shell command that creates a compressed file. Accepts two arguments. The
first is the name of the archive to be created. The second is a space
separated list of files to be included (wildcards are possible). You
HAVE to add two %s specifiers in your command.

NB: set up the command line so that any subdirectories ARE recursed into
and included in the generated archive. Go for behaviour similar to that
of tar(1).

COMPRESS5 {(f="%s"; tar cvf - %s |gzip -9c >$f)} S 256 Archiver 5, compression

Like compress, only decompresses an archive. Two %s are needed here; the
first is the archive name, the second the list of files to be retrieved
from the archive.  The second argument may be blank, in which case all
of the files should be retrieved. Any directories should be created,
like tar(1) does.

UNCOMPRESS5 {tar -xzvf %s >&/dev/null} S 256 Archiver 5, decompression

Shell command that views the contents of an archive file.  The command
is called with one argument, the name of the file whose contents are to
be viewed. You HAVE to add a %s somewhere in the command (it will be
replaced by the filename).

VIEW5 {(f="%s"; gzip -l $f; tar -tzvf $f) >&/dev/null} S 256 Archiver 5, view contents






Sets the magic(4) file(1) substring used to detect this type of
archiver (eg "gzip compressed data"). The search type is
case-sensitive substring (strstr()). Look in /etc/magic for
more information on the detected types.

STRING6 {compressed data} S 39 Archiver 6, detection string

A description of the archiver.

NAME6 {Tar & Compress (Unix)} S 39 Archiver 6, description

Short file type description (eg "ZIP", "TAR/GZIP", etc).

TYPE6 {TAR/Z} S 15 Archiver 6, file type (extension)

Used by the file libraries to stamp archives with the BBS's ASCII/ANSI
logo. This specifies a command that will add a comment to the archive
(the kind that appears while the archive is uncompressed. Some archivers
don't have this feature -- do not include a comment command for
them. One %s is needed and replaced by the name of the archive. The
actual comment comes from the standard input. YOU have to take care to
terminate it properly (some archivers like infozip need a period to end
the comment).

COMMENT6 {} S 256 Archiver 6, command to add comment

Shell command that creates a compressed file. Accepts two arguments. The
first is the name of the archive to be created. The second is a space
separated list of files to be included (wildcards are possible). You
HAVE to add two %s specifiers in your command.

NB: set up the command line so that any subdirectories ARE recursed into
and included in the generated archive. Go for behaviour similar to that
of tar(1).

COMPRESS6 {(f="%s"; tar cvf - %s |compress -c >$f)} S 256 Archiver 6, compression

Like compress, only decompresses an archive. Two %s are needed here; the
first is the archive name, the second the list of files to be retrieved
from the archive.  The second argument may be blank, in which case all
of the files should be retrieved. Any directories should be created,
like tar(1) does.

UNCOMPRESS6 {tar -xzvf %s >&/dev/null} S 256 Archiver 6, decompression

Shell command that views the contents of an archive file.  The command
is called with one argument, the name of the file whose contents are to
be viewed. You HAVE to add a %s somewhere in the command (it will be
replaced by the filename).

VIEW6 {(f="%s"; gzip -l $f;tar -tvf $f)>&/dev/null} S 256 Archiver 6, view contents






Sets the magic(4) file(1) substring used to detect this type of
archiver (eg "gzip compressed data"). The search type is
case-sensitive substring (strstr()). Look in /etc/magic for
more information on the detected types.

STRING7 {} S 39 Archiver 7, detection string

A description of the archiver.

NAME7 {} S 39 Archiver 7, description

Short file type description (eg "ZIP", "TAR/GZIP", etc).

TYPE7 {} S 15 Archiver 7, file type (extension)

Used by the file libraries to stamp archives with the BBS's ASCII/ANSI
logo. This specifies a command that will add a comment to the archive
(the kind that appears while the archive is uncompressed. Some archivers
don't have this feature -- do not include a comment command for
them. One %s is needed and replaced by the name of the archive. The
actual comment comes from the standard input. YOU have to take care to
terminate it properly (some archivers like infozip need a period to end
the comment).

COMMENT7 {} S 256 Archiver 7, command to add comment

Shell command that creates a compressed file. Accepts two arguments. The
first is the name of the archive to be created. The second is a space
separated list of files to be included (wildcards are possible). You
HAVE to add two %s specifiers in your command.

NB: set up the command line so that any subdirectories ARE recursed into
and included in the generated archive. Go for behaviour similar to that
of tar(1).

COMPRESS7 {} S 256 Archiver 7, compression

Like compress, only decompresses an archive. Two %s are needed here; the
first is the archive name, the second the list of files to be retrieved
from the archive.  The second argument may be blank, in which case all
of the files should be retrieved. Any directories should be created,
like tar(1) does.

UNCOMPRESS7 {} S 256 Archiver 7, decompression

Shell command that views the contents of an archive file.  The command
is called with one argument, the name of the file whose contents are to
be viewed. You HAVE to add a %s somewhere in the command (it will be
replaced by the filename).

VIEW7 {} S 256 Archiver 7, view contents






Sets the magic(4) file(1) substring used to detect this type of
archiver (eg "gzip compressed data"). The search type is
case-sensitive substring (strstr()). Look in /etc/magic for
more information on the detected types.

STRING8 {} S 39 Archiver 8, detection string

A description of the archiver.

NAME8 {} S 39 Archiver 8, description

Short file type description (eg "ZIP", "TAR/GZIP", etc).

TYPE8 {} S 15 Archiver 8, file type (extension)

Used by the file libraries to stamp archives with the BBS's ASCII/ANSI
logo. This specifies a command that will add a comment to the archive
(the kind that appears while the archive is uncompressed. Some archivers
don't have this feature -- do not include a comment command for
them. One %s is needed and replaced by the name of the archive. The
actual comment comes from the standard input. YOU have to take care to
terminate it properly (some archivers like infozip need a period to end
the comment).

COMMENT8 {} S 256 Archiver 8, command to add comment

Shell command that creates a compressed file. Accepts two arguments. The
first is the name of the archive to be created. The second is a space
separated list of files to be included (wildcards are possible). You
HAVE to add two %s specifiers in your command.

NB: set up the command line so that any subdirectories ARE recursed into
and included in the generated archive. Go for behaviour similar to that
of tar(1).

COMPRESS8 {} S 256 Archiver 8, compression

Like compress, only decompresses an archive. Two %s are needed here; the
first is the archive name, the second the list of files to be retrieved
from the archive.  The second argument may be blank, in which case all
of the files should be retrieved. Any directories should be created,
like tar(1) does.

UNCOMPRESS8 {} S 256 Archiver 8, decompression

Shell command that views the contents of an archive file.  The command
is called with one argument, the name of the file whose contents are to
be viewed. You HAVE to add a %s somewhere in the command (it will be
replaced by the filename).

VIEW8 {} S 256 Archiver 8, view contents






Sets the magic(4) file(1) substring used to detect this type of
archiver (eg "gzip compressed data"). The search type is
case-sensitive substring (strstr()). Look in /etc/magic for
more information on the detected types.

STRING9 {} S 39 Archiver 9, detection string

A description of the archiver.

NAME9 {} S 39 Archiver 9, description

Short file type description (eg "ZIP", "TAR/GZIP", etc).

TYPE9 {} S 15 Archiver 9, file type (extension)

Used by the file libraries to stamp archives with the BBS's ASCII/ANSI
logo. This specifies a command that will add a comment to the archive
(the kind that appears while the archive is uncompressed. Some archivers
don't have this feature -- do not include a comment command for
them. One %s is needed and replaced by the name of the archive. The
actual comment comes from the standard input. YOU have to take care to
terminate it properly (some archivers like infozip need a period to end
the comment).

COMMENT9 {} S 256 Archiver 9, command to add comment

Shell command that creates a compressed file. Accepts two arguments. The
first is the name of the archive to be created. The second is a space
separated list of files to be included (wildcards are possible). You
HAVE to add two %s specifiers in your command.

NB: set up the command line so that any subdirectories ARE recursed into
and included in the generated archive. Go for behaviour similar to that
of tar(1).

COMPRESS9 {} S 256 Archiver 9, compression

Like compress, only decompresses an archive. Two %s are needed here; the
first is the archive name, the second the list of files to be retrieved
from the archive.  The second argument may be blank, in which case all
of the files should be retrieved. Any directories should be created,
like tar(1) does.

UNCOMPRESS9 {} S 256 Archiver 9, decompression

Shell command that views the contents of an archive file.  The command
is called with one argument, the name of the file whose contents are to
be viewed. You HAVE to add a %s somewhere in the command (it will be
replaced by the filename).

VIEW9 {} S 256 Archiver 9, view contents






Sets the magic(4) file(1) substring used to detect this type of
archiver (eg "gzip compressed data"). The search type is
case-sensitive substring (strstr()). Look in /etc/magic for
more information on the detected types.

STRING10 {} S 39 Archiver 10, detection string

A description of the archiver.

NAME10 {} S 39 Archiver 10, description

Short file type description (eg "ZIP", "TAR/GZIP", etc).

TYPE10 {} S 15 Archiver 10, file type (extension)

Used by the file libraries to stamp archives with the BBS's ASCII/ANSI
logo. This specifies a command that will add a comment to the archive
(the kind that appears while the archive is uncompressed. Some archivers
don't have this feature -- do not include a comment command for
them. One %s is needed and replaced by the name of the archive. The
actual comment comes from the standard input. YOU have to take care to
terminate it properly (some archivers like infozip need a period to end
the comment).

COMMENT10 {} S 256 Archiver 10, command to add comment

Shell command that creates a compressed file. Accepts two arguments. The
first is the name of the archive to be created. The second is a space
separated list of files to be included (wildcards are possible). You
HAVE to add two %s specifiers in your command.

NB: set up the command line so that any subdirectories ARE recursed into
and included in the generated archive. Go for behaviour similar to that
of tar(1).

COMPRESS10 {} S 256 Archiver 10, compression

Like compress, only decompresses an archive. Two %s are needed here; the
first is the archive name, the second the list of files to be retrieved
from the archive.  The second argument may be blank, in which case all
of the files should be retrieved. Any directories should be created,
like tar(1) does.

UNCOMPRESS10 {} S 256 Archiver 10, decompression

Shell command that views the contents of an archive file.  The command
is called with one argument, the name of the file whose contents are to
be viewed. You HAVE to add a %s somewhere in the command (it will be
replaced by the filename).

VIEW10 {} S 256 Archiver 10, view contents






Sets the magic(4) file(1) substring used to detect this type of
archiver (eg "gzip compressed data"). The search type is
case-sensitive substring (strstr()). Look in /etc/magic for
more information on the detected types.

STRING11 {} S 39 Archiver 11, detection string

A description of the archiver.

NAME11 {} S 39 Archiver 11, description

Short file type description (eg "ZIP", "TAR/GZIP", etc).

TYPE11 {} S 15 Archiver 11, file type (extension)

Used by the file libraries to stamp archives with the BBS's ASCII/ANSI
logo. This specifies a command that will add a comment to the archive
(the kind that appears while the archive is uncompressed. Some archivers
don't have this feature -- do not include a comment command for
them. One %s is needed and replaced by the name of the archive. The
actual comment comes from the standard input. YOU have to take care to
terminate it properly (some archivers like infozip need a period to end
the comment).

COMMENT11 {} S 256 Archiver 11, command to add comment

Shell command that creates a compressed file. Accepts two arguments. The
first is the name of the archive to be created. The second is a space
separated list of files to be included (wildcards are possible). You
HAVE to add two %s specifiers in your command.

NB: set up the command line so that any subdirectories ARE recursed into
and included in the generated archive. Go for behaviour similar to that
of tar(1).

COMPRESS11 {} S 256 Archiver 11, compression

Like compress, only decompresses an archive. Two %s are needed here; the
first is the archive name, the second the list of files to be retrieved
from the archive.  The second argument may be blank, in which case all
of the files should be retrieved. Any directories should be created,
like tar(1) does.

UNCOMPRESS11 {} S 256 Archiver 11, decompression

Shell command that views the contents of an archive file.  The command
is called with one argument, the name of the file whose contents are to
be viewed. You HAVE to add a %s somewhere in the command (it will be
replaced by the filename).

VIEW11 {} S 256 Archiver 11, view contents






Sets the magic(4) file(1) substring used to detect this type of
archiver (eg "gzip compressed data"). The search type is
case-sensitive substring (strstr()). Look in /etc/magic for
more information on the detected types.

STRING12 {} S 39 Archiver 12, detection string

A description of the archiver.

NAME12 {} S 39 Archiver 12, description

Short file type description (eg "ZIP", "TAR/GZIP", etc).

TYPE12 {} S 15 Archiver 12, file type (extension)

Used by the file libraries to stamp archives with the BBS's ASCII/ANSI
logo. This specifies a command that will add a comment to the archive
(the kind that appears while the archive is uncompressed. Some archivers
don't have this feature -- do not include a comment command for
them. One %s is needed and replaced by the name of the archive. The
actual comment comes from the standard input. YOU have to take care to
terminate it properly (some archivers like infozip need a period to end
the comment).

COMMENT12 {} S 256 Archiver 12, command to add comment

Shell command that creates a compressed file. Accepts two arguments. The
first is the name of the archive to be created. The second is a space
separated list of files to be included (wildcards are possible). You
HAVE to add two %s specifiers in your command.

NB: set up the command line so that any subdirectories ARE recursed into
and included in the generated archive. Go for behaviour similar to that
of tar(1).

COMPRESS12 {} S 256 Archiver 12, compression

Like compress, only decompresses an archive. Two %s are needed here; the
first is the archive name, the second the list of files to be retrieved
from the archive.  The second argument may be blank, in which case all
of the files should be retrieved. Any directories should be created,
like tar(1) does.

UNCOMPRESS12 {} S 256 Archiver 12, decompression

Shell command that views the contents of an archive file.  The command
is called with one argument, the name of the file whose contents are to
be viewed. You HAVE to add a %s somewhere in the command (it will be
replaced by the filename).

VIEW12 {} S 256 Archiver 12, view contents






Sets the magic(4) file(1) substring used to detect this type of
archiver (eg "gzip compressed data"). The search type is
case-sensitive substring (strstr()). Look in /etc/magic for
more information on the detected types.

STRING13 {} S 39 Archiver 13, detection string

A description of the archiver.

NAME13 {} S 39 Archiver 13, description

Short file type description (eg "ZIP", "TAR/GZIP", etc).

TYPE13 {} S 15 Archiver 13, file type (extension)

Used by the file libraries to stamp archives with the BBS's ASCII/ANSI
logo. This specifies a command that will add a comment to the archive
(the kind that appears while the archive is uncompressed. Some archivers
don't have this feature -- do not include a comment command for
them. One %s is needed and replaced by the name of the archive. The
actual comment comes from the standard input. YOU have to take care to
terminate it properly (some archivers like infozip need a period to end
the comment).

COMMENT13 {} S 256 Archiver 13, command to add comment

Shell command that creates a compressed file. Accepts two arguments. The
first is the name of the archive to be created. The second is a space
separated list of files to be included (wildcards are possible). You
HAVE to add two %s specifiers in your command.

NB: set up the command line so that any subdirectories ARE recursed into
and included in the generated archive. Go for behaviour similar to that
of tar(1).

COMPRESS13 {} S 256 Archiver 13, compression

Like compress, only decompresses an archive. Two %s are needed here; the
first is the archive name, the second the list of files to be retrieved
from the archive.  The second argument may be blank, in which case all
of the files should be retrieved. Any directories should be created,
like tar(1) does.

UNCOMPRESS13 {} S 256 Archiver 13, decompression

Shell command that views the contents of an archive file.  The command
is called with one argument, the name of the file whose contents are to
be viewed. You HAVE to add a %s somewhere in the command (it will be
replaced by the filename).

VIEW13 {} S 256 Archiver 13, view contents






Sets the magic(4) file(1) substring used to detect this type of
archiver (eg "gzip compressed data"). The search type is
case-sensitive substring (strstr()). Look in /etc/magic for
more information on the detected types.

STRING14 {} S 39 Archiver 14, detection string

A description of the archiver.

NAME14 {} S 39 Archiver 14, description

Short file type description (eg "ZIP", "TAR/GZIP", etc).

TYPE14 {} S 15 Archiver 14, file type (extension)

Used by the file libraries to stamp archives with the BBS's ASCII/ANSI
logo. This specifies a command that will add a comment to the archive
(the kind that appears while the archive is uncompressed. Some archivers
don't have this feature -- do not include a comment command for
them. One %s is needed and replaced by the name of the archive. The
actual comment comes from the standard input. YOU have to take care to
terminate it properly (some archivers like infozip need a period to end
the comment).

COMMENT14 {} S 256 Archiver 14, command to add comment

Shell command that creates a compressed file. Accepts two arguments. The
first is the name of the archive to be created. The second is a space
separated list of files to be included (wildcards are possible). You
HAVE to add two %s specifiers in your command.

NB: set up the command line so that any subdirectories ARE recursed into
and included in the generated archive. Go for behaviour similar to that
of tar(1).

COMPRESS14 {} S 256 Archiver 14, compression

Like compress, only decompresses an archive. Two %s are needed here; the
first is the archive name, the second the list of files to be retrieved
from the archive.  The second argument may be blank, in which case all
of the files should be retrieved. Any directories should be created,
like tar(1) does.

UNCOMPRESS14 {} S 256 Archiver 14, decompression

Shell command that views the contents of an archive file.  The command
is called with one argument, the name of the file whose contents are to
be viewed. You HAVE to add a %s somewhere in the command (it will be
replaced by the filename).

VIEW14 {} S 256 Archiver 14, view contents






Sets the magic(4) file(1) substring used to detect this type of
archiver (eg "gzip compressed data"). The search type is
case-sensitive substring (strstr()). Look in /etc/magic for
more information on the detected types.

STRING15 {} S 39 Archiver 15, detection string

A description of the archiver.

NAME15 {} S 39 Archiver 15, description

Short file type description (eg "ZIP", "TAR/GZIP", etc).

TYPE15 {} S 15 Archiver 15, file type (extension)

Used by the file libraries to stamp archives with the BBS's ASCII/ANSI
logo. This specifies a command that will add a comment to the archive
(the kind that appears while the archive is uncompressed. Some archivers
don't have this feature -- do not include a comment command for
them. One %s is needed and replaced by the name of the archive. The
actual comment comes from the standard input. YOU have to take care to
terminate it properly (some archivers like infozip need a period to end
the comment).

COMMENT15 {} S 256 Archiver 15, command to add comment

Shell command that creates a compressed file. Accepts two arguments. The
first is the name of the archive to be created. The second is a space
separated list of files to be included (wildcards are possible). You
HAVE to add two %s specifiers in your command.

NB: set up the command line so that any subdirectories ARE recursed into
and included in the generated archive. Go for behaviour similar to that
of tar(1).

COMPRESS15 {} S 256 Archiver 15, compression

Like compress, only decompresses an archive. Two %s are needed here; the
first is the archive name, the second the list of files to be retrieved
from the archive.  The second argument may be blank, in which case all
of the files should be retrieved. Any directories should be created,
like tar(1) does.

UNCOMPRESS15 {} S 256 Archiver 15, decompression

Shell command that views the contents of an archive file.  The command
is called with one argument, the name of the file whose contents are to
be viewed. You HAVE to add a %s somewhere in the command (it will be
replaced by the filename).

VIEW15 {} S 256 Archiver 15, view contents






Sets the magic(4) file(1) substring used to detect this type of
archiver (eg "gzip compressed data"). The search type is
case-sensitive substring (strstr()). Look in /etc/magic for
more information on the detected types.

STRING16 {} S 39 Archiver 16, detection string

A description of the archiver.

NAME16 {} S 39 Archiver 16, description

Short file type description (eg "ZIP", "TAR/GZIP", etc).

TYPE16 {} S 15 Archiver 16, file type (extension)

Used by the file libraries to stamp archives with the BBS's ASCII/ANSI
logo. This specifies a command that will add a comment to the archive
(the kind that appears while the archive is uncompressed. Some archivers
don't have this feature -- do not include a comment command for
them. One %s is needed and replaced by the name of the archive. The
actual comment comes from the standard input. YOU have to take care to
terminate it properly (some archivers like infozip need a period to end
the comment).

COMMENT16 {} S 256 Archiver 16, command to add comment

Shell command that creates a compressed file. Accepts two arguments. The
first is the name of the archive to be created. The second is a space
separated list of files to be included (wildcards are possible). You
HAVE to add two %s specifiers in your command.

NB: set up the command line so that any subdirectories ARE recursed into
and included in the generated archive. Go for behaviour similar to that
of tar(1).

COMPRESS16 {} S 256 Archiver 16, compression

Like compress, only decompresses an archive. Two %s are needed here; the
first is the archive name, the second the list of files to be retrieved
from the archive.  The second argument may be blank, in which case all
of the files should be retrieved. Any directories should be created,
like tar(1) does.

UNCOMPRESS16 {} S 256 Archiver 16, decompression

Shell command that views the contents of an archive file.  The command
is called with one argument, the name of the file whose contents are to
be viewed. You HAVE to add a %s somewhere in the command (it will be
replaced by the filename).

VIEW16 {} S 256 Archiver 16, view contents






Sets the magic(4) file(1) substring used to detect this type of
archiver (eg "gzip compressed data"). The search type is
case-sensitive substring (strstr()). Look in /etc/magic for
more information on the detected types.

STRING17 {} S 39 Archiver 17, detection string

A description of the archiver.

NAME17 {} S 39 Archiver 17, description

Short file type description (eg "ZIP", "TAR/GZIP", etc).

TYPE17 {} S 15 Archiver 17, file type (extension)

Used by the file libraries to stamp archives with the BBS's ASCII/ANSI
logo. This specifies a command that will add a comment to the archive
(the kind that appears while the archive is uncompressed. Some archivers
don't have this feature -- do not include a comment command for
them. One %s is needed and replaced by the name of the archive. The
actual comment comes from the standard input. YOU have to take care to
terminate it properly (some archivers like infozip need a period to end
the comment).

COMMENT17 {} S 256 Archiver 17, command to add comment

Shell command that creates a compressed file. Accepts two arguments. The
first is the name of the archive to be created. The second is a space
separated list of files to be included (wildcards are possible). You
HAVE to add two %s specifiers in your command.

NB: set up the command line so that any subdirectories ARE recursed into
and included in the generated archive. Go for behaviour similar to that
of tar(1).

COMPRESS17 {} S 256 Archiver 17, compression

Like compress, only decompresses an archive. Two %s are needed here; the
first is the archive name, the second the list of files to be retrieved
from the archive.  The second argument may be blank, in which case all
of the files should be retrieved. Any directories should be created,
like tar(1) does.

UNCOMPRESS17 {} S 256 Archiver 17, decompression

Shell command that views the contents of an archive file.  The command
is called with one argument, the name of the file whose contents are to
be viewed. You HAVE to add a %s somewhere in the command (it will be
replaced by the filename).

VIEW17 {} S 256 Archiver 17, view contents






Sets the magic(4) file(1) substring used to detect this type of
archiver (eg "gzip compressed data"). The search type is
case-sensitive substring (strstr()). Look in /etc/magic for
more information on the detected types.

STRING18 {} S 39 Archiver 18, detection string

A description of the archiver.

NAME18 {} S 39 Archiver 18, description

Short file type description (eg "ZIP", "TAR/GZIP", etc).

TYPE18 {} S 15 Archiver 18, file type (extension)

Used by the file libraries to stamp archives with the BBS's ASCII/ANSI
logo. This specifies a command that will add a comment to the archive
(the kind that appears while the archive is uncompressed. Some archivers
don't have this feature -- do not include a comment command for
them. One %s is needed and replaced by the name of the archive. The
actual comment comes from the standard input. YOU have to take care to
terminate it properly (some archivers like infozip need a period to end
the comment).

COMMENT18 {} S 256 Archiver 18, command to add comment

Shell command that creates a compressed file. Accepts two arguments. The
first is the name of the archive to be created. The second is a space
separated list of files to be included (wildcards are possible). You
HAVE to add two %s specifiers in your command.

NB: set up the command line so that any subdirectories ARE recursed into
and included in the generated archive. Go for behaviour similar to that
of tar(1).

COMPRESS18 {} S 256 Archiver 18, compression

Like compress, only decompresses an archive. Two %s are needed here; the
first is the archive name, the second the list of files to be retrieved
from the archive.  The second argument may be blank, in which case all
of the files should be retrieved. Any directories should be created,
like tar(1) does.

UNCOMPRESS18 {} S 256 Archiver 18, decompression

Shell command that views the contents of an archive file.  The command
is called with one argument, the name of the file whose contents are to
be viewed. You HAVE to add a %s somewhere in the command (it will be
replaced by the filename).

VIEW18 {} S 256 Archiver 18, view contents






Sets the magic(4) file(1) substring used to detect this type of
archiver (eg "gzip compressed data"). The search type is
case-sensitive substring (strstr()). Look in /etc/magic for
more information on the detected types.

STRING19 {} S 39 Archiver 19, detection string

A description of the archiver.

NAME19 {} S 39 Archiver 19, description

Short file type description (eg "ZIP", "TAR/GZIP", etc).

TYPE19 {} S 15 Archiver 19, file type (extension)

Used by the file libraries to stamp archives with the BBS's ASCII/ANSI
logo. This specifies a command that will add a comment to the archive
(the kind that appears while the archive is uncompressed. Some archivers
don't have this feature -- do not include a comment command for
them. One %s is needed and replaced by the name of the archive. The
actual comment comes from the standard input. YOU have to take care to
terminate it properly (some archivers like infozip need a period to end
the comment).

COMMENT19 {} S 256 Archiver 19, command to add comment

Shell command that creates a compressed file. Accepts two arguments. The
first is the name of the archive to be created. The second is a space
separated list of files to be included (wildcards are possible). You
HAVE to add two %s specifiers in your command.

NB: set up the command line so that any subdirectories ARE recursed into
and included in the generated archive. Go for behaviour similar to that
of tar(1).

COMPRESS19 {} S 256 Archiver 19, compression

Like compress, only decompresses an archive. Two %s are needed here; the
first is the archive name, the second the list of files to be retrieved
from the archive.  The second argument may be blank, in which case all
of the files should be retrieved. Any directories should be created,
like tar(1) does.

UNCOMPRESS19 {} S 256 Archiver 19, decompression

Shell command that views the contents of an archive file.  The command
is called with one argument, the name of the file whose contents are to
be viewed. You HAVE to add a %s somewhere in the command (it will be
replaced by the filename).

VIEW19 {} S 256 Archiver 19, view contents






Sets the magic(4) file(1) substring used to detect this type of
archiver (eg "gzip compressed data"). The search type is
case-sensitive substring (strstr()). Look in /etc/magic for
more information on the detected types.

STRING20 {} S 39 Archiver 20, detection string

A description of the archiver.

NAME20 {} S 39 Archiver 20, description

Short file type description (eg "ZIP", "TAR/GZIP", etc).

TYPE20 {} S 15 Archiver 20, file type (extension)

Used by the file libraries to stamp archives with the BBS's ASCII/ANSI
logo. This specifies a command that will add a comment to the archive
(the kind that appears while the archive is uncompressed. Some archivers
don't have this feature -- do not include a comment command for
them. One %s is needed and replaced by the name of the archive. The
actual comment comes from the standard input. YOU have to take care to
terminate it properly (some archivers like infozip need a period to end
the comment).

COMMENT20 {} S 256 Archiver 20, command to add comment

Shell command that creates a compressed file. Accepts two arguments. The
first is the name of the archive to be created. The second is a space
separated list of files to be included (wildcards are possible). You
HAVE to add two %s specifiers in your command.

NB: set up the command line so that any subdirectories ARE recursed into
and included in the generated archive. Go for behaviour similar to that
of tar(1).

COMPRESS20 {} S 256 Archiver 20, compression

Like compress, only decompresses an archive. Two %s are needed here; the
first is the archive name, the second the list of files to be retrieved
from the archive.  The second argument may be blank, in which case all
of the files should be retrieved. Any directories should be created,
like tar(1) does.

UNCOMPRESS20 {} S 256 Archiver 20, decompression

Shell command that views the contents of an archive file.  The command
is called with one argument, the name of the file whose contents are to
be viewed. You HAVE to add a %s somewhere in the command (it will be
replaced by the filename).

VIEW20 {} S 256 Archiver 20, view contents






