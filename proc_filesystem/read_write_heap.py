#!/usr/bin/python3
""" ex 0 """


def rpst():
    """ replace string """
    import os
    import sys

    # Check & asign arguments
    if (len(sys.argv) != 4):
        print("Usgae: ./<exe name> <pid> <string to search> <string to write>")
        exit(1)
    pid = int(sys.argv[1])
    ss = sys.argv[2]
    sw = sys.argv[3]

    # Open files
    try:
        maps = open(f"/proc/{pid}/maps", 'r')
        mem = open(f"/proc/{pid}/mem", 'r+b')
    except:
        print("Couldn't open the files")
        exit(1)

    end = False
    for line in maps:
        if end:
            break
        l = line.split()
        if (l[-1] == "[stack]"):
            end = True
        char_address = l[0].split('-')
        int_address = [int(each, 16) for each in char_address]
        size = int_address[1] - int_address[0]
        cur = os.lseek(mem.fileno(), int_address[0], os.SEEK_SET)
        mc = mem.read(size)
        try:
            pos = mc.index(bytes(ss, 'ascii'))
        except:
            continue
        os.lseek(mem.fileno(), (int_address[0] + pos), os.SEEK_SET)
        mem.write(bytes(sw, 'ascii'))
        mem.flush()
        break

    # Close files
    maps.close()
    mem.close()


if (__name__ == "__main__"):
    rpst()
