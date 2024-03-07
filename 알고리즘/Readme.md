[알고리즘]

이진탐색 트리 정렬 - Nlog(N)내에 가능


힙정렬.cpp)

  findmax 재귀하여 node.leff, right중에 큰 게 있으면 서로 key를 바꾼다
  
  left right 비교하여 작은 놈을 왼쪽으로 한다트.
  
  언제까지? = findmax하기 전과 후를 깊은 복사로 비교해서 같으면 멈춤(Nlog(N)이하)


머지소트.cpp)

  divide(int* array, int start, int end)
  start==end가 될때까지 재귀하며 좌반, 우반으로 나누어 merge함수 실행

  merge(int* array, int start, int mid, int end)
  array[start:mid - start + 1], array[mid + 1:end - mid]로 나누어
  새 배열로 복제 후 둘 중 작은 것으로 array를 갱신
