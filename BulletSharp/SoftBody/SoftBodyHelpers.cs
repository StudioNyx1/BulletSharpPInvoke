using BulletSharp.Math;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using static BulletSharp.UnsafeNativeMethods;

namespace BulletSharp.SoftBody
{
	public enum DrawFlags
	{
		None = 0x00,
		Nodes = 0x01,
		Links = 0x02,
		Faces = 0x04,
		Tetras = 0x08,
		Normals = 0x10,
		Contacts = 0x20,
		Anchors = 0x40,
		Notes = 0x80,
		Clusters = 0x100,
		NodeTree = 0x200,
		FaceTree = 0x400,
		ClusterTree = 0x800,
		Joints = 0x1000,
		Std = Links | Faces | Tetras | Anchors | Notes | Joints,
		StdTetra = Std - Faces - Tetras
	}

	public sealed class SoftBodyHelpers
	{
		private SoftBodyHelpers()
		{
		}

		public static double CalculateUV(int resx, int resy, int ix, int iy, int id)
		{
			switch (id)
			{
				case 0:
					return 1.0f / (resx - 1) * ix;
				case 1:
					return 1.0f / (resy - 1) * (resy - 1 - iy);
				case 2:
					return 1.0f / (resy - 1) * (resy - 1 - iy - 1);
				case 3:
					return 1.0f / (resx - 1) * (ix + 1);
				default:
					return 0;
			}
		}

		public static SoftBody CreateEllipsoid(SoftBodyWorldInfo worldInfo, Vector3 center, Vector3 radius, int res)
		{
			int numVertices = res + 3;
			Vector3[] vtx = new Vector3[numVertices];
			for (int i = 0; i < numVertices; i++)
			{
				double p = 0.5f, t = 0;
				for (int j = i; j > 0; j >>= 1)
				{
					if ((j & 1) != 0)
						t += p;
					p *= 0.5f;
				}
				double w = 2 * t - 1;
				double a = ((1 + 2 * i) * (double)System.Math.PI) / numVertices;
				double s = (double)System.Math.Sqrt(1 - w * w);
				vtx[i] = new Vector3(s * (double)System.Math.Cos(a), s * (double)System.Math.Sin(a), w) * radius + center;
			}
			return CreateFromConvexHull(worldInfo, vtx);
		}

		public static SoftBody CreateFromConvexHull(SoftBodyWorldInfo worldInfo,
			Vector3[] vertices, int nVertices, bool randomizeConstraints = true)
		{
			var body = new SoftBody(btSoftBodyHelpers_CreateFromConvexHull(
				worldInfo.Native, vertices, nVertices, randomizeConstraints))
			{
				WorldInfo = worldInfo
			};
			return body;
		}

		public static SoftBody CreateFromConvexHull(SoftBodyWorldInfo worldInfo,
			Vector3[] vertices, bool randomizeConstraints = true)
		{
			var body = new SoftBody(btSoftBodyHelpers_CreateFromConvexHull(
				worldInfo.Native, vertices, vertices.Length, randomizeConstraints))
			{
				WorldInfo = worldInfo
			};
			return body;
		}

		public static SoftBody CreateFromTetGenData(SoftBodyWorldInfo worldInfo,
			string ele, string face, string node, bool faceLinks, bool tetraLinks, bool facesFromTetras)
		{
			CultureInfo culture = CultureInfo.InvariantCulture;
			char[] separator = new[] { ' ' };
			Vector3[] pos;

			using (var nodeReader = new StringReader(node))
			{
				string[] nodeHeader = nodeReader.ReadLine().Split(separator, StringSplitOptions.RemoveEmptyEntries);
				int numNodes = int.Parse(nodeHeader[0]);
				//int numDims = int.Parse(nodeHeader[1]);
				//int numAttrs = int.Parse(nodeHeader[2]);
				//bool hasBounds = !nodeHeader[3].Equals("0");

				pos = new Vector3[numNodes];
				for (int n = 0; n < numNodes; n++)
				{
					string[] nodeLine = nodeReader.ReadLine().Split(separator, StringSplitOptions.RemoveEmptyEntries);
					pos[int.Parse(nodeLine[0])] = new Vector3(
						double.Parse(nodeLine[1], culture),
						double.Parse(nodeLine[2], culture),
						double.Parse(nodeLine[3], culture));
				}
			}
			var psb = new SoftBody(worldInfo, pos.Length, pos, null);
			/*
			if (!string.IsNullOrEmpty(face))
			{
				throw new NotImplementedException();
			}
			*/
			if (!string.IsNullOrEmpty(ele))
			{
				using (var eleReader = new StringReader(ele))
				{
					string[] eleHeader = eleReader.ReadLine().Split(separator, StringSplitOptions.RemoveEmptyEntries);
					int numTetras = int.Parse(eleHeader[0]);
					//int numCorners = int.Parse(eleHeader[1]);
					//int numAttrs = int.Parse(eleHeader[2]);

					for (int n = 0; n < numTetras; n++)
					{
						string[] eleLine = eleReader.ReadLine().Split(separator, StringSplitOptions.RemoveEmptyEntries);
						//int index = int.Parse(eleLine[0], culture);
						int ni0 = int.Parse(eleLine[1], culture);
						int ni1 = int.Parse(eleLine[2], culture);
						int ni2 = int.Parse(eleLine[3], culture);
						int ni3 = int.Parse(eleLine[4], culture);
						psb.AppendTetra(ni0, ni1, ni2, ni3);
						if (tetraLinks)
						{
							psb.AppendLink(ni0, ni1, null, true);
							psb.AppendLink(ni1, ni2, null, true);
							psb.AppendLink(ni2, ni0, null, true);
							psb.AppendLink(ni0, ni3, null, true);
							psb.AppendLink(ni1, ni3, null, true);
							psb.AppendLink(ni2, ni3, null, true);
						}
					}
				}
			}

			//Console.WriteLine("Nodes: {0}", psb.Nodes.Count);
			//Console.WriteLine("Links: {0}", psb.Links.Count);
			//Console.WriteLine("Faces: {0}", psb.Faces.Count);
			//Console.WriteLine("Tetras: {0}", psb.Tetras.Count);

			return psb;
		}

		public static SoftBody CreateFromTetGenFile(SoftBodyWorldInfo worldInfo, string elementFilename, string faceFilename, string nodeFilename, bool faceLinks, bool tetraLinks, bool facesFromTetras)
		{
			string ele = (elementFilename != null) ? File.ReadAllText(elementFilename) : null;
			string face = (faceFilename != null) ? File.ReadAllText(faceFilename) : null;

			return CreateFromTetGenData(worldInfo, ele, face, File.ReadAllText(nodeFilename), faceLinks, tetraLinks, facesFromTetras);
		}

		public static SoftBody CreateFromTriMesh(SoftBodyWorldInfo worldInfo, double[] vertices,
			int[] triangles, bool randomizeConstraints = true)
		{
			int numVertices = vertices.Length / 3;
			Vector3[] vtx = new Vector3[numVertices];
			for (int i = 0, j = 0; j < numVertices; j++, i += 3)
			{
				vtx[j] = new Vector3(vertices[i], vertices[i + 1], vertices[i + 2]);
			}
			return CreateFromTriMesh(worldInfo, vtx, triangles, randomizeConstraints);
		}

		public static SoftBody CreateFromTriMesh(SoftBodyWorldInfo worldInfo, Vector3[] vertices,
			int[] triangles, bool randomizeConstraints = true)
		{
			int numTriangleIndices = triangles.Length;
			int numTriangles = numTriangleIndices / 3;

			int maxIndex = 0; // triangles.Max() + 1;
			for (int i = 0; i < numTriangleIndices; i++)
			{
				if (triangles[i] > maxIndex)
				{
					maxIndex = triangles[i];
				}
			}
			maxIndex++;

			var psb = new SoftBody(worldInfo, maxIndex, vertices, null);

			BitArray chks = new BitArray(maxIndex * maxIndex);
			for (int i = 0; i < numTriangleIndices; i += 3)
			{
				int[] idx = new int[] { triangles[i], triangles[i + 1], triangles[i + 2] };
				for (int j = 2, k = 0; k < 3; j = k++)
				{
					int chkIndex = maxIndex * idx[k] + idx[j];
					if (!chks[chkIndex])
					{
						chks[chkIndex] = true;
						chks[maxIndex * idx[j] + idx[k]] = true;
						psb.AppendLink(idx[j], idx[k]);
					}
				}
				psb.AppendFace(idx[0], idx[1], idx[2]);
			}

			if (randomizeConstraints)
			{
				psb.RandomizeConstraints();
			}
			return psb;
		}

		public static SoftBody CreateFromVtkFile(SoftBodyWorldInfo worldInfo, string fileName)
		{
			List<Vector3> points = new List<Vector3>(0);
			List<int[]> cells = new List<int[]>(0);

			using (var reader = new StreamReader(fileName))
			{
				bool readingPoints = false;
				bool readingCells = false;
				string line;
				while ((line = reader.ReadLine()) != null)
				{
					if (line.Length == 0) continue;

					string[] lineParts = line.Split(' ');
					if (lineParts[0] == "POINTS")
					{
						readingPoints = true;
						readingCells = false;
						points.Capacity = int.Parse(lineParts[1]);
					}
					else if (lineParts[0] == "CELLS")
					{
						readingPoints = false;
						readingCells = true;
						cells.Capacity = int.Parse(lineParts[1]);
					}
					else if (lineParts[0] == "CELL_TYPES")
					{
						readingPoints = false;
						readingCells = false;
					}
					else if (readingPoints)
					{
						Vector3 point = new Vector3(
							(float)ParseDouble(lineParts[0]),
							(float)ParseDouble(lineParts[1]),
							(float)ParseDouble(lineParts[2]));
						points.Add(point);
					}
					else if (readingCells)
					{
						int numPoints = int.Parse(lineParts[0]);
						int[] cell = new int[numPoints];
						for (int i = 0; i < numPoints; i++)
						{
							cell[i] = int.Parse(lineParts[i + 1]);
						}
						cells.Add(cell);
					}
				}
			}
			SoftBody body = new SoftBody(worldInfo, points.Count, points.ToArray(), null);

			foreach (int[] cell in cells)
			{
				body.AppendTetra(cell[0], cell[1], cell[2], cell[3]);
				body.AppendLink(cell[0], cell[1], null, true);
				body.AppendLink(cell[1], cell[2], null, true);
				body.AppendLink(cell[2], cell[0], null, true);
				body.AppendLink(cell[0], cell[3], null, true);
				body.AppendLink(cell[1], cell[3], null, true);
				body.AppendLink(cell[2], cell[3], null, true);
			}

			GenerateBoundaryFaces(body);
			body.InitializeDmInverse();
			body.TetraScratches.Resize(body.Tetras.Count);
			body.TetraScratchesTn.Resize(body.Tetras.Count);
			//Console.WriteLine($"Nodes:  {body.Nodes.Count}");
			//Console.WriteLine($"Links:  {body.Links.Count}");
			//Console.WriteLine($"Faces:  {body.Faces.Count}");
			//Console.WriteLine($"Tetras: {body.Tetras.Count}");

			return body;

		}

		private static double ParseDouble(string value)
		{
			return double.Parse(value, CultureInfo.InvariantCulture);
		}

		private static void GenerateBoundaryFaces(SoftBody body)
		{
			int counter = 0;
			foreach (Node node in body.Nodes)
			{
				node.Index = counter++;
			}

			List<int[]> indices = new List<int[]>(body.Tetras.Count);
			foreach (Tetra tetra in body.Tetras)
			{
				NodePtrArray nodes = tetra.Nodes;
				int[] index = new int[] {
					nodes[0].Index,
					nodes[1].Index,
					nodes[2].Index,
					nodes[3].Index
				};
				indices.Add(index);
			}

			var faceMap = new List<KeyValuePair<int[], int[]>>();
			foreach (int[] tetraIndices in indices)
			{
				for (int i = 0; i < 4;  i++)
				{
					int[] face;
					switch (i)
					{
						case 0:
							face = new int[] { tetraIndices[1], tetraIndices[0], tetraIndices[2] };
							break;
						case 1:
							face = new int[] { tetraIndices[3], tetraIndices[0], tetraIndices[1] };
							break;
						case 2:
							face = new int[] { tetraIndices[3], tetraIndices[1], tetraIndices[2] };
							break;
						default:
							face = new int[] { tetraIndices[2], tetraIndices[0], tetraIndices[3] };
							break;
					}

					List<int> faceSorted = new List<int>(face);
					faceSorted.Sort();

					bool removed = false;
					for (int j = 0; j < faceMap.Count; j++)
					{
						KeyValuePair<int[], int[]> f = faceMap[j];
						int[] faceInMap = f.Key;
						if (faceInMap[0] == faceSorted[0] && faceInMap[1] == faceSorted[1] && faceInMap[2] == faceSorted[2])
						{
							faceMap.RemoveAt(j);
							j--;
							removed = true;
							break;
						}
					}
					if (!removed)
					{
						faceMap.Add(new KeyValuePair<int[], int[]>(faceSorted.ToArray(), face));
					}
				}
			}

			foreach (var faceInMap in faceMap)
			{
				int[] face = faceInMap.Value;
				body.AppendFace(face[0], face[1], face[2]);
			}
		}

		public static SoftBody CreatePatch(SoftBodyWorldInfo worldInfo, Vector3 corner00,
			Vector3 corner10, Vector3 corner01, Vector3 corner11, int resolutionX, int resolutionY,
			int fixedCorners, bool generateDiagonals)
		{
			// Create nodes
			if ((resolutionX < 2) || (resolutionY < 2))
				return null;

			int rx = resolutionX;
			int ry = resolutionY;
			int total = rx * ry;
			var positions = new Vector3[total];
			var masses = new double[total];

			for (int y = 0; y < ry; y++)
			{
				double ty = y / (double)(ry - 1);
				Vector3 py0, py1;
				Vector3.Lerp(ref corner00, ref corner01, ty, out py0);
				Vector3.Lerp(ref corner10, ref corner11, ty, out py1);
				for (int ix = 0; ix < rx; ix++)
				{
					double tx = ix / (double)(rx - 1);
					int index = rx * y + ix;
					Vector3.Lerp(ref py0, ref py1, tx, out positions[index]);
					masses[index] = 1;
				}
			}

			var body = new SoftBody(worldInfo, total, positions, masses);

			if ((fixedCorners & 1) != 0)
				body.SetMass(0, 0);
			if ((fixedCorners & 2) != 0)
				body.SetMass(rx - 1, 0);
			if ((fixedCorners & 4) != 0)
				body.SetMass(rx * (ry - 1), 0);
			if ((fixedCorners & 8) != 0)
				body.SetMass(rx * (ry - 1) + rx - 1, 0);

			// Create links and faces
			for (int y = 0; y < ry; ++y)
			{
				for (int x = 0; x < rx; ++x)
				{
					int ixy = rx * y + x;
					int ix1y = ixy + 1;
					int ixy1 = rx * (y + 1) + x;

					bool mdx = (x + 1) < rx;
					bool mdy = (y + 1) < ry;
					if (mdx)
						body.AppendLink(ixy, ix1y);
					if (mdy)
						body.AppendLink(ixy, ixy1);
					if (mdx && mdy)
					{
						int ix1y1 = ixy1 + 1;
						if (((x + y) & 1) != 0)
						{
							body.AppendFace(ixy, ix1y, ix1y1);
							body.AppendFace(ixy, ix1y1, ixy1);
							if (generateDiagonals)
							{
								body.AppendLink(ixy, ix1y1);
							}
						}
						else
						{
							body.AppendFace(ixy1, ixy, ix1y);
							body.AppendFace(ixy1, ix1y, ix1y1);
							if (generateDiagonals)
							{
								body.AppendLink(ix1y, ixy1);
							}
						}
					}
				}
			}

			return body;
		}

		public static SoftBody CreatePatchUV(SoftBodyWorldInfo worldInfo, Vector3 corner00,
			Vector3 corner10, Vector3 corner01, Vector3 corner11, int resolutionX, int resolutionY,
			int fixedCorners, bool generateDiagonals, double[] texCoords = null)
		{
			var body = new SoftBody(btSoftBodyHelpers_CreatePatchUV(worldInfo.Native,
				ref corner00, ref corner10, ref corner01, ref corner11, resolutionX, resolutionY,
				fixedCorners, generateDiagonals, texCoords))
			{
				WorldInfo = worldInfo
			};
			return body;
		}

		public static SoftBody CreateRope(SoftBodyWorldInfo worldInfo, Vector3 from,
			Vector3 to, int resolution, int fixedTips)
		{
			// Create nodes
			int numLinks = resolution + 2;
			var positions = new Vector3[numLinks];
			var masses = new double[numLinks];

			for (int i = 0; i < numLinks; i++)
			{
				Vector3.Lerp(ref from, ref to, i / (double)(numLinks - 1), out positions[i]);
				masses[i] = 1;
			}

			var body = new SoftBody(worldInfo, numLinks, positions, masses);
			if ((fixedTips & 1) != 0)
				body.SetMass(0, 0);
			if ((fixedTips & 2) != 0)
				body.SetMass(numLinks - 1, 0);

			// Create links
			for (int i = 1; i < numLinks; i++)
			{
				body.AppendLink(i - 1, i);
			}

			return body;
		}

		public static void Draw(SoftBody psb, DebugDraw iDraw, DrawFlags drawFlags = DrawFlags.Std)
		{
			btSoftBodyHelpers_Draw(psb.Native, iDraw.Native, drawFlags);
		}

		public static void DrawClusterTree(SoftBody psb, DebugDraw iDraw, int minDepth = 0,
			int maxDepth = -1)
		{
			btSoftBodyHelpers_DrawClusterTree(psb.Native, iDraw.Native,
				minDepth, maxDepth);
		}

		public static void DrawFaceTree(SoftBody psb, DebugDraw iDraw, int minDepth = 0,
			int maxDepth = -1)
		{
			btSoftBodyHelpers_DrawFaceTree(psb.Native, iDraw.Native,
				minDepth, maxDepth);
		}

		public static void DrawFrame(SoftBody psb, DebugDraw iDraw)
		{
			btSoftBodyHelpers_DrawFrame(psb.Native, iDraw.Native);
		}

		public static void DrawInfos(SoftBody psb, DebugDraw iDraw, bool masses,
			bool areas, bool stress)
		{
			if (masses || areas)
			{
				foreach (Node node in psb.Nodes)
				{
					string text = string.Empty;
					if (masses)
					{
						text = $" M({node.InverseMass:F2})";
					}
					if (areas)
					{
						text += $" A({node.Area:F2})";
					}
					Vector3 location = node.Position;
					iDraw.Draw3DText(ref location, text);
				}
			}
		}

		public static void DrawNodeTree(SoftBody psb, DebugDraw iDraw, int minDepth = 0,
			int maxDepth = -1)
		{
			btSoftBodyHelpers_DrawNodeTree(psb.Native, iDraw.Native,
				minDepth, maxDepth);
		}

		private class LinkDep
		{
			public bool LinkB { get; set; }
			public LinkDep Next { get; set; }
			public Link Value { get; set; }
		}

		// ReoptimizeLinkOrder minimizes the cases where links L and L+1 share a common node.
		public static void ReoptimizeLinkOrder(SoftBody psb)
		{
			AlignedLinkArray links = psb.Links;
			AlignedNodeArray nodes = psb.Nodes;
			int nLinks = links.Count;
			int nNodes = nodes.Count;

			List<Link> readyList = new List<Link>();
			Dictionary<Link, Link> linkBuffer = new Dictionary<Link, Link>();
			Dictionary<Link, LinkDep> linkDeps = new Dictionary<Link, LinkDep>();
			Dictionary<Node, Link> nodeWrittenAt = new Dictionary<Node, Link>();

			Dictionary<Link, Link> linkDepA = new Dictionary<Link, Link>(); // Link calculation input is dependent upon prior calculation #N
			Dictionary<Link, Link> linkDepB = new Dictionary<Link, Link>();

			foreach (Link link in links)
			{
				Node ar = link.Nodes[0];
				Node br = link.Nodes[1];
				linkBuffer.Add(link, new Link(btSoftBody_Link_new2(link.Native)));

				LinkDep linkDep;
				if (nodeWrittenAt.ContainsKey(ar))
				{
					linkDepA[link] = nodeWrittenAt[ar];
					linkDeps.TryGetValue(nodeWrittenAt[ar], out linkDep);
					linkDeps[nodeWrittenAt[ar]] = new LinkDep() { Next = linkDep, Value = link};
				}

				if (nodeWrittenAt.ContainsKey(br))
				{
					linkDepB[link] = nodeWrittenAt[br];
					linkDeps.TryGetValue(nodeWrittenAt[br], out linkDep);
					linkDeps[nodeWrittenAt[br]] = new LinkDep() { Next = linkDep, Value = link, LinkB = true };
				}

				if (!linkDepA.ContainsKey(link) && !linkDepB.ContainsKey(link))
				{
					readyList.Add(link);
				}

				// Update the nodes to mark which ones are calculated by this link
				nodeWrittenAt[ar] = link;
				nodeWrittenAt[br] = link;
			}

			int i = 0;
			while (readyList.Count != 0)
			{
				Link link = readyList[0];
				links[i++] = linkBuffer[link];
				readyList.RemoveAt(0);

				LinkDep linkDep;
				linkDeps.TryGetValue(link, out linkDep);
				while (linkDep != null)
				{
					link = linkDep.Value;

					if (linkDep.LinkB)
					{
						linkDepB.Remove(link);
					}
					else
					{
						linkDepA.Remove(link);
					}

					// Add this dependent link calculation to the ready list if *both* inputs are clear
					if (!linkDepA.ContainsKey(link) && !linkDepB.ContainsKey(link))
					{
						readyList.Add(link);
					}
					linkDep = linkDep.Next;
				}
			}

			foreach (Link link in linkBuffer.Values)
			{
				btSoftBody_Link_delete(link.Native);
			}
		}
	}
}
