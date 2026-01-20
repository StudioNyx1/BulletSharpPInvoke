#include <BulletCollision/CollisionDispatch/btCollisionConfiguration.h>
#include <BulletCollision/CollisionDispatch/btCollisionDispatcherMt.h>
#include <BulletCollision/NarrowPhaseCollision/CustomManifold.h>

#include "btCollisionDispatcherMt_wrap.h"
#include "conversion.h"

btCollisionDispatcher* btCollisionDispatcherMt_new(btCollisionConfiguration* collisionConfiguration, int grainSize)
{
	return new btCollisionDispatcherMt(collisionConfiguration, grainSize);
}

int btCollisionDispatcherMt_getNumManifoldsCache(btCollisionDispatcherMt* obj)
{
	return obj->getNumManifoldsCache();
}

int btCollisionDispatcherMt_getNumParticlesManifolds(btCollisionDispatcherMt* obj)
{
	return obj->getNumParticlesManifolds();
}

const btCollisionObject* btCollisionDispatcherMt_CustomManifold_getBody0(btCollisionDispatcherMt* obj, int manifoldIndex)
{
	return obj->getManifoldsCacheByIndexInternal(manifoldIndex)->getBody0();
}

const btCollisionObject* btCollisionDispatcherMt_CustomManifold_getBody1(btCollisionDispatcherMt* obj, int manifoldIndex)
{
	return obj->getManifoldsCacheByIndexInternal(manifoldIndex)->getBody1();
}

int btCollisionDispatcherMt_CustomManifold_getNumContacts(btCollisionDispatcherMt* obj, int manifoldIndex)
{
	return obj->getManifoldsCacheByIndexInternal(manifoldIndex)->getCount();
}

void btCollisionDispatcherMt_CustomManifold_getPositionWorldOnAByIndex(btCollisionDispatcherMt* obj, int manifoldIndex, int pointIndex, btVector3* posA)
{
	BTVECTOR3_COPY(posA,obj->getManifoldsCacheByIndexInternal(manifoldIndex)->getManifoldPoint(pointIndex)->GetPositionWorldOnA());
}

void btCollisionDispatcherMt_CustomManifold_getPositionWorldOnBByIndex(btCollisionDispatcherMt* obj, int manifoldIndex, int pointIndex, btVector3* posA)
{
	BTVECTOR3_COPY(posA, obj->getManifoldsCacheByIndexInternal(manifoldIndex)->getManifoldPoint(pointIndex)->GetPositionWorldOnB());
}

void btCollisionDispatcherMt_CustomManifold_getNormalWorldOnBByIndex(btCollisionDispatcherMt* obj, int manifoldIndex, int pointIndex, btVector3* posA)
{
	BTVECTOR3_COPY(posA, obj->getManifoldsCacheByIndexInternal(manifoldIndex)->getManifoldPoint(pointIndex)->GetNormal());
}

double btCollisionDispatcherMt_CustomManifold_getDistanceByIndex(btCollisionDispatcherMt* obj, int manifoldIndex, int pointIndex)
{
	return obj->getManifoldsCacheByIndexInternal(manifoldIndex)->getManifoldPoint(pointIndex)->GetDepth();
}

double btCollisionDispatcherMt_CustomManifold_getAppliedImpulse(btCollisionDispatcherMt* obj, int manifoldIndex, int pointIndex)
{
	return obj->getManifoldsCacheByIndexInternal(manifoldIndex)->getManifoldPoint(pointIndex)->GetImpulse();
}


const btCollisionObject* btCollisionDispatcherMt_ParticlesCustomManifold_getBody0(btCollisionDispatcherMt* obj, int manifoldIndex)
{
	return obj->getManifoldsCacheByIndexInternal(manifoldIndex)->getBody0();
}

const btCollisionObject* btCollisionDispatcherMt_ParticlesCustomManifold_getBody1(btCollisionDispatcherMt* obj, int manifoldIndex)
{
	return obj->getParticlesManifoldsByIndexInternal(manifoldIndex)->getBody1();
}

int btCollisionDispatcherMt_ParticlesCustomManifold_getNumContacts(btCollisionDispatcherMt* obj, int manifoldIndex)
{
	return obj->getParticlesManifoldsByIndexInternal(manifoldIndex)->getCount();
}

void btCollisionDispatcherMt_ParticlesCustomManifold_getPositionWorldOnAByIndex(btCollisionDispatcherMt* obj, int manifoldIndex, int pointIndex, btVector3* posA)
{
	BTVECTOR3_COPY(posA, obj->getParticlesManifoldsByIndexInternal(manifoldIndex)->getManifoldPoint(pointIndex)->GetPositionWorldOnA());
}

void btCollisionDispatcherMt_ParticlesCustomManifold_getPositionWorldOnBByIndex(btCollisionDispatcherMt* obj, int manifoldIndex, int pointIndex, btVector3* posA)
{
	BTVECTOR3_COPY(posA, obj->getParticlesManifoldsByIndexInternal(manifoldIndex)->getManifoldPoint(pointIndex)->GetPositionWorldOnB());
}

void btCollisionDispatcherMt_ParticlesCustomManifold_getNormalWorldOnBByIndex(btCollisionDispatcherMt* obj, int manifoldIndex, int pointIndex, btVector3* posA)
{
	BTVECTOR3_COPY(posA, obj->getParticlesManifoldsByIndexInternal(manifoldIndex)->getManifoldPoint(pointIndex)->GetNormal());
}

double btCollisionDispatcherMt_ParticlesCustomManifold_getDistanceByIndex(btCollisionDispatcherMt* obj, int manifoldIndex, int pointIndex)
{
	return obj->getParticlesManifoldsByIndexInternal(manifoldIndex)->getManifoldPoint(pointIndex)->GetDepth();
}

double btCollisionDispatcherMt_ParticlesCustomManifold_getAppliedImpulse(btCollisionDispatcherMt* obj, int manifoldIndex, int pointIndex)
{
	return obj->getParticlesManifoldsByIndexInternal(manifoldIndex)->getManifoldPoint(pointIndex)->GetImpulse();
}

