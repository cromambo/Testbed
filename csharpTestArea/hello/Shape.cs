using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace hello
{
    public abstract class Shape
    {
        private string myId;

        public string Id
        {
            get { return myId; }
            set { myId = value; }
        }

        public Shape(string s)
        {
            Id = s;
        }

        public abstract double Area
        {
            get;
        }

        public override string ToString()
        {
            return "test";
        }
    }
}
