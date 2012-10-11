//
//  MeshLoader.cpp
//  D3
//
//  Created by Srđan Rašić on 10/11/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#include "MeshLoader.hpp"
#include <fstream>
#include <sstream>

namespace d3 {
    
    bool startsWith(String what, String with) {
        if (what.size() < with.size())
            return false;
        
        for (int i = 0; i < with.size(); i++)
            if (what[i] != with[i])
                return false;
        return true;
    }
    
    String getDirectory(String path) {
        const size_t last_slash_idx = path.rfind('/');
        if (std::string::npos != last_slash_idx)
            return path.substr(0, last_slash_idx);
        return String();
    }
    
    shared_ptr<TexturedMesh> MeshLoader::loadOBJ(String path)
    {
        std::ifstream obj_file(path.c_str());
		
		assert(obj_file.is_open());
        
        struct FaceIndices {
            unsigned position[3];
            unsigned texcoord[3];
            unsigned normal[3];
        };
		
		std::vector<Vec3> vertices;
		std::vector<Vec3> texcoords;
		std::vector<Vec3> normals;
        std::vector<FaceIndices> faces;
        float max_length = 0.0;
        
        String material_filename;
        
        while (obj_file.good()) {
            char c;
			std::string line;
            std::getline(obj_file, line);
            std::stringstream ss(line);
			
			if (line[0] == 'v' && line[1] == ' ') {
				Vec3 p;
				ss >> c >> p.x >> p.y >> p.z;
				vertices.push_back(p);
                
                if (p.length() > max_length)
                    max_length = p.length();
                
			} else if (line[0] == 'v' && line[1] == 't') {
				Vec3 p;
				ss >> c >> c >> p.x >> p.y;
				texcoords.push_back(p);
			} else if (line[0] == 'v' && line[1] == 'n') {
				Vec3 p;
				ss >> c >> c >> p.x >> p.y >> p.z;
				normals.push_back(p);
			} else if (line[0] == 'f' && line[1] == ' ') {
                FaceIndices fi;
				ss >> c;
				if (texcoords.size() > 0 && normals.size() > 0) {
					ss	>> fi.position[0] >> c >> fi.texcoord[0] >> c >> fi.normal[0]
                        >> fi.position[1] >> c >> fi.texcoord[1] >> c >> fi.normal[1]
                        >> fi.position[2] >> c >> fi.texcoord[2] >> c >> fi.normal[2];
				} else if (texcoords.size() == 0 && normals.size() > 0) {
					ss	>> fi.position[0] >> c >> c >> fi.normal[0]
                        >> fi.position[1] >> c >> c >> fi.normal[1]
                        >> fi.position[2] >> c >> c >> fi.normal[2];
				} else if (texcoords.size() == 0 && normals.size() == 0) {
					ss	>> fi.position[0] >> fi.position[1] >> fi.position[2];
				}
				
				faces.push_back(fi);
			} else if (startsWith(line, "mtllib")) {
				ss >> material_filename >> material_filename;
			}
		}
        
        bool have_texcoords = texcoords.size() > 0;
        bool have_normals = normals.size() > 0;
        unsigned vertex_count = (int)vertices.size();
        unsigned element_count = (unsigned)faces.size() * 3;
        unsigned stride = sizeof(Vec3);
        
        unsigned position_offset = 0;
        unsigned texcoord_offset = 0;
        unsigned normal_offset = 0;
        
        if (have_texcoords) {
            stride += sizeof(Vec3);
            texcoord_offset = sizeof(Vec3);
        }
        
        if (have_normals) {
            stride += sizeof(Vec3);
            normal_offset = texcoord_offset + sizeof(Vec3);
        }
        
        shared_ptr<VertexData> indices(new BufferedVertexData(element_count * sizeof(unsigned), 0, GL_STATIC_DRAW, GL_ELEMENT_ARRAY_BUFFER, NULL));
        shared_ptr<VertexData> vbo(new BufferedVertexData(stride * vertex_count, stride, GL_STATIC_DRAW, GL_ARRAY_BUFFER, NULL));
        
        unsigned * index_array = (unsigned *)indices->mapData();
        unsigned char * vbo_array = (unsigned char *)vbo->mapData();
        
        for (unsigned int i = 0; i < faces.size(); i++) {   // for all faces
            for (unsigned int j = 0; j < 3; j++) {  // for each vertex in face
                unsigned index = i * 3 + j;
                index_array[index] = faces[i].position[j];  // copy index to array of indices
                
                ((Vec3 *)(vbo_array + index_array[index] * stride + position_offset))[0] = vertices[faces[i].position[j] - 1] * (1.0 / max_length);
                
                if (have_texcoords)
                    ((Vec3 *)(vbo_array + index_array[index] * stride + texcoord_offset))[0] = texcoords[faces[i].texcoord[j] - 1];
                
                if (have_normals)
                    ((Vec3 *)(vbo_array + index_array[index] * stride + normal_offset))[0] = normals[faces[i].normal[j] - 1];
            }
        }
        
        indices->unmapData();
        vbo->unmapData();
        
        vbo->setAttribute("in_position", VertexData::AttribProps(position_offset, 3, GL_FLOAT));
        
        if (have_texcoords)
            vbo->setAttribute("in_texcoord", VertexData::AttribProps(texcoord_offset, 2, GL_FLOAT));
        
        if (have_normals)
            vbo->setAttribute("in_normal", VertexData::AttribProps(normal_offset, 3, GL_FLOAT));
        
        shared_ptr<TexturedMesh> textured_mesh(new TexturedMesh(indices, vbo, GL_TRIANGLES, element_count));
        shared_ptr<Material> material(new Material());
        
        // Load material info
        if (material_filename.size() > 1) {
            String material_path = getDirectory(path) + "/" + material_filename;
            std::ifstream mat_file(material_path.c_str());
            assert(mat_file.is_open());
            
            while (mat_file.good()) {
                char c;
                std::string line;
                std::getline(mat_file, line);
                std::stringstream ss(line);
                
                if (line[0] == 'K' && line[1] == 'a') {
                    Vec4 color;
                    ss >> c >> c >> color.r >> color.g >> color.b;
                    material->setAmbientColor(color);
                } else if (line[0] == 'K' && line[1] == 'd') {
                    Vec4 color;
                    ss >> c >> c >> color.r >> color.g >> color.b;
                    material->setDiffuseColor(color);
                } else if (line[0] == 'K' && line[1] == 's') {
                    Vec4 color;
                    ss >> c >> c >> color.r >> color.g >> color.b;
                    material->setSpecularColor(color);
                } else if (line[0] == 'N' && line[1] == 's') {
                    float shininess;
                    ss >> c >> c >> shininess;
                    material->setShininess(shininess);
                } else if (startsWith(line, "map_Kd")) {
                    String texture_filename;
                    ss >> texture_filename >> texture_filename;
                    textured_mesh->setTexture(Application::get().getResourceManager().getTexture(texture_filename));
                }
            }
        }
        
        textured_mesh->setMaterial(material);
        
        return textured_mesh;
    }
}