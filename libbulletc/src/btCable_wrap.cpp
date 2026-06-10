#include <BulletCollision/BroadphaseCollision/btBroadphaseInterface.h>
#include <BulletCollision/BroadphaseCollision/btDispatcher.h>
#include <BulletCollision/CollisionDispatch/btCollisionObjectWrapper.h>
#include <BulletSoftBody/btSoftBody.h>
#include <BulletCable/btCable.h>
#include <BulletSoftBody/btSoftBodySolvers.h>
#include "conversion.h"
#include "btSoftBody_wrap.h"
#include "btCable_wrap.h"

btCable* btCable_new(btSoftBodyWorldInfo* worldInfo, btCollisionWorld* world, int node_count,  int section_count ,const btScalar* x, const btScalar* m)
{
	btVector3* xTemp = Vector3ArrayIn(x, node_count);
	btCable* ret = new btCable(worldInfo, world, node_count,section_count, xTemp, m);
	delete[] xTemp;
	return ret;
}

void btCable_removeLinkAt(btCable* obj, int index)
{
	obj->m_links.removeAtIndex(index);
}

void btCable_removeNodeAt(btCable* obj, int index)
{
	obj->removeNodeAt(index);
}

void btCable_removeAnchorAt(btCable* obj, int index)
{
	int idxNode = obj->m_anchors[index].m_node->index;

	// Update rigidbody count and clamp count to avoid divergence
	obj->m_anchors[index].m_body->m_anchorsCount = max(0, obj->m_anchors[index].m_body->m_anchorsCount - 1);
	obj->m_collisionDisabledObjects.remove(obj->m_anchors[index].m_body);
	obj->m_anchors.removeAtIndex(index);

	// Search if another anchor is attached to the node used by the removed one
	for (int i = 0; i < obj->m_anchors.size(); i++)
	{
		if (idxNode == obj->m_anchors[i].m_node->index)
		{
			return;
		}
	}

	if (idxNode >= obj->m_nodes.size()) return;

	obj->m_nodes[idxNode].m_battach = 0;
}

void btCable_getTensionAt(btCable* obj, int index, btVector3* impulse)
{
	BTVECTOR3_SET(impulse, obj->getTensionAt(index));
}

void btCable_getLocalAnchorWithNode(btCable* obj, int indexNode, btVector3* local)
{
	BTVECTOR3_SET(local, obj->getLocalAnchorWithNode(indexNode));
}

int btCable_getNumberOfNode(btCable* obj)
{
	return obj->m_nodes.size();
}

int btCable_getNumberOfAnchor(btCable* obj)
{
	return obj->m_anchors.size();
}

int btCable_getNumberOfLink(btCable* obj)
{
	return obj->m_links.size();
}

btCable::CableData* btCable_getCableData(btCable* obj)
{
	return obj->getCableData();
}

btCable::NodePos* btCable_getNodePos(btCable* obj)
{
	return obj->getNodePos();
}

btScalar btCable_getLength(btCable* obj)
{
	return obj->getLength();
}

btScalar btCable_getRestLength(btCable* obj)
{
	return obj->getRestLength();
}

void btCable_Node_GetPosition(btCable* obj, int index, btVector3* position)
{
	BTVECTOR3_SET(position, obj->m_nodes[index].m_x);
}

void btCable_Node_SetPosition(btCable* obj, int index, btVector3 position)
{
	BTVECTOR3_SET(&obj->m_nodes[index].m_x, position);
}

void btCable_Node_GetVelocity(btCable* obj, int index, btVector3* velocity)
{
	BTVECTOR3_SET(velocity, obj->m_nodes[index].m_v);
}

void btCable_Node_SetVelocity(btCable* obj, int index, btVector3 velocity)
{
	BTVECTOR3_SET(&obj->m_nodes[index].m_v, velocity);
}

void btCable_Node_GetForce(btCable* obj, int index, btVector3* force)
{
	BTVECTOR3_SET(force, obj->m_nodes[index].m_f);
}

void btCable_Node_SetForce(btCable* obj, int index, btVector3 force)
{
	BTVECTOR3_SET(&obj->m_nodes[index].m_f, force);
}

btScalar btCable_Node_GetInverseMass(btCable* obj, int index)
{
	if (index >= 0 && index < obj->m_nodes.size()) {
		return obj->m_nodes[index].m_im;
	}
	return 0.0;
}

void btCable_Node_SetInverseMass(btCable* obj, int index, btScalar inverseMass)
{
	obj->m_nodes[index].m_im = inverseMass;
}

btScalar btCable_Node_GetArea(btCable* obj, int index)
{
	return obj->m_nodes[index].m_area;
}

void btCable_Node_SetArea(btCable* obj, int index, btScalar area)
{
	obj->m_nodes[index].m_area = area;
}

int btCable_Node_GetIsAttached(btCable* obj, int index)
{
	return obj->m_nodes[index].m_battach;
}

void btCable_Node_SetIsAttached(btCable* obj, int index, int isAttached)
{
	obj->m_nodes[index].m_battach = isAttached;
}

int btCable_Node_GetIndex(btCable* obj, int index)
{
	return obj->m_nodes[index].index;
}

void btCable_Node_SetIndex(btCable* obj, int index, int newIndex)
{
	obj->m_nodes[index].index = newIndex;
}

bool btCable_Anchor_HasNode(btCable* obj, int index)
{
	try
	{
		return obj->m_anchors[index].m_node != nullptr;
	}
	catch (exception e)
	{
		return false;
	}
}

int btCable_Anchor_GetIndexOfNode(btCable* obj, int index)
{
	return obj->m_anchors[index].m_node->index;
}

void btCable_Anchor_SetNode(btCable* obj, int indexAnchor, int indexNode)
{
	obj->m_anchors[indexAnchor].m_node = &obj->m_nodes[indexNode];
}

int btCable_Link_GetNode0(btCable* obj, int index)
{
	return obj->m_links[index].m_n[0]->index;
}

void btCable_Link_SetNode0(btCable* obj, int indexLink, int indexNode)
{
	obj->m_links[indexLink].m_n[0] = &obj->m_nodes[indexNode];
}

int btCable_Link_GetNode1(btCable* obj, int index)
{
	return obj->m_links[index].m_n[1]->index;
}

void btCable_Link_SetNode1(btCable* obj, int indexLink, int indexNode)
{
	obj->m_links[indexLink].m_n[1] = &obj->m_nodes[indexNode];
}

btScalar btCable_Link_GetRestLength(btCable* obj, int index)
{
	return obj->m_links[index].m_rl;
}

void btCable_Link_SetRestLength(btCable* obj, int index, btScalar rl)
{
	obj->m_links[index].m_rl = rl;
	obj->m_links[index].m_c1 = obj->m_links[index].m_rl * obj->m_links[index].m_rl;
}

bool btCable_LRA_GetActive(btCable* obj)
{
	return obj->getUseLRA();
}

void btCable_LRA_SetActive(btCable* obj, bool active)
{
	obj->setUseLRA(active);
}

void btCable_LRA_SetInvert(btCable* obj, bool invert)
{
	obj->setInvertLRA(invert);
}

bool btCable_Bending_GetActive(btCable* obj)
{
	return  obj->getUseBending();
}

void btCable_Bending_SetActive(btCable* obj, bool active)
{
	obj->setUseBending(active);
}

btScalar btCable_Bending_GetBendingMaxAngle(btCable* obj)
{
	return obj->getBendingMaxAngle();
}

void btCable_Bending_SetBendingMaxAngle(btCable* obj, btScalar angle)
{
	obj->setBendingMaxAngle(angle);
}

btScalar btCable_Bending_GetBendingStiffness(btCable* obj)
{
	return obj->getBendingStiffness();
}

void btCable_Bending_SetBendingStiffness(btCable* obj, btScalar stiffness)
{
	obj->setBendingStiffness(stiffness);
}

bool btCable_Gravity_GetActive(btCable* obj)
{
	return obj->getUseGravity();
}

void btCable_Gravity_SetActive(btCable* obj, bool active)
{
	return obj->setUseGravity(active);
}

bool btCable_Collision_GetActive(btCable* obj)
{
	return obj->getUseCollision();
}

void btCable_Collision_SetActive(btCable* obj, bool active)
{
	obj->setUseCollision(active);
}

void btCable_setCableRadius(btCable* obj, float radius)
{
	obj->setCableRadius(radius);
}

void btCable_setCableNormalDragCoefficient(btCable* obj, float normalDragCoefficient)
{
	obj->setCableNormalDragCoefficient(normalDragCoefficient);
}

void btCable_setCableTangentDragCoefficient(btCable* obj, float tangentDragCoefficient)
{
	obj->setCableTangentDragCoefficient(tangentDragCoefficient);
}

bool btGetUseHydroAero(btCable* obj)
{
	return obj->getUseHydroAero();
}

void btSetUseHydroAero(btCable* obj, bool active)
{
	obj->setUseHydroAero(active);
}

void* btGetCableNodesPos(btCable* obj)
{
	return obj->getCableNodesPos();
}

int btGetCableState(btCable* obj)
{
	return obj->getCableState();
}

int btGetCollisionMode(btCable* obj)
{
	return obj->getCollisionMode();
}

void btCable_appendNode(btSoftBody* obj, const btVector3* x, btScalar m)
{
	BTVECTOR3_IN(x);
	obj->appendNode(BTVECTOR3_USE(x), m);
}

void btCable_setCollisionParameters(btCable* obj, int substepDelaySolver, int substeDelayNarrow)
{
	obj->setCollisionParameters(substepDelaySolver, substeDelayNarrow);
}


float btCable_getCollisionMargin(btCable* obj) 
{
	return obj->getCollisionMargin();
}

void btCable_setCollisionMargin(btCable* obj, float collisionMargin) 
{
	obj->setCollisionMargin(collisionMargin);
}

void btCable_addSection(btCable* obj, btScalar rl, int start, int end, int nbNodes)
{
	return obj->addSection( rl,  start,  end,  nbNodes);
}

void btCable_setDefaultRestLength(btCable* obj, btScalar rl)
{
	obj->setDefaultRestLength(rl);
}

void btCable_setMinLength(btCable* obj, btScalar value)
{
	obj->setMinLength(value);
}

void  btCable_setWantedGrowSpeedAndDistance(btCable* obj, btScalar speed, btScalar distance)
{
	obj->setWantedGrowSpeedAndDistance(speed,distance);
}

int btCable_getGrowingState(btCable* obj) 
{
	return obj->getGrowingState();
}

void btCable_setLinearMass(btCable* obj, btScalar mass)
{
	obj->setLinearMass(mass);
}

void btCable_setCollisionStiffness(btCable* obj, btScalar stiffnessMin, btScalar stiffnessMax, btScalar distMin, btScalar distMax)
{
	obj->setCollisionStiffness(stiffnessMin, stiffnessMax, distMin, distMax);
}

void btCable_setCollisionResponseActive(btCable* obj, bool active)
{
	obj->setCollisionResponseActive(active);
}

void btCable_setCollisionMode(btCable* obj, int mode) 
{
	obj->setCollisionMode(mode);
}

void btCable_updateCurveResponse(btCable* obj, btScalar* dataX, btScalar* dataY, int size)
{
	obj->updateCurveResponse(dataX, dataY, size);
}

void btCable_setGravity(btCable* obj, const btVector3* gravity)
{
	BTVECTOR3_COPY(&obj->m_gravity, gravity);
}

void btCable_getGravity(btCable* obj, btVector3* gravity)
{
	BTVECTOR3_SET(gravity, obj->m_gravity);
}

void btCable_resetForceAndVelocity(btCable* obj)
{
	obj->ResetForceAndVelocity();
}

void btCable_resetNodePositions(btCable* obj, const int nodeIndex, const btVector3 position)
{
	obj->ResetNodePosition(nodeIndex,position);
}

void btCable_synchNodesInfos(btCable* obj)
{
	obj->synchNodesInfos();
}

void btCable_updateNodesMass(btCable* obj)
{
	obj->updateNodesMass();
}

void btCable_setMaxTension(btCable* obj, btScalar maxTension)
{
	obj->setMaxTension(maxTension);
}

void btCable_setDistanceMode(btCable* obj, int mode)
{
	obj->setDistanceMode(mode);
}

int btCable_getDistanceMode(btCable* obj)
{
	return obj->getDistanceMode();
}

void btCable_AnchorPlacement_SetActive(btCable* obj, bool active)
{
	obj->setUseAnchorConstraintPlacement(active);
}


//
// Mass Balance tweaked by cable stretch
// 

btScalar btCable_getStretchRatio(btCable* obj)
{
	return obj->getStretchRatio();
}

btScalar btCable_getStretchRatioDamped(btCable* obj)
{
	return obj->getStretchRatioDamped();
}

btScalar btCable_getMassBalanceRatio(btCable* obj)
{
	return obj->getMassBalanceRatio();
}

bool btCable_getIsMassBalanceEnabled(btCable* obj)
{
	return obj->getIsMassBalanceEnabled();
}

void btCable_setStretchRatioMode(btCable* obj, int value)
{
	obj->setStretchRatioMode(value);
}

int btCable_getStretchRatioMode(btCable* obj)
{
	return obj->getStretchRatioMode();
}

void btCable_setStretchRatioMinThreshold(btCable* obj, btScalar value)
{
	obj->setStretchRatioMinThreshold(value);
}

btScalar btCable_getStretchRatioMinThreshold(btCable* obj)
{
	return obj->getStretchRatioMinThreshold();
}


void btCable_setStretchRatioMaxThreshold(btCable* obj, btScalar value)
{
	obj->setStretchRatioMaxThreshold(value);
}

btScalar btCable_getStretchRatioMaxThreshold(btCable* obj)
{
	return obj->getStretchRatioMaxThreshold();
}


void btCable_setStretchRatioHysteresis(btCable* obj, btScalar value)
{
	obj->setStretchRatioHysteresis(value);
}

btScalar btCable_getStretchRatioHysteresis(btCable* obj)
{
	return obj->getStretchRatioHysteresis();
}


void btCable_setStretchRatioDamping(btCable* obj, btScalar value)
{
	obj->setStretchRatioDamping(value);
}

btScalar btCable_getStretchRatioDamping(btCable* obj)
{
	return obj->getStretchRatioDamping();
}

void btCable_setStretchRatioLowSpeedCurve(btCable* obj, int value)
{
	obj->setStretchRatioLowSpeedCurve(value);
}

int btCable_getStretchRatioLowSpeedCurve(btCable* obj)
{
	return obj->getStretchRatioLowSpeedCurve();
}

void btCable_setStretchRatioHighSpeedCurve(btCable* obj, int value)
{
	obj->setStretchRatioHighSpeedCurve(value);
}

int btCable_getStretchRatioHighSpeedCurve(btCable* obj)
{
	return obj->getStretchRatioHighSpeedCurve();
}

void btCable_setStretchRatioSpeedThreshold(btCable* obj, btScalar value)
{
	return obj->setStretchRatioSpeedThreshold(value);
}

btScalar btCable_getStretchRatioSpeedThreshold(btCable* obj)
{
	return obj->getStretchRatioSpeedThreshold();
}

void btCable_setStretchRatioHysteresisThreshold(btCable* obj, btScalar value)
{
	return obj->setStretchRatioHysteresisThreshold(value);
}

btScalar btCable_getStretchRatioHysteresisThreshold(btCable* obj)
{
	return obj->getStretchRatioHysteresisThreshold();
}


void btCable_setStretchRatioDampingThreshold(btCable* obj, btScalar value)
{
	obj->setStretchRatioDampingThreshold(value);
}

btScalar btCable_getStretchRatioDampingThreshold(btCable* obj)
{
	return obj->getStretchRatioDampingThreshold();
}

int btCable_getLastNodeData(btCable* obj, btVector3* position)
{
	int lastIndex = obj->m_nodes.size() - 1;
	BTVECTOR3_SET(position, obj->m_nodes[lastIndex].m_x);
	return lastIndex;
}

void btCable_setAnchorIndex(btCable *obj, int index)
{
	obj->setAnchorIndex(index);
}

int btCable_getAnchorIndex(btCable* obj)
{
	return obj->getAnchorIndex();
}