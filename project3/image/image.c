#include <stdlib.h>
#include <stdio.h>
#include <jpeglib.h>
#include <libexif/exif-data.h>

#define IMG_NAME ("sample_img.JPG")

int main(void) {
    ExifData *data;
    ExifEntry *entry;

    data = exif_data_new_from_file(IMG_NAME);

    if (!data) {
        printf("File not readable or no EXIF data in file %s\n", IMG_NAME);

        exit(1);
    }

    entry = exif_content_get_entry(data->ifd[EXIF_IFD_0], EXIF_TAG_DATE_TIME);

    if (entry) {
        char buffer[20];

        if (exif_entry_get_value(entry, buffer, 20)) {
            printf("date time: %.*s\n", 20, buffer);
        }
    }

    return 0;
}
