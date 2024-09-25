#!/usr/bin/python3

import os
import time


if (__name__ == "__main__"):
    string = "Hello World!"
    while (True):
        time.sleep(2)
        print(f"{string} ->{os.getpid()}    {hex(id(string))}")
