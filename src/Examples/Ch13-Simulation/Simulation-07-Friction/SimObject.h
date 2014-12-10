//===============================================================================
// @ SimObject.h
// ------------------------------------------------------------------------------
//
// Copyright (C) 2008 by Elsevier, Inc. All rights reserved.
//
//
//
//===============================================================================

#ifndef __SimObjectDefs__
#define __SimObjectDefs__

//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------

#include <IvQuat.h>
#include <IvVector3.h>
#include <IvMatrix33.h>
#include <IvBoundingSphere.h>

//-------------------------------------------------------------------------------
//-- Classes --------------------------------------------------------------------
//-------------------------------------------------------------------------------

class SimObject
{
public:
    SimObject();
    virtual ~SimObject();

    virtual void Update( float dt );
    void Render();
    void Reset();
    void SetMass( float mass );
    void SetBounds( float radius );
    void SetTranslate( const IvVector3& position );

    void HandleCollision( SimObject* other );
    
    inline void SetConstantForce( const IvVector3& force ) { mConstantForce = force; }
    inline void SetConstantTorque( const IvVector3& torque ) { mConstantTorque = torque; }

protected:
    void        InitializeMoments();
    void        Integrate( float dt );
    IvVector3   CurrentForce( const IvVector3& position, const IvVector3& velocity,
                              const IvQuat& orientation, const IvVector3& angularVelocity );
    IvVector3   CurrentTorque( const IvVector3& position, const IvVector3& velocity,
                              const IvQuat& orientation, const IvVector3& angularVelocity );
    bool        Colliding( const SimObject* other, 
                    IvVector3& collisionNormal, IvVector3& collisionPoint, float& penetration ) const;

    IvQuat       mRotate;
    IvVector3   mTranslate;

    float       mElasticity;
    IvVector3   mVelocity;
    IvVector3   mConstantForce; // part of force which is constant over interval
    
    // angular physics
    IvMatrix33      mMomentsInverse;
    IvMatrix33      mWorldMomentsInverse;
    IvVector3       mAngularMomentum;
    IvVector3       mAngularVelocity;
    IvVector3       mConstantTorque;    // part of torque which is constant over interval

private:
    // put here so child classes have to use SetMass() and SetBounds()
    float       mMass;

    // bounding data
    IvBoundingSphere    mSphere;
};

#endif