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
    return LineNodes

# Parse file
def parseAOfile(filename,array):
    lineparser = LineParse()
    with open(filename) as file:
        # first line is a json one-liner
        first_line = file.readline()
        dict = json.loads(first_line)
        for line in file:
            parsedline = lineparser.parseString(line)
            array += parsedline.asList()
    return (dict["S0min"], dict["depth"], dict["basedepth"],
            dict["basefactor"], dict["spd"], dict["up"], dict["options"])
