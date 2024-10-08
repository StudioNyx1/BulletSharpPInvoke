using BulletSharp.Math;
using static BulletSharp.UnsafeNativeMethods;

namespace BulletSharp
{
	public class ConvexShape : CollisionShape
	{
		protected internal ConvexShape()
		{
		}

		/*
		public void BatchedUnitVectorGetSupportingVertexWithoutMargin(Vector3 vectors,
			Vector3 supportVerticesOut, int numVectors)
		{
			btConvexShape_batchedUnitVectorGetSupportingVertexWithoutMargin(Native,
				vectors.Native, supportVerticesOut.Native, numVectors);
		}
		*/

		public void GetAabbNonVirtual(Matrix t, out Vector3 aabbMin, out Vector3 aabbMax)
		{
			btConvexShape_getAabbNonVirtual(Native, ref t, out aabbMin, out aabbMax);
		}

		public void GetAabbSlow(Matrix t, out Vector3 aabbMin, out Vector3 aabbMax)
		{
			btConvexShape_getAabbSlow(Native, ref t, out aabbMin, out aabbMax);
		}

		public void GetPreferredPenetrationDirection(int index, out Vector3 penetrationVector)
		{
			btConvexShape_getPreferredPenetrationDirection(Native, index, out penetrationVector);
		}

		public Vector3 LocalGetSupportingVertex(Vector3 vec)
		{
			Vector3 value;
			btConvexShape_localGetSupportingVertex(Native, ref vec, out value);
			return value;
		}

		public Vector3 LocalGetSupportingVertexWithoutMargin(Vector3 vec)
		{
			Vector3 value;
			btConvexShape_localGetSupportingVertexWithoutMargin(Native, ref vec,
				out value);
			return value;
		}

		public Vector3 LocalGetSupportVertexNonVirtual(Vector3 vec)
		{
			Vector3 value;
			btConvexShape_localGetSupportVertexNonVirtual(Native, ref vec, out value);
			return value;
		}

		public Vector3 LocalGetSupportVertexWithoutMarginNonVirtual(Vector3 vec)
		{
			Vector3 value;
			btConvexShape_localGetSupportVertexWithoutMarginNonVirtual(Native, ref vec,
				out value);
			return value;
		}

		public void ProjectRef(ref Matrix trans, ref Vector3 dir, out double minProj, out double maxProj,
			out Vector3 witnesPtMin, out Vector3 witnesPtMax)
		{
			btConvexShape_project(Native, ref trans, ref dir, out minProj, out maxProj,
				out witnesPtMin, out witnesPtMax);
		}

		public void Project(Matrix trans, Vector3 dir, out double minProj, out double maxProj,
			out Vector3 witnesPtMin, out Vector3 witnesPtMax)
		{
			btConvexShape_project(Native, ref trans, ref dir, out minProj, out maxProj,
				out witnesPtMin, out witnesPtMax);
		}

		public double MarginNonVirtual => btConvexShape_getMarginNonVirtual(Native);

		public int NumPreferredPenetrationDirections => btConvexShape_getNumPreferredPenetrationDirections(Native);
	}
}
