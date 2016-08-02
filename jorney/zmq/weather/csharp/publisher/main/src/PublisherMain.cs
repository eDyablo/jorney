using System;
using ZeroMQ;

namespace Zmq.Weather
{
  static partial class Publisher
  {
    public static void Main(string[] args)
    {
      using (var context = new ZContext())
      using (var publisher = new ZSocket(context, ZSocketType.PUB))
      {
        string address = "tcp://*:5556";
        Console.WriteLine("I: Publisher.Bind'ing on {0}", address);
        publisher.Bind(address);
        var rnd = new Random();
        while (true)
        {
          int zipcode = rnd.Next(99999);
          int temperature = rnd.Next(-55, +45);
          var update = string.Format("{0:D5} {1}", zipcode, temperature);
          using (var updateFrame = new ZFrame(update))
          {
            publisher.Send(updateFrame);
          }
        }
      }
    }
  }
}