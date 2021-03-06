"""LCM type definitions
This file automatically generated by lcm.
DO NOT MODIFY BY HAND!!!!
"""

try:
    import cStringIO.StringIO as BytesIO
except ImportError:
    from io import BytesIO
import struct

class query_msg(object):
    __slots__ = ["timestamp", "query"]

    def __init__(self):
        self.timestamp = 0
        self.query = ""

    def encode(self):
        buf = BytesIO()
        buf.write(query_msg._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        buf.write(struct.pack(">h", self.timestamp))
        __query_encoded = self.query.encode('utf-8')
        buf.write(struct.pack('>I', len(__query_encoded)+1))
        buf.write(__query_encoded)
        buf.write(b"\0")

    def decode(data):
        if hasattr(data, 'read'):
            buf = data
        else:
            buf = BytesIO(data)
        if buf.read(8) != query_msg._get_packed_fingerprint():
            raise ValueError("Decode error")
        return query_msg._decode_one(buf)
    decode = staticmethod(decode)

    def _decode_one(buf):
        self = query_msg()
        self.timestamp = struct.unpack(">h", buf.read(2))[0]
        __query_len = struct.unpack('>I', buf.read(4))[0]
        self.query = buf.read(__query_len)[:-1].decode('utf-8', 'replace')
        return self
    _decode_one = staticmethod(_decode_one)

    _hash = None
    def _get_hash_recursive(parents):
        if query_msg in parents: return 0
        tmphash = (0x812290b364f31a90) & 0xffffffffffffffff
        tmphash  = (((tmphash<<1)&0xffffffffffffffff)  + (tmphash>>63)) & 0xffffffffffffffff
        return tmphash
    _get_hash_recursive = staticmethod(_get_hash_recursive)
    _packed_fingerprint = None

    def _get_packed_fingerprint():
        if query_msg._packed_fingerprint is None:
            query_msg._packed_fingerprint = struct.pack(">Q", query_msg._get_hash_recursive([]))
        return query_msg._packed_fingerprint
    _get_packed_fingerprint = staticmethod(_get_packed_fingerprint)

