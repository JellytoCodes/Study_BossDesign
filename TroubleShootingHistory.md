# ✅ [250614 TroubleShooting]

<br>

## 📌 BossWidget이 화면에 출력안되는 문제  

### 🎯 원인  
&nbsp;&nbsp;→ SetBossInstance() 함수 내부에서 변수 대입 방향 오류  
&nbsp;&nbsp;→ boss = bossInstance;로 작성되어 bossInstance = nullptr 상태 유지  

<br>

### ⚠️ 부작용
&nbsp;&nbsp;→ boss 상태 변환 반영 시 nullptr 접근으로 크래시 발생

<br>

### 🛠 해결 방안
&nbsp;&nbsp;→ Setter 함수 내 변수 방향 수정

```cpp
void SetBossInstance(AEnemy_Boss* inBoss) { bossInstance = inBoss; }
```

<br>

### 🔎 체크 포인트
&nbsp;&nbsp;**✔️ 변수 명명 규칙 : 함수 매개 변수에는 InBoss, InTarget처럼 접두어 사용으로 혼동 방지**  
