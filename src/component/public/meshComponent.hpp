#pragma once
#include "sceneComponent.hpp"

class IMesh;
class IMaterial;

class MeshComponent:public SceneComponent
{
    public:
        MeshComponent(IMesh* mesh, IMaterial* material):
                        mesh(mesh), material(material){}
        void SetMesh(IMesh* mesh){this->mesh = mesh;}
        void SetMaterial(IMaterial* material){this->material = material;}
        IMesh* GetMesh(){return mesh;}
        IMaterial* GetMaterial(){return material;}
    private:
        IMesh* mesh;
        IMaterial* material;

};