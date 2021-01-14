## TODO
## FIXME

ROW_SPAN = 29

rows_possition = range(20, 454, ROW_SPAN)
cols_possition = [124, 154, 204, 250, 296]
cols_mirror_possition = [640 - i for i in cols_possition]

# Rozpiętość między kolumnami do 
# wygenerowania punktów w każdym wierszu
column_ranges = [[(0, 4)],
                 [(0, 0), (2, 2), (4, 4)],
                 [(0, 4)],
                 [(0, 0), (2, 2), (3, 3)],
                 [(0, 2), (3, 4)],
                 [(2, 2), (4, 4)],
                 [(2, 2)],
                 [(2, 2)], [(2, 2)], [(2, 2)],
                 [(0, 4)]]

rowNumber = 0
points = []
for ranges in column_ranges:
    for point_range in ranges:
        start, end = point_range
        
        if start == end:
           points.append((cols_possition[start], rows_possition[rowNumber]))
        
        for column in range(cols_possition[start], cols_possition[end], ROW_SPAN):
            points.append((column, rows_possition[rowNumber]))
            
    rowNumber += 1

for point in points:
    print("{%s, %s}" % point, end = ", ")

