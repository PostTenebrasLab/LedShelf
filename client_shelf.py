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
import time
import random

SRV = '192.168.80.168'
PORT = '5000'


def set_led(x, y, color):
    val = ":".join(('led', hex(color).__str__(), x.__str__(), y.__str__()))
    requests.get('http://'+SRV+':'+PORT+'/ptl?values='+val)

def set_line(line, color):
    val = ":".join(('line', hex(color).__str__(), line.__str__())   )
    requests.get('http://'+SRV+':'+PORT+'/ptl?values='+val)

def set_column(col, color):
    val = ":".join(('column', hex(color).__str__(), col.__str__()))
    requests.get('http://'+SRV+':'+PORT+'/ptl?values='+val)

def set_all(color):
    val = ":".join(('set_all', hex(color).__str__()))
    requests.get('http://'+SRV+':'+PORT+'/ptl?values='+val)

def clear_all():
    requests.get('http://'+SRV+':'+PORT+'/ptl?values=clear_all')

MIN = 50
MAX = 150

while(1):
    color = random.randint(MIN, MAX) << 16 | random.randint(MIN, MAX) << 8 | random.randint(MIN, MAX)
    set_led(random.randint(4, 7), random.randint(0, 14), color)
    time.sleep(random.random())

# while(1):
#     color = random.randint(MIN, MAX) << 16 | random.randint(MIN, MAX) << 8 | random.randint(MIN, MAX)
#     set_line(random.randint(0, 15), color)
#     time.sleep(random.random())



