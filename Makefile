CC=gcc

GST_LIBS=`pkg-config --libs gstreamer-1.0 glib-2.0`
GST_CFLAGS=`pkg-config --cflags gstreamer-1.0 glib-2.0`

CFLAGS=-Wall

BINS=nvconv_nvenc_loop

all:	$(BINS)

nvconv_nvenc_loop:	nvconv_nvenc_loop.c
	$(CC) $(CFLAGS) $(GST_CFLAGS) $< $(GST_LIBS) -o $@

clean:
	$(RM) $(BINS)
