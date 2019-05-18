class Solution:
    def flowShop(self, M):
        '''
        n tasks, 2 machines. To minimize the time it taks for the flow line
        :param M: M[i][0/1]--the time it takes for the ith task on the 0/1th machine
            i: from 0 to n - 1
        '''
        n = len (M)
        self.bestX = [] # the best order
        self.bestT = float('inf') # the shortest time
        currX = [-1 for i in range (n)]
        tag = [False for i in range (n)]
        self.backTrack(M, 0, currX, 0, tag, 0)
        return (self.bestT, self.bestX)


    def backTrack(self, M, i, currX, currT, tag, end1):
        '''
        select which one to put into currX[i]
        :param end2_list: end2_list[j]--the end time of the no.j task on machine 2
        :param end1: the end time of the task on machine 1; machine 1 is always busy
        '''
        n = len (M)
        if i > n - 1:
            # has went outside
            # the case when currT > bestT has been excluded outside
            self.bestX = currX.copy()
            self.bestT = currT
            # print("-------------temp result start---------------")
            # print (currT, self.bestT)
            # print (currX, self.bestX)
            # print("-------------temp result end---------------")
            return

        old_end1 = end1
        old_currT = currT
        for j in range (n):
            if tag[j] is False:
                # time of the last one on machine2 vs. this one on machine 1
                longest = M[j][0] if i == 0 or M[currX[i - 1]][1] < M[j][0] else M[currX[i-1]][1]
                currT = end1 + longest + M[currX[j]][1]
                if currT < self.bestT:
                    currX[i] = j
                    end1 = currT - M[currX[j]][1]
                    tag[j] = True
                    self.backTrack(M, i + 1, currX, currT, tag, end1)
                    tag[j] = False
                    end1 = old_end1
                    currX[i] = -1
                currT = old_currT

        # print (currT, self.bestT)
        # print (currX, self.bestX)

if __name__ == "__main__":
    M = [[2, 1], [3, 1], [2, 3]]
    bestT, bestX = Solution().flowShop (M)
    print ("-------------Solution-------------")
    print (bestT, bestX)
    print ("-------------Solution-------------")



































