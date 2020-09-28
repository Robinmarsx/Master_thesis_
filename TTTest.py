#!/usr/bin/env python3

import random
import networkx as nx
import matplotlib.pyplot as plt
import sys
# noinspection PyUnresolvedReferences
from collections import defaultdict

# noinspection PyUnresolvedReferences
from itertools import repeat

import xml.etree.ElementTree as xml


N = 10
E = 5

MAX_SCHEDULE_TIME = 100
INF = sys.maxsize

schedule_time = [random.randint(0, MAX_SCHEDULE_TIME-1) for x in range(N)]

min_val = min(schedule_time)
schedule_time = [x-min_val for x in schedule_time]

print(schedule_time)

edges = []

for i in range(E):
    src_id = random.randint(0, N-1)
    dest_id = random.randint(0, N-1)

    while src_id == dest_id:
        dest_id = random.randint(0, N-1)
    # print(schedule_time[src_id])

    if schedule_time[src_id] > schedule_time[dest_id]:
        temp = src_id
        src_id = dest_id
        dest_id = temp

    distance = schedule_time[dest_id] - schedule_time[src_id]

    scenario = random.randint(0, 2)

    lo = distance
    hi = distance
    if scenario == 1:
        lo = random.randint(0, distance)
        hi = INF
    elif scenario == 2:
        lo = random.randint(distance - 10, distance) # <0 why
        hi = random.randint(distance, distance+10)

    edges.append((src_id, dest_id, lo, hi))

print(edges)

G = nx.MultiDiGraph()

for i in range(N):
    G.add_node(i, schedule_time=schedule_time[i], rot=...)

for i in range(E):
    G.add_edge(edges[i][0], edges[i][1], lo=edges[i][2], hi=edges[i][3])

nx.draw(G, with_labels=True)
plt.show()

# Resrouces  cconstraint

all_nodes = []

MAX_SCHEDULE_TIME = 1000


# positive and negative
positive_infnity = 2**31 - 1
negative_infinity = -2**31


NUM_NODES = 10
NUM_RESOURCE = 5
for i in range(NUM_NODES):
    node = {"name": "node"+str(i), "schedule_time": 0, "rot": {}}
    all_nodes.append(node)


all_index = range(len(all_nodes))

# print(all_index)

for i in all_index:
    all_nodes[i]["schedule_time"] = random.randint(0, MAX_SCHEDULE_TIME)

# print(all_nodes)


counter = 1
for r in range(NUM_RESOURCE):
    selected_index = random.sample(all_nodes, random.randint(1, len(all_nodes)))

    # print(selected_index)

    sorted_selected_index = sorted(selected_index, key = lambda i: i["schedule_time"])

    print(sorted_selected_index)

    for i in range(len(sorted_selected_index)):

        scenario = 0
        if i < len(sorted_selected_index) - 1:
            scenario = random.randint(0, 1)

            if scenario == 0:
                sn1 = 1

        # M and N
                m = random.randint(sorted_selected_index[i - 1].get("schedule_time") - sorted_selected_index[i].get("schedule_time"), MAX_SCHEDULE_TIME)
                n = random.randint(m, MAX_SCHEDULE_TIME)

                frame1 = [m, n, sn1]
                sorted_selected_index[i]["rot"]["R" + str(r)] = frame1
                i = i + 1

            if scenario == 1:
                m = random.randint(0, MAX_SCHEDULE_TIME - sorted_selected_index[i - 1].get("schedule_time") + sorted_selected_index[i].get("schedule_time"))

                n = random.randint(m + sorted_selected_index[i - 1].get("schedule_time") - sorted_selected_index[i].get("schedule_time"), MAX_SCHEDULE_TIME)

                sn = counter
                counter = counter + 1


                Lock = [m, positive_infnity, sn]
                Unlock = [negative_infinity, n, sn]

                sorted_selected_index[i - 1]["rot"]["R" + str(r)] = Lock
                sorted_selected_index[i]["rot"]["R" + str(r)] = Unlock

                i = i + 2

print(all_nodes)




#### Generate XML ####

# creating the root
root = xml.Element('Descriptor')
#creating the operation
child1 = xml.Element('Operations')
root.append(child1)

for n in all_nodes:
    # creating different Operation_nodes
    child11 = xml.SubElement(child1, "Operation")
    #creating schedule_time and Rot
    name = n['name']
    rot = n['rot']
    name01 = xml.SubElement(child11, 'name')
    name01.text = name
    Rot1 = xml.SubElement(child11,'Rot')
    for r in rot.keys():
        timetable01 = xml.SubElement(Rot1,'timetable',rs='\''+r+'\'')
        frame = rot[r]
        #tag1 = 't0={}'.format(frame[0]), 't1={}'.format(frame[1]), 't2={}'.format(frame[2])
        frame01 = xml.SubElement(timetable01,'Frame',attrib={'t0':str(frame[0]),'t1':str(frame[1]),'t2':str(frame[2])})
#creating the constraint
child2 = xml.Element('Constraints')
root.append(child2)
# #creating different constraint
for e in edges:
    child22 = xml.SubElement(child2, 'Constraint')
    src01 = xml.SubElement(child22,'src')
    src01.text = "node"+str(e[0])
   
    dest01 = xml.SubElement(child22,'dest')
    dest01.text = "node"+str(e[1])
    d_lo01 = xml.SubElement(child22,'d_lo')
    d_lo01.text = str(e[2])
    d_hi01 = xml.SubElement(child22,'d_hi')
    d_hi01.text = str(e[3])
     
#creating tree
tree = xml.ElementTree(root)

tree.write('testA.xml')
