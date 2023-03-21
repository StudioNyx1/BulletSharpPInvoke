#include <BulletCollision/BroadphaseCollision/btBroadphaseInterface.h>
#include <BulletCollision/BroadphaseCollision/btDispatcher.h>
#include <BulletCollision/CollisionDispatch/btCollisionObjectWrapper.h>
#include <BulletSoftBody/btSoftBody.h>
#include <BulletCable/btCable.h>
#include <BulletSoftBody/btSoftBodySolvers.h>

#include "conversion.h"
#include "btSoftBody_wrap.h"
#include "btCable_wrap.h"

btCable* btCable_new(btSoftBodyWorldInfo* worldInfo, int node_count, const btScalar* x, const btScalar* m)
{
	btVector3* xTemp = Vector3ArrayIn(x, node_count);
	btCable* ret = new btCable(worldInfo, node_count, xTemp, m);
	delete[] xTemp;
	return ret;
}

void btCable_removeLink(btCable* obj, int index)
{
	obj->removeLink(index);
}

void btCable_removeNode(btCable* obj, int index)
{
	obj->removeNode(index);
}

void btCable_removeAnchor(btCable* obj, int index)
{
	obj->removeAnchor(index);
}

void btCable_setRestLengtLink(btCable* obj, int index, btScalar distance)
{
	obj->setRestLenghtLink(index, distance);
}

btScalar btCable_getRestLengtLink(btCable* obj, int index)
{
	return obj->getRestLenghtLink(index);
}

void btCable_swapNodes(btCable* obj, int index0, int index1)
{
	return obj->swapNodes(index0, index1);
}

btScalar btCable_getLength(btCable* obj)
{
	return obj->getLength();
}

btVector3* btCable_getImpulseAnchors(btCable* obj, int nb)
{
	return obj->getImpulseAnchors(nb);
}
