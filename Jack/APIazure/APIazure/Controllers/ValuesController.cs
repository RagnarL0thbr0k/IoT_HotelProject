using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Configuration;
using APIazure.Models;

namespace APIazure.Controllers
{
    public class ValuesController : Controller
    {
        // GET api/values       ricevo valore specifico per la stanza in questione
        [HttpGet]
        [Route("api/getTemp/{t}")]
        public JsonResult Get(string t)
        {
            List<tblRoomValue> lista = new List<tblRoomValue>();

            var builder = new ConfigurationBuilder()
                .SetBasePath(Directory.GetCurrentDirectory())
                .AddJsonFile("appsettings.json", optional: true, reloadOnChange: true);

            var configuration = builder.Build();
            using (var conn = new SqlConnection(configuration["SqlConnectionString"]))
            {
                try
                {
                    conn.Open();
                    var cmd = conn.CreateCommand();

                    cmd.CommandText = "SELECT TOP 1 * FROM RoomValue WHERE Dev_name = '" + t + "' ORDER BY (Timestamp) ";
                    SqlDataReader dataReader = cmd.ExecuteReader();


                    while (dataReader.Read())
                    {
                        var tblTmp = new tblRoomValue();

                        tblTmp.Devname = dataReader["Dev_name"].ToString();
                        tblTmp.Room_temp = Convert.ToInt32(dataReader["Room_temp"]);
                        tblTmp.Status_door = Convert.ToInt32(dataReader["Status_door"]);
                        tblTmp.Timestamp = Convert.ToDateTime(dataReader["Timestamp"]);

                        lista.Add(tblTmp);
                    }
                    conn.Close();
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Errore ReciveData: " + ex);
                }
            }
            return new JsonResult(lista);
        }
        
        // POST api/values
        [HttpPost]
        [Route("api/setTemp/{id}/{temp}/{us3r}")]
        public void Post(string id, int temp, string us3r)
        {
            var tblTmp = new tblRoomChange();
            tblTmp.Devname = id;
            tblTmp.Set_room_temp = temp;
            tblTmp.Timestamp = Convert.ToDateTime("1998-01-02T00:00:00");
            tblTmp.User = us3r;
            tblTmp.Flag = '1';
            
            List<tblRoomChange> lista = new List<tblRoomChange>();

            var builder = new ConfigurationBuilder()
                .SetBasePath(Directory.GetCurrentDirectory())
                .AddJsonFile("appsettings.json", optional: true, reloadOnChange: true);

            var configuration = builder.Build();
            using (var conn = new SqlConnection(configuration["SqlConnectionString"]))
            {
                try
                {
                    conn.Open();
                    var cmd = conn.CreateCommand();

                    cmd.CommandText = "INSERT INTO RoomChange (Dev_name, Set_room_temp, [Timestamp], [User], Flag) VALUES ('"+tblTmp.Devname+"', '"+tblTmp.Set_room_temp+"', '"+tblTmp.Timestamp+"', '"+tblTmp.User+"', '"+tblTmp.Flag+"')";
                    
                    //cmd.Parameters.Add
                    cmd.ExecuteNonQuery();
                    conn.Close();
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Errore ReciveData: " + ex);
                }
            }
            //return new JsonResult(lista);
        }

        // PUT api/values/5
        [HttpPut("{id}")]
        public void Put(int id, [FromBody]string value)
        {
        }

        // DELETE api/values/5
        [HttpDelete("{id}")]
        public void Delete(int id)
        {
        }

        // GET api/values/5
        [HttpGet("{id}")]
        public void Get(int id)
        {

        }
    }
}
