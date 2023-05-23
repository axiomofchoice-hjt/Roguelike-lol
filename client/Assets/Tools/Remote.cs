using Google.Protobuf;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using UnityEngine;

namespace Tools {
    public class Remote {
        static private Socket socket;
        static private List<byte> recv_buf;
        static private byte[] recv_temp;
        static public DateTime test_delay_last;
        static public TimeSpan delay;
        static public TMPro.TMP_Text delay_text;
        static public bool fail;

        static public void Start() {
            test_delay_last = DateTime.Now;
            delay = TimeSpan.Zero;
            delay_text = GameObject.Find("Delay").GetComponent<TMPro.TMP_Text>();
            delay_text.text = "0 ms";
            fail = false;

            try {
                recv_buf = new();
                socket = new(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                socket.SendTimeout = 1000;
                socket.BeginConnect(Config.host, Config.port, new AsyncCallback(ConnectCallback), socket);
            } catch (Exception) {
                fail = true;
            }
        }

        static public void ConnectCallback(IAsyncResult result) {
            try {
                socket.EndConnect(result);
                Send(System.Text.Encoding.ASCII.GetBytes("ED3l)3V@eAh*0(Lk7nBgAmdwJA4QpWVgexay(9CyjmwzE3!Om1XQ#+8Ks15"));
                recv_temp = new byte[1024];
                socket.BeginReceive(recv_temp, 0, recv_temp.Length, SocketFlags.None, new AsyncCallback(ReceiveCallback), socket);
            } catch (Exception) {
                fail = true;
            }
        }

        static public void Send(byte[] data) {
            if (fail) { return; }
            try {
                socket.Send(IntSerialize.PutSize(data));
            } catch (Exception) {
                fail = true;
            }
        }

        static void ReceiveCallback(IAsyncResult result) {
            int bytesRead = socket.EndReceive(result);
            if (bytesRead > 0) {
                for (int i = 0; i < bytesRead; i++) {
                    recv_buf.Add(recv_temp[i]);
                }
                byte[] ret = null;
                while (IntSerialize.Completed(recv_buf)) {
                    ret = IntSerialize.PopFront(recv_buf);
                    if (ret != null) {
                        SceneProto proto = SceneProto.Parser.ParseFrom(ret);
                        if (proto.TestDelay) {
                            delay = DateTime.Now - test_delay_last;
                        } else {
                            Model.Scene.proto = proto;
                        }
                    }
                }
                socket.BeginReceive(recv_temp, 0, recv_temp.Length, SocketFlags.None, new AsyncCallback(ReceiveCallback), socket);
            } else {
                fail = true;
            }
        }

        static public void Destroy() {
            socket.Shutdown(SocketShutdown.Both);
            socket.Close();
            socket = null;
        }

        static public void Update() {
            var now = DateTime.Now;
            if (now - test_delay_last >= TimeSpan.FromSeconds(1)) {
                test_delay_last = now;
                MessageProto proto = new() {
                    Type = MessageProto.Types.Type.TestDelay
                };
                Send(proto.ToByteArray());
            }
            Model.Events.ConnectFail.SetActive(fail);
            delay_text.text = Convert.ToInt32(delay.TotalMilliseconds) + " ms";
        }
    }
}