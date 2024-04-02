[![코드트리|실력진단-qwg724](https://banner.codetree.ai/v1/banner/qwg724)](https://www.codetree.ai/profiles/qwg724)

## 피드백 
---
1. 도형관련 잘못된 접근에 대한 피드백 -> 문제에 충실하게 풀자 (혼자 식 만들어서 푸는게 리스크가 큼)
- 문제에 정사각형을 만들어서 푸는데 시간복잡도가 널널하면 한 직접 문제대로 적용해서 풀어보는게 좋다.
 ```C
  1. minPos 잡는 부분 잘못된 접근이 계속 나옴
	--> 처음에는 단순히 rx, ry가 큰 애로 잡았다가 오류가 남..
	--> 두 번째 시도에서는 단순히 혼자 해석해서 max(t1, t2) 로 두다가 직사각형이 안만들어져서 오류가남
	--> 세 번째 시도에서는 포기하고 직사각형을 미리 그려본 후 문제 그대로 좌상단 좌표를 문제와 비교를 해봤었음 (단, 에러처리는 뒤에 뒀었음)
	--> 네 번째 시도에서는 위에서 음수값이 나오는 경우 세팅 과정에서 문제가 생기게 되어서 예외처리도 뒤에 뒀어야함..
 ```
 
2. 문제애서 얻은 피드백
```C
A. 중간 debug 매크로 이용해서 찍어보는 과정은 매우 굿
B. 이동, 회전 부분 함수 분할 부분도 매우 굿 (함수 분할 매우 좋음)
C. --> 다만 문제에 정사각형 좌표를 찍어보는 문제는 쟁점을 잘 파악해서 좌상단, 우하단을 파악한 뒤에 
	>> 문제에 충실하게 한 케이스 당 적용해보기 *시간복잡도가 허용해준다면..
D. 회전 문제의 피드백
	>> 회전은 평행이동이 고려된 경우에는 똑같이 넣어주면 되지만
		좌표 하나를 이동시켜야한다면 (시계방향의 경우)
		int mx = curX-a, my = curY-b;
		int mnx = my+a, mny = r - mx - 1 + b;
		a = {mnx, mny}와 같이 정의될 수 있다.

E. vector 활용

1. 특정 영역 삭제 방법
	src.end() - move_cnt 와 같이 삭제 가능. (인덱스 방식으로 접근해서 삭제 가능
  ex) dst.insert(dst.end(), src.end() - move_cnt, src.end()); 
2. 시간복잡도
 > 접근 O(1) <-- 배열이라서 그럼
 > 맨 뒤에 추가, 맨 뒤 삭제 : O(1)
 > 중간 요소 삭제 O(N)
>> Technique :: vector 형태로 사용할 수 있지만 초기에 순서를 반대로 넣어줘야한다면.. 그때만 반대로 넣어라.
```

---
# 푼 문제들
|기록분류|이름|티어|유형|상태|최근 제출 코드|
|---|---|---|---|---|---|
|기출문제|[코드트리 오마카세](https://www.codetree.ai/training-field/frequent-problems/problems/codetree-omakase)|![Platinum3][p3]|`Simulation` `Sort` `HashMap` `HashSet`|![Passed][passed]|[링크](https://github.com/20190511/codetree-TILs/blob/main/240320/%EC%BD%94%EB%93%9C%ED%8A%B8%EB%A6%AC%20%EC%98%A4%EB%A7%88%EC%B9%B4%EC%84%B8/codetree-omakase.cpp)|
|기출문제|[코드트리 오마카세](https://www.codetree.ai/training-field/frequent-problems/problems/codetree-omakase)|![Platinum3][p3]|`Simulation` `Sort` `HashMap` `HashSet`|![Passed][passed]|[링크](https://github.com/20190511/codetree-TILs/blob/main/240321/%EC%BD%94%EB%93%9C%ED%8A%B8%EB%A6%AC%20%EC%98%A4%EB%A7%88%EC%B9%B4%EC%84%B8/codetree-omakase.cpp)|
|일반 연습|[격자 밟기](https://www.codetree.ai/training-field/search/problems/stepping-on-grid)|![Gold5][g5]|`Backtracking`|![Passed][passed]|[링크](https://github.com/20190511/codetree-TILs/blob/main/240321/%EA%B2%A9%EC%9E%90%20%EB%B0%9F%EA%B8%B0/stepping-on-grid.cpp)|
|기출문제|[루돌프의 반란](https://www.codetree.ai/training-field/frequent-problems/problems/rudolph-rebellion)|![Gold2][g2]|`Simulation`|![Passed][passed]|[링크](https://github.com/20190511/codetree-TILs/blob/main/240323/%EB%A3%A8%EB%8F%8C%ED%94%84%EC%9D%98%20%EB%B0%98%EB%9E%80/rudolph-rebellion.cpp)|
|기출문제|[코드트리 메신저](https://www.codetree.ai/training-field/frequent-problems/problems/codetree-messenger)|![Platinum4][p4]|`Tree` `Simulation`|![Failed][failed]|[링크](https://github.com/20190511/codetree-TILs/blob/main/240325/%EC%BD%94%EB%93%9C%ED%8A%B8%EB%A6%AC%20%EB%A9%94%EC%8B%A0%EC%A0%80/codetree-messenger.cpp)|
|기출문제|[왕실의 기사 대결](https://www.codetree.ai/training-field/frequent-problems/problems/royal-knight-duel)|![Gold3][g3]|`BFS` `Simulation`|![Passed][passed]|[링크](https://github.com/20190511/codetree-TILs/blob/main/240325/%EC%99%95%EC%8B%A4%EC%9D%98%20%EA%B8%B0%EC%82%AC%20%EB%8C%80%EA%B2%B0/royal-knight-duel.cpp)|
|기출문제|[메이즈 러너](https://www.codetree.ai/training-field/frequent-problems/problems/maze-runner)|![Gold3][g3]|`Simulation`|![Passed][passed]|[링크](https://github.com/20190511/codetree-TILs/blob/main/240327/%EB%A9%94%EC%9D%B4%EC%A6%88%20%EB%9F%AC%EB%84%88/maze-runner.cpp)|
|기출문제|[포탑 부수기](https://www.codetree.ai/training-field/frequent-problems/problems/destroy-the-turret)|![Gold1][g1]|`Simulation`|![Passed][passed]|[링크](https://github.com/20190511/codetree-TILs/blob/main/240327/%EB%A9%94%EC%9D%B4%EC%A6%88%20%EB%9F%AC%EB%84%88/maze-runner.cpp)|
|기출문제|[코드트리 빵](https://www.codetree.ai/training-field/frequent-problems/problems/codetree-mon-bread)|![Gold2][g2]|`BFS` `Simulation`|![Passed][passed]|[링크](https://github.com/20190511/codetree-TILs/blob/main/240401/%EC%BD%94%EB%93%9C%ED%8A%B8%EB%A6%AC%20%EB%B9%B5/codetree-mon-bread.cpp)|
|기출문제|[산타의 선물 공장 2 ](https://www.codetree.ai/training-field/frequent-problems/problems/santa-gift-factory-2)|![Platinum5][p5]|`Double LinkedList` `Simulation`|![Passed][passed]|[링크](https://github.com/20190511/codetree-TILs/blob/main/240402/%EC%82%B0%ED%83%80%EC%9D%98%20%EC%84%A0%EB%AC%BC%20%EA%B3%B5%EC%9E%A5%202/santa-gift-factory-2.cpp)|
|기출문제|[싸움땅](https://www.codetree.ai/training-field/frequent-problems/problems/battle-ground)|![Gold2][g2]|`Simulation`|![Passed][passed]|[링크](https://github.com/20190511/codetree-TILs/blob/main/240402/%EC%8B%B8%EC%9B%80%EB%95%85/battle-ground.cpp)|



[b5]: https://img.shields.io/badge/Bronze_5-%235D3E31.svg
[b4]: https://img.shields.io/badge/Bronze_4-%235D3E31.svg
[b3]: https://img.shields.io/badge/Bronze_3-%235D3E31.svg
[b2]: https://img.shields.io/badge/Bronze_2-%235D3E31.svg
[b1]: https://img.shields.io/badge/Bronze_1-%235D3E31.svg
[s5]: https://img.shields.io/badge/Silver_5-%23394960.svg
[s4]: https://img.shields.io/badge/Silver_4-%23394960.svg
[s3]: https://img.shields.io/badge/Silver_3-%23394960.svg
[s2]: https://img.shields.io/badge/Silver_2-%23394960.svg
[s1]: https://img.shields.io/badge/Silver_1-%23394960.svg
[g5]: https://img.shields.io/badge/Gold_5-%23FFC433.svg
[g4]: https://img.shields.io/badge/Gold_4-%23FFC433.svg
[g3]: https://img.shields.io/badge/Gold_3-%23FFC433.svg
[g2]: https://img.shields.io/badge/Gold_2-%23FFC433.svg
[g1]: https://img.shields.io/badge/Gold_1-%23FFC433.svg
[p5]: https://img.shields.io/badge/Platinum_5-%2376DDD8.svg
[p4]: https://img.shields.io/badge/Platinum_4-%2376DDD8.svg
[p3]: https://img.shields.io/badge/Platinum_3-%2376DDD8.svg
[p2]: https://img.shields.io/badge/Platinum_2-%2376DDD8.svg
[p1]: https://img.shields.io/badge/Platinum_1-%2376DDD8.svg
[passed]: https://img.shields.io/badge/Passed-%23009D27.svg
[failed]: https://img.shields.io/badge/Failed-%23D24D57.svg
[easy]: https://img.shields.io/badge/쉬움-%235cb85c.svg?for-the-badge
[medium]: https://img.shields.io/badge/보통-%23FFC433.svg?for-the-badge
[hard]: https://img.shields.io/badge/어려움-%23D24D57.svg?for-the-badge

