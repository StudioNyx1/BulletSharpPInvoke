#include <BulletCollision/CollisionDispatch/btCollisionConfiguration.h>
#include <BulletDynamics/ConstraintSolver/btConstraintSolver.h>
#include <BulletSoftBody/btSoftBodySolvers.h>
#include <BulletSoftBody/btSoftRigidDynamicsWorld.h>

#include "btSoftRigidDynamicsWorld_wrap.h"

//btSoftRigidDynamicsWorld* btSoftRigidDynamicsWorld_new(btDispatcher* dispatcher,
//	btBroadphaseInterface* pairCache, btConstraintSolver* constraintSolver, btCollisionConfiguration* collisionConfiguration,
//	btSoftBodySolver* softBodySolver)
//{
//	return new btSoftRigidDynamicsWorld(dispatcher, pairCache, constraintSolver,
//		collisionConfiguration, softBodySolver);
//}

btSoftRigidDynamicsWorld* btSoftRigidDynamicsWorld_new(btSoftBodyWorldInfo* worldInfo, btConstraintSolver* constraintSolver, btCollisionConfiguration* collisionConfiguration,
	btSoftBodySolver* softBodySolver)
{
	return new btSoftRigidDynamicsWorld(worldInfo, constraintSolver,
		collisionConfiguration, softBodySolver);
}

void btSoftRigidDynamicsWorld_addSoftBody(btSoftRigidDynamicsWorld* obj, btSoftBody* body)
{
	obj->addSoftBody(body);
}

void btSoftRigidDynamicsWorld_addSoftBody2(btSoftRigidDynamicsWorld* obj, btSoftBody* body,
	int collisionFilterGroup)
{
	obj->addSoftBody(body, collisionFilterGroup);
}

void btSoftRigidDynamicsWorld_addSoftBody3(btSoftRigidDynamicsWorld* obj, btSoftBody* body,
	int collisionFilterGroup, int collisionFilterMask)
{
	obj->addSoftBody(body, collisionFilterGroup, collisionFilterMask);
}

int btSoftRigidDynamicsWorld_getDrawFlags(btSoftRigidDynamicsWorld* obj)
{
	return obj->getDrawFlags();
}

btAlignedObjectArray_btSoftBodyPtr* btSoftRigidDynamicsWorld_getSoftBodyArray(btSoftRigidDynamicsWorld* obj)
{
	return &obj->getSoftBodyArray();
}

btSoftBodyWorldInfo* btSoftRigidDynamicsWorld_getWorldInfo(btSoftRigidDynamicsWorld* obj)
{
	return &obj->getWorldInfo();
}

void btSoftRigidDynamicsWorld_removeSoftBody(btSoftRigidDynamicsWorld* obj, btSoftBody* body)
{
	obj->removeSoftBody(body);
}

void btSoftRigidDynamicsWorld_setDrawFlags(btSoftRigidDynamicsWorld* obj, int f)
{
	obj->setDrawFlags(f);
}

void btUpdateCableForces(btSoftRigidDynamicsWorld* obj, btSoftBody_NodeForces* co, int size)
{
	obj->updateCableForces(co, size);
}

void* btGetCablesData(btSoftRigidDynamicsWorld* obj)
{
	return obj->getCablesData();
}

void btPrepareSingleStepSimulation(btSoftRigidDynamicsWorld* obj)
{
	obj->prepareSingleStepSimulation();
}

void* btGetNodesPos(btSoftRigidDynamicsWorld* obj)
{
	return obj->getNodesPos();
}

void* btGetNodesData(btSoftRigidDynamicsWorld* obj)
{
	return obj->getNodesData();
}

int* btGetCableIndexesArray(btSoftRigidDynamicsWorld* obj)
{
	return obj->getCableIndexesArray();
}

int btGetHydroNodesNumber(btSoftRigidDynamicsWorld* obj)
{
	return obj->getHydroNodesNumber();
}

void btSoftRigidDynamicsWorld_addMapCableCollisionObjects(btSoftRigidDynamicsWorld* world, btCollisionObject* key, btCollisionObject* value)
{
	world->m_cableCollisionObjects.insert({ key, value });
}

void btSoftRigidDynamicsWorld_eraseMapCableCollisionObjects(btSoftRigidDynamicsWorld* world, btCollisionObject* key)
{
	world->m_cableCollisionObjects.erase(key);
}