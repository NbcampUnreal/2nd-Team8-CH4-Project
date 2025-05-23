# 팀 프로젝트 KPT 회고록

## Keep (잘한 점)
- Git에서 변경사항을 풀 리퀘스트(PR)로 머지하여 충돌이 비교적 적었다.  
- 매일 스크럼 미팅으로 진행 상황을 공유할 수 있어 좋았다.  
- 커밋과 이슈 정리를 통해 각자 맡은 부분의 진행과 문제점을 파악할 수 있어 프로젝트 이해도가 높아졌다.  
- 머지 및 풀 리퀘스트 과정에서 충돌 해소를 위한 좋은 지표가 되었다.  
- GitHub 이슈 기능을 활용해 해야 할 일을 정리한 점이 매우 좋았다.  
- PR로 머지할 때 다른 사람과 확인하는 과정이 좋았다.  
- Subsystem, ActorComponent로 기능을 분리해 충돌 해결과 재사용에 용이했다.  
- 기능을 컴포넌트로 세분화하여 오류 발생을 최소화했다.  
- 언리얼 버전, Git 규칙을 사전에 팀원들과 협의하여 오류를 줄였다.  
- 액터 이름 규칙(예: 접두사 활용)으로 구성 요소를 명확히 하여 가독성을 높였다.  
- GitHub 이슈 분리 및 역할 할당이 효과적이었다.  
- 매일 회의로 작업 상황을 공유하며 문제점 공유가 원활했다.  
- Git 컨벤션, 코드 컨벤션, 파일 경로 등 협업 룰을 사전에 정해두어 프로젝트 진행에 도움이 되었다.  
- 협업 룰을 자세히 정한 점과 Rebase 활용의 필요성을 인지한 점도 긍정적이었다.

---

## Problem (문제점)
- 템플릿 사용 시 충돌 발생이 불가피했으며, 작업 중인 내용 공유 부족으로 충돌 감소에 어려움이 있었다.  
- 브랜치 재사용 금지 룰을 제대로 지키지 못한 점도 아쉬웠다.  
- 바이너리 파일 충돌 시 문제 파악이 어려웠다.  
- 템플릿 구조 파악에 시간이 많이 소요되었고, 싱글/멀티 환경을 모두 고려한 설계가 부족했다.  
- 언리얼 에셋(.uasset) 병합 시 충돌 해결이 매우 불편했다.  
- 블루프린트로 핵심 코드를 구현한 것은 바람직하지 않다는 점을 재인식했다.  
- 프로젝트 초반 이슈 및 시간 관리가 부족해 진행에 어려움이 있었다.  
- 모든 기능이 특정 블루프린트에 몰려 유지보수가 어려웠다.  
- 시간 관리 미흡으로 아이디어 구현이 부족했다.  
- 협업 룰 미준수 문제 발생.  
- Git 기본 기능 숙련도 부족으로 팀에 부담이 되었음.  
- 디버깅 능력 향상이 필요함.

---

## Try (개선 및 시도할 점)
- 브랜치 머지 후 삭제 및 재생성 습관화.  
- Git 락 기능 활용 검토.  
- 작업 계획 세분화 및 시간 분배 철저히 하여 누락 방지.  
- 중단점 활용 등 디버깅 능력 향상 노력.  
- Git 락 기능 공부 및 적용 시도.  
- 설득을 위한 상세 다이어그램 및 토론 진행.  
- 이슈 및 시간 관리 명확화.  
- 유지보수 어려운 블루프린트는 처음부터 C++과 병행하여 재구성.  
- 개발 우선순위 및 일정 조율을 팀원에게 즉시 공유.  
- 작업 중인 파일에 락 걸기 및 작업 내용 공유 강화.  
- 코드 및 블루프린트 작성 시 정리 철저.  
- 중단점과 로그 활용한 디버깅 강화.  
- 블루프린트 동시 수정 구조 지양.  
- 언리얼 Git 플러그인 및 마일스톤 활용 검토.  
- 템플릿 대신 자체 구조 개발 고민.
