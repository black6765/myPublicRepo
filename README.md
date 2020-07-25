## pcap-test

프로그램 구성 의도 및 설명
==================
* 과제 요구 사항 
    1. "TCP 패킷이 잡히는 경우에만" 정보를 출력
    2. "각각의 헤더에 있는 특정 정보"를 출력
      - Ethernet Header의 src mac / dst mac
      - IP Header의 src ip / dst ip
      - TCP Header의 src port / dst port
      - Payload(Data)의 hexadecimal value(최대 16바이트까지만)

* 과제 요구 사항에 대한 코드 구성

  - 수업 시간의 내용과 "Wireshark"를 통해 TCP 패킷만을 필터링하여 정보 획득(각 바이트의 정보)
  
  - TCP 패킷은 0x17(23) 위치에 "0x06" 패킷을 가지는 것을 확인
    -> "if(packet[23] != 0x06)" 구문을 이용해 "과제 요구 사항 1."의 TCP 패킷이 잡히는 경우만을 만족
  - TCP 패킷에서 각 바이트가 가지는 의미를 분석함
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
  
  - 과제에서 요구하진 않았지만 Ethernet Type과 IP Version and Header를 함께 출력함

* 과제 중 애로사항

  - packet에 있는 정보를 그대로 출력할 것인가?
    - packet의 정보를 바로 출력하는 방법도 있지만, 각 데이터를 분할하여 저장하는게 좀 더 효율적이라고 봄(과제 외의 경우)
    - 각 헤더에 맞는 구조체를 만들어서 memcpy를 이용하여 복사한 후 출력하도록 함
    - memcpy를 이용한 출력에서 모든 정보를 memcpy한 후 한 번에 출력하는 방법을 사용하면 데이터가 오염되는 문제 발견
      - 정확한 원인을 찾지 못해 memcpy 이후 바로 해당 정보를 출력하는 방식으로 코드를 구성
      
  - TCP 페이로드가 없는 경우 어떻게 할 것인가?
    - 과제의 '상세'에서 Data의 크기가 0여도 출력하라고 되어 있으므로, 해당 위치의 데이터를 무조건 출력하도록 하였음
      - TCP Payload의 길이를 구하여 0인 경우 출력하지 않는 것을 생각해 보았음
      - 그러나 TCP Payload 길이가 0일 때에도 0으로 패딩되는 경우가 있다는 것을 발견
      - TCP 페이로드 길이가 0일 때, 패딩이 없다면 출력하지 않고 넘어가고, 길이가 0일 때 패딩이 있다면 출력하는 코드가 필요
        - 많은 방법을 동원했지만, 페이로드에서 잘못된 값이 출력됨 
        - 이 점에 대해서는 명확한 해결책을 찾지 못하였음
    
  - packet의 시작 위치로부터 일일이 바이트를 세며 출력하지 않는 방법
    - 본인이 구성한 코드가 과제 상세사항에 언급된 "packet의 시작 위치로부터 일일이 바이트를 세며 출력하는 방법"인 것 같음
    - 코드를 구성하면서도 이러한 방법이 비효율적인 느낌이 들었으나, 해결책을 찾지는 못함
 
* 과제 결과
  - 과제에서 요구하는 출력 결과는 모두 만족시킴
  - 추가적으로 Ethernet Type과 IP Version and Header를 함께 출력함
  - Wireshark와 대조한 결과 출력 결과가 올바른 것으로 확인
