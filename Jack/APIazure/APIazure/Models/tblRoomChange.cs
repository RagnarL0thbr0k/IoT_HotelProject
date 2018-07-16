using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace APIazure.Models
{
    public class tblRoomChange
    {
        public string Devname { get; set; }
        public int Set_room_temp { get; set; }
        public DateTime Timestamp { get; set; }
        public string User { get; set; }
        public char Flag { get; set; }
    }
}
