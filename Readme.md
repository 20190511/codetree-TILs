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

