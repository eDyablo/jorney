using System;
using System.Diagnostics;
using ZeroMQ;

namespace Zmq.Parallel
{
  static partial class Sink
  {
    public static void Main(string[] args)
    {
			using (var context = new ZContext())
			using (var sink = new ZSocket(context, ZSocketType.PULL))
			{
				sink.Bind("tcp://*:5558");
				sink.ReceiveFrame();
				var stopwatch = new Stopwatch();
				stopwatch.Start();
				const int taskNumber = 100;
				for (int i = 0; i < taskNumber; ++i)
				{
					sink.ReceiveFrame();
					if ((i / 10) * 10 == i)
						Console.Write(":");
					else
						Console.Write(".");
				}
				stopwatch.Stop();
				Console.WriteLine("Total elapsed time: {0} ms",
						stopwatch.ElapsedMilliseconds);
			}
    }
  }
}