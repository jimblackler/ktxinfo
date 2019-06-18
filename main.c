#include "info.h"

#include <getopt.h>
#include <ktx.h>
#include <memory.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  static int help_flag = 0;
  char* filename = 0;
  char* out_filename = 0;
  while (true) {
    int option_index = 0;
    static struct option long_options[] = {
        {"file", required_argument, 0, 0},
        {"out", required_argument, 0, 0},
        {"help", no_argument, &help_flag, 1},
        {0, 0, 0, 0}
    };

    int c = getopt_long(argc, argv, "f:o:h", long_options, &option_index);
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
    ktxTextureCreateFlags flags = KTX_TEXTURE_CREATE_LOAD_IMAGE_DATA_BIT;
    ktxTexture* texture;
    KTX_error_code error =
        ktxTexture_CreateFromNamedFile(filename, flags, &texture);
    switch (error) {
      case KTX_SUCCESS:
        output_info(texture);

        if (out_filename) {
          KTX_error_code error2 =
              ktxTexture_WriteToNamedFile(texture, out_filename);
          switch (error2) {
            case KTX_SUCCESS:
              printf("Written %s\n", out_filename);
              break;
            default:
              printf("Unknown error %d occurred\n", error2);
          }
        }
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