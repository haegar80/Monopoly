#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include "OBJLoader.h"
  
ObjectLoader::ObjectLoader()
{
}
 
ObjectLoader::~ObjectLoader()
{
}
 
void ObjectLoader::LoadOBJ(std::string file_name)
{
	FILE* objFile;
	bool done = false;
	bool has_normals = false;
	bool has_uvs = false;
	ObjVertexCoords vertex;
	ObjTextureCoords texture;
 
	if(0 != fopen_s(&objFile, file_name.c_str(), "r")) {
		return;
	}
 
	while(!done) {
		char c = fgetc(objFile);
		switch(c) {
		case '#': // Comment. Fall through
		case 'u': // Fall through
		case 's': // Fall through
		case 'g': // Group. Not supported. Fall through
			while(fgetc(objFile) != '\n'); { // Skip to the next line
				break;
			}
		case EOF: // End of file reached. We be done.
			done = true;
			break;
		case 'v':
			c = fgetc(objFile); // The next character determines what type of vertex we are loading
			switch(c)
			{
			case ' ': // Loading vertices
				vertex = ReadObjVertexCoords(objFile);
				m_vertices.push_back(vertex);
				break;
			case 'n': // Loading normals
				has_normals = true;
				vertex = ReadObjVertexCoords(objFile);
                m_normals.push_back(vertex);
				break;
			case 't': // Loading UVs
				has_uvs = true;
				texture = ReadObjTextureCoords(objFile);
				m_uvs.push_back(texture);
				break;
			default: // Uh oh... What are we trying to read here? Someone screwed up their OBJ exporter...
				std::cout << "Invalid vertex type: " << "v" << c << " Should be of type \"v \", \"vn\" or \"vt\"." << std::endl;
				return;
				break;
			}
			break;
		case 'f':
			ObjFace face;
			face.Valid = false;
			if(has_normals && has_uvs) {
				face = ReadObjFaceWithNormalsAndTexture(objFile);
			} else if(has_normals && !has_uvs) {
				face = ReadObjFaceWithNormals(objFile);
			} else if(!has_normals && has_uvs) {
				face = ReadObjFaceWithTexture(objFile);
			} else if(!has_normals && !has_uvs) {
				face = ReadObjFace(objFile);
			}
			if(face.Valid) {
				m_faces.push_back(face);
			}
			break;
		}
	}
 
	fclose(objFile);
}
 
void ObjectLoader::DumpOBJ(void)
{
	for(unsigned long i = 0; i < m_vertices.size(); i++) {
		std::cout << m_vertices.at(i).X << " " << m_vertices.at(i).Y << " " << m_vertices.at(i).Z << std::endl;
	}
	for(unsigned long i = 0; i < m_normals.size(); i++) {
		std::cout << m_normals.at(i).X << " " << m_normals.at(i).Y << " " << m_normals.at(i).Z << std::endl;
	}
	for(unsigned long i = 0; i < m_uvs.size(); i++) {
		std::cout << m_uvs.at(i).U << " " << m_uvs.at(i).V << std::endl;
	}
	for(unsigned long i = 0; i < m_faces.size(); i++) {
		for(unsigned long j = 0; j < m_faces.at(i).Vertices.size(); j++) {
			std::cout << m_faces.at(i).Vertices.at(j) << "/" << m_faces.at(i).UVs.at(j) << "/" << m_faces.at(i).Normals.at(j) << " ";
            std::cout << std::endl;
		}
	}
}

ObjVertexCoords ObjectLoader::ReadObjVertexCoords(FILE* const pc_file)
{
	ObjVertexCoords vertex;
	fscanf_s(pc_file, "%f %f %f\n", &vertex.X, &vertex.Y, &vertex.Z);
	return vertex;
}

ObjTextureCoords ObjectLoader::ReadObjTextureCoords(FILE* const pc_file)
{
	ObjTextureCoords texture;
	fscanf_s(pc_file, "%f %f\n", &texture.U, &texture.V);
	return texture;
}

ObjFace ObjectLoader::ReadObjFaceWithNormalsAndTexture(FILE* const pc_file)
{
	ObjFace face;
	while(fgetc(pc_file) != '\n') {
		int vertIndex = 0;
		int normIndex = 0;
		int uvIndex = 0;
		int read_count = fscanf_s(pc_file, "%d/%d/%d", &vertIndex, &uvIndex, &normIndex);
		if((3 != read_count) || (0 == vertIndex) || (0 == uvIndex) || (0 == normIndex)) {
			std::cout << "Invalid vertex index." << std::endl;
			face.Valid = false;
			break;
		}
		else {
			face.Valid = true;
			face.Vertices.push_back(vertIndex - 1);
			face.Normals.push_back(normIndex - 1);
			face.UVs.push_back(uvIndex - 1);
		}
	}
	return face;
}

ObjFace ObjectLoader::ReadObjFaceWithNormals(FILE* const pc_file)
{
	ObjFace face;
	while(fgetc(pc_file) != '\n') {
		int vertIndex = 0;
		int normIndex = 0;
		int read_count = fscanf_s(pc_file, "%d//%d", &vertIndex, &normIndex);
		if((2 != read_count) || (0 == vertIndex) || (0 == normIndex)) {
			std::cout << "Invalid vertex index." << std::endl;
			face.Valid = false;
			break;
		}
		else {
			face.Valid = true;
			face.Vertices.push_back(vertIndex - 1);
			face.Normals.push_back(normIndex - 1);
			face.UVs.push_back(0);
		}
	}
	return face;
}

ObjFace ObjectLoader::ReadObjFaceWithTexture(FILE* const pc_file)
{
	ObjFace face;
	while(fgetc(pc_file) != '\n') {
		int vertIndex = 0;
		int uvIndex = 0;
		int read_count = fscanf_s(pc_file, "%d//%d", &vertIndex, &uvIndex);
		if((2 != read_count) || (0 == vertIndex) || (0 == uvIndex)) {
			std::cout << "Invalid vertex index." << std::endl;
			face.Valid = false;
			break;
		}
		else {
			face.Valid = true;
			face.Vertices.push_back(vertIndex - 1);
			face.Normals.push_back(0);
			face.UVs.push_back(uvIndex - 1);
		}
	}
	return face;
}

ObjFace ObjectLoader::ReadObjFace(FILE* const pc_file)
{
	ObjFace face;
	while(fgetc(pc_file) != '\n') {
		int vertIndex = 0;
		int read_count = fscanf_s(pc_file, "%d//", &vertIndex);
		if((1 != read_count) || (0 == vertIndex)) {
			std::cout << "Invalid vertex index." << std::endl;
			face.Valid = false;
			break;
		}
		else {
			face.Valid = true;
			face.Vertices.push_back(vertIndex - 1);
			face.Normals.push_back(0);
			face.UVs.push_back(0);
		}
	}
	return face;
}