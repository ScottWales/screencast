#include <stdio.h>
#include <stdlib.h>

#include <libavformat/avformat.h>
#include <libavdevice/avdevice.h>
#include <libavutil/opt.h>

/**
 *  Screencast recorder
 *
 *  Swap between desktop, desktop + camera inset and camera fullscreen
 */

void connectDesktop(AVFormatContext ** desktop) {

    AVInputFormat * iformat = av_find_input_format("x11grab");
    const char * display = getenv("DISPLAY");

    // Set up options
    AVDictionary * options = NULL;
    int flags = 0;
    av_dict_set(&options, "video_size", "hd1080", flags);
    av_dict_set(&options, "framerate", "30", flags);
    av_dict_set(&options, "show_region", "1", flags);

    // Open the connection
    int ierr = avformat_open_input(desktop, "0:0", iformat, &options);
    if (ierr) fprintf(stderr,"Error opening desktop\n");
    
    av_dict_free(&options);
}

int main() {
    AVFormatContext * desktop    = NULL;
    AVFormatContext * camera     = NULL;
    AVFormatContext * microphone = NULL;

    // Register all available devices
    av_register_all();
    avdevice_register_all();

    AVInputFormat * iformat = NULL;

    // Connect devices to each context
    connectDesktop(&desktop);
    iformat = av_find_input_format("video4linux2");
    avformat_open_input(&camera, "/dev/video0", iformat, NULL);
    iformat = av_find_input_format("alsa");
    avformat_open_input(&microphone, "hw:2", iformat, NULL);

    // Get the video options
    const AVOption * option = NULL;
    do {
        uint8_t * value = NULL;
        option = av_opt_next((desktop->priv_data), option);
        if (option) {
            av_opt_get(desktop->priv_data, option->name, 0, &value);
            printf("%s:%s\t%s\n", option->name, (char*)value, option->help);
        }
        free(value);
    } while (option != NULL);

    // Close streams
    avformat_close_input(&desktop);
    avformat_close_input(&camera);
    avformat_close_input(&microphone);

    return 0;
}
