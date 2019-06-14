#include "info.h"

#include <getopt.h>
#include <ktx.h>
#include <memory.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  static int help_flag = 0;
  char* filename = 0;
  while (true) {
    int option_index = 0;
    static struct option long_options[] = {
        {"file", required_argument, 0, 0},
        {"help", no_argument, &help_flag, 1},
        {0, 0, 0, 0}
    };

    int c = getopt_long(argc, argv, "f:h", long_options, &option_index);
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
    } else {
      filename = strdup(argv[optind++]);
    }
  }

  if (!filename) {
    help_flag = 1;
  }

  if (help_flag) {
    printf("ktxifo by jimblackler@gmail.com\n");
    printf("Usage:\n");
    printf("--file <name of KTX file>\n");
  } else {
    ktxTextureCreateFlags flags = 0;
    ktxTexture* texture;
    KTX_error_code error =
        ktxTexture_CreateFromNamedFile(filename, flags, &texture);
    switch (error) {
      case KTX_SUCCESS:
        output_info(texture);
        break;
      case KTX_FILE_DATA_ERROR:
        printf("The data in the file is inconsistent with the spec.\n");
        break;
      case KTX_FILE_OPEN_FAILED:
        printf("File open failed.\n");
        break;
      default:
        printf("Unknown error %d occurred\n", error);
    }

    free(texture);
  }

  free(filename);

  exit(EXIT_SUCCESS);
}