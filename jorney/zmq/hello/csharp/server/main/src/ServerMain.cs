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
			using (var responder = new ZSocket(context, ZSocketType.REP))
			{
				responder.Bind("tcp://*:5555");
				while (true)
				{
					using (ZFrame request = responder.ReceiveFrame())
					{
						Console.WriteLine("Received {0}", request.ReadString());
						Thread.Sleep(1);
						responder.Send(new ZFrame("World"));
					}
				}
			}
		}
	}
}