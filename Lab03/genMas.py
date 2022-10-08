file = open('mas.txt', 'r')


numbers = file.read().split()
#print(numbers)
#print(len(numbers))

'''
res = "{\n"
for i in range (8):
    res += "{"
    for j in range (4):
        res += "{"
        for k in range (1,17):
            #print(k, j, i)
            res += str(numbers[i*68+j*17+k])
            if k != 16:
                res += ","
        res += "}"
        if j != 3:
            res += ","
    res += "}"
    if i != 7:
        res += ","
    res += "\n"
res += "};"
'''


res = "{"
for n in numbers:
    res += n + ","
res += "}"


'''
res = "{"
for line in file:
    res += line.strip() + ","
res += "}"
'''

file.close()
print(res)
