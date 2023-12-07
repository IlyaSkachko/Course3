using Aircompany.Models;
using Aircompany.Planes;
using System;
using System.Collections.Generic;
using System.Linq;

namespace Aircompany
{
    public class Airport
    {
        public List<Plane> planes;

        public Airport(IEnumerable<Plane> planes)
        {
            this.planes = planes.ToList();
        }

        public List<PassengerPlane> GetPassengersPlanes()
        {
            List<PassengerPlane> passengerPlanes = new List<PassengerPlane>();

            for (int i=0; i < planes.Count; i++)
            {
                if (planes[i].GetType() == typeof(PassengerPlane))
                {
                    passengerPlanes.Add((PassengerPlane)planes[i]);
                }
            }
            return passengerPlanes;
        }

        public List<MilitaryPlane> GetMilitaryPlanes()
        {
            List<MilitaryPlane> militaryPlanes = new List<MilitaryPlane>();

            for (int i = 0; i < planes.Count; i++)
            {
                if (planes[i].GetType() == typeof(MilitaryPlane))
                {
                    militaryPlanes.Add((MilitaryPlane)planes[i]);
                }
            }
            return militaryPlanes;
        }

        public PassengerPlane GetPassPlaneWithMaxPassCapacity()
        {
            List<PassengerPlane> passengerPlanes = GetPassengersPlanes();

            return passengerPlanes.Aggregate((w, x) => w.PassengersCapacityIs() > x.PassengersCapacityIs() ? w : x);             
        }

        public List<MilitaryPlane> GetTransportMilitaryPlanes()
        {
            List<MilitaryPlane> transportMilitaryPlanes = new List<MilitaryPlane>();
            List<MilitaryPlane> militaryPlanes = GetMilitaryPlanes();

            for (int i = 0; i < militaryPlanes.Count; i++)
            {
                MilitaryPlane plane = militaryPlanes[i];
                if (plane.PlaneTypeIs() == MilitaryType.TRANSPORT)
                {
                    transportMilitaryPlanes.Add(plane);
                }
            }

            return transportMilitaryPlanes;
        }

        public Airport SortByMaxDistance()
        {
            return new Airport(planes.OrderBy(w => w.getMaxFlightDistance()));
        }

        public Airport SortByMaxSpeed()
        {
            return new Airport(planes.OrderBy(w => w.getMaxSpeed()));
        }

        public Airport SortByMaxLoadCapacity()
        {
            return new Airport(planes.OrderBy(w => w.getMaxLoadCapacity()));
        }


        public IEnumerable<Plane> GetPlanes()
        {
            return planes;
        }

        public override string ToString()
        {
            return "Airport{" +
                    "planes=" + string.Join(", ", planes.Select(x => x.getModel())) +
                    '}';
        }
    }
}
