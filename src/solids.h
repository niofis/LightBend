#ifndef SOLIDS_H
#define SOLIDS_H

List* CreateSphere(float* center, float radious, int num_slices, int slice_resolution, int group_id);

void Translate(float* offset, List* triangles);

#endif // SOLIDS_H
