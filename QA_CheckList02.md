# AVaOut: Avatar Out — QA 체크리스트

- **게임**: AVaOut: Avatar Out
- **엔진**: Unreal Engine 5.6.1
- **아키텍처**: Listen Server · Steam OSS · GAS · StateTree AI
- **최대 인원**: 4인 협동 멀티플레이
- **작성일**: 2026-04-28

---

## 우선순위 정의

| 등급 | 정의 |
|------|------|
| **P0-Critical** | 게임 진행 불가 — 크래시, 무한 루프, 세이브 데이터 손실 |
| **P1-High** | 핵심 기능 오작동 — 우회 방법 없음 |
| **P2-Medium** | 주요 기능 일부 오작동 (우회 가능) 또는 부가 기능 오류 |
| **P3-Low** | 사소한 문제 — 게임 진행에 영향 없음 |

---

## 체크리스트

### 1. 세션 / 로비

| 영역 | 카테고리 | 우선순위 | 테스트케이스 |
|------|----------|----------|--------------|
| 멀티 | 네트워크 | P0 | **호스트 강제 종료(Alt+F4)** 시 클라이언트 전원이 크래시 없이 메인메뉴로 복귀되는지 확인 |
| 멀티 | 네트워크 | P0 | `HandleNetworkFailure` 핸들러 — Steam 네트워크 단절 시 게임 크래시 없이 에러 UI 표시 후 메인메뉴 복귀 |
| 멀티 | 기능 | P0 | `bOpInProgress` 재진입 가드 — FindSessions 진행 중 HostSession 동시 호출 시 크래시 없이 무시되는지 확인 |
| 멀티 | 기능 | P1 | 비밀번호 방 생성 후 올바른 비밀번호로 입장 성공, 틀린 비밀번호로 입장 차단 (MD5 검증) |
| 멀티 | 기능 | P1 | `KEY_IN_GAME` 플래그 — 스테이지 진행 중인 방에 새 플레이어 입장 시도 시 차단되는지 확인 |
| 멀티 | 기능 | P1 | Steam 초대(`ShowInviteUI`) — 초대 수락 후 `CachedInviteResult`로 세션 자동 참가 성공 |
| 멀티 | 기능 | P1 | 세션 파괴 후 재호스팅(`bPendingRehost`) — 로비 재진입 시 기존 방 설정(방 이름, 비밀번호, 인원)이 유지되는지 확인 |
| 멀티 | 기능 | P2 | `FindSessionsAuto` — LAN/Steam 환경 자동 분기 시 각각 올바른 결과 목록 반환 |
| 멀티 | 기능 | P2 | 방 목록 `GetServerNameByIndex` — 한글 방 이름 인코딩(`EncodeRoomNameForSession`) 후 UI에 정상 표시 |
| 멀티 | 기능 | P2 | `UpdateCurrentPlayers` — 플레이어 입장/퇴장 시 세션 메타데이터의 현재 인원이 즉시 갱신 |
| 멀티 | UI | P2 | 세션 검색 중 `IsFinding()` == true일 때 로딩 스피너 표시, 완료 시 자동 해제 |
| 멀티 | 기능 | P3 | `CancelFind` — 검색 도중 취소 버튼 클릭 시 UI 락 없이 정상 종료 |

---

### 2. 플레이어 캐릭터 — 이동 및 GAS

| 영역 | 카테고리 | 우선순위 | 테스트케이스 |
|------|----------|----------|--------------|
| 싱글 | 기능 | P1 | 스프린트 → 걷기 → 달리기 Gait 전환이 애니메이션 끊김 없이 정상 동작 |
| 멀티 | 네트워크 | P1 | `Replicated EGait` — 호스트·클라이언트 화면에서 상대방 Gait 상태가 동기화 |
| 멀티 | 네트워크 | P1 | `ServerRPC_SetInputState` (Reliable) — 고지연(300ms+) 환경에서 스프린트/걷기 입력이 서버에 정확히 반영 |
| 싱글 | 기능 | P1 | 파쿠르(벽 오르기, 점프, 스프린트, 웅크리기) 각 Ability가 GAS InputID 바인딩으로 정상 발동 |
| 멀티 | 네트워크 | P2 | **Local Prediction** — 파쿠르 Ability 발동 시 클라이언트 예측 이동 후 서버 보정 시 눈에 띄는 위치 오차 없음 |
| 멀티 | 네트워크 | P2 | `Replicated LandVelocity / bJustLanded` — 착지 이벤트가 모든 클라이언트에서 동일 타이밍에 재생 |
| 멀티 | 네트워크 | P2 | `OnRep_Controller` — 클라이언트 재접속 후 캐릭터 빙의(Possess)가 정상적으로 이루어지는지 확인 |
| 싱글 | 기능 | P2 | `CalcCamera` 오버라이드 — 파쿠르 중 카메라 클리핑·튀는 현상 없음 |
| 멀티 | 성능 | P3 | Motion Matching 캐릭터 4명 동시 구동 시 프레임 드랍(30fps 이하) 발생 여부 |

---

### 3. GAS — AttributeSet (체력·스태미나·속도)

| 영역 | 카테고리 | 우선순위 | 테스트케이스 |
|------|----------|----------|--------------|
| 싱글 | 기능 | P0 | 체력 0 도달 시 `PostGameplayEffectExecute → OnPlayerDeath` 델리게이트 발화 → 사망 처리 흐름 완전 실행 |
| 멀티 | 네트워크 | P1 | `ReplicatedUsing=OnRep_Health` — 피격 후 체력 변화가 모든 클라이언트 HUD에 동일하게 반영 |
| 멀티 | 네트워크 | P1 | `ReplicatedUsing=OnRep_Stamina` — 스프린트 소비 및 회복이 서버·클라이언트 간 수치 불일치 없음 |
| 싱글 | 기능 | P1 | `StaminaLockoutPercent(25%)` — 스태미나 25% 이하 시 스프린트 잠금, 회복 후 재활성화 |
| 멀티 | 네트워크 | P2 | 속도 Attribute(`WalkSpeed / RunSpeed / SprintSpeed`) Replication — 속도 변경 GameplayEffect 적용 후 모든 클라이언트에서 실제 이동속도 반영 |
| 멀티 | 네트워크 | P2 | `PreAttributeChange` — 체력·스태미나 클램핑(0~Max)이 서버·클라이언트 양쪽에서 동일하게 동작 |
| 싱글 | 기능 | P2 | 아이템 사용 `AddHealthClass` GameplayEffect — 체력 회복 수치가 DataTable 정의 값과 일치 |

---

### 4. 인벤토리

| 영역 | 카테고리 | 우선순위 | 테스트케이스 |
|------|----------|----------|--------------|
| 싱글 | 기능 | P1 | 아이템 획득 → 슬롯 채우기 → 사용 → 버리기 전 과정 정상 동작 |
| 멀티 | 네트워크 | P1 | `ReplicatedUsing=OnRep_Slots` — 아이템 획득 직후 다른 클라이언트 화면에서 해당 슬롯 동기화 |
| 멀티 | 네트워크 | P1 | `UseInventoryItem_Server` (Reliable) — 사용 처리 후 클라이언트·서버 슬롯 수량 정합성 |
| 멀티 | 네트워크 | P1 | `DropInventoryItem_Server` (Reliable) — 드랍된 아이템 액터가 서버 위치에 스폰, 모든 클라이언트에서 가시 |
| 멀티 | 네트워크 | P2 | `Multicast_PlayInventorySound` (Unreliable) — 패킷 손실 시 사운드 미재생만 발생, 기능적 오작동 없음 |
| 멀티 | 기능 | P2 | 사망 시 `CharDead → bDroppedOnDeath` — 인벤토리 전체 드랍, 재접속 시 슬롯 중복 없음 |
| 멀티 | 네트워크 | P2 | `ServerSetSelectedSlot` — 슬롯 선택 상태(`SelectedSlotIndex`) 서버 동기화, HUD 슬롯 강조 표시 일치 |
| 싱글 | 기능 | P2 | 연료(`FuelAmount`) 아이템이 트레인 연료 보충에 올바른 수치로 반영 |
| 멀티 | 기능 | P3 | 인벤토리 꽉 찬 상태에서 추가 획득 시 "슬롯 없음" UI 피드백 표시 |

---

### 5. 레벨 전환 & 데이터 지속성

| 영역 | 카테고리 | 우선순위 | 테스트케이스 |
|------|----------|----------|--------------|
| 멀티 | 네트워크 | P0 | **레벨 이동 중 클라이언트 연결 끊김** 시 서버 `PersistentInventory` 데이터 손실 없이 유지 |
| 멀티 | 기능 | P1 | `SaveInventoryBeforeTravel` → 레벨 이동 → `ApplySlotsFromSave` — 아이템·수량이 100% 복원 |
| 멀티 | 기능 | P1 | `SaveHealthBeforeTravel` → 레벨 이동 → 체력 복원(`bHasPersistentHealth`) — 체력 수치 정합성 |
| 멀티 | 기능 | P1 | `bInsideTravelSafeZone` — 안전 구역 내 플레이어만 레벨 이동, 구역 밖 플레이어 차단 처리 |
| 멀티 | 네트워크 | P2 | `CopyProperties` (PlayerState) — SeamlessTravel 후 LobbyJoinOrder·IsLobbyHost 플래그 보존 |
| 멀티 | 기능 | P2 | 레벨 전환 후 `RunResetTrigger OnRep` — 패시브 능력치 전체 리셋이 모든 클라이언트에서 동일 타이밍 실행 |
| 멀티 | 기능 | P2 | 레벨 전환 후 Mutable 커스터마이징 외형이 유지되는지 확인 (CharacterCustomizingData Replicated) |

---

### 6. 사망 / 관전 / 부활

| 영역 | 카테고리 | 우선순위 | 테스트케이스 |
|------|----------|----------|--------------|
| 멀티 | 기능 | P0 | 4명 전원 사망 시 `bIsStageFailed` Replication → `OnStageFailed` 델리게이트 → 스테이지 실패 UI 표시 |
| 멀티 | 네트워크 | P1 | `MulticastRPC_EnterRagdoll` (Reliable) — 사망 후 Ragdoll이 모든 클라이언트에서 동일하게 전환 |
| 멀티 | 네트워크 | P1 | `MulticastRPC_PlayDeathMontage` (Reliable) — 사망 몽타주가 모든 클라이언트에서 재생 |
| 멀티 | 기능 | P1 | `ClientRPC_HandleDeathView` — 사망 후 본인 클라이언트에만 사망 카메라 전환 |
| 멀티 | 기능 | P1 | `ServerRPC_RequestSpectate` → `ClientRPC_SetSpectateTarget` — 관전 대상 전환이 서버·클라이언트 양방향으로 정상 처리 |
| 멀티 | 기능 | P1 | `Server_RequestRevive` → `Client_OnRevived` — 공유 부활 횟수 차감 후 정상 부활, HUD 카운터 갱신 |
| 멀티 | 네트워크 | P1 | `TryConsumeSharedReviveCount` 동시 다중 요청 — Race Condition으로 부활 횟수가 음수가 되지 않는지 확인 |
| 멀티 | 네트워크 | P2 | `ServerRPC_UpdateCameraView` (Unreliable) + `FVector_NetQuantize10` — 관전 카메라 위치가 실시간으로 부드럽게 동기화 |
| 멀티 | UI | P2 | `RespawnCountdownWidget` — 부활 카운트다운 타이머 UI가 사망 즉시 노출, 0초 후 자동 부활 처리 |
| 멀티 | 기능 | P2 | `RequestSpectateNext(bForward)` — 생존 플레이어가 0명일 때 관전 대상 없음 처리(`NoValidTarget`) |
| 멀티 | 네트워크 | P2 | `OnRep_StreamEnabled` — 관전 스트림 ON/OFF 상태가 관전자·피관전자 양쪽에서 정확히 동기화 |
| 멀티 | UI | P3 | 관전 카메라 스무딩(PosInterpSpeed=12, RotInterpSpeed=12) — 타겟 전환 시 카메라 튀는 현상 없음 |

---

### 7. 퍼즐 시스템

| 영역 | 카테고리 | 우선순위 | 테스트케이스 |
|------|----------|----------|--------------|
| 멀티 | 네트워크 | P1 | `ReplicatedUsing=OnRep_IsActivated` — 한 클라이언트의 퍼즐 상호작용 후 전체 클라이언트의 퍼즐 상태(시각적 변화) 동기화 |
| 멀티 | 기능 | P1 | **협동 퍼즐** (2인 동시 압력판) — 두 플레이어가 동시에 다른 퍼즐 요소 조작 시 `PuzzleConditionChecker`가 올바른 순서로 평가 |
| 멀티 | 네트워크 | P1 | `MulticastPlayInteractionEffect` (Reliable) — 퍼즐 상호작용 VFX/SFX가 모든 클라이언트에서 동시 재생 |
| 멀티 | 기능 | P1 | `PasswordPanelInspectable` — 클라이언트 A가 패스워드 패널 입력 성공 시 `NetMulticast`로 잠금 해제 상태 전파 |
| 싱글 | 기능 | P2 | OneTime 퍼즐 — 한 번 활성화 후 재상호작용 불가(`bInteractionEnabled = false`) |
| 싱글 | 기능 | P2 | Toggle 퍼즐 — 활성화 → 비활성화 반복 시 `ActivatedEventTag / DeactivatedEventTag` 교대로 전송 |
| 멀티 | 기능 | P2 | `ResetToInitialState` — 스테이지 재시도 시 모든 퍼즐이 초기 상태로 복구 |
| 멀티 | 기능 | P2 | `DecayHoldElement` — 홀딩 도중 인터럽트(사망, 이동) 시 진행률 리셋, 서버·클라이언트 상태 일치 |
| 멀티 | 네트워크 | P2 | `GasRoomPuzzle` 독가스 퍼즐 — 6개 NetMulticast RPC 고지연 환경에서 순서 역전 없이 실행 |
| 멀티 | 기능 | P2 | `AO_ElevatorReactionActor` — 승강기 이동 중 탑승 플레이어 위치가 서버와 동일하게 유지 |
| 멀티 | 기능 | P2 | `AO_CannonElement + AO_CannonProjectile` — 대포 발사 투사체 스폰·충돌이 서버에서 권한 처리, 클라이언트에 `NetMulticast`로 피드백 |
| 멀티 | 기능 | P2 | `AO_PinballBall` — 핀볼 공 물리 시뮬레이션 서버 권한, 위치 Replication 오차 허용 범위 이내 |
| 멀티 | 기능 | P3 | `AO_Valve` — 밸브 회전 각도 Replication 시 시각적 부드러움 (보간 여부) |

---

### 8. Chaos 파괴 시스템

| 영역 | 카테고리 | 우선순위 | 테스트케이스 |
|------|----------|----------|--------------|
| 멀티 | 네트워크 | P1 | `AO_DestructibleCacheActor ServerRPC_Destroy` → `NetMulticast_OnDestroyed` — 파괴 이벤트가 모든 클라이언트에서 동일하게 재생 |
| 멀티 | 기능 | P2 | 이미 파괴된 오브젝트에 추가 RPC 호출 시 중복 파괴 없음 |
| 멀티 | 성능 | P2 | 4인 동시 파괴 이벤트 — Chaos Physics 시뮬레이션 동시 다발 시 FPS 드랍(20fps 이하) 여부 |
| 멀티 | 네트워크 | P3 | 클라이언트 합류 시 이미 파괴된 오브젝트가 파괴 상태로 정상 표시 (초기 Replication) |

---

### 9. 상호작용 시스템

| 영역 | 카테고리 | 우선순위 | 테스트케이스 |
|------|----------|----------|--------------|
| 멀티 | 기능 | P1 | 두 플레이어가 동일 오브젝트 동시 상호작용 시도 — 서버가 먼저 도착한 RPC만 처리, 충돌 없음 |
| 멀티 | 네트워크 | P1 | `InteractionComponent ServerRPC_StartInteract` (Reliable) — 상호작용 성공 시 `MulticastRPC_OnInteractSuccess` 전파 |
| 멀티 | 기능 | P1 | `AO_InspectionComponent` 검사 중 — 다른 클라이언트 화면에서 해당 플레이어 인스펙션 포즈 표시 |
| 멀티 | 네트워크 | P2 | `InspectionComponent ClientRPC_StartInspect` — 검사 UI가 해당 클라이언트에서만 오픈 |
| 멀티 | 기능 | P2 | `AO_BunkerDoor` 상호작용 — 문 열림 상태가 Replicated 변수로 동기화 |
| 멀티 | 기능 | P2 | `AO_WorldInteractable` 아웃라인 하이라이트 — 거리 조건 충족 플레이어에게만 하이라이트 표시 |
| 싱글 | 기능 | P3 | Motion Warping `WarpTargetName` — 상호작용 위치에 캐릭터가 정확히 정렬 |

---

### 10. AI 시스템

| 영역 | 카테고리 | 우선순위 | 테스트케이스 |
|------|----------|----------|--------------|
| 싱글 | 기능 | P1 | Werewolf — Howl 신호(`AO_STCond_HowlReceived`) 수신 후 팩 전체 어그로 전환 |
| 싱글 | 기능 | P1 | Stalker — 천장 이동(`AO_STTask_Stalk_Ceiling`) → 매복(`AO_STTask_Stalk_Ambush`) 순서대로 StateTree 전환 |
| 싱글 | 기능 | P1 | Insect — 납치 어빌리티(`AO_GA_Insect_Kidnap`) 발동 후 플레이어 끌기(`AO_STTask_Insect_Drag`) 정상 처리 |
| 싱글 | 기능 | P1 | Bull — Charge 어빌리티 발동 중 장애물 충돌 시 스턴(`AO_GA_AI_Stun`) 정상 처리 |
| 싱글 | 기능 | P1 | AI Sight Perception — 플레이어가 시야 각도 밖으로 이동 시 추적 중단, 수색 상태 전환 |
| 멀티 | 네트워크 | P1 | `MulticastRPC_PlayDeathAnimation / PlayHitReaction` (AICharacterBase, Reliable) — AI 사망·피격 애니메이션이 모든 클라이언트에서 동일 재생 |
| 멀티 | 기능 | P2 | EQS 포위 공격 — 4인 플레이 시 여러 AI가 EQS 쿼리 충돌 없이 각자 유효한 포위 위치를 할당받는지 확인 |
| 멀티 | 기능 | P2 | `AO_PackCoordComp` 팩 협동 — Werewolf 팩이 멀티플레이 환경에서도 서버 권한으로 올바르게 조율 |
| 싱글 | 기능 | P2 | Sound Perception — 발자국·전투 소음에 AI가 반응하여 소리 발생 위치로 이동 |
| 멀티 | 성능 | P2 | AI 스폰 집중 구역(`AO_Area_SpawnIntensive`) 내 4인 플레이 시 서버 CPU 부하 허용 범위 내 |
| 멀티 | 기능 | P2 | `AO_KidnapComponent` — 납치 중 피납치 플레이어 위치가 AI 위치에 올바르게 Attach, 해방 후 정상 복귀 |
| 싱글 | 기능 | P3 | `AO_CeilingMoveComponent` — 천장 이동 시 충돌 메시 정확도, 플레이어와 물리 충돌 없음 |
| 멀티 | 성능 | P3 | `AO_STTask_AIMoveTo` — 다수 AI 동시 이동 시 네비게이션 경로 계산 프레임 히치 없음 |

---

### 11. 음성 채팅 (Voice Chat)

| 영역 | 카테고리 | 우선순위 | 테스트케이스 |
|------|----------|----------|--------------|
| 멀티 | 기능 | P1 | `StartVoiceChat` — 세션 입장 후 음성 채팅 자동 활성화, 모든 플레이어에게 음성 전달 |
| 멀티 | 기능 | P1 | `MuteRemoteTalker / UnmuteRemoteTalker` — 특정 플레이어 음소거 토글 정상 작동 |
| 멀티 | 기능 | P1 | 레벨 전환 후 음성 채팅 연결 유지 — 스테이지 이동 후 재개 없이 바로 통신 가능 |
| 멀티 | 기능 | P1 | `MuteAllDeadRemoteTalker` — 사망한 플레이어 음성이 생존자에게 들리지 않음 |
| 멀티 | 기능 | P2 | `UnmuteVoiceOnAddPlayerState` — 재접속 플레이어의 음성이 기존 플레이어에게 즉시 해제됨 |
| 멀티 | UI | P2 | `IsRemotePlayerTalking` — 음성 활성 플레이어 아이콘이 발화 중에만 표시 |
| 멀티 | 기능 | P2 | `UpdateVoiceMember` — 플레이어 사망·부활 시 음성 멤버 목록 자동 갱신 |
| 멀티 | 기능 | P3 | `VOIPTalker`의 `SA_VoiceChat` SoundAttenuation — 원거리 플레이어 음성 감쇄 정상 적용 |

---

### 12. 캐릭터 커스터마이징 (Mutable)

| 영역 | 카테고리 | 우선순위 | 테스트케이스 |
|------|----------|----------|--------------|
| 싱글 | 기능 | P1 | 의상·외형 변경 후 `ServerRPC_SetCharacterCustomizingData` 호출 → 서버 반영 |
| 멀티 | 네트워크 | P1 | `Replicated CharacterCustomizingData` — 커스터마이징 변경 후 모든 클라이언트에서 동일 외형 표시 |
| 멀티 | 기능 | P1 | 레벨 전환 후 커스터마이징 상태 유지 (`CopyProperties` PlayerState) |
| 멀티 | 기능 | P2 | 신규 클라이언트 접속 시 기존 플레이어들의 커스터마이징 외형이 올바르게 초기 동기화 |
| 멀티 | 성능 | P2 | Mutable 메시 업데이트 — 4인 동시 커스터마이징 변경 시 프레임 히치 없이 비동기 처리 |
| 멀티 | 기능 | P3 | BodyComponent / HeadComponent 각각 독립 업데이트 — 헤드 변경이 바디에 영향 없음 |

---

### 13. 로비 UI

| 영역 | 카테고리 | 우선순위 | 테스트케이스 |
|------|----------|----------|--------------|
| 멀티 | 기능 | P1 | `OnRep_LobbyIsReady` — 클라이언트 Ready 상태 변경이 호스트 화면 `LobbyReadyBoardActor`에 즉시 반영 |
| 멀티 | 기능 | P1 | 모든 플레이어 Ready 확인 후 호스트만 게임 시작 가능 (`IsLobbyHost` 검사) |
| 멀티 | 기능 | P2 | `OnRep_LobbyJoinOrder` — 입장 순서(0~3)에 따른 슬롯 UI 위치 정확도 |
| 멀티 | UI | P2 | 플레이어 이름 표시 — Steam 닉네임 `OnRep_PlayerName` 이후 `OnPlayerNameReady` 딜레이 없이 UI 갱신 |
| 멀티 | 기능 | P3 | Ready하지 않은 플레이어가 있을 때 게임 시작 버튼 비활성화 |

---

### 14. 인게임 HUD 및 UI

| 영역 | 카테고리 | 우선순위 | 테스트케이스 |
|------|----------|----------|--------------|
| 싱글 | UI | P1 | HUD 체력바 — 피해·회복 시 실시간 업데이트, 최대 체력 기준 비율 정확 |
| 싱글 | UI | P1 | 스태미나바 — 스프린트 소비·자연 회복 실시간 반영 |
| 멀티 | UI | P1 | 팀원 체력 UI — 다른 플레이어 체력이 자신의 HUD에 올바르게 표시 |
| 멀티 | UI | P1 | `NameplateComponent` — 모든 클라이언트에서 팀원 이름 네임플레이트 표시 (거리 기반 가시성) |
| 멀티 | UI | P2 | `OnRep_SharedReviveCount` — 공유 부활 횟수 HUD 동기화 |
| 멀티 | UI | P2 | 선발대 흔적 UI (`OnRep_HintCount`) — 힌트 발견 시 전체 플레이어 화면에 카운터 증가 |
| 싱글 | UI | P2 | 게임 설정 — 그래픽 품질(Lumen/Nanite 토글), 해상도, 음량 변경 즉시 적용 |
| 멀티 | UI | P2 | 게임 클리어 UI (`OnRep_IsGameCleared`) — 모든 클라이언트 동시 결과 화면 표시 |
| 멀티 | UI | P3 | 통계 화면 (`TeamDeathCount, GameStartTime, GameEndTime`) — 게임 종료 후 정확한 플레이 시간·사망 횟수 표시 |

---

### 15. 트레인 (스테이지 탈출)

| 영역 | 카테고리 | 우선순위 | 테스트케이스 |
|------|----------|----------|--------------|
| 멀티 | 기능 | P1 | 연료 충전 완료 후 `Server_RequestStageExit` — 모든 플레이어가 안전 구역에 있을 때만 레벨 전환 실행 |
| 멀티 | 네트워크 | P1 | `ReplicatedUsing=OnRep_DoorState` (`AO_TrainDoor`) — 문 열림 상태가 모든 클라이언트에서 동기화, 애니메이션 일치 |
| 멀티 | 기능 | P2 | 일부 플레이어 안전 구역 미진입 상태에서 레벨 이동 차단 확인 (`bInsideTravelSafeZone`) |
| 멀티 | 기능 | P2 | 트레인 탑승 후 레벨 이동 완료 시 연료(`FuelAmount`) 정산 및 초기화 |

---

### 16. 성능 / 최적화

| 영역 | 카테고리 | 우선순위 | 테스트케이스 |
|------|----------|----------|--------------|
| 멀티 | 성능 | P1 | 4인 플레이 + AI 10마리 이상 동시 활성 시 서버 FPS 30 이상 유지 |
| 멀티 | 성능 | P2 | Replication 대역폭 — 4인 플레이 중 NetProfiler로 채널당 패킷 크기 측정, 스파이크 없음 |
| 싱글 | 성능 | P2 | Lumen / Nanite 활성화 상태에서 메인 스테이지 진입 시 VRAM 사용량 4GB 이하 |
| 멀티 | 성능 | P2 | 텍스처 스트리밍 — 스테이지 로드 완료 후 텍스처 해상도 안정화 시간 5초 이내 |
| 멀티 | 성능 | P3 | `AO_AIMemoryComponent` — 장시간 플레이 시 AI 메모리 누수 여부 (메모리 증가 추이 모니터링) |
| 싱글 | 성능 | P3 | Motion Matching 블렌드 스페이스 — 빠른 방향 전환 시 CPU 부하 스파이크 없음 |

---

### 17. 크래시 / 엣지 케이스

| 영역 | 카테고리 | 우선순위 | 테스트케이스 |
|------|----------|----------|--------------|
| 멀티 | 크래시 | P0 | 클라이언트가 상호작용 RPC 전송 직후 연결 끊김 — 서버에서 NULL 포인터 접근 크래시 없음 |
| 멀티 | 크래시 | P0 | AI Kidnap 도중 피납치 플레이어 강제 퇴장 — `AO_KidnapComponent` 포인터 해제 시 크래시 없음 |
| 멀티 | 크래시 | P0 | 스테이지 클리어 직전 호스트 퇴장 — `OnDestroyThenRecreateSession` 콜백 중 NullReference 크래시 없음 |
| 멀티 | 크래시 | P0 | `bPendingReturnToMenu` 플래그 — Destroy 미완료 상태에서 씬 전환 중복 호출 시 크래시 없음 |
| 멀티 | 크래시 | P1 | 4명 전원 동시 사망 + `TryConsumeSharedReviveCount(0)` — 음수 부활 카운트로 인한 로직 오류 없음 |
| 멀티 | 크래시 | P1 | `OnRep_PlayerState` — 플레이어 재접속 시 PlayerState 재할당 중 GAS AbilitySystemComponent NULL 크래시 없음 |
| 멀티 | 크래시 | P1 | `NetMulticast` RPC 수신 중 Actor 파괴(BeginDestroy) 시 크래시 없음 (약참조 체크) |
| 싱글 | 크래시 | P2 | DataTable 항목 없는 ItemID 조회 시 인벤토리 크래시 없이 빈 슬롯 처리 |
| 멀티 | 크래시 | P2 | 세션 검색 결과 0개일 때 `JoinSessionByIndex(0)` 호출 — 배열 범위 초과 크래시 없음 |
| 멀티 | 크래시 | P3 | 퍼즐 `LinkedChecker` nullptr — 미연결 퍼즐 요소 상호작용 시 크래시 없이 경고 로그 출력 |

---

### 18. UE5 특화 — Replication 최적화 및 GAS 동기화

| 영역 | 카테고리 | 우선순위 | 테스트케이스 |
|------|----------|----------|--------------|
| 멀티 | 네트워크 | P1 | **GAS Local Prediction 검증** — 파쿠르·스프린트 Ability의 클라이언트 예측 실행이 서버 보정 시 눈에 띄는 Rollback 없음 |
| 멀티 | 네트워크 | P1 | **GAS Attribute Replication** — Health·Stamina OnRep가 서버 GameplayEffect 적용 직후 모든 클라이언트에 올바르게 전파 |
| 멀티 | 네트워크 | P2 | **Relevancy 컬링** — 원거리 플레이어·AI의 Actor Replication이 비가시 구역에서 올바르게 일시 중단 (`NetCullDistanceSquared`) |
| 멀티 | 네트워크 | P2 | **NetQuantize10 정밀도** (`FRepCameraView`) — 관전 카메라 위치 압축 후 복원 오차가 시각적으로 허용 범위 이내 |
| 멀티 | 네트워크 | P2 | **Unreliable RPC 누락 허용** — `Multicast_PlayInventorySound (Unreliable)` 패킷 손실 시 사운드 미재생만 발생, 게임 상태 오류 없음 |
| 멀티 | 네트워크 | P2 | **Gameplay Tag Replication** — `GameplayTagContainer` 복제 시 태그 순서·중복 없이 클라이언트 동기화 |
| 멀티 | 성능 | P2 | **StateTree 서버 전용 실행** — AI StateTree가 서버에서만 틱, 클라이언트에서 불필요한 Tick 없음 확인 |
| 멀티 | 네트워크 | P3 | **TArray Replication 오버헤드** — `TArray<FInventorySlot> Slots` 전체 배열 변경 시 불필요한 전체 재전송 발생 여부 프로파일링 |
| 멀티 | 네트워크 | P3 | **대규모 AI 스폰 구역** 넷 패킷 스파이크 — `AO_Area_SpawnIntensive` 진입 시 대역폭 급증 여부 NetProfiler 확인 |

---

*본 체크리스트는 `Source/` 폴더 코드 분석(2026-04-28) 기준으로 작성되었습니다. 신규 기능 추가 시 해당 섹션을 업데이트하십시오.*
