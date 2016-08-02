using System;
using ZeroMQ;

namespace Zmq.Weather
{
  static partial class Subscriber
  {
    public static void Main(string[] args)
    {
      string endpoint = "tcp://localhost:5556";
      using (var context = new ZContext())
      using (var subscriber = new ZSocket(context, ZSocketType.SUB))
      {
        Console.WriteLine("I: Connecting to {0} ...", endpoint);
        subscriber.Connect(endpoint);
        string zipCode =  "1001";
        Console.WriteLine("I: Subscribing to zip code {0} ...", zipCode);
        subscriber.Subscribe(zipCode);
        long total_temperature = 0;
        for (int i=0; i < 20; ++i)
        {
          using (var replyFrame = subscriber.ReceiveFrame())
          {
            string reply = replyFrame.ReadString();
            Console.WriteLine(reply);
            total_temperature += Convert.ToInt64(reply.Split(' ')[1]);
          }
        }
        Console.WriteLine("Average temperature for zipcode '{0}' was {1}°",
            zipCode, (total_temperature / 20));
      }
    }
  }
}