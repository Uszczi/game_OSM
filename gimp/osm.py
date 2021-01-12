rows = [22, 84, 132, 170, 220, 270, 316, 362, 412, 458]
cols = [124, 158, 204, 250, 296]
cols_mirror = [640 - i for i in cols]
nodes = []
nodes.append([0, 2, 4])
nodes.append([0, 2, 3, 4])
nodes.append([0, 2, 3, 4])
nodes.append([3, 4])
nodes.append([2,3])
nodes.append([3])
nodes.append([0,2,3,4])
nodes.append([0,1,3,4])
nodes.append([0,1,2,3,4])
nodes.append([0,4])

# i = 1
# for number, row in enumerate(nodes):
#     for r in row:
#         # print(f"Node * n{i} = new Node({rows[number]}, {cols[r]});")
#         i += 1



i = 0
for number, row in enumerate(nodes):
    for r in row:
        print(f"xx[{i}] = {cols[r]};")
        i += 1

i = 0
for number, row in enumerate(nodes):
    for r in row:
        print(f"yy[{i}] = {rows[number]};")
        i += 1
