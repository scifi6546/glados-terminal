from terminal import *
from parser import *
from interperter import *
def run():
    parse = parser()
    interp = interperter(parse.token_arr)
run()