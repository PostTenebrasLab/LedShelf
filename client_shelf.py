#! /usr/bin/python3
# -*- coding: utf-8 -*-

#
#   Description :  small script to test Post Tenebras Lab shelf REST node
#
# 
#
#
#
#

__author__ = 'Sebastien Chassot'
__author_email__ = 'sebastien.chassot@etu.hesge.ch'

__version__ = "1.0.1"
__copyright__ = ""
__licence__ = "GPL"
__status__ = "Project"

import requests
import struct
import json
import base64

SRV = '192.168.101.208'
PORT = '8080'

setoneled = struct.pack('5B', 0x11, 0x25, 0x72, 0xFF, 0xF2)
r = requests.get('http://'+SRV+':'+PORT+'/ptl?values='+base64.b64encode(setoneled).__str__())

print(json.loads(r.text))
