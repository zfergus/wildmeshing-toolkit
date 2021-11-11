#pragma once

#include "TetMesh.h"

namespace wmtk {

    class VertexAttributes {
    public:
        Vector3 m_pos;
        Vector3f m_posf;

        bool m_is_on_surface;
        bool m_is_on_boundary;
        bool m_is_on_bbox;
        bool m_is_outside;

        Scalar m_sizing_scalars;
        Scalar m_scalars;
        bool m_is_freezed;
    };

    class EdgeAttributes {
    public:
        // Scalar length;
    };

    class FaceAttributes {
    public:
        Scalar tag;

        int m_is_surface_fs;
        int m_is_bbox_fs;
        int m_opp_t_ids;
        int m_surface_tags;
    };

    class TetAttributes {
    public:
        Scalar m_qualities;
        Scalar m_scalars;
        bool m_is_outside;
    };

    class TetWild : public TetMesh {
    public:

        class InfoCacheSplit: public InfoCache{
        public:
            Vector3f mid_p;
            ~InfoCacheSplit(){}
        };

        Parameters& m_params;
        Envelope& m_envelope;

        TetWild(Parameters& _m_params, Envelope& _m_envelope): m_params(_m_params), m_envelope(_m_envelope){}
        ~TetWild(){}

        void create_mesh_attributes(const std::vector<VertexAttributes> &_vertex_attribute,
                                    const std::vector<TetAttributes> &_tet_attribute){
            m_vertex_attribute = _vertex_attribute;
            m_tet_attribute = _tet_attribute;
        }

        // Stores the attributes attached to simplices
        std::vector<VertexAttributes> m_vertex_attribute;
        std::vector<EdgeAttributes> m_edge_attribute;
        std::vector<FaceAttributes> m_face_attribute;
        std::vector<TetAttributes> m_tet_attribute;

        inline void resize_attributes(size_t v, size_t e, size_t t, size_t tt) override {
            m_vertex_attribute.resize(v);
            m_edge_attribute.resize(e);
            m_face_attribute.resize(t);
            m_tet_attribute.resize(tt);
        }

        void smoothing(const Tuple &t);

        // all the other functions
        inline void test(){
            std::shared_ptr<InfoCache> info0 = std::make_shared<InfoCache>();
            std::shared_ptr<InfoCacheSplit> info = std::make_shared<InfoCacheSplit>();
            info->mid_p = Vector3f(1,2,3);
            info0 = info;

            auto testtest = [](std::shared_ptr<InfoCache> info1){
                std::shared_ptr<InfoCacheSplit> info2 = std::dynamic_pointer_cast<InfoCacheSplit> (info1);
                cout<<info2->mid_p<<endl;
            };

            testtest(info0);
        }
    private:
        bool split_before(const Tuple &t, std::shared_ptr<InfoCache> info) override;
        bool split_after(const Tuple &t, std::shared_ptr<InfoCache> info) override;

        bool is_inverted(size_t t_id);
        double get_quality(size_t t_id);

    };

}