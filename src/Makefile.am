LE_FILES = chewing.so

libdir = $(prefix)/lib/im/leif

chewing_la_CFLAGS = \
	$(X_CFLAGS) $(THREAD_CXX_CFLAGS) \
	-DLIBCHEWING_DATADIR=\"$(datadir)/chewing\" \
	-I$(IM_INCLUDEDIR)/iml \
	@CHEWING_CFLAGS@
chewing_la_LDFLAGS = \
	-avoid-version \
	-module \
	-rpath $(IM_LEIFDIR) \
	$(SHLIBLDFLAGS) $(THREAD_LDFLAGS) \
	@CHEWING_LIBS@
chewing_la_SOURCES = chewing.c

lib_LTLIBRARIES = chewing.la
