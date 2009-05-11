## Process this file with automake to produce Makefile.in

INCLUDES = -I$(top_builddir) \
           -I$(top_srcdir)/include \
           $(UIOMUX_CFLAGS)

SHCODECSDIR = ../libshcodecs
SHCODECS_LIBS = $(SHCODECSDIR)/libshcodecs.la $(UIOMUX_LIBS) -lm

bin_PROGRAMS = shcodecs-decode-qvga-mpeg4

shcodecs_decode_qvga_mpeg4_SOURCES = shcodecs-decode-qvga-mpeg4.c
shcodecs_decode_qvga_mpeg4_LDADD = $(SHCODECS_LIBS)
