"""LCM type definitions
This file automatically generated by lcm.
DO NOT MODIFY BY HAND!!!!
"""

try:
    import cStringIO.StringIO as BytesIO
except ImportError:
    from io import BytesIO
import struct

class teensy_data(object):
    __slots__ = ["BME_temp", "BME_pressure", "BME_humidity", "GPIO", "Leak", "OneWireTemp", "Analog", "Error"]

    def __init__(self):
        self.BME_temp = 0.0
        self.BME_pressure = 0.0
        self.BME_humidity = 0.0
        self.GPIO = [ 0 for dim0 in range(2) ]
        self.Leak = 0
        self.OneWireTemp = [ 0.0 for dim0 in range(5) ]
        self.Analog = [ 0.0 for dim0 in range(8) ]
        self.Error = False

    def encode(self):
        buf = BytesIO()
        buf.write(teensy_data._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        buf.write(struct.pack(">fff", self.BME_temp, self.BME_pressure, self.BME_humidity))
        buf.write(struct.pack('>2h', *self.GPIO[:2]))
        buf.write(struct.pack(">h", self.Leak))
        buf.write(struct.pack('>5f', *self.OneWireTemp[:5]))
        buf.write(struct.pack('>8f', *self.Analog[:8]))
        buf.write(struct.pack(">b", self.Error))

    def decode(data):
        if hasattr(data, 'read'):
            buf = data
        else:
            buf = BytesIO(data)
        if buf.read(8) != teensy_data._get_packed_fingerprint():
            raise ValueError("Decode error")
        return teensy_data._decode_one(buf)
    decode = staticmethod(decode)

    def _decode_one(buf):
        self = teensy_data()
        self.BME_temp, self.BME_pressure, self.BME_humidity = struct.unpack(">fff", buf.read(12))
        self.GPIO = struct.unpack('>2h', buf.read(4))
        self.Leak = struct.unpack(">h", buf.read(2))[0]
        self.OneWireTemp = struct.unpack('>5f', buf.read(20))
        self.Analog = struct.unpack('>8f', buf.read(32))
        self.Error = bool(struct.unpack('b', buf.read(1))[0])
        return self
    _decode_one = staticmethod(_decode_one)

    _hash = None
    def _get_hash_recursive(parents):
        if teensy_data in parents: return 0
        tmphash = (0xec09c75f9fd23976) & 0xffffffffffffffff
        tmphash  = (((tmphash<<1)&0xffffffffffffffff)  + (tmphash>>63)) & 0xffffffffffffffff
        return tmphash
    _get_hash_recursive = staticmethod(_get_hash_recursive)
    _packed_fingerprint = None

    def _get_packed_fingerprint():
        if teensy_data._packed_fingerprint is None:
            teensy_data._packed_fingerprint = struct.pack(">Q", teensy_data._get_hash_recursive([]))
        return teensy_data._packed_fingerprint
    _get_packed_fingerprint = staticmethod(_get_packed_fingerprint)

