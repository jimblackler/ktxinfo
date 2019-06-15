#include "info.h"
#include "glnames.h"
#include "ktx/gl_format.h"

void output_info(ktxTexture* texture) {
  printf("glFormat:\t");
  printf_glenum(texture->glFormat);
  printf("\n");

  printf("glInternalformat:\t");
  printf_glenum(texture->glInternalformat);
  printf("\n");

  printf("glBaseInternalformat:\t");
  printf_glenum(texture->glBaseInternalformat);
  printf("\n");

  printf("glType:\t");
  printf_glenum(texture->glType);
  printf("\n");

  printf("isArray:\t%s\n", texture->isArray ? "true" : "false");
  printf("isCubemap:\t%s\n", texture->isCubemap ? "true" : "false");
  printf("isCompressed:\t%s\n", texture->isCompressed ? "true" : "false");
  printf("generateMipmaps:\t%s\n", texture->generateMipmaps ? "true" : "false");
  printf("baseWidth:\t%d\n", texture->baseWidth);
  printf("baseHeight:\t%d\n", texture->baseHeight);
  printf("baseDepth:\t%d\n", texture->baseDepth);
  printf("numDimensions:\t%d\n", texture->numDimensions);
  printf("numLevels:\t%d\n", texture->numLevels);
  printf("numLayers:\t%d\n", texture->numLayers);
  printf("numFaces:\t%d\n", texture->numFaces);
  printf("kvDataLen:\t%u\n", texture->kvDataLen);
  printf("dataSize:\t%zu\n", texture->dataSize);
}
