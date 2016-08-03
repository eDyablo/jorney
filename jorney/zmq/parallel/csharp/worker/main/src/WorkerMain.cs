using System;
using System.Threading;
using ZeroMQ;

namespace Zmq.Parallel
{
  static partial class Worker
  {
    public static void Main(string[] args)
    {
			using (var context = new ZContext())
			using (var receiver = new ZSocket(context, ZSocketType.PULL))
			using (var sink = new ZSocket(context, ZSocketType.PUSH))
			{
				receiver.Connect("tcp://localhost:5557");
				sink.Connect("tcp://localhost:5558");
				while (true)
				{
					var replyBytes = new byte[4];
					receiver.ReceiveBytes(replyBytes, 0, replyBytes.Length);
					int workload = BitConverter.ToInt32(replyBytes, 0);
					Console.Write("{0} ", workload);
					Thread.Sleep(workload);
					sink.Send(new byte[0], 0, 0);
				}
			}
    }
  }
}