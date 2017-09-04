
#ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4 

AM_CPPFLAGS = ${AM_CPPFLAGS} -Imath_lib

SUBDIRS = math_lib

bin_PROGRAMS = pow
pow_SOURCES = main.cc
#pow_CPPFLAGS = -std=c++11 
pow_CPPFLAGS = -std=c++11 -DUSE_MY_MATH_LIB
pow_LDADD = math_lib/libmath.a 
