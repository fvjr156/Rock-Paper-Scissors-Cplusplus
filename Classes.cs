using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;

namespace _01_LMS_Activity_1
{
    public class Player
    {
        public string name { get; set; }
        public int damage { get; set; }
        public int hp { get; set; }
        public int wins { get; set; }
        public int winstreak { get; set; }
        public int losses { get; set; }
        public string choice { get; set; }
    }
    public class Bot
    {
        public string name { get; set; }
        public int damage { get; set; }
        public int hp { get; set; }
        public string choice { get; set; }
    }
}
