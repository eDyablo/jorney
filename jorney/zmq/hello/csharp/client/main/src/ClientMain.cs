using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

using ZeroMQ;

namespace Zmq.Hello
{
	class Client : IDisposable
	{
		private ZContext context;
		private ZSocket channel;

		public static void Main(string[] args)
		{
			using (var client = new Client())
			{
				client.Run();
			}
		}

		public Client()
		{
			context = new ZContext();
			channel = new ZSocket(context, ZSocketType.REQ);
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
			channel.Connect("tcp://localhost:5555");
		}

		private void Communicate()
		{
			const int requestNumber = 10;
			for (int i = 0; i < requestNumber; ++i)
				MakeRequest("Hello");
		}

		private void MakeRequest(string text)
		{
			Report("Sending {0}...", text);
			Send(text);
			Report(" Received: {0}\n", Receive());
		}

		private void Send(string text)
		{
			using (var request = new ZFrame(text))
			{
				channel.Send(request);
			}
		}

		private string Receive()
		{
			using (var replay = channel.ReceiveFrame())
			{
				return replay.ReadString();
			}
		}

		private void Report(string text, params string[] extra)
		{
			Console.Write(text, extra);
		}
	}
}