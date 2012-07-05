#include "primitives.h"

Triangle* triangle_new()
{
    Triangle* tr;
    tr=(Triangle*)aligned_malloc16(sizeof(Triangle));
    return tr;
}
