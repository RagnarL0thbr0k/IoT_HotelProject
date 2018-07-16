using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace APIazure.Models
{
    public class tblRoomValue
    {
        public string Devname { get; set; }
        public int Room_temp { get; set; }
        public int Status_door { get; set; }
        public DateTime Timestamp { get; set; }
    }
}
