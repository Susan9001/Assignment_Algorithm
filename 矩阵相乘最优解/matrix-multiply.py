#!/usr/bin/python3
#vim:set fileencoding=utf-8 :

def bestMultiply_0(matrix):
    '''
    用最低的时间复杂度进程矩阵相乘
    时间复杂度用m*p*n来算(m*p, p*n的俩矩阵)
    动态规划思想
    :param matrix: [[rownum0, colnum0], [rownum1, colnum1], ...]
    :ret: 时间复杂度
    '''
    n = len (matrix)
    dp = [[0 for j in range (n)] for i in range (n)] # dp[i][j]: 从i乘到j
    for interval in range (1, n):
        for i in range (0, n - interval):
            j = i + interval
            dp[i][j] = dp[i][i] + dp[i+1][j] + matrix[i][0] * matrix[i][1] * matrix[j][1] # 初始化一个
            for k in range (i+1, j):
                curr_sum = dp[i][k] + dp[k + 1][j] + matrix[i][0] * matrix[k][1] * matrix[j][1]
                dp[i][j] = min(curr_sum, dp[i][j]) 
    for row in dp:
        for num in row:
            print (num, end='\t')
        print ("\n")
    return matrix[0][n - 1]

def bestMultiply_1(matrix):
    '''
    用备忘录的方法
    '''
    # TODO
    

if __name__ == "__main__":
    matrix = [[30, 35], [35, 15], [15, 5], [5, 10], [10, 20], [20, 25]]
    res = bestMultiply_0 (matrix)
    print (res)














