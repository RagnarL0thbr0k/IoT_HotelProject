using RJCP.IO.Ports;
using System;
using System.IO.Ports;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

using static System.Console;

namespace RS485Communication
{
    class Program
    {
        static async Task Main(string[] args)
        {
            WriteLine("RS485Master");
            WriteLine($"Opening on {args[0]} port");

            var port = new SerialPortStream(args[0], 9600, 8, Parity.None, StopBits.One);
            port.DataReceived += (s, e) => {
                /* var buffer = new byte[port.BytesToRead];
                 var read = port.Read(buffer, 0, buffer.Length);
                 var id = buffer[0];
                 var cmd = buffer[1];
                 var cmdlen = buffer[2];

                 WriteLine($"{read} bytes from {id}: cmd={cmd} len={cmdlen}");

                 switch (cmd)
                 {
                     case 0x80 + 0x02:
                         var readTemperatureValue = System.BitConverter.ToSingle(buffer, 3);
                         WriteLine($"READ TEMPERATURE={readTemperatureValue}");
                         break;
                 }*/
            };
            port.Open();

            var dato = new char[1];
            var send = new char[1];

             send[0] =  'a' ;


            try
            {
                while (true)
                {
                    await Task.Delay(1000);
                    WriteLine("RECEIVING T0");
                    port.Write(send, 0, 1);
                    while(dato[0] != 'o')
                    {
                        port.Read(dato, 0, 1);
                        WriteLine(dato);

                        WriteLine("HEY PIC");
                        send[0] = '0';
                    }



                }
            }
            catch (Exception ex)
            {
                throw ex;
            }
            finally
            {
                port.Close();
            }
        }
    }
}
