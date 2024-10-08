using BulletSharp.Math;

namespace BulletSharp
{
    public class VehicleRaycasterResult
    {
        public double DistFraction { get; set; }
        public Vector3 HitNormalInWorld { get; set; }
        public Vector3 HitPointInWorld { get; set; }
    }
    
    public interface IVehicleRaycaster
	{
        object CastRay(ref Vector3 from, ref Vector3 to, VehicleRaycasterResult result);
	}
}
