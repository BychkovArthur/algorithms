def get_det(a, b, c, d):
    return a * d - b * c

def main(a, b, c, d, e, f):
    EPS = 1e-5
    # print(EPS)
    # a = float(input())
    # b = float(input())
    # c = float(input())
    # d = float(input())
    # e = float(input())
    # f = float(input())

    if a == b == c == d == e == f == 0:
        return [5]
    else:
        if a == b == c == d == 0:
            rgA = 0
        elif abs(get_det(a, b, c, d)) <= EPS:
            rgA = 1
        else:
            rgA = 2
        # print('РАНГ ', rgA)
        rgAB = 1
        # Найдем не нулевой элемент расширенной системы
        ind = [-1, -1]
        
        matrix = [[0, 0, 0, 0], [0, a, b, e], [0, c, d, f]]
        
        for i in range(1, 3):
            for j in range(1, 4):
                if matrix[i][j] != 0:
                    ind[0] = i
                    ind[1] = j
                    
        key = 0
        
        # Пытаемся найти окаймляющих минор второго порядка
        for i in range(1, 3):
            for j in range(1, 4):
                if i != ind[0] and j != ind[1]:
                    
                    if ind[1] < j:
                        key = get_det(matrix[1][ind[1]], matrix[1][j], matrix[2][ind[1]], matrix[2][j])
                    else:
                        key = get_det(matrix[1][j], matrix[1][ind[1]], matrix[2][j], matrix[2][ind[1]])

                    if not(abs(key) <= EPS):
                        break
            if not(abs(key) <= EPS):
                break
            
        if not(abs(key) <= EPS):
            rgAB += 1
        # rgAB += 1 if key else 0
        # print('Ранг расширенной матрицы системы равен ', rgAB)
        if rgAB != rgA:
            return [0]
        
        # Система имеет либо одно решение, либо бесконечное множество (но не любой х любой у)
        else:
            # Теперь в дело вступает Крамер
            det = get_det(a, b, c, d)
            d1 = get_det(e, b, f, d)
            d2 = get_det(a, e, c, f)
            # print('here', e,b,f,d)
            # print(d, d1, d2)
            if not(abs(det) <= EPS):
                return [2, d1 / det, d2 / det]
            else:
                # Теперь остались только случаи, когда бесконечно много решений
                
                if b == d == 0:
                    return [3, e / a]
                elif a == c == 0:
                    return [4, e / b]
                else:
                    if b != 0:
                        return [1,- a / b, e / b]
                    else:
                        return [1,- c / d, f / d]


assert main(1, 0, 0, 1, 3, 3) == [2, 3.00000, 3.00000]
assert main(2, 2, 3, -3, 6, -3) == [2, 1.00000, 2.00000]
assert main(1, 1, 1, -1, 3, -1) == [2, 1.00000, 2.00000]
assert main(1, 1, 2, 2, 1, 2) == [1, -1.00000, 1.00000]
assert main(1, 1, 1, 1, 1, 2) == [0]
assert main(0, 1, 0, 1, 2, 3) == [0]
assert main(0, 1, 0, 2, 2, 4) == [4, 2.00000]
assert main(1, 0, 2, 0, 2, 4) == [3, 2.00000]
assert main(0, 0, 0, 0, 0, 0) == [5]
assert main(0, 0, 0, 0, 1, 0) == [0]
assert main(0, 2, 0, 4, 1, 2) == [4, 0.50000]
assert main(0, 2, 0, 4, 1, 2) == [4, 0.50000]
assert main(0, 0, 2, 4, 0, 2) == [1, -0.50000, 0.50000]
assert main(2, 4, 0, 0, 2, 0) == [1, -0.50000, 0.50000]
assert main(2, 0, 3, 0, 2, 3) == [3, 1.00000]
assert main(2, 2, 3, 0, 6, 3) == [2, 1.00000, 2.00000]
assert main(1, 1, 1.5, 0, 3, 1.5) == [2, 1.00000, 2.00000]