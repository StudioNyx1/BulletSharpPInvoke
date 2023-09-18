#include "main.h"
#include <vector> 
using namespace std;

#ifdef __cplusplus
extern "C" {
#endif
	EXPORT btCable* btCable_new(btSoftBodyWorldInfo* worldInfo,btCollisionWorld* world, int node_count, const btScalar* x, const btScalar* m);

	EXPORT void btCable_removeLink(btCable* obj, int index);
	EXPORT void btCable_removeNode(btCable* obj, int index);
	EXPORT void btCable_removeAnchor(btCable* obj, int index);
	EXPORT void btCable_setRestLengthLink(btCable* obj, int index, btScalar distance);
	EXPORT btScalar btCable_getRestLengthLink(btCable* obj, int index);
	EXPORT void btCable_swapNodes(btCable* obj, int index0, int index1);
	EXPORT void btCable_swapAnchors(btCable* obj, int index0, int index1);
	EXPORT btScalar btCable_getLengthPosition(btCable* obj);
	EXPORT btScalar btCable_getLengthRestlength(btCable* obj);
	EXPORT btVector3* btCable_getImpulses(btCable* obj);
	EXPORT void btCable_getImpulse(btCable* obj, btVector3* v, int index);
	EXPORT int btCable_getNumberNodes(btCable* obj);
	EXPORT void btCable_getPositionNode(btCable* obj, btVector3* v, int index);
	EXPORT void btCable_updateImpulses(btCable* obj, btVector3* vecPtr, int length);
	EXPORT void btCable_setBendingMaxAngle(btCable* obj,btScalar angle);
	EXPORT btScalar btCable_getBendingMaxAngle(btCable* obj);
	EXPORT void btCable_setBendingStiffness(btCable* obj,btScalar stiffness);
	EXPORT btScalar btCable_getBendingStiffness(btCable* obj);
	EXPORT void btCable_setAnchorIndex(btCable* obj, int index);
	EXPORT int btCable_getAnchorIndex(btCable* obj);
	EXPORT void btCable_setUseLRA(btCable* obj, bool active);
	EXPORT bool btCable_getUseLRA(btCable* obj);
	EXPORT void btCable_setUseBending(btCable* obj, bool active);
	EXPORT bool btCable_getUseBending(btCable* obj);
	EXPORT void btCable_setUseGravity(btCable* obj, bool active);
	EXPORT bool btCable_getUseGravity(btCable* obj);
	EXPORT void btCable_setUseCollision(btCable* obj, bool active);
	EXPORT bool btCable_getUseCollision(btCable* obj);
#ifdef __cplusplus
}
#endif