l = [ i + 1 for i in range(4) ]
n = len(l)

def permutation(k):
    if k == n:
        print(l)
    else:
        for i in range(k, n):
            l[i], l[k] = l[k], l[i]
            permutation(k + 1)
            l[i], l[k] = l[k], l[i]


if __name__ == '__main__':
    permutation(0)

