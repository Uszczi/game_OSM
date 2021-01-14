rows_possition = [22, 84, 132, 170, 220, 270, 316, 362, 412, 458]
cols_possition = [124, 158, 204, 250, 296]
cols_mirror_possition = [640 - i for i in cols_possition]

class Node:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.n = []
        
    def add(self, other):
        self.n.append(other)

    def getPointsBetweenAll(self):
        points = []
        distance = 20
        for other in self.n:
            if other.x == self.x:
                delta = other.y - self.y
                count = delta // distance
                sign = -1 if (count < 0) else 1
                for i in range(abs(count) - 1):
                    points.append((self.x, self.y + sign*distance*(i + 1)))
            elif other.y == self.y:
                delta = other.x - self.x
                count = delta // distance
                sign = -1 if (count < 0) else 1
                for i in range(abs(count) - 1):
                    points.append((self.x + sign*distance*(i + 1), self.y))
        return points

nodes = []
nodes.append([0, 2, 4])
nodes.append([0, 2, 3, 4])
nodes.append([0, 2, 3, 4])
nodes.append([3, 4])
nodes.append([2, 3])
nodes.append([3])
nodes.append([0, 2, 3, 4])
nodes.append([0, 1, 2, 3, 4])
nodes.append([0, 1, 2, 3, 4])
nodes.append([0, 4])

row_connections = []
row_connections.append([1, 1])
row_connections.append([1, 1, 1])
row_connections.append([1, 0, 1])
row_connections.append([1])
row_connections.append([1])
row_connections.append([])
row_connections.append([1, 1, 1])
row_connections.append([1, 0, 1, 1])
row_connections.append([1, 1, 0, 1])
row_connections.append([1])

col_connection = []
col_connection.append([1, 1, 1])
col_connection.append([1, 1, 1, 0])
col_connection.append([0, 1, 0, 1])
col_connection.append([1, 0])
col_connection.append([1, 1])
col_connection.append([1])
col_connection.append([1, 1, 0, 1])
col_connection.append([0, 1, 1, 1, 0])
col_connection.append([1, 0, 0, 0, 1])

nodeList = []

## Node creation
i = 0
for number, row in enumerate(nodes):
    for r in row:
        nodeList.append(Node(cols_possition[r], rows_possition[number]))
        i += 1

for number, row in enumerate(nodes):
    for r in row:
        nodeList.append(Node(cols_mirror_possition[r], rows_possition[number]))
        i += 1


## Lewe Wiersze
index = 0
for n, row in enumerate(nodes):
    if len(row) == 1:
        index += 1
        continue
    for cell_index, cell in enumerate(row):
        if cell_index + 1 == len(row):
            index += 1
            break
        connect = row_connections[n][cell_index]
        if connect != 0:
            nodeList[index].add(nodeList[index + 1])
        index += 1

## Lewe Kolumny
index = 0
for n, col in enumerate(nodes):
    if len(nodes) - n == 1:
        break

    for cell_index, cell in enumerate(col):
        connect = col_connection[n][cell_index]
        if connect == 1:
            con_index = index + len(col) - cell_index
            found = False
            for local_n in nodes[n + 1]:
                if local_n != cell:
                    con_index += 1
                if local_n == cell:
                    found = True
                    break
            if not found:
                for local_n in nodes[n + 2]:
                    if local_n != cell:
                        con_index += 1
                    else:
                        break
            nodeList[index].add(nodeList[con_index])
        index += 1

## Odbicie lustrzane
allPoints = []
for node in nodeList:
    for point in node.getPointsBetweenAll():
        allPoints.append(point)
        allPoints.append((640 - point[0], point[1]))

## Punkty
for point in allPoints:
    print("{%s, %s}" % point, end = ", ")


