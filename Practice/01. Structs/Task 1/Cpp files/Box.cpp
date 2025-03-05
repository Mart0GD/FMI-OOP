
#include "Box.h";
#include "Vector3D.h";


Vector3D GetCenter(const Box& box) {
    Vector3D vector = {
        (box.min.x + box.max.x) / 2,
        (box.min.y + box.max.y) / 2,
        (box.min.z + box.max.z) / 2
    };

    return vector;
}

Vector3D GetExtent(const Box& box) {
    Vector3D vector = {
        box.max.x - box.min.x,
        box.max.y - box.min.y,
        box.max.z - box.min.z
    };

    return vector;
}

bool IntersectBox(const Box& B1, const Box& B2) {
    return 
        (B1.min.x <= B2.max.x && B1.max.x >= B2.min.x) &&
        (B1.min.y <= B2.max.y && B1.max.y >= B2.min.y) &&
        (B1.min.z <= B2.max.z && B1.max.z >= B2.min.z);
}