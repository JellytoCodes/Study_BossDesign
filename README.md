# 👹 Boss AI BehaviorTree System

페이즈 기반 보스 전투 AI 시스템 설계
<br>

## 🧠 개요

이 프로젝트는 Unreal Engine의 BehaviorTree를 활용하여
보스 캐릭터의 전투 패턴을 **Phase** 단위로 구조화하고,
**연출(Task)**, **상태 감지(Service)**, **조건 분기(Decorator)**를 통해
유연하게 확장 가능한 AI 구조를 설계하는 것을 목표로 합니다.
<br>

## 🔧 핵심 구조

### ✅ 전체 트리 구성

- WakeUp Phase: 전투 시작 전 애니메이션
- Phase 트리 (1~3): 체력 비율에 따른 공격 로직 분기
- Death 트리: 체력 0 상태 전환 처리

### ✅ 구조별 담당

| 구성 요소 | 설명 |
|-----------|------|
| **Service** | `BTService_CheckPhase`: 체력 비율 감지 및 Blackboard에 PhaseKey 설정 |
| **Task** | `BTTask_PhaseSwapAnimation`: 페이즈 진입 시 애니메이션 재생 |
| **Decorator** | `BlackboardKey == PhaseX`: Phase 전용 행동 분기 |
| **Blackboard Key** | `PhaseKey`, `isCombat`, `isGroggy` 등 상태 전환 조건 사용
<br>

## 🎬 연출 설계

- `PlayAnimation` Task를 기반으로 **PlayRate**, **Montage 선택** 기능 추가
- 향후 `LevelSequence` 기반의 시네마틱 전환 구조도 고려 중
- **모든 연출 Task는 재사용 가능하게 설계**, 보스마다 세부 조정은 UPROPERTY로 설정
<br>

## 🧱 확장 고려 요소

- 약점 시스템 도입 (Groggy)
  - 일정 데미지 누적 → Controller에서 상태 강제 전환
  - BT Decorator로 행동 차단 처리
- 보스 전용 Subtree 구조화
- FPhaseData 구조체 기반 연출 데이터 통합 (WIP)
<br>

## 🧪 Troubleshooting 기록

| 날짜 | 내용 |
|------|------|
| 2025.06.14 | `SetBossInstance()` 내부 변수 대입 오류로 인해 BossWidget에 정보 미출력 / 방향 수정 후 해결 |
| 2025.06.14 | `BTService_PhaseCheck`가 작동하지 않던 원인 → `ObserverAborts` 누락으로 Decorator 반응 없음 → Self/Both 설정 후 해결 |
| 2025.06.14 | BTTask 재사용 전략 논의 → 기능이 동일하면 분기 처리, 구조가 다르면 분리하는 기준 확립 |
<br>

## 🗂️ 현재 상태

- [x] Behavior Tree Phase 구조 정리
- [x] Phase 체크용 Service 구성
- [x] 기본 애니메이션 Task 구조
- [ ] Groggy 상태 연출 처리
- [ ] PhaseSwap LevelSequence Task 구성
