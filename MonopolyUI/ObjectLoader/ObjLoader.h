#ifndef _ObjLoader_H
#define _ObjLoader_H
 
#include <vector>
#include <string>

struct ObjVertexCoords
{
    float X;
    float Y;
    float Z;
};

struct ObjTextureCoords
{
    float U;
	float V;
};

struct ObjFace
{
	std::vector<long> Vertices;
    std::vector<long> Normals;
    std::vector<long> UVs;
	bool Valid;
};

class VertexCoords{
public:
        VertexCoords(){}
        ~VertexCoords(){}
 
        float GetX() const {return(m_x);}
        void SetX(float p_x) {m_x = p_x;}
 
        float GetY() const {return(m_y);}
        void SetY(float p_y) {m_y = p_y;}
 
        float GetZ() const {return(m_z);}
        void SetZ(float p_z) {m_z = p_z;}
 
private:
        float m_x;
        float m_y;
        float m_z;
};
 
class TextureCoords{
public:
        TextureCoords(){}
        ~TextureCoords(){}
 
        float GetU() const {return(m_u);}
        void SetU(float p_u) {m_u = p_u;}
 
        float GetV() const {return(m_v);}
        void SetV(float p_v) {m_v = p_v;}
 
private:
        float m_u;
        float m_v;
};
 
class Face{
public:
        Face();
        Face(const Face& pc_orig);
        ~Face();
 
        long GetNumVertices() const;
        long GetNumNormals() const;
        long GetNumUVs() const;
 
        void AddVertex(long p_index);
        long GetVertex(long p_index) const;
 
        void AddNormal(long p_index);
        long GetNormal(long p_index) const;
 
        void AddUV(long p_index);
        long GetUV(long p_index) const;


 
private:
        std::vector<long> m_vertices;
        std::vector<long> m_normals;
        std::vector<long> m_uv;
};
 
class ObjectLoader{
public:
        ObjectLoader();
        ~ObjectLoader();
 
        long GetNumVertices() const;
        long GetNumNormals() const;
        long GetNumUVs() const;
        long GetNumFaces() const;
 
		std::vector<ObjVertexCoords> GetVertices() const {
			return m_vertices;
		}
		std::vector<ObjVertexCoords> GetNormals() const {
			return m_normals;
		}
        std::vector<ObjTextureCoords> GetTextures() const {
			return m_uvs;
		}
		std::vector<ObjFace> GetFaces() const {
			return m_faces;
		}
 
        void LoadOBJ(std::string p_file_name);
        void DumpOBJ(void);
 
private:
		ObjVertexCoords ReadObjVertexCoords(FILE* const pc_file);
        ObjTextureCoords ReadObjTextureCoords(FILE* const pc_file);
		ObjFace ReadObjFaceWithNormalsAndTexture(FILE* const pc_file);
		ObjFace ReadObjFaceWithNormals(FILE* const pc_file);
		ObjFace ReadObjFaceWithTexture(FILE* const pc_file);
		ObjFace ReadObjFace(FILE* const pc_file);

		std::vector<ObjVertexCoords> m_vertices;
        std::vector<ObjVertexCoords> m_normals;
        std::vector<ObjTextureCoords> m_uvs;
        std::vector<ObjFace> m_faces;
};
 
#endif