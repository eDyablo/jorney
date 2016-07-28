using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

using ZeroMQ;

namespace Zmq.Hello
{
	static partial class Server
	{
		public static void Main(string[] args)
		{
			using (var context = new ZContext())
			using (var requester = new ZSocket(context, ZSocketType.REQ))
			{
				requester.Connect("tcp://localhost:5555");
				for (int n = 0; n < 10; ++n)
				{
					string requestText = "Hello";
					Console.Write("Sending {0}…", requestText);
					requester.Send(new ZFrame(requestText));
					using (ZFrame reply = requester.ReceiveFrame())
					{
						Console.WriteLine(" Received: {0} {1}!", requestText, reply.ReadString());
					}
				}
			}
		}
	}
}