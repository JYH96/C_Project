[알고리즘]

이진탐색 트리 정렬 - Nlog(N)내에 가능
힙정렬.cpp)
  findmax 재귀하여 node.leff, right중에 큰 게 있으면 서로 key를 바꾼다
  
  left right 비교하여 작은 놈을 왼쪽으로 한다.
  
  언제까지? = findmax하기 전과 후를 깊은 복사로 비교해서 같으면 멈춤(Nlog(N)이하)
