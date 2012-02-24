#if !defined(NBVH)
#define NBVH



void BuildBVH();
void CleanBVH();
int BoxHit(int box_id,Ray *ray);
void TraverseBVH(int bv_id, Ray* ray);

#endif