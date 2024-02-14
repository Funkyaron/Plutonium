


#include "Geometry.h"

#include "Material.h"


void Geometry::setMaterial(std::shared_ptr<Material> material_) {
    material = material_;
}

std::shared_ptr<Material> Geometry::getMaterial() {
    return material;
}