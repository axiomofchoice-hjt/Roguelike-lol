using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using UnityEngine;

namespace Tools {
    public class Remote {
        static private Socket socket;
        static private List<byte> recvBuf;
        static byte[] recvTmp;

        static public void Start() {
            try {
                recvBuf = new();
                socket = new(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                socket.SendTimeout = 1000;
                socket.BeginConnect(Config.host, Config.port, new AsyncCallback(ConnectCallback), socket);
            } catch (Exception) {
                Model.Events.ConnectFail.SetActive(true);
            }
        }

        static public void ConnectCallback(IAsyncResult result) {
            try {
                socket.EndConnect(result);
                Send(System.Text.Encoding.ASCII.GetBytes("ED3l)3V@eAh*0(Lk7nBgAmdwJA4QpWVgexay(9CyjmwzE3!Om1XQ#+8Ks15"));
                recvTmp = new byte[1024];
                socket.BeginReceive(recvTmp, 0, recvTmp.Length, SocketFlags.None, new AsyncCallback(ReceiveCallback), socket);
            } catch (Exception) {
                Model.Events.ConnectFail.SetActive(true);
            }
        }

        static public void Send(byte[] data) {
            try {
                socket.Send(IntSerialize.PutSize(data));
            } catch (Exception) {
                Model.Events.ConnectFail.SetActive(true);
            }
        }

        static void ReceiveCallback(IAsyncResult result) {
            int bytesRead = socket.EndReceive(result);
            if (bytesRead > 0) {
                for (int i = 0; i < bytesRead; i++) {
                    recvBuf.Add(recvTmp[i]);
                }
                byte[] ret = null;
                while (IntSerialize.Completed(recvBuf)) {
                    ret = IntSerialize.PopFront(recvBuf);
                }
                if (ret != null) {
                    Model.Scene.proto = SceneProto.Parser.ParseFrom(ret);
                }
                socket.BeginReceive(recvTmp, 0, recvTmp.Length, SocketFlags.None, new AsyncCallback(ReceiveCallback), socket);
            } else {
                Model.Events.ConnectFail.SetActive(true);
            }
        }

        static public void Destroy() {
            socket.Shutdown(SocketShutdown.Both);
            socket.Close();
            socket = null;
        }
    }
}