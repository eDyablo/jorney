using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

using ZeroMQ;

namespace Zmq.Hello
{
	class Server : IDisposable
	{
		private ZContext context;
		private ZSocket channel;

		public static void Main(string[] args)
		{
			using (var server = new Server())
			{
				server.Run();
			}
		}

		public Server()
		{
			context = new ZContext();
			channel = new ZSocket(context, ZSocketType.REP);
		}

		public void Run()
		{
			Initialize();
			Communicate();
		}

		public void Dispose()
		{
			channel.Dispose();
			context.Dispose();
		}

		private void Initialize()
		{
			channel.Bind("tcp://*:5555");
		}

		private void Communicate()
		{
			while (true)
				ProcessRequest();
		}

		private void ProcessRequest()
		{
			var request = Receive();
			Report("Received {0}\n", request);
			Busy();
			Answer("World");
		}

		private string Receive()
		{
			using (var request = channel.ReceiveFrame())
			{
				return request.ReadString();
			}
		}

		private void Answer(string text)
		{
			using (var answer =  new ZFrame(text))
			{
				channel.Send(answer);
			}
		}

		private void Busy()
		{
			Thread.Sleep(500);
		}

		private void Report(string text, params string[] extra)
		{
			Console.Write(text, extra);
		}
	}
}