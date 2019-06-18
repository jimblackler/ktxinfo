add_definitions("-DKTX_OPENGL_ES2")

add_library(ktx STATIC
     checkheader.c
     etcdec.cxx
     etcunpack.cxx
     filestream.c
     glloader.c
     hashlist.c
     memstream.c
     swap.c
     texture.c
     writer.c
    )

target_include_directories(ktx PRIVATE include other_include)
