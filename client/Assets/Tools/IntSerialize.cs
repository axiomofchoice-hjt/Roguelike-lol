using System;
using System.Collections.Generic;
using System.Linq;

namespace Tools {
    public class IntSerialize {
        public static int GetSize(List<byte> s) {
            return s[0] | (s[1] << 8) | (s[2] << 16) | (s[3] << 24);
        }

        public static bool Completed(List<byte> s) {
            return s.Count() >= 4 && GetSize(s) + 4 <= s.Count();
        }

        public static byte[] PopFront(List<byte> s) {
            int sz = GetSize(s);
            byte[] ret = new byte[sz];
            s.CopyTo(4, ret, 0, sz);
            s.RemoveRange(0, sz + 4);
            return ret;
        }

        public static byte[] PutSize(byte[] s) {
            byte[] tmp = new byte[s.Length + 4];
            tmp[0] = (byte)(s.Length & 0xff);
            tmp[1] = (byte)((s.Length >> 8) & 0xff);
            tmp[2] = (byte)((s.Length >> 16) & 0xff);
            tmp[3] = (byte)((s.Length >> 24) & 0xff);
            Array.Copy(s, 0, tmp, 4, s.Length);
            return tmp;
        }
    }
}
