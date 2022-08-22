

if __name__ == "__main__":
    op_1s = []
    op_2s = []
    results = []
    flag = True
    with open('output.txt', 'r', encoding='utf-8') as fin:
        lines = fin.readlines()
    lines = [i.strip('\n') for i in lines]
    for i in lines:
        t = i.split(' ')
        if t[0] == 'op_1':
            op_1s.append(int(t[1]))
        elif t[0] == 'op_2':
            op_2s.append(int(t[1]))
        else:
            results.append(int(t[1]))
    print(f'len of op_1s:{len(op_1s)}')
    print(f'len of op_2s:{len(op_2s)}')
    print(f'len of results:{len(results)}')
    for index, i in enumerate(results):
        if(i != op_1s[index]*op_2s[index]):
            print(f'{op_1s[index]} * {op_2s[index]} should be {op_1s[index]*op_2s[index]}\n')
            print(f'But result is {i}')
            flag = False
    if(flag):
        print("PASS!!!")