#ifndef MODELS_H
#define MODELS_H
#include <assimp/cimport.h>        // Plain-C interface
#include <assimp/scene.h>          // Output data structure
#include <assimp/postprocess.h>    // Post processing flags


extern struct aiScene* importmodel(const char* file);
extern void freemodel(struct aiScene* scene);

#endif // MODELS_H
