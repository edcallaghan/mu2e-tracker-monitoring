# Ed Callaghan
# Abstract out details of communicating with RS485 server
# August 2025

import ctypes
import os.path
import time
from MessagingConnection import MessagingConnection

class MonitoringServerConnection():
    def __init__(self, host, port):
        self.host = host
        self.port = port
        self.reestablish()

        self.opcodes = {
            'I3p3'          : 0,
            'I2p5'          : 1,
            'I1p8HV'        : 2,
            'IHV5p0'        : 3,
            'VDMBHV5p0'     : 4,
            'V1p8HV'        : 5,
            'V3p3HV'        : 6,
            'V2p5'          : 7,
            'Flow'          : 8,
            'AbsPressure'   : 9,
            'DMBTEMP'       : 10,
            'A3'            : 11,
            'I1p8CAL'       : 12,
            'I1p2'          : 13,
            'ICAL5p0'       : 14,
            'ADCSPARE'      : 15,
            'V3p3'          : 16,
            'VCAL5p0'       : 17,
            'V1p8CAL'       : 18,
            'V1p0'          : 19,
            'ROCPCBTEMP'    : 20,
            'HVPCBTEMP'     : 21,
            'CALPCBTEMP'    : 22,
            'RTD'           : 23,
            'V5KEY'         : 24,
            'KEYPCBTEMP'    : 25,
            'DCDCTEMP'      : 26,
            'V2p5KEY'       : 27,
            'ROC_RAIL_1V'   : 28,
            'ROC_RAIL_1p8V' : 29,
            'ROC_RAIL_2p5V' : 30,
            'ROC_TEMP'      : 31,
            'CAL_RAIL_1V'   : 32,
            'CAL_RAIL_1p8V' : 33,
            'CAL_RAIL_2p5V' : 34,
            'CAL_TEMP'      : 35,
            'HV_RAIL_1V'    : 36,
            'HV_RAIL_1p8V'  : 37,
            'HV_RAIL_2p5V'  : 38,
            'HV_TEMP'       : 39,
            'ID'            : 252,
            'HB'            : 253,
            'DBG'           : 254,
        }

    def reestablish(self):
        self.connection = MessagingConnection(self.host, self.port)

    def close(self):
        self.connection.close()

    def WriteRead(self, channel, command):
        channel = ctypes.c_uint(channel)
        opcode = ctypes.c_uint(self.opcodes[command])
        self.connection.send_message(channel, opcode)
        rvs = self.connection.recv_message()
        return rvs

    def QuerySome(self, channel, commands):
        rvs = {}
        for command in commands:
            readback = None
            rv = self.WriteRead(channel, command)
            rv = rv[0][0]
            if type(rv) == float:
                readback = rv
            rvs[command] = rv
        return rvs

    def QueryAll(self, channel):
        commands = self.opcodes.keys()
        rvs = self.QuerySome(channel, commands)
        return rvs

    def QueryTemperatures(self, channel):
        commands = [k for k in self.opcodes.keys() if 'TEMP' in k]
        rvs = self.QuerySome(channel, commands)
        return rvs
