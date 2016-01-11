using System;
using System.Management;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace CheckGateway
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Start Gateway Check....");

            int available_dev = 0;
            List<string> gateway_list = new List<string>();
            ManagementObjectSearcher mos = new ManagementObjectSearcher("select * from Win32_NetworkAdapterConfiguration");
            foreach (ManagementObject mo in mos.Get())
            {
                //Console.WriteLine(mo["IPEnabled"].ToString().ToLower());
                //if (RuntimeHelpers.Equals(mo["IPEnabled"], true))
                if (mo["IPEnabled"].ToString().ToUpper().Contains("TRUE"))
                {
                    Console.WriteLine("Available Network Adapter: " + (++available_dev));
                    Console.WriteLine("INDEX: " + mo["Index"]);
                    Console.WriteLine("DEV: " + mo["Description"]);
                    Console.WriteLine("NAME:" + mo["ServiceName"]);
                    Console.WriteLine("IP Address: " + (mo["IPAddress"] as string[])[0]);
                    if ((mo["DefaultIPGateway"] as string[]) != null)
                    {
                        gateway_list.Add((mo["DefaultIPGateway"] as string[])[0]);
                        Console.WriteLine("Gateway: " + (mo["DefaultIPGateway"] as string[])[0]);
                    }
                    else
                    {
                        Console.WriteLine("Gateway: NULL");
                    }
                    Console.WriteLine("MASK: " + (mo["IPSubnet"] as string[])[0]);
                    //Console.WriteLine("DNS: " + (mo["DNSServerSearchOrder"] as string[])[0]);
                    Console.WriteLine("MAC: " + mo["MACAddress"]);
                    //Console.WriteLine("ETC: " + mo["DatabasePath"]);
                    //Console.WriteLine("CLSID: " + mo["SettingID"]);
                    Console.WriteLine("\n\n");
                
                }
            }

            if (gateway_list.Count == 0)
            {
                Console.WriteLine("[ Warn] No gateway has been set! Internet unavailable!\n\n");
            }
            else if (gateway_list.Count == 1)
            {
                Console.WriteLine("Correct: your gateway {0}.\n\n", gateway_list[0]);
            }
            else
            {
                Console.WriteLine("[Error]: your have too many gateways :");
                foreach (string gateway in gateway_list)
                {
                    Console.WriteLine(gateway);
                }
                Console.WriteLine("\nPlease remove until only 1 gateway remained.\n\n");
            }

            Console.WriteLine("Check Gateway Done!");
            Console.ReadKey(false);

        }
    }
}
