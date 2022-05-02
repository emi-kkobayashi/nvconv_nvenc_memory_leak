#include <gst/gst.h>
#include <unistd.h>
#include <stdio.h>

static const gchar *const h264enc_str = "nvv4l2h264enc";
static const gchar *const vp8enc_str = "nvv4l2vp8enc";
static const gchar *const vp9enc_str = "nvv4l2vp9enc";

int main (int argc, char *argv[])
{
  int opt;
  gchar *codec = NULL;
  GstElement *pipeline;
  gchar pipe_str[256];
  const gchar *enc_str;

  gst_init (&argc, &argv);

  while ((opt = getopt (argc, argv, "c:")) != -1) {
    switch (opt) {
      case 'c':
        codec = g_strdup (optarg);
        break;
      default:
        g_print ("Invalid option\n");
        exit (1);
    }
  }

  if (!codec || g_strcmp0 (codec, "h264") == 0) {
    enc_str = h264enc_str;
  } else if (g_strcmp0 (codec, "vp8") == 0) {
    enc_str = vp8enc_str;
  } else if (g_strcmp0 (codec, "vp9") == 0) {
    enc_str = vp9enc_str;
  } else {
    g_print ("Invalid codec\n");
    exit (1);
  }

  sprintf (pipe_str,
      "videotestsrc ! video/x-raw,width=1920,height=1080 ! nvvideoconvert ! %s insert-sps-pps=true control-rate=0 peak-bitrate=5000000 iframeinterval=10 ! fakesink",
      enc_str);

  g_print ("Launch \"%s\"\n", pipe_str);

  pipeline = gst_parse_launch (pipe_str, NULL);

  while (1) {
    g_print ("Set pipeline to PLYAING\n");
    gst_element_set_state (pipeline, GST_STATE_PLAYING);

    sleep (3);

    g_print ("Set pipeline to NULL\n");
    gst_element_set_state (pipeline, GST_STATE_NULL);

    sleep (3);
  }

  /* Not reached here. */

  return 0;
}
