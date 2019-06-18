extern "C" {
#include "info.h"
#include "glnames.h"
#include "ktx.h"
}

#include <sstream>
#include <cstring>
#include "variadictable.h"

#define PADN(n, nbytes) (nbytes + (n-1) & ~(ktx_uint32_t)(n-1))

/*
 * Pad nbytes to next multiple of 4
 */
#define _KTX_PAD4(nbytes) _KTX_PADN(4, nbytes)

std::string toHex(int i) {
  std::ostringstream stringStream;
  stringStream << std::hex << "0x" << i;
  return stringStream.str();
}

void output_header(ktxTexture* texture) {
  VariadicTable<std::string, int, std::string, std::string>
      vt({"Field", "Dec", "Hex", "Enum"});

  vt.setColumnFormat({{VariadicTableType::AUTO, VariadicTableJustify::AUTO},
                      {VariadicTableType::AUTO, VariadicTableJustify::AUTO},
                      {VariadicTableType::AUTO, VariadicTableJustify::RIGHT},
                      {VariadicTableType::AUTO, VariadicTableJustify::AUTO}});

  vt.addRow({"glFormat", texture->glFormat, toHex(texture->glFormat), name_from_enum(texture->glFormat)});
  vt.addRow({"glInternalformat", texture->glInternalformat, toHex(texture->glInternalformat),
             name_from_enum(texture->glInternalformat)});
  vt.addRow({"glBaseInternalformat", texture->glBaseInternalformat, toHex(texture->glBaseInternalformat),
             name_from_enum(texture->glBaseInternalformat)});
  vt.addRow({"glType", texture->glType, toHex(texture->glType), name_from_enum(texture->glType)});
  vt.addRow({"isArray", texture->isArray, toHex(texture->isArray), ""});
  vt.addRow({"isCubemap", texture->isCubemap, toHex(texture->isCubemap), ""});
  vt.addRow({"isCompressed", texture->isCompressed, toHex(texture->isCompressed), ""});
  vt.addRow({"generateMipmaps", texture->generateMipmaps, toHex(texture->generateMipmaps), ""});
  vt.addRow({"baseWidth", texture->baseWidth, toHex(texture->baseWidth), ""});
  vt.addRow({"baseHeight", texture->baseHeight, toHex(texture->baseHeight), ""});
  vt.addRow({"baseDepth", texture->baseDepth, toHex(texture->baseDepth), ""});
  vt.addRow({"numDimensions", texture->numDimensions, toHex(texture->numDimensions), ""});
  vt.addRow({"numLevels", texture->numLevels, toHex(texture->numLevels), ""});
  vt.addRow({"numLayers", texture->numLayers, toHex(texture->numLayers), ""});
  vt.addRow({"numFaces", texture->numFaces, toHex(texture->numFaces), ""});
  vt.addRow({"kvDataLen", texture->kvDataLen, toHex(texture->kvDataLen), ""});
  vt.addRow({"dataSize", texture->dataSize, toHex(texture->dataSize), ""});

  vt.print(std::cout);
}


void output_key_values(ktxTexture* texture) {
  VariadicTable<std::string, std::string> vt({"Key", "Value"});

  unsigned int kvdLen;
  unsigned char* pKvd;

  ktxHashList_Serialize(&texture->kvDataHead, &kvdLen, &pKvd);
  auto src = (char*) pKvd;
  while (src < (char*) pKvd + kvdLen) {
    ktx_uint32_t keyAndValueByteSize = *((ktx_uint32_t*) src);
    src += sizeof(keyAndValueByteSize);
    char* key = src;
    unsigned int keyLen = (unsigned int) strlen(key) + 1;
    char* value = key + keyLen;
    vt.addRow({key, value});
    src += PADN(4, keyAndValueByteSize);
  }

  vt.print(std::cout);
}


void output_info(ktxTexture* texture) {
  output_header(texture);
  output_key_values(texture);
}
