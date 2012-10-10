//
//  BillboardParticles.h
//  D3
//
//  Created by Srđan Rašić on 10/7/12.
//  Copyright (c) 2012 Srđan Rašić. All rights reserved.
//

#ifndef __D3__BillboardParticles__
#define __D3__BillboardParticles__

namespace d3 {
    class BillboardParticles : public Drawable, public SceneSimulator::Updatable {        
    public:
        BillboardParticles(shared_ptr<ParticleSystem> particle_system);
        
        //! @return Referenct to bound emitter
        shared_ptr<ParticleSystem> & getEmitter() { return emitter; }
        
        //! SceneSimulator::Updatable:: Updates VBO
        virtual void update(float dt);
        
        //! Drawable:: Called upon drawing
        virtual void preDraw(SceneRenderer & renderer);
        
        //! Drawable:: Draw one occurrence
        virtual void drawOccurrence(SceneRenderer & renderer, SceneNode & node);
        
        //! Drawable:: Called after drawing
        virtual void postDraw(SceneRenderer & renderer);
        
    protected:
        shared_ptr<ParticleSystem> emitter;
        
        struct IndexTemplate {
            unsigned int indices[6] = { 3, 3, 0, 2, 1, 1 }; // Short!
        };
        
        struct VertexTemplate {
            Vec3 position;
            int color;
        };
        
        shared_ptr<VertexData> ibo;
        shared_ptr<VertexData> tbo;
        shared_ptr<VertexData> vbo;
        
        unsigned int vbo_size;
        unsigned int particle_count;
        unsigned int current_node;
    };
}

#endif