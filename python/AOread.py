import numpy as np
import pyparsing as pp
import json

# Define Grammar
def LineParse():
    ParB = pp.Suppress("(")
    ParE = pp.Suppress(")")
    BraB = pp.Suppress("[")
    BraE = pp.Suppress("]")
    comma = pp.Suppress(",")
    number = pp.Word(pp.nums+'.'+'e'+'E'+'+'+'-').setParseAction( lambda t: float(t[0]))
    boolean = pp.Literal("0") ^ pp.Literal("1")
    boolean.setParseAction( lambda t: int(t[0]))
    NodeOneReading = ParB + number + comma + boolean + ParE
    NodeManyReadings =  BraB + pp.Group(NodeOneReading) + pp.ZeroOrMore( comma + pp.Group(NodeOneReading)) + BraE
    LineNodes = pp.Group(NodeManyReadings) + pp.ZeroOrMore( comma + pp.Group(NodeManyReadings) ) + pp.Suppress(pp.LineEnd())
#   EOL = pp.Suppress("\n")
#   commaOREOL = comma ^ EOL
    return LineNodes

# Parse file
def parseAOfile(filename):
    array = []
    lineparser = LineParse()
    with open(filename) as file:
        # first line is a json one-liner
        first_line = file.readline()
        dict = json.loads(first_line)
        for line in file:
            parsedline = lineparser.parseString(line)
            array += parsedline.asList()
        nparray = np.array(array)
    return dict, nparray

# get time array
def time(dict):
    depth = dict['depth']
    basedepth = dict['basedepth']
    spd = dict['spd']
    time = np.array([])
    for i in range(depth+1):
        list=np.full(i+basedepth+1,i/spd,dtype=np.float)
        time = np.concatenate((time,list))
    return time

# get spots array
def spots(dict):
    depth = dict['depth']
    basedepth = dict['basedepth']
    spd = dict['spd']
    S0min = dict['S0min']
    up = dict['up']
    spots = np.array([])
    upperspot = S0min*up**basedepth
    for i in range(depth+1):
        list = [upperspot/(up**(2*j)) for j in range(basedepth+i+1)]
        spots =np.concatenate((spots,list))
        upperspot *= up
    return spots

# get time and spots arrays
def timespots(dict):
    timet = time(dict)
    spotst = spots(dict)
    return timet,spotst
