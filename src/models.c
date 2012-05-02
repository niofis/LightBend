#include "models.h"

struct aiScene* importmodel( const char* file)
{
  // Start the import on the given file with some example postprocessing
  // Usually - if speed is not the most important aspect for you - you'll t
  // probably to request more postprocessing than we do in this example.
  struct aiScene* scene = aiImportFile( file,
    aiProcess_CalcTangentSpace       |
        aiProcess_Triangulate            |
        aiProcess_JoinIdenticalVertices  |
        aiProcess_SortByPType);

  // If the import failed, report it
  if(!scene)
  {
    //Error
    return 0;
  }

  // Now we can access the file's contents
  //DoTheSceneProcessing( scene);

  // We're done. Release all resources associated with this import

  return scene;
}

void freemodel(struct aiScene* scene)
{
    aiReleaseImport(scene);
}
