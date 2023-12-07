using System;

namespace Aircompany.Planes
{
    public class PassengerPlane : Plane
    {
        public int passengersCapacity;

        public PassengerPlane(string model, int maxSpeed, int maxFlightDistance, int maxLoadCapacity, int currentPassengersCapacity)
            :base(model, maxSpeed, maxFlightDistance, maxLoadCapacity)
        {
            passengersCapacity = currentPassengersCapacity;
        }

        public override bool Equals(object obj)
        {
            var plane = obj as PassengerPlane;
            return plane != null &&
                   base.Equals(obj) &&
                   passengersCapacity == plane.passengersCapacity;
        }

        public override int GetHashCode()
        {
            var hashCode = 751774561;
            hashCode = hashCode * -1521134295 + base.GetHashCode();
            hashCode = hashCode * -1521134295 + passengersCapacity.GetHashCode();
            return hashCode;
        }

        public int PassengersCapacityIs()
        {
            return passengersCapacity;
        }

       
        public override string ToString()
        {
            return base.ToString().Replace("}",
                    ", passengersCapacity=" + passengersCapacity +
                    '}');
        }       
        
    }
}
