


#ifndef PLUTONIUM_OBJIMPORTER_H
#define PLUTONIUM_OBJIMPORTER_H



#include <string>
#include <vector>
#include <memory>

#include "Mesh.h"




enum class OBJImporterState {
    START,
    SKIP_LINE,
    V,
    VERT,
    REC_VERT_COORD,
    VERT_COORD_SEP,
    NORM,
    REC_NORM_COORD,
    NORM_COORD_SEP,
    TEX,
    REC_TEX_COORD,
    TEX_COORD_SEP,
    FACE,
    REC_FACE_VERT_IND,
    MAYBE_FACE_TEX_IND,
    REC_FACE_TEX_IND,
    REC_FACE_NORM_IND,
    FACE_VERT_SEP,
    NOT_YET_IMPLEMENTED
};



class OBJImporter {
public:

    static std::shared_ptr<Mesh> importOBJ(const std::string& filename);

private:

    static bool triangulateAndAdd(std::vector<TriangleIndex>& face, std::vector<std::array<TriangleIndex, 3> >& allTriangles);

};




#endif