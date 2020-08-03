# send-arp-test

프로그램 구성 의도
=====

1. 계획
* 과제가 조금 어려워 보이고, 어떻게 해야할 지 감이 오지 않음
  - 필요한 구성요소를 파악한 후 작은 기능 단위로 나누기로 함
  - 센터에서 진행된 실습과 코드를 참고하여 프로그램을 구성
  - 자신(공격자)의 MAC 주소, 자신의 IP 주소, Sender의 MAC 주소가 필요함
  - 이에 따라 프로그램을 크게 4부분의 기능으로 나누기로 함
  - find_attacker_mac(자신-공격자의 MAC 주소를 얻음) / find_attacker_ip(자신의 IP 주소를 얻음) / arp_request(Sender의 MAC 주소를 얻음) / arp_reply(ARP 캐시 테이블 감염)
  
2. 과제 진행
* 실습 시간에 했던 내용을 재연해도 Sender의 인터넷이 끊기지 않았음
  - 6일 동안 실습 내용을 반복해서 했으나, ARP Infection이 발생하지 않음
  - 하지만 계속된 과정 끝에 개념적으로는 맞으나 다른 알 수 없는 네트워크 문제라 파악하고 과제를 진행
  
* 공격자의 MAC 주소와 IP 주소를 얻는 코드를 스스로 구성하고 싶었으나, 미흡한 실력으로는 구현하는 것이 어려웠음
  - 생각난 방법은 지난 시간에 배운 pcap-test의 코드를 이용하여 TCP 패킷에서 자신의 MAC 주소와 IP 주소를 얻는 방법
    - 하지만 과제 주제가 ARP이기 떄문에 TCP 패킷으로 하는 것은 주제에 벗어난 것이라고 생각
    - 코드가 너무 복잡해지고 가독성을 해칠 가능성이 있음
  - 따라서 두 함수는 검색을 통해서 찾은 코드를 이번 과제에 맞게 적절히 변형하였음
  - 출처(find_attacker_mac) : https://community.onion.io/topic/2441/obtain-the-mac-address-in-c-code/2
    - 참조한 find_attacker_mac의 코드는 16진수로 출력하는 함수였기 때문에 적절히 변형하여 MAC 주소를 문자열로 저장할 수 있도록 함
  - 출처(find_attacker_ip)  : https://technote.kr/176 
   
* ARP Request를 발생시키는 방법은 실습을 통해 배웠으나, 발생시킨 패킷을 통해 Sender의 MAC 주소를 얻는 것은 별도의 문제
  - 기본적으로 ARP 패킷을 발생시키는 코드는 이경문 멘토님의 코드를 참고
  - 문득 지난 시간에 배웠던 pcap 과제가 생각났음
  - TCP를 필터링하기 위해 사용했던 코드를 변형하면 ARP 패킷만 뽑아낼 수 있다는 생각
    - ARP Request에 대한 Reply에는 12~13 바이트에 ARP Type이 있고, Source MAC(Sender MAC)은 6~11 바이트에 존재함
    - 이렇게 받아온 MAC 주소를 문자열로 저장함

* 앞의 과정에서 얻어낸 것들을 이용하여 arp_reply 함수에서 ARP 캐시 테이블을 감염시키는 공격 진행
  - 기본적으로 ARP 패킷을 발생시키는 코드는 이경문 멘토님의 코드를 참고
  - ARP 캐시 테이블 Infection은 ARP Reply를 Sender에게 보내 자신(Attacker)의 MAC 주소를 게이트웨이로 착각하게 하는 공격이라고 파악
    - 이에 따라 적절히 코드를 작성
    
3. 실행 결과
  - 실행 결과 성공적으로 자신의 MAC, IP 주소를 가져왔으며 이를 이용하여 Sender의 MAC 주소를 얻음
  - arp_reply를 통해 Sender의 ping 작동이 멈추는 것을 확인
  - arp -an 명령어를 통해 ARP 캐시 테이블을 조작한 것을 확인
