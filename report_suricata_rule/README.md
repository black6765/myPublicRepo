## report_suricata_rule
### 과제
- test.rules 파일에 20개의 사이트를 탐지하는 룰을 만든다.
- 이후 fast.log를 확인하면서 20개의 사이트가 제대로 탐지되는지 확인을 해 본다.
- 가급적이면 평문 통신(HTTP)이 이루어 지는 사이트 뿐만 아니라 TLS 통신(HTTPS)을 하는 사이트에 대한 탐지를 구현해 본다.

### test.rules
- TLS가 적용된 사이트의 트래픽을 탐지하기 위해서 아래의 기본 틀에서 약간의 변형을 함
```
// 멘토님의 suricata rule 예시
alert tcp any any -> any 80 (msg:"gilgil.net access"; content:"GET /"; content:"Host: "; content:"gilgil.net"; sid:10001; rev:1;)
```
- port를 의미하는 80을 443으로 변경하고, flow:established; tls_sni;를 추가
- content:"GET /"; content:"Host: "; 부분 삭제
- content의 사이트 URL과 메시지를 각각의 사이트에 맞게 변경

### fast.log
- suricata를 실행하여(sudo suricata -s [룰 파일] -i [인터페이스]) 생긴 로그가 "/var/log/suricata/fast.log"에 기록됨
- 해당 로그를 tail 명령어를 이용해 추적 가능
- test.rules에 적용된 20개의 룰에 대해서 테스트 결과 로그가 남는 것을 확인할 수 있었음

