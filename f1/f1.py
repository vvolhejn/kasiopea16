def toInt(c):
    return ord(c)-ord('A')

def fromInt(i):
    return chr(i + ord('A'))

t = int(input())
for ti in range(0,t):
    n = int(input())
    arr = []
    for j in range(0,n):
        arr.append(input())

    gt = [[0]*26 for i in range(26)]

    hasAns = True

    for i in range(0,n-1):
        a = arr[i]; b = arr[i+1]; ok = False
        for j in range(0,len(a)):
            if j >= len(b):
                break

            if a[j] != b[j]:
                gt[toInt(b[j])][toInt(a[j])] = 1
                ok = True
                break

        if not ok and len(a) > len(b):
            hasAns = False

    if hasAns:
        res = [0]*26
        done = [False]*26

        for i in range(0,26):
            best = -1
            for j in range(0,26):
                if done[j]:
                    continue

                bad = max(gt[j][:])
                if bad == 0:
                    best = j
                    break

            if best == -1:
                hasAns = False
                break

            for k in range(0,26):
                gt[k][j] = False

            res[best] = i
            done[best] = True

        if hasAns:
            for i in range(0,len(arr)):
                a = list(arr[i])
                for j in range(0,len(a)):
                    a[j] = fromInt(res[toInt(a[j])])

                print("".join(a))

    if not hasAns:
        print("#")

