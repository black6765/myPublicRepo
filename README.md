## pcap-test

프로그램 구성 의도
==================
* 문제 요구 사항 
1. "TCP 패킷이 잡히는 경우에만" 정보를 출력
2. "각각의 헤더에 있는 특정 정보"를 출력
  - Ethernet Header의 src mac / dst mac
  - IP Header의 src ip / dst ip
  - TCP Header의 src port / dst port
  - Payload(Data)의 hexadecimal value(최대 16바이트까지만)

* 문제 요구 사항에 대한 코드 구성
  0. 수업 시간의 내용과 "Wireshark"를 통해 TCP 패킷만을 필터링하여 대략적인 정보 획득(각 바이트의 정보)
  1. TCP 패킷은 0x17(23) 위치에 "0x06" 패킷을 가지는 것을 확인
    -> "if(packet[23] != 0x06)" 구문을 이용해 "문제 요구 사항 1."의 TCP 패킷이 잡히는 경우만을 만족
  2. TCP 패킷에서 각 바이트가 가지는 의미를 분석함
    - Ethernet Header
      - src mac : 6~11
      - det mac : 0~5
      - eth type : 12~13
  
    - IP Header
      - IP Version and Header Length : 14
      - src ip : 26~29
      - dst ip : 30~33
  
    - TCP Header
      - src port : 34~35
      - dst port : 36~37
      - Payload  : 54~69

