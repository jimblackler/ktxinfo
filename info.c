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

}



//    ktx_uint32_t ; /*!< Type of the texture data, e.g, GL_UNSIGNED_BYTE.*/
//      ktx_bool_t isArray; /*!< KTX_TRUE if the texture is an array texture, i.e,
//                               a GL_TEXTURE_*_ARRAY target is to be used. */
//      ktx_bool_t isCubemap; /*!< KTX_TRUE if the texture is a cubemap or
//                                 cubemap array. */
//      ktx_bool_t isCompressed; /*!< KTX_TRUE if @c glInternalFormat is that of
//                                    a compressed texture. */
//      ktx_bool_t generateMipmaps; /*!< KTX_TRUE if mipmaps should be generated
//                                       for the texture by ktxTexture_GLUpload()
//                                       or ktx_Texture_VkUpload(). */
//    ktx_uint32_t baseWidth;  /*!< Width of the base level of the texture. */
//    ktx_uint32_t baseHeight; /*!< Height of the base level of the texture. */
//    ktx_uint32_t baseDepth;  /*!< Depth of the base level of the texture. */
//    ktx_uint32_t numDimensions; /*!< Number of dimensions in the texture: 1, 2
//                                     or 3. */
//    ktx_uint32_t numLevels; /*!< Number of mip levels in the texture. Should be
//                                 1, if @c generateMipmaps is KTX_TRUE. Can be
//                                 less than a full pyramid but always starts at
//                                 the base level. */
//    ktx_uint32_t numLayers; /*!< Number of array layers in the texture. */
//    ktx_uint32_t numFaces; /*!< Number of faces, 6 for cube maps, 1 otherwise.*/
//     ktxHashList kvDataHead; /*!< Head of the hash list of metadata. */
//    ktx_uint32_t kvDataLen; /*!< Length of the metadata, if it has been
//                                 extracted in its raw form, otherwise 0. */
//    ktx_uint8_t* kvData; /*!< Pointer to the metadata, if it has been extracted
//                              in its raw form, otherwise NULL. */
//      ktx_size_t dataSize; /*!< Length of the image data in bytes. */
//    ktx_uint8_t* pData; /*!< Pointer to the image data. */