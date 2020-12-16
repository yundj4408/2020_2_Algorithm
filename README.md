# COMP319 / 알고리즘 / 2020 / 2학기 / 장길진
---
## HW # 1
>   ## 목표
>   1. C프로그램의 기초를 복습
>   2. Linux command line interface (CLI) 에서의 compile and execution 실습
>   3. 지적재산권 보호를 위한 학번과 이름 표시
>   4. CLI 에서의 argument 주기
>   5. 파일 입출력 실습

### [Homework1-1.c](hw1/hw1-1.c)
주어진 코드를 수정하여 자신의 학번, 이름, 학과(부)를 출력하는 C프로그램을 작성한다.

### [Homework1-2.c](hw1/hw1-2.c)
3개의 정수를 command line arguments 로 입력받고, 크기순으로 출력하는 프로그램을 작성함.


### [Homework1-3.c](hw1/hw1-3.c)
텍스트 파일을 command line argument 로 입력받고, 최소/최대/평균/분산을 계산하여 출력하
는 프로그램을 작성한다.

---

## HW # 2

>   ## 목표
>   1. char array를 이용한 문자열(string)의 입출력/비교/복사 등 기본적인 연산을 실습
>   2. (핵심) 문자열 정렬 알고리즘 구현(insertion, selection, bubble sort)


### [Homework2-1.c](hw2/hw2-1.c)
주어진 텍스트 파일에서 단어(word)들을 읽어들여 오름차순으로 정렬하고, 이를 다시 텍스트 파일로 저장하는 프로그램을 작성한다.


### [Homework2-2.c](hw2/hw2-2.c)
 hw2-1 은 고정된 크기의 2차원 배열을 사용하기 때문에 문자열을 저장하기 위해 메모리의 낭비가 심하다. 따라서 단어의 숫자가 많아지면 실행이 불가능하다. hw2-2에서는 이 문제를 해결하기 위하여 동적 메모리를 할당하는 방법으로 메모리 사용량을 최소화하는 코드를 작성한다.

---

## HW # 3

>   ## 목표
>   1. Quick sort, merge sort를 이용한 문자열 정렬 알고리즘 구현
>   2. 연속된 메모리 공간에 순차적으로 저장된 문자열 정렬 알고리즘 구현
>   3. 문자열의 길이가 고정되어 있을 경우와 가변 길이의 정렬 알고리즘 구현


### [Homework3-1.c](hw3/hw3-1.c)
주어진 텍스트 파일을 한꺼번에 메모리로 올리고(char array), 메모리의 단어들을 merge sort와 quick sort를 이용하여 오름차순으로 정렬하고, 이를 다시 텍스트 파일로 저장하는 프로그램을 작성한다.



### [Homework3-2.c](hw3/hw3-2.c)
가변 단어들을 merge sort와 quick sort를 이용하여 오름차순으로 정렬하고, 이를 다시 텍스트 파일로 저장하는 프로그램을 작성한다.


---

## HW # 5

>   ## 목표
>   1. LCS (longest common subsequence) 알고리즘을 직접 구현하여 보고 이해한다.
>   2. Circular shift를 허용한 LCS 의 변형을 구현한다.

### [Homework5.c](hw5/hw5.c)
 command-line arguments 로 주어진 두 개의 문자열의 LCS를 찾고 화면에 출력한다.

같은 문자열에 대하여 LCS-CS를 찾고 화면에 출력한다.
