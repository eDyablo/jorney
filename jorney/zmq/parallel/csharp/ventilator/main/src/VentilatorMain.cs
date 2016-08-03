using System;
using ZeroMQ;

namespace Zmq.Parallel
{
  static partial class Ventilator
  {
    public static void Main(string[] args)
    {
			using (var context = new ZContext())
			using (var sender = new ZSocket(context, ZSocketType.PUSH))
			using (var sink = new ZSocket(context, ZSocketType.PUSH))
			{
				sender.Bind("tcp://*:5557");
				sink.Connect("tcp://localhost:5558");
				Console.WriteLine("Press ENTER when the workers are ready...");
				Console.ReadKey(true);
				Console.WriteLine("Sending tasks to workers...");
				sink.Send(new byte[] { 0x00 }, 0, 1);
				var rnd = new Random();
				const int taskNumber = 100;
				long totalWorkload = 0;
				for (var i = 0; i < taskNumber; ++i)
				{
					var workload = rnd.Next(taskNumber) + 1;
					totalWorkload += workload;
					var action = BitConverter.GetBytes(workload);
					Console.WriteLine("{0}", workload);
					sender.Send(action, 0, action.Length);
				}
				Console.WriteLine("Total expected cost: {0} ms", totalWorkload);
			}
    }
  }
}