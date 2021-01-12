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

i = 1
for number, row in enumerate(nodes):
    for r in row:
        print(f"Node * n{i} = new Node({cols[r]}, {rows[number]});")
        i += 1

for number, row in enumerate(nodes):
    for r in row:
        print(f"Node * n{i} = new Node({cols_mirror[r]}, {rows[number]});")
        i += 1


# a = 0
# for number, row in enumerate(nodes):
#     for r in row:
#         print(f"xx[{a}] = {cols[r]};")
#         a += 1

# b = 0
# for number, row in enumerate(nodes):
#     for r in row:
#         print(f"yy[{b}] = {rows[number]};")
#         b += 1

# for number, row in enumerate(nodes):
#     for r in row:
#         print(f"xx[{a}] = {cols_mirror[r]};")
#         a += 1

# for number, row in enumerate(nodes):
#     for r in row:
#         print(f"yy[{b}] = {rows[number]};")
#         b += 1


