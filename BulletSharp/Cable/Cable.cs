using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Security;
using BulletSharp.Math;
using static BulletSharp.UnsafeNativeMethods;

namespace BulletSharp.SoftBody
{
    public class Cable : SoftBody
	{
		private CableState _cableState = CableState.Valid;

		public Cable(SoftBodyWorldInfo worldInfo, CollisionWorld world, int nodeCount,int sectionCount, Vector3[] positions, double[] masses) :
			 base(CreateCable(worldInfo, world, nodeCount, sectionCount, positions, masses))
		{
			WorldInfo = worldInfo;
		}

		private static IntPtr CreateCable(SoftBodyWorldInfo worldInfo, CollisionWorld world, int nodeCount, int sectionCount, Vector3[] positions, double[] masses)
		{
			return btCable_new(worldInfo.Native, world.Native, nodeCount,sectionCount, positions, masses);
		}

		public void RemoveLinkAt(int index)
        {
			btCable_removeLinkAt(Native, index);
        }

		public void RemoveNodeAt(int index)
		{
			btCable_removeNodeAt(Native, index);
		}

		public void RemoveAnchorAt(int index)
		{
			btCable_removeAnchorAt(Native, index);
		}

		public void GetTensionAt(int index, out Vector3 impulse)
        {
	        btCable_getTensionAt(Native, index, out impulse);
		}
        
	    public int GetNumberOfNode()
        {
			return btCable_getNumberOfNode(Native);
        }

		public int GetNumberOfAnchor()
        {
			return btCable_getNumberOfAnchor(Native);
		}

		public int GetNumberOfLink()
		{
			return btCable_getNumberOfLink(Native);
		}

        public Vector3[] GetAllNodePositions()
        {
            Vector3[] positions = new Vector3[btCable_getNumberOfNode(Native)];
            for (int i = 0; i < positions.Length; ++i)
            {
                btCable_Node_GetPosition(Native, i, out positions[i]);
            }
            return positions;
        }

		public double GetLength()
        {
			return btCable_getLength(Native);
		}

		public double GetRestLength()
		{
			return btCable_getRestLength(Native);
		}

		public Vector3 Node_GetPosition(int index)
        {
            Vector3 v;
            btCable_Node_GetPosition(Native, index, out v);
            return v;
        }
        
		public void Node_SetPosition(int index, Vector3 position)
        {
			btCable_Node_SetPosition(Native, index, position);
		}

        public Vector3 Node_GetVelocity(int index)
		{
            Vector3 v;
            btCable_Node_GetVelocity(Native, index, out v);
            return v;
		}
        
		public void Node_SetVelocity(int index, Vector3 velocity)
		{
			btCable_Node_SetVelocity(Native, index, velocity);
		}

        public Vector3 Node_GetForce(int index)
		{
            Vector3 v;
            btCable_Node_GetForce(Native, index, out v);
            return v;
        }
        
		public void Node_SetForce(int index, Vector3 force)
		{
			btCable_Node_SetForce(Native, index, force);
		}

        public double Node_GetInverseMass(int index)
        {
			return btCable_Node_GetInverseMass(Native, index);
		}

		public void Node_SetInverseMass(int index, double inverseMass)
        {
			btCable_Node_SetInverseMass(Native, index, inverseMass);
		}
		
		public double Node_GetArea(int index)
        {
			return btCable_Node_GetArea(Native, index);
		}

		public void Node_SetArea(int index, double area)
        {
			btCable_Node_SetArea(Native, index, area);
        }

		public int Node_GetIsAttached(int index)
        {
			return btCable_Node_GetIsAttached(Native, index);
		}

		public void Node_SetIsAttached(int index, int isAttached)
        {
			btCable_Node_SetIsAttached(Native, index, isAttached);
		}

		public int Node_GetIndex(int index)
        {
			return btCable_Node_GetIndex(Native, index);
		}

		public void Node_SetIndex(int index, int newIndex)
        {
			btCable_Node_SetIndex(Native, index, newIndex);
		}

		public bool Anchor_HasNode(int index)
		{
			return btCable_Anchor_HasNode(Native, index);
		}

		public int Anchor_GetIndexOfNode(int index)
        {
			return btCable_Anchor_GetIndexOfNode(Native, index);
		}

		public void Anchor_SetNode(int indexAnchor, int indexNode)
		{
			btCable_Anchor_SetNode(Native, indexAnchor, indexNode);
		}

		public int Link_GetNode0(int index)
        {
			return btCable_Link_GetNode0(Native, index);
        }

		public void Link_SetNode0(int indexLink, int indexNode)
		{
			btCable_Link_SetNode0(Native, indexLink, indexNode);
		}

		public int Link_GetNode1(int index)
		{
			return btCable_Link_GetNode1(Native, index);
		}

		public void Link_SetNode1(int indexLink, int indexNode)
		{
			btCable_Link_SetNode1(Native, indexLink, indexNode);
		}

		public double Link_GetRestLength(int index)
        {
			return btCable_Link_GetRestLength(Native, index);
        }

		public void Link_SetRestLength(int index, double rl)
        {
			btCable_Link_SetRestLength(Native, index, rl);
		}

		public bool LRA_GetActive()
        {
			return btCable_LRA_GetActive(Native);
		}

		public void LRA_SetActive(bool active)
		{
			btCable_LRA_SetActive(Native, active);
		}
        
		public bool Bending_GetActive()
        {
			return btCable_Bending_GetActive(Native);
        }

		public void Bending_SetActive(bool active)
        {
			btCable_Bending_SetActive(Native, active);
        }

		public double Bending_GetBendingMaxAngle()
        {
			return btCable_Bending_GetBendingMaxAngle(Native);
		}

		public void Bending_SetBendingMaxAngle(double angle)
        {
			btCable_Bending_SetBendingMaxAngle(Native, angle);
		}

		public double Bending_GetBendingStiffness()
        {
			return btCable_Bending_GetBendingStiffness(Native);
		}

		public void Bending_SetBendingStiffness(double stiffness)
		{
			btCable_Bending_SetBendingStiffness(Native, stiffness);
		}

		public bool Gravity_GetActive()
		{
			return btCable_Gravity_GetActive(Native);
		}

		public void Gravity_SetActive(bool active)
		{
			btCable_Gravity_SetActive(Native, active);
		}

		public bool Collision_GetActive()
		{
			return btCable_Collision_GetActive(Native);
		}

		public void Collision_SetActive(bool active)
		{
			btCable_Collision_SetActive(Native, active);
		}

		public bool UpdateCableData(ref CableData cableData)
        {
			return btUpdateCableData(Native, ref cableData);
		}

		public bool GetUseHydroAeroForces()
        {
			return btGetUseHydroAero(Native);
        }

		public void SetUseHydroAeroForces(bool value)
		{
			btSetUseHydroAero(Native, value);
		}

		public IntPtr GetCableNodesPos()
        {
			return btGetCableNodesPos(Native);
        }

		public CableState GetCableState()
		{
			_cableState = (CableState)btGetCableState(Native);
			return _cableState;
		}

		[StructLayout(LayoutKind.Sequential)]
		public struct CableData
		{
			public float radius;
			public float tangentDragCoefficient;
			public float normalDragCoefficient;
			public int startIndex;
			public int endIndex;
		};

		public enum CableState
		{
			Valid = 0,
			InternalForcesError = 1,
			ExternalForcesError = 2
		};
		public new void AppendNode(Vector3 x, double m)
		{
			btCable_appendNode(Native, ref x, m);
		}

        /// <summary>
        /// 
        /// </summary>
        /// <param name="substepDelayCollision"> Number of step before each iteration of the collision solver </param>
        /// <param name="subIterationCollision"> Number of iteration of each multicontact node in the collision solver</param>
        /// <param name="correctionNormal"> Additional distance add on the normal on node colllision resolution </param>
        /// <param name="safeDirectionThreshold"> Safe distance add to dectect collision</param>
        /// <param name="sleepingThreshold"> Sleeping threshold </param>
		public void SetCollisionParameters(int substepDelayCollision = 3, int subIterationCollision= 3, double sleepingThreshold=0.0001)
        {
			btCable_setCollisionParameters(Native, substepDelayCollision, subIterationCollision, sleepingThreshold);
		}


		public void SetCollisionMargin(float collisionMargin)
		{
			btCable_setCollisionMargin(Native, collisionMargin);
		}
		public float GetCollisionMargin()
		{
			return btCable_getCollisionMargin(Native);
		}

		public void addSection(double restLenght,int startIndex, int endIndex,int nbNodes)
        {
			btCable_addSection(Native, restLenght, startIndex, endIndex, nbNodes);
        }

        public void SetDefaultRestLength(double restLenght)
        {
            btCable_setDefaultRestLength(Native, restLenght);
        }

		public void SetMinLength(double length)
		{
			btCable_setMinLength(Native, length);
		}

		public void SetWantedGrowSpeedAndDistance(double speed, double distance)
        {
			btCable_setWantedGrowSpeedAndDistance(Native, speed, distance);
		}

		public int GetGrowingState()
        {
			return btCable_getGrowingState(Native);
		}

		public void SetLinearMass(double mass)
        {
			btCable_setLinearMass(Native, mass);
		}

		public void SetCollisionViscosity(double coef)
		{
			btCable_setCollisionViscosity(Native, coef);
		}

		public void SetCollisionStiffness(double stiffnessMin, double stiffnessMax, double distMin, double distMax)
		{
			btCable_setCollisionStiffness(Native, stiffnessMin, stiffnessMax, distMin, distMax);
		}

		public void SetCollisionResponseActive(bool active)
        {
			btCable_setCollisionResponseActive(Native, active);
		}

        public void SetCollisionMode(int mode)
        {
            btCable_setCollisionMode(Native, mode);
        }

        public void UpdateCurveResponse(double[] dataX, double[] dataY)
        {
            btCable_updateCurveResponse(Native, dataX, dataY, dataX.Length);
        }
	}
}
