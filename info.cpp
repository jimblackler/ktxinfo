extern "C" {
#include "info.h"
#include "glnames.h"
}

#include <c++/v1/iostream>
#include "variadictable.h"

void output_info(ktxTexture* texture) {

  VariadicTable<std::string, int, std::string> vt({"Field", "Hex", "Enum"});

  vt.addRow({"glFormat", texture->glFormat, name_from_enum(texture->glFormat)});
  vt.addRow({"glInternalformat", texture->glInternalformat, name_from_enum(texture->glInternalformat)});
  vt.addRow({"glBaseInternalformat", texture->glBaseInternalformat, name_from_enum(texture->glBaseInternalformat)});
  vt.addRow({"glType", texture->glType, name_from_enum(texture->glType)});
  vt.addRow({"isArray", texture->isArray, ""});
  vt.addRow({"isCubemap", texture->isCubemap, ""});
  vt.addRow({"isCompressed", texture->isCompressed, ""});
  vt.addRow({"generateMipmaps", texture->generateMipmaps, ""});
  vt.addRow({"baseWidth", texture->baseWidth, ""});
  vt.addRow({"baseHeight", texture->baseHeight, ""});
  vt.addRow({"baseDepth", texture->baseDepth, ""});
  vt.addRow({"numDimensions", texture->numDimensions, ""});
  vt.addRow({"numLevels", texture->numLevels, ""});
  vt.addRow({"numLayers", texture->numLayers, ""});
  vt.addRow({"numFaces", texture->numFaces, ""});
  vt.addRow({"kvDataLen", texture->kvDataLen, ""});
  vt.addRow({"dataSize", texture->dataSize, ""});

  vt.print(std::cout);
}
