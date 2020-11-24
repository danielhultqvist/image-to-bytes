#include <iostream>
#include <cairo.h>
#include <zconf.h>
#include <fcntl.h>

static const int SCREEN_WIDTH = 480;
static const int SCREEN_HEIGHT = 272;

using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 3) {
    cout << "USAGE: image-to-bytes <image-file> <output-file>" << endl;
    exit(1);
  }

  char* input = argv[1];
  char* output = argv[2];
  cairo_surface_t* image = cairo_image_surface_create_from_png(input);
  int imageWidth = cairo_image_surface_get_width(image);
  int imageHeight = cairo_image_surface_get_height(image);

  // Rescale image onto surface
  cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, SCREEN_WIDTH, SCREEN_HEIGHT);
  cairo_t *cr = cairo_create(surface);
  cairo_new_path(cr);
  cairo_scale(cr, (float) SCREEN_WIDTH / (float) imageWidth, (float) SCREEN_HEIGHT / (float) imageHeight);
  cairo_set_source_surface(cr, image, 0, 0);
  cairo_paint(cr);
  cairo_scale(cr, (float) imageWidth / (float) SCREEN_WIDTH, (float) imageHeight / (float) SCREEN_HEIGHT);
  cairo_surface_flush(surface);

  // Write raw bytes to output file
  int fd = open(output, O_CREAT | O_TRUNC | O_RDWR, 0755);
  lseek(fd, 0, SEEK_SET);
  auto numBytesWritten = write(fd, cairo_image_surface_get_data(surface), SCREEN_WIDTH * SCREEN_HEIGHT * 4);
  if (numBytesWritten == -1) {
    cout << "Unable to write to output file" << std::endl;
    exit(1);
  }
  close(fd);

  // Cleanup
  cairo_destroy(cr);
  cairo_surface_destroy(surface);
  cairo_surface_destroy(image);

  std::cout << "Done! The image is scaled and written as bytes to " << output << std::endl;
  return 0;
}
