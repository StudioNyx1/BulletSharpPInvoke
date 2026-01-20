#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif
	EXPORT btCollisionDispatcher* btCollisionDispatcherMt_new(btCollisionConfiguration* collisionConfiguration, int grainSize);
	EXPORT int btCollisionDispatcherMt_getNumManifoldsCache(btCollisionDispatcherMt* obj);
	EXPORT int btCollisionDispatcherMt_getNumParticlesManifolds(btCollisionDispatcherMt* obj);

	EXPORT const btCollisionObject* btCollisionDispatcherMt_CustomManifold_getBody0(btCollisionDispatcherMt* obj, int manifoldIndex);
	EXPORT const btCollisionObject* btCollisionDispatcherMt_CustomManifold_getBody1(btCollisionDispatcherMt* obj, int manifoldIndex);
	EXPORT int btCollisionDispatcherMt_CustomManifold_getNumContacts(btCollisionDispatcherMt* obj, int manifoldIndex);
	EXPORT void btCollisionDispatcherMt_CustomManifold_getPositionWorldOnAByIndex(btCollisionDispatcherMt* obj, int manifoldIndex, int pointIndex, btVector3* posA);
	EXPORT void btCollisionDispatcherMt_CustomManifold_getPositionWorldOnBByIndex(btCollisionDispatcherMt* obj, int manifoldIndex, int pointIndex, btVector3* posB);
	EXPORT void btCollisionDispatcherMt_CustomManifold_getNormalWorldOnBByIndex(btCollisionDispatcherMt* obj, int manifoldIndex, int pointIndex, btVector3* normalB);
	EXPORT double btCollisionDispatcherMt_CustomManifold_getDistanceByIndex(btCollisionDispatcherMt* obj, int manifoldIndex, int pointIndex);
	EXPORT double btCollisionDispatcherMt_CustomManifold_getAppliedImpulse(btCollisionDispatcherMt* obj, int manifoldIndex, int pointIndex);

	EXPORT const btCollisionObject* btCollisionDispatcherMt_ParticlesCustomManifold_getBody0(btCollisionDispatcherMt* obj, int manifoldIndex);
	EXPORT const btCollisionObject* btCollisionDispatcherMt_ParticlesCustomManifold_getBody1(btCollisionDispatcherMt* obj, int manifoldIndex);
	EXPORT int btCollisionDispatcherMt_ParticlesCustomManifold_getNumContacts(btCollisionDispatcherMt* obj, int manifoldIndex);
	EXPORT void btCollisionDispatcherMt_ParticlesCustomManifold_getPositionWorldOnAByIndex(btCollisionDispatcherMt* obj, int manifoldIndex, int pointIndex, btVector3* posA);
	EXPORT void btCollisionDispatcherMt_ParticlesCustomManifold_getPositionWorldOnBByIndex(btCollisionDispatcherMt* obj, int manifoldIndex, int pointIndex, btVector3* posB);
	EXPORT void btCollisionDispatcherMt_ParticlesCustomManifold_getNormalWorldOnBByIndex(btCollisionDispatcherMt* obj, int manifoldIndex, int pointIndex, btVector3* normalB);
	EXPORT double btCollisionDispatcherMt_ParticlesCustomManifold_getDistanceByIndex(btCollisionDispatcherMt* obj, int manifoldIndex, int pointIndex);
	EXPORT double btCollisionDispatcherMt_ParticlesCustomManifold_getAppliedImpulse(btCollisionDispatcherMt* obj, int manifoldIndex, int pointIndex);


#ifdef __cplusplus
}
#endif
