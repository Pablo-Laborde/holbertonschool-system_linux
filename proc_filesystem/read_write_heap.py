#!/usr/bin/python3
""" ex 0 """


def rpst():
    """ replace string """
    import os
    import sys

    # get pid - os.getpid()
    pid = int(sys.argv[1])
    ss = sys.argv[2]
    ws = sys.argv[3]
    # open /proc/pid/maps
    try:
        maps = open(f'/proc/{pid}/maps', 'r')
    except:
        print('error in maps')
        exit(1)
    # loop to find heap in maps
    for i in maps:
        line = i.split()
        if ('[heap]' in line):
            found_data = True
            add = line[0].split('-')
            add_beg = int(add[0], 16)
            add_end = int(add[1], 16)
            per = line[1]
            off = int(line[2])
            ino = line[4]
            pat = line[5]
            break
    # if heap found it looks for the mem
    if (found_data):
        try:
            mem = open(f'/proc/{pid}/mem', 'rb+')
        except:
            print('error in mem')
            maps.close()
            exit(1)
        mem.seek(add_beg)
        heap = mem.read(add_end - add_beg)
        try:
            sth = heap.index(bytes(ss, 'ASCII'))
        except:
            print("error in index")
            mem.close()
            maps.close()
            exit(1)
        mem.seek(add_beg + sth)
        if len(ws) < len(ss):
            mem.write(bytes(ws + '\0', 'ASCII'))
        maps.close()
        mem.close()
