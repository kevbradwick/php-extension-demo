dnl $Id$
dnl config.m4 for extension demo_ext

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(demo_ext, for demo_ext support,
dnl Make sure that the comment is aligned:
dnl [  --with-demo_ext             Include demo_ext support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(demo_ext, whether to enable demo_ext support,
[  --enable-demo_ext           Enable demo_ext support])

if test "$PHP_DEMO_EXT" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-demo_ext -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/demo_ext.h"  # you most likely want to change this
  dnl if test -r $PHP_DEMO_EXT/$SEARCH_FOR; then # path given as parameter
  dnl   DEMO_EXT_DIR=$PHP_DEMO_EXT
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for demo_ext files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       DEMO_EXT_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$DEMO_EXT_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the demo_ext distribution])
  dnl fi

  dnl # --with-demo_ext -> add include path
  dnl PHP_ADD_INCLUDE($DEMO_EXT_DIR/include)

  dnl # --with-demo_ext -> check for lib and symbol presence
  dnl LIBNAME=demo_ext # you may want to change this
  dnl LIBSYMBOL=demo_ext # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $DEMO_EXT_DIR/$PHP_LIBDIR, DEMO_EXT_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_DEMO_EXTLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong demo_ext lib version or lib not found])
  dnl ],[
  dnl   -L$DEMO_EXT_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  PHP_SUBST(DEMO_EXT_SHARED_LIBADD)
  PHP_NEW_EXTENSION(demo_ext, demo_ext.c, $ext_shared)
fi
