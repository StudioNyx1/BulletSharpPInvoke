#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif
	//EXPORT btSoftRigidDynamicsWorld* btSoftRigidDynamicsWorld_new(btDispatcher* dispatcher, btBroadphaseInterface* pairCache, btConstraintSolver* constraintSolver, btCollisionConfiguration* collisionConfiguration, btSoftBodySolver* softBodySolver);
	EXPORT btSoftRigidDynamicsWorld* btSoftRigidDynamicsWorld_new(btSoftBodyWorldInfo* worldInfo, btConstraintSolver* constraintSolver, btCollisionConfiguration* collisionConfiguration, btSoftBodySolver* softBodySolver);
	EXPORT void btSoftRigidDynamicsWorld_addSoftBody(btSoftRigidDynamicsWorld* obj, btSoftBody* body);
	EXPORT void btSoftRigidDynamicsWorld_addSoftBody2(btSoftRigidDynamicsWorld* obj, btSoftBody* body, int collisionFilterGroup);
	EXPORT void btSoftRigidDynamicsWorld_addSoftBody3(btSoftRigidDynamicsWorld* obj, btSoftBody* body, int collisionFilterGroup, int collisionFilterMask);
	EXPORT int btSoftRigidDynamicsWorld_getDrawFlags(btSoftRigidDynamicsWorld* obj);
	EXPORT btAlignedObjectArray_btSoftBodyPtr* btSoftRigidDynamicsWorld_getSoftBodyArray(btSoftRigidDynamicsWorld* obj);
	EXPORT btSoftBodyWorldInfo* btSoftRigidDynamicsWorld_getWorldInfo(btSoftRigidDynamicsWorld* obj);
	EXPORT void btSoftRigidDynamicsWorld_removeSoftBody(btSoftRigidDynamicsWorld* obj, btSoftBody* body);
	EXPORT void btSoftRigidDynamicsWorld_setDrawFlags(btSoftRigidDynamicsWorld* obj, int f);
	EXPORT void btUpdateCableForces(btSoftRigidDynamicsWorld* obj, btSoftBody_NodeForces* co, int size);
	EXPORT void* btGetCablesData(btSoftRigidDynamicsWorld* obj);
	EXPORT void btPrepareSingleStepSimulation(btSoftRigidDynamicsWorld* obj);
	EXPORT void* btGetNodesPos(btSoftRigidDynamicsWorld* obj);
	EXPORT void* btGetNodesData(btSoftRigidDynamicsWorld* obj);
	EXPORT int* btGetCableIndexesArray(btSoftRigidDynamicsWorld* obj);
	EXPORT int btGetHydroNodesNumber(btSoftRigidDynamicsWorld* obj);
	EXPORT void btSoftRigidDynamicsWorld_addMapCableCollisionObjects(btSoftRigidDynamicsWorld* world, btCollisionObject* key, btCollisionObject* value);
	EXPORT void btSoftRigidDynamicsWorld_eraseMapCableCollisionObjects(btSoftRigidDynamicsWorld* world, btCollisionObject* key);
#ifdef __cplusplus
}
#endif
