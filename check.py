

if __name__ == "__main__":
    op_1s = []
    op_2s = []
    quotients = []
    remainders = []
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
        elif t[0] == 'quotient':
            quotients.append(int(t[1]))
        else:
            remainders.append(int(t[1]))
    print(f'len of op_1s:{len(op_1s)}')
    print(f'len of op_2s:{len(op_2s)}')
    print(f'len of quotients:{len(quotients)}')
    print(f'len of remainders:{len(remainders)}')
    for index, i in enumerate(quotients):
        if(i*op_2s[index]+remainders[index] != op_1s[index]):
            print(f'{op_1s[index]} // {op_2s[index]} should be {op_1s[index]//op_2s[index]} ... {op_1s[index]%op_2s[index]}\n')
            print(f'But quotient is {i}, remainder is {remainders[index]}')
            flag = False
    if(flag):
        print("PASS!!!")