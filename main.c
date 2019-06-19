#include "info.h"
#include "update.h"

#include <getopt.h>
#include <ktx.h>
#include <memory.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  static int help_flag = 0;
  char* filename = 0;
  char* out_filename = 0;
  char* data_string = 0;
  int width = 8;
  while (true) {
    int option_index = 0;
    static struct option long_options[] = {
        {"file", required_argument, 0, 0},
        {"out", required_argument, 0, 0},
        {"data", required_argument, 0, 0},
        {"width", required_argument, 0, 0},
        {"help", no_argument, &help_flag, 1},
        {0, 0, 0, 0}
    };

    int c = getopt_long(argc, argv, "f:o:d:w:h", long_options, &option_index);
    if (c == -1) {
      break;
    }

    switch (c) {
      case 0:
        if (long_options[option_index].flag != 0)
          break;
        switch (option_index) {
          case 0:
            if (filename) {
              help_flag = 1;
            } else {
              filename = strdup(optarg);
            }
            break;
          case 1:
            if (out_filename) {
              help_flag = 1;
            } else {
              out_filename = strdup(optarg);
            }
            break;
          case 2:
            if (data_string) {
              help_flag = 1;
            } else {
              data_string = strdup(optarg);
            }
            break;
          case 3:
            if (strcmp("8", optarg) == 0) {
              width = 8;
            } else if (strcmp("16", optarg) == 0) {
              width = 16;
            } else if (strcmp("32", optarg) == 0) {
              width = 32;
            } else {
              help_flag = 1;
            }
            break;
          default:
            break;
        }
        break;
      case 'f':
        if (filename) {
          help_flag = 1;
        } else {
          filename = strdup(optarg);
        }
        break;
      case 'o':
        if (out_filename) {
          help_flag = 1;
        } else {
          out_filename = strdup(optarg);
        }
        break;
      case 'd':
        if (data_string) {
          help_flag = 1;
        } else {
          data_string = strdup(optarg);
        }
        break;
      case 'w':
        if (strcmp("8", optarg) == 0) {
          width = 8;
        } else if (strcmp("16", optarg) == 0) {
          width = 16;
        } else if (strcmp("32", optarg) == 0) {
          width = 32;
        } else {
          help_flag = 1;
        }
      case 'h':
        help_flag = 1;
        break;

      default:
        help_flag = 1;
    }
  }

  while (optind < argc) {
    if (filename) {
      help_flag = 1;
      optind++;
    } else {
      filename = strdup(argv[optind++]);
    }
  }

  if (!filename) {
    help_flag = 1;
  }

  int result = EXIT_SUCCESS;

  if (help_flag) {
    printf("ktxifo by jimblackler@gmail.com\n");
    printf("Usage:\n");
    printf("--file <name of input KTX file>\n");
    printf("--out <name of output KTX file>\n");
    printf("--data <JSON formatted key/value data to load>\n");
    printf("--width <8, 16, 32 - width of data in key/value>\n");
    printf("--help\n");

  } else {
    ktxTextureCreateFlags flags = KTX_TEXTURE_CREATE_LOAD_IMAGE_DATA_BIT;
    ktxTexture* texture;
    KTX_error_code error =
        ktxTexture_CreateFromNamedFile(filename, flags, &texture);
    switch (error) {
      case KTX_SUCCESS:
        if (data_string) {
          if (update(texture, data_string, width) < 0) {
            result = EXIT_FAILURE;
            printf("Error updating data\n");
            break;
          }
        }
        output_info(texture, width);

        if (out_filename) {
          KTX_error_code error2 =
              ktxTexture_WriteToNamedFile(texture, out_filename);
          switch (error2) {
            case KTX_SUCCESS:
              printf("Written %s\n", out_filename);
              break;
            default:
              result = EXIT_FAILURE;
              printf("Unknown error %d occurred\n", error2);
          }
        }
        break;
      case KTX_FILE_DATA_ERROR:
        result = EXIT_FAILURE;
        printf("The data in the file is inconsistent with the spec.\n");
        break;
      case KTX_FILE_OPEN_FAILED:
        result = EXIT_FAILURE;
        printf("File open failed.\n");
        break;
      default:
        result = EXIT_FAILURE;
        printf("Unknown error %d occurred\n", error);
    }

    free(texture);
  }

  free(filename);

  exit(result);
}
