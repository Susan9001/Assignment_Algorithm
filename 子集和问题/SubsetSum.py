class Solution(object):
    def subsetSum(self, c, numset):
        numlist = list (filter (lambda x: x < c, numset))
        n = len (numlist)

        self.restag = "No Solution!"
        currtag = [False for i in range (n)]
        if self.__dfs (0, c, numlist, currtag, 0):
            self.restag = list (filter (lambda x: x > 0, 
                [self.restag[i] * numlist[i] for i in range(n)]))
        return self.restag

    def __dfs(self, i, c, numlist, currtag, currsum):
        n = len (numlist)
        if i > n - 1: # 遍历完所有了还是不行
            return False
        if currsum + numlist[i] == c:
            currtag[i] = True
            self.restag = currtag.copy()
            return True
        if currsum + numlist[i] < c:
            currtag[i] = True
            isOK = self.__dfs(i + 1, c, numlist, currtag, currsum + numlist[i])
            if isOK:
                return True
            currtag[i] = False
        return self.__dfs (i + 1, c, numlist, currtag,currsum)


if __name__ == '__main__':
    input_list = []
    with open ("input.txt", "r", encoding='utf-8') as f:
        input_list = f.read().split()
    c = int (input_list[1])
    numset = [int(input_list[i]) for i in range (2, len (input_list))]

    result = Solution ().subsetSum (c, numset)

    with open ("output.txt", "w", encoding='utf-8') as f:
        f.write(" ".join(list (map (lambda x: str(x), result))))



















