# vending-machine

프로그램 구성의도
=====

## 1. 계획
  - 실습시간에 이미 대부분의 내용을 디루었고, 몇 가지 부분만 추가하면 되는 상황 
  - 과제 자체가 캐쥬얼하고 GUI로 직관적이었기 때문에 그다지 어렵지 않았음
  - 하지만, C++에 대해 잘 모르는 것은 약간의 벽으로 다가왔음
  - 만들어야 할 부분은 Reset을 통해 거스름돈을 계산하여 출력하는 기능과 상품을 구매할 수 없을 때 버튼을 비활성화 시키는 것
  
## 2. 구현
  - QtCreator를 이용헤 GUI를 구현함
  - money에 값을 더해주는 것과, ui를 display 하는 기능들은 반복적인 기능으로, 수업시간에 언급하셨듯 widget.h에 하나의 changeMoney 함수로 만들어서 사용함
  - changeMoney 함수에 #define을 통해 정의된 각 상품들의 가격을 if 문으로 비교하여 버튼을 비활성화 시킴 : setEnabled(false)
    - 한 번 비활성화 된 버튼이 다시 활성화되지 않는 문제 : if와 else문을 통해 비교하면서 각 상황에 따라 버튼을 활성/비활성화
    - Reset 버튼에 출력 : sprint를 통해 각 거스름돈의 내용을 temp에 저장한 후 m.information을 이용해 출력함
  - Reset 버튼을 통해 거스름 돈을 계산하는 것은 while문과 - 연산을 이용한 간단한 그리디 알고리즘으로 구현
    - 정해진 금액이 500, 100, 50, 10으로 그리디 알고리즘을 통해서도 항상 최적해를 구할 수 있음
  - 별도로 Hello라는 버튼을 통해 제작자의 정보가 출력될 수 있도록 함
  
## 3. 소감
  - C++에 익숙하지 않아 몇 가지 막히는 부분이 있었지만, 과제 자체의 난이도가 낮기 때문에 금방 해결함
  - Qt Creator를 이용해보긴 하였으나, 모든 코딩 과정을 Qt로 해보는 것은 처음이라서 새로운 경험이 되었음(아주 편함)
  - ARP 스푸핑으로 고통받던 두뇌를 마사지하는 기분(멘토님 감사합니다)

## 4. Qt Creator에서 실행이 안될 때 다음 명령어를 실행
`# g++`
'''sudo apt install g++'''

# libpcap-dev
sudo apt install libpcap-dev

# libssl-dev
sudo apt install libssl-dev

# opengl
sudo apt install libglu1-mesa-dev

# libnetfilter-queue
sudo apt install libnetfilter-queue-dev

# google test
sudo apt install libgtest-dev
