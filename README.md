# 🦖 Boss AI BehaviorTree System
페이즈 기반 보스 전투 AI 시스템 설계

<br>

## 🧠 개요
BehaviorTree를 활용하여 보스 캐릭터의 전투 패턴을 **Phase** 단위로 구조화하고 유연하게 확장 가능한 AI 구조를 설계하는 것을 목표로 합니다.

<br>

## 🔧 핵심 구조

### ✅ 전체 트리 구성

| Phase            | 설명                       |
| ---------------- | ------------------------ |
| **WakeUp Phase** | 전투 시작 전 각성 연출            |
| **Phase 1**      | 체력 100% \~ N% (기본 공격 루프) |
| **Phase 2**      | 체력 N% \~ M% (패턴 변화)      |
| **Phase 3**      | 체력 M% 이하 (막타 패턴 등)       |
| **Death**        | 사망 시 연출 및 행동 종료          |

### 🧩 구조별 담당

| 타입             | 클래스명                                                         | 설명                                   |
| -------------- | ------------------------------------------------------------ | ------------------------------------ |
| **Service**    | `UBTService_PhaseCheck`                                      | 보스 체력 퍼센트를 기준으로 `PhaseKey` 값을 업데이트   |
| **Task**       | `UBTTask_PhaseSwapAnimation`                                 | 해당 Phase 진입 시 애니메이션/연출 재생 후 상태 변경    |
| **Decorator**  | Blackboard 기반 조건                                             | `BlackboardKey == PhaseX` 조건으로 분기 제어 |
| **Blackboard** | `PhaseKey`, `isCombat`, `bIsGroggy`, `bIsPhase2Transition` 등 | 상태 조건값 정의 및 활용                       |

<br>

## 🎬 연출 설계

| 항목              | 구현 방식                                             |
| --------------- | ------------------------------------------------- |
| **페이즈 진입 연출**   | Task로 구성 (`BTTask_PhaseSwapAnimation`)            |
| **애니메이션 재생 제어** | `UAnimMontage` + `PlayRate` 조정 가능 (UPROPERTY로 설정) |
| **재생 조건 제어**    | `Blackboard Bool` 사용하여 1회만 재생 처리                  |
| **확장 계획**       | `LevelSequence`, Niagara 등도 연출 Task에 포함 예정        |


<br>

## ⚔️ 전투 중 상태 변화 처리

Groggy 상태:  
약점 공격 또는 누적 데미지 발생 시 AIController에서 강제 전환  
→ bIsGroggy Blackboard Key로 BT 차단  
→ 상태 회복 후 다시 루트 트리 진입 가능  
  
Death 처리:  
HP가 0이 되면 BT 내부 트리를 완전히 변경  
애니메이션 및 연출 종료 후 Pawn Destroy 가능  

## 🧑‍💻 Author  
JellytoCodes / 2025.06  

