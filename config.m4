PHP_ARG_ENABLE(exsort, whether to enable Extended
sorting support,
[ --enable-exsort   Enable Extended Sort support])
if test "$PHP_EXSORT" = "yes"; then
  AC_DEFINE(HAVE_EXSORT, 1, [Whether you have Extended Sort])
  PHP_NEW_EXTENSION(exsort, exsort.c, $ext_shared)
fi