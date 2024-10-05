//https://school.programmers.co.kr/learn/courses/30/lessons/340212
/*
  이진탐색 이용 범위 찾기
  중요한건 minVal 이 계속 갱신이 안되면서 같은 값으로 갱신되는 지점에서 break를 걸어줘야한다.
*/
# 1833 ~ 1914

def solveTime(diffs, times, curL):
    saveT = 0
    
    prevT = 0
    for i in range(len(diffs)):
        pro = diffs[i]
        t = times[i]
        if pro <= curL:
            saveT += t
            continue
        else:
            diffTime = pro - curL
            if i >= 1:
                prevT = times[i-1]
                
            saveT += (t + diffTime*(prevT+t))
            
    return saveT
    
def solution(diffs, times, limit):
    minLevel = 1
    maxLevel = 100000
    
    answer = (minLevel + maxLevel) // 2
    
    cnt = 100
    while minLevel < maxLevel and cnt > 0:
        cnt  -= 1
        t = solveTime(diffs, times, answer)
        #print(f"t={t}, minLevel={minLevel} maxLevel={maxLevel} curLevel={answer}")
        if t < limit:
            maxLevel = answer
            
        elif t > limit:
            if minLevel == answer:
                answer = maxLevel
                break
            minLevel = answer
            
        else:
            maxLevel = minLevel = answer
            break
            
        if minLevel >= maxLevel:
            break
        
        answer = (maxLevel + minLevel) // 2
        
            
            
        
    
    return answer
