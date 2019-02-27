#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "tensor.h"
#include "material.h"

namespace e8
{

typedef e8util::vec<3, unsigned> triangle;

class if_geometry
{
public:
        if_geometry();
        virtual ~if_geometry();

        virtual std::vector<e8util::vec3> const&        vertices() const = 0;
        virtual std::vector<e8util::vec3> const&        normals() const = 0;
        virtual std::vector<e8util::vec2> const&        texcoords() const = 0;
        virtual std::vector<triangle> const&            triangles() const = 0;
        virtual void                                    sample(e8util::rng& rng, e8util::vec3& p, e8util::vec3& n, float& pdf) const = 0;
        virtual float                                   surface_area() const = 0;
        virtual e8util::aabb                            aabb() const = 0;
};

class trimesh: public if_geometry
{
public:
        trimesh();
        virtual ~trimesh() override;

        std::vector<e8util::vec3> const&        vertices() const override;
        std::vector<e8util::vec3> const&        normals() const override;
        std::vector<e8util::vec2> const&        texcoords() const override;
        std::vector<triangle> const&            triangles() const override;
        void                                    sample(e8util::rng& rng, e8util::vec3& p, e8util::vec3& n, float& pdf) const override;
        float                                   surface_area() const override;
        virtual e8util::aabb                    aabb() const override;

        void                                    vertices(std::vector<e8util::vec3> const& v);
        void                                    normals(std::vector<e8util::vec3> const& n);
        void                                    texcoords(std::vector<e8util::vec2> const& t);
        void                                    triangles(std::vector<triangle> const& t);

        void                                    update();
protected:
        std::vector<e8util::vec3>       m_verts;
        std::vector<e8util::vec3>       m_norms;
        std::vector<e8util::vec2>       m_texcoords;
        std::vector<triangle>           m_tris;
        e8util::aabb                    m_aabb;
        std::vector<float>              m_cum_area;
        float                           m_area;
};


class uv_sphere: public trimesh
{
public:
        uv_sphere(e8util::vec3 const& o, float r, unsigned const res);
        ~uv_sphere();
};



}

#endif // GEOMETRY_H
