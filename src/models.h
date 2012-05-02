#ifndef MODELS_H
#define MODELS_H
#include <assimp/assimp.h>
#include <assimp/aiScene.h>
#include <assimp/aiPostProcess.h>


extern struct aiScene* importmodel(const char* file);
extern void freemodel(struct aiScene* scene);

#endif // MODELS_H
