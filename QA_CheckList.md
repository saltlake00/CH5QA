# QA 체크리스트 – AVaOut: Avatar Out

| 영역 | 카테고리 | 우선순위 | 테스트케이스 |
|------|----------|----------|--------------|
| 멀티플레이 | 네트워크 | P0-Critical | 서버에서 `ServerRPC` 호출 시 클라이언트가 정상적으로 요청을 전송하고 서버가 처리하는가? (예: `ServerTriggerInteract`, `Server_RequestStageExit`) |
| 멀티플레이 | 네트워크 | P0-Critical | `ClientRPC` (예: `Client_OpenInviteOverlay`, `Client_OnRevived`)가 서버에서 호출될 때 해당 클라이언트에서만 실행되는가? |
| 멀티플레이 | 네트워크 | P0-Critical | `NetMulticast` RPC (예: `MulticastExplode`, `MulticastPlayInteractionEffect`)가 모든 클라이언트에서 동일하게 재생되는가? |
| 멀티플레이 | 네트워크 | P0-Critical | `Replicated` 속성 (예: `bIsActivated`, `CurrentVictim`, `Slots`)이 서버에서 변경될 때 모든 클라이언트에 정확히 복제되는가? |
| 멀티플레이 | 네트워크 | P1-High | `DOREPLIFETIME_CONDITION_NOTIFY` 조건 (COND_None, COND_OwnerOnly 등)이 의도한 대로 동작하는가? |
| 멀티플레이 | 네트워크 | P1-High | 세션 생성/참가/파괴 (`HostSession`, `JoinSessionByIndex`, `DestroyCurrentSession`)가 Steam OSS에서 정상 작동하는가? |
| 멀티플레이 | 네트워크 | P1-High | 비밀번호 방 생성 시 `VerifyPasswordAgainstIndex`가 올바른 해시 비교를 수행하는가? |
| 멀티플레이 | 네트워크 | P1-High | `SetSessionInGame(true)` 호출 후 중간 입장이 차단되는가? |
| 멀티플레이 | 네트워크 | P2-Medium | `OnSessionUserInviteAccepted`를 통한 Steam 초대 수락이 정상적으로 세션 참가로 이어지는가? |
| 멀티플레이 | 네트워크 | P2-Medium | 네트워크 실패 시 `HandleNetworkFailure`가 호출되고 세션이 정리되는가? |
| 멀티플레이 | 네트워크 | P2-Medium | `RequestSynchronizedServerTravel`에서 모든 플레이어의 `Client_PrepareForTravel` 수신 후 `ServerTravel`이 실행되는가? |
| 멀티플레이 | 네트워크 | P3-Low | `UpdateCurrentPlayers`가 세션 메타데이터에 현재 인원을 정확히 반영하는가? |
| 싱글플레이 | 기능 | P0-Critical | 캐릭터 이동 (WASD), 점프, 스프린트, 크라우치가 GAS 기반으로 정상 작동하는가? |
| 싱글플레이 | 기능 | P0-Critical | 상호작용 (F키) – 홀딩, 즉시, 토글 등 모든 타입이 의도대로 동작하는가? |
| 싱글플레이 | 기능 | P0-Critical | 인벤토리 – 아이템 획득, 슬롯 선택, 사용, 버리기가 서버 권한으로 처리되는가? |
| 싱글플레이 | 기능 | P0-Critical | 퍼즐 조건 검사기 (`AAO_PuzzleConditionChecker`) – AND/OR, 순서, 시간 제한 조건이 올바르게 평가되는가? |
| 싱글플레이 | 기능 | P0-Critical | AI 기본 행동 – 배회, 추격, 수색, 공격, 기절이 StateTree와 GAS를 통해 정상 작동하는가? |
| 싱글플레이 | 기능 | P1-High | 파쿠르 (Traversal) – 허들, 볼트, 맨틀이 Motion Matching과 Chooser Table로 올바르게 선택되는가? |
| 싱글플레이 | 기능 | P1-High | Inspection 모드 – 진입, 카메라 전환, 클릭 처리, 종료가 네트워크 동기화되어 작동하는가? |
| 싱글플레이 | 기능 | P1-High | 연료 시스템 – 기차에 연료 주입, 소모, 부족 시 스테이지 실패가 정상 처리되는가? |
| 싱글플레이 | 기능 | P1-High | 사망/부활 – Death Ability, 래그돌, 부활칩 소모, 자동 부활 큐가 올바르게 동작하는가? |
| 싱글플레이 | 기능 | P1-High | AI 특수 행동 – Troll 무기 줍기, Insect 납치, Werewolf 포위, Stalker 천장 이동, Crab 아이템 운반이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | 퍼즐 요소 – 토치, 압력판, 회전 퍼즐, 밀기 퍼즐, 비밀번호 패널, 가스실 등이 각각의 규칙대로 동작하는가? |
| 싱글플레이 | 기능 | P2-Medium | 캐릭터 커스터마이징 – Mutable 시스템을 통한 외형 변경이 실시간으로 반영되고 복제되는가? |
| 싱글플레이 | 기능 | P2-Medium | 음성 채팅 – Steam IOnlineVoice를 통한 음성 전송, Mute/Unmute, 사망 시 자동 Mute가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | 관전 모드 – 사망 후 다른 플레이어 관전, 카메라 보간, 시점 전환이 정상 작동하는가? |
| 싱글플레이 | 기능 | P3-Low | 레벨별 머티리얼/메시 변경 (Crab, Troll) – Meadow/Lava/Ice 레벨에서 올바른 외형이 적용되는가? |
| 싱글플레이 | UI | P1-High | HUD – 체력, 스태미나, 상호작용 프롬프트, 인벤토리 UI가 올바르게 표시되고 업데이트되는가? |
| 싱글플레이 | UI | P1-High | 일시정지 메뉴 – ESC 키로 열리고, 설정/로비 복귀/게임 종료가 정상 작동하는가? |
| 싱글플레이 | UI | P2-Medium | 로비 레디 보드 – 플레이어 목록, 레디 상태, 호스트 표시가 실시간으로 갱신되는가? |
| 싱글플레이 | UI | P2-Medium | 설정 창 – 그래픽, 오디오, 키 설정이 저장되고 적용되는가? |
| 싱글플레이 | 성능 | P1-High | AI 다수 존재 시 프레임 드롭이 발생하지 않는가? (특히 StateTree + GAS 조합) |
| 싱글플레이 | 성능 | P2-Medium | 오브젝트 풀 (CannonProjectilePool)이 정상적으로 재사용되고 메모리 누수가 없는가? |
| 싱글플레이 | 성능 | P2-Medium | Lumen/Nanite 사용 시 복잡한 장면에서도 30fps 이상 유지되는가? |
| 싱글플레이 | 크래시 | P0-Critical | 레벨 전환 시 `EndPlay`에서 타이머/델리게이트 정리가 누락되어 크래시가 발생하지 않는가? |
| 싱글플레이 | 크래시 | P0-Critical | 음성 채팅 종료 시 `StopVoiceChat` → `RemoveAllRemoteTalkers` → `DisconnectAllEndpoints` 호출 순서로 크래시가 없는가? |
| 싱글플레이 | 크래시 | P1-High | 널 포인터 참조 – 모든 `GetOwner()`, `GetWorld()`, `Cast` 결과가 `ensure` 또는 `check`로 검증되는가? |
| 싱글플레이 | 크래시 | P1-High | `AbilitySystemComponent`가 유효하지 않은 상태에서 GAS 함수 호출 시 크래시가 발생하지 않는가? |
| 싱글플레이 | 크래시 | P2-Medium | `OnRep_` 함수에서 복제된 데이터가 불완전할 때 (예: `CurrentVictim`이 nullptr) 크래시가 없는가? |
| 멀티플레이 | 네트워크 | P0-Critical | GAS Attribute Set (체력, 스태미나, 이동속도)의 `Replicated` 값이 모든 클라이언트에서 일관된가? |
| 멀티플레이 | 네트워크 | P1-High | `GameplayEffect`의 `SetByCaller` 매그니튜드 (예: `Data.Damage`)가 서버에서 계산되어 클라이언트에 올바르게 전달되는가? |
| 멀티플레이 | 네트워크 | P1-High | `AbilityTask` (예: `WaitForInteractableTraceHit`)가 로컬에서만 실행되어야 하는데 서버에서도 실행되지 않는가? |
| 멀티플레이 | 네트워크 | P2-Medium | `LocalPredicted` 넷 실행 정책을 가진 어빌리티 (예: 점프, 스프린트)가 클라이언트 예측 후 서버 검증을 받는가? |
| 멀티플레이 | 네트워크 | P2-Medium | `ServerInitiated` 넷 실행 정책을 가진 AI 공격 어빌리티가 서버에서만 발동되고 클라이언트에 복제되는가? |
| 싱글플레이 | 기능 | P0-Critical | AI Perception – Sight/Hearing Config가 올바르게 설정되고 `OnTargetPerceptionUpdated`가 호출되는가? |
| 싱글플레이 | 기능 | P1-High | StateTree Evaluator (예: `AO_STEval_AggressiveCtx`)가 매 틱마다 올바른 데이터를 제공하는가? |
| 싱글플레이 | 기능 | P1-High | EQS 쿼리 (예: `AO_EQS_Test_PlayerFOV`, `AO_EQS_Test_LineOfSight`)가 AI 스폰 위치를 올바르게 필터링하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_Area_SpawnRestriction` 및 `AO_NavArea_SpawnRestriction`이 스폰 금지 영역을 올바르게 적용하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_Area_SpawnIntensive` 영역 내에서 집중 스폰이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_Spawner_AIManager`의 `DebugSpawn` 함수가 에디터에서 즉시 스폰을 수행하는가? |
| 싱글플레이 | 기능 | P1-High | `AO_KidnapComponent` – 납치 시 플레이어 부착, 입력 차단, DoT 데미지, 던지기, 쿨다운이 정상 작동하는가? |
| 싱글플레이 | 기능 | P1-High | `AO_CeilingMoveComponent` – 천장 감지, 모드 전환, Mesh 오프셋 보간이 정상 작동하는가? |
| 싱글플레이 | 기능 | P1-High | `AO_PackCoordComp` – Howl 전파, 포위 위치 예약, 일제 공격 타이머가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_ItemCarryComponent` – 아이템 줍기/드롭, AISubsystem 예약, 쿨다운이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_WeaponHolderComp` – 무기 감지, 줍기, 드롭, 시야 목록 관리가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_InventorySubsystem` – `OnInvenRegistered` 델리게이트가 Pawn 변경 시 올바르게 호출되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_UIStackManager` – Push/Pop/PopAll이 입력 모드와 포커스를 올바르게 관리하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_UIActionKeySubsystem` – UI 열기/닫기 키가 IMC에서 올바르게 로드되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_PlayerSoundSubsystem` – 캐릭터 메시 타입에 따라 올바른 사운드가 재생되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_FoleyAudioBank` – 발소리, 점프, 착지 사운드가 GAS 태그 기반으로 재생되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_CameraManagerComponent` – 상태 태그(죽음, 스프린트, 트래버설)에 따라 카메라 프로필이 전환되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_NameplateComponent` – 이름표가 거리에 따라 크기/위치가 조절되고, 음성 표시가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_DeathSpectateComponent` – 사망 시 관전자 등록/해제, 카메라 스트리밍이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_Passive_WorldSubsystem` – 패시브 업그레이드 기록 및 재적용이 플레이어별로 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_InventorySaveZone` – 세이프 존 내에서 인벤토리 유지가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_TrainFuelListener` – 연료 변경 시 UI 업데이트가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_GameMode_Stage` – 스테이지 종료 조건 (연료+단서) 충족 시 다음 맵으로 이동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_GameMode_Lobby` – 호스트만 게임 시작 가능, 모든 게스트 레디 필요 조건이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_GameState` – `SetStageFailed`, `SetGameClear`가 올바르게 복제되고 UI에 반영되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_PlayerState` – `bIsAlive`, `DeathCount`, `PersistentInventory`가 레벨 전환 시 올바르게 복사되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_OnlineSessionSubsystem` – `StartVoiceChat`/`StopVoiceChat`이 중복 호출 시 크래시 없이 처리되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_GameplayAbility_Death` – 사망 몽타주 재생 후 래그돌 이벤트가 정상 전송되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_GameplayAbility_HitReact` – 방향별(전/후/좌/우) 피격 몽타주가 올바르게 선택되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_GameplayAbility_Sprint` – 스태미나 부족 시 `Ability.Fail.NotEnoughStamina` 태그가 전송되고 사운드가 재생되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_GameplayAbility_Jump` – 점프 시 스태미나 소모, 착지 시 `PostSprintNoChangeEffect` 적용이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_GameplayAbility_Traversal` – Motion Matching으로 선택된 몽타주가 Warp Target과 함께 재생되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_GameplayAbility_Outline` – 포스트 프로세스 아웃라인 효과가 지속 시간 후 제거되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_GA_AI_Stun` – `Event.AI.Stunned` 이벤트로 기절 Ability가 트리거되고, 이동 비활성화/복구가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_GA_AIAttackBase` – `Event.Combat.Confirm` 수신 시 SphereTrace로 플레이어를 감지하고 데미지를 적용하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_GA_Troll_Attack` – 랜덤 공격 타입 선택, 몽타주 재생, 넉백/넉다운 적용이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_GA_Insect_Kidnap` – 몽타주 재생 후 SphereTrace로 플레이어를 감지하고 `TryKidnapPlayer`를 호출하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_GA_Bull_Charge` – 돌진 Ability 활성화, 충돌 시 데미지/넉백, 후퇴 모드 전환이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_GA_LavaMonster_Attack` – 땅속 공격 시 전조 VFX, 타겟별 타이머, 분출 VFX가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_GA_Werewolf_Attack` – Heavy HitReact 이벤트 전송이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_GA_Werewolf_Howl` – Howl 몽타주 재생 후 `BroadcastHowl`이 호출되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_GA_Stalker_Attack` – 기습 공격 후 `SetRetreatMode(true)`가 호출되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_NotifyState_MeleeCollision` – NotifyState 구간 동안 히트 이벤트가 한 번만 전송되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_AnimNotify_SendDeathRagdollEvent` – 사망 몽타주 중 래그돌 이벤트가 서버/클라이언트에서 정상 전송되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_AN_AIFootstep` – AI 발소리 AnimNotify가 Attenuation 설정과 함께 재생되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_AN_StalkerCeilingTransition` – 천장/바닥 전환 AnimNotify가 `SetCeilingMode`를 호출하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_NotifyState_MontageBlendOut` – 조건(Force, WithMovementInput, IfFalling)에 따라 몽타주가 블렌드 아웃되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STTask_Chase` – 추격 중 경로 재계산 간격이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STTask_Search` – 수색 시간 종료 후 배회로 전환되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STTask_AIRoam` – 배회 중 랜덤 위치로 이동하고 대기 후 재이동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STTask_Stalker_Roam` – 배회 중 천장 전환 확률에 따라 천장 모드로 전환되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STTask_Stalk_Approach` – 플레이어가 보고 있으면 실패(Hide), 공격 거리 도달 시 성공(Attack)하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STTask_Stalk_Hide` – EQS 결과를 기다리고, 타임아웃 시 동기 방식으로 폴백하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STTask_Stalk_Ambush` – 공격 실행 후 `IsAttacking` 상태가 false가 될 때까지 대기하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STTask_Crab_Pickup` – 아이템 탐색 후 이동, 줍기 애니메이션(선택) 후 픽업이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STTask_Crab_Drop` – 드롭 위치로 이동, 플레이어 감지 시 재계산, 도착 시 드롭이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STTask_Crab_Flee` – 위협 위치로부터 안전 거리만큼 멀어지면 도주 종료하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STTask_Troll_PickWeapon` – 무기로 이동, 근접 시 몽타주 재생 후 줍기가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STTask_Troll_Attack` – 랜덤 공격 타입 선택 후 `ExecuteAttack` 호출, 공격 완료 대기하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STTask_Insect_Kidnap` – 납치 Ability 태그로 활성화, 납치 성공 시 Succeeded 반환하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STTask_Insect_Drag` – SafeLocation으로 NavMesh 이동, 도착 시 `ReleaseKidnap(true)` 호출하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STTask_Wolf_Howl` – Howl Ability 실행, `MarkHowledOrJoined` 호출, 애니메이션 시간 대기하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STTask_Wolf_Surround` – EQS 또는 도주로 차단 위치로 이동, 포위 위치 예약이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STTask_Wolf_Attack` – 공격 범위 내면 Ability 활성화, 범위 밖이면 추격하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STTask_Bull_Charge` – 돌진 Ability 실행, 플레이어 방향으로 이동, 돌진 종료 시 Succeeded 반환하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STTask_LavaMonster_Attack` – 사거리 기반 공격 타입 선택, 공격 완료 대기하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STTask_PlaySoundOnce` – EnterState에서 1회 사운드 재생 후 즉시 Succeeded 반환하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STTask_PlaySoundInterval` – 랜덤 간격으로 사운드 재생, 겹침 방지, ExitState에서 정리하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STEval_AggressiveCtx` – 추격/수색/공격 범위 등 상태를 올바르게 업데이트하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STEval_StalkerContext` – 엄폐 위치, 도주 위치, 시선 감지(Hysteresis)를 올바르게 계산하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STEval_TrollContext` – 무기 소지, 공격 가능, 무기 줍기 우선순위를 올바르게 평가하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STEval_CrabContext` – 아이템 소지, 위협 감지, 기절 상태를 올바르게 평가하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STEval_InsectContext` – 납치 상태와 안전 위치를 올바르게 계산하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STCond_PlayerInSight` – 시야 내 플레이어 조건이 올바르게 테스트되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STCond_InAttackRange` – 공격 범위 조건이 올바르게 테스트되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STCond_IsStunned` – 기절 상태 조건이 GAS 태그 기반으로 올바르게 테스트되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STCond_HasWeapon` – Troll 무기 소지 조건이 올바르게 테스트되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STCond_TrollWeaponNearby` – 주변 무기 존재 조건이 올바르게 테스트되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STCond_PlayerNearby` – 시야+청각 기반 플레이어 근접 조건이 올바르게 테스트되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STCond_PlayerTooClose` – 최소 안전 거리 조건이 올바르게 테스트되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STCond_CanAmbush` – 플레이어 등 뒤/옆 각도 조건이 올바르게 테스트되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STCond_PlayerLooking` – 플레이어 시선 조건이 올바르게 테스트되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STCond_IsRetreating` – Stalker 후퇴 모드 조건이 올바르게 테스트되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STCond_HasItem` – Crab 아이템 소지 조건이 올바르게 테스트되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STCond_ItemNearby` – 주변 아이템 존재 조건이 올바르게 테스트되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STCond_IsKidnapping` – Insect 납치 상태 조건이 올바르게 테스트되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STCond_WolfPackState` – 팩 상태(Howl, 포위, 공격 등) 조건이 올바르게 테스트되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STCond_HowlReceived` – Howl 수신(포위 모드) 조건이 올바르게 테스트되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STCond_CeilingAvailable` – 천장 가용 조건이 올바르게 테스트되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_STCond_InCeiling` – 천장 모드 조건이 올바르게 테스트되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_EQS_Context_AllPlayers` – 모든 플레이어 위치를 EQS에 제공하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_EQS_Context_Target` – 추격 대상 위치를 EQS에 제공하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_EQS_Context_PackMembers` – 주변 Werewolf 위치를 EQS에 제공하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_EQS_Test_PlayerFOV` – 플레이어 시야각 밖 위치만 통과시키는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_EQS_Test_LineOfSight` – 모든 플레이어 시야에서 숨겨진 위치만 통과시키는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_EQS_Test_VolumeExclusion` – 스폰 금지 볼륨 내부 위치를 필터링하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_EQS_Test_NavAreaExclusion` – 스폰 금지 NavArea 내부 위치를 필터링하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_GameplayAbility_Interact_Execute` – 홀딩 중 이탈 감지, Duration 완료, DecayHold 처리 등이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_GameplayAbility_Interact_Trace` – 사망 태그 추가 시 Trace Ability가 종료되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_AbilityTask_WaitForInteractableTraceHit` – 주기적 SphereCast로 상호작용 가능 오브젝트를 감지하고 하이라이트를 업데이트하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_AbilityTask_WaitForInvalidInteraction` – 홀딩 중 각도/거리 이탈 시 `OnInvalidInteraction`을 브로드캐스트하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_AbilityTask_WaitInteractionInputRelease` – 입력 해제 시 `OnReleased`를 브로드캐스트하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_InteractionWidgetController` – `BroadcastInteractionMessage`가 위젯에 올바르게 전달되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_InteractableComponent` – `NotifyInteractionSuccess`가 서버에서만 호출되고 `OnInteractionSuccess` 델리게이트가 실행되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_InspectionComponent` – `EnterInspectionMode`/`ExitInspectionMode`가 서버 권한으로 처리되고 클라이언트에 RPC로 알리는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_InspectableComponent` – `SetInspectionLocked`가 다른 플레이어의 진입을 막는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_BaseInteractable` – `OnInteractionSuccess`에서 토글/원타임 동작, 이펙트 재생, LinkedReactionActor 호출이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_WorldInteractable` – 소모성 상호작용 시 `bWasConsumed` 설정 및 다른 플레이어 어빌리티 취소가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_PuzzleElement` – ElementType(OneTime/Toggle/HoldToggle)에 따른 상태 변경 및 태그 전송이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_DecayHoldElement` – 홀드 시 진행도 증가, 놓으면 감소, LinkedReactionActor에 진행도 전달이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_PressurePlate` – Overlap 기반 활성화/비활성화, 진행도 변화, ReactionActor 연동이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_RotationPuzzleElement` – 회전 단계별 애니메이션, 정답 체크, 태그 전송이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_PushableRockElement` – 밀기 방향 계산, 이동 애니메이션, 캐릭터 밀쳐내기, 정답 셀 체크가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_GridManager` – 격자 좌표 변환, 벽/바위 충돌 체크, 방향 계산이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_GridWall` – 벽 방향(Horizontal/Vertical)에 따른 경로 차단이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_InspectionPuzzle` – ElementMappings 기반 클릭 태그 전송, LinkedChecker 연동이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_OverwatchInspectionPuzzle` – 외부 메시 매핑, 스페이스바 모드, 하이라이트가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_PasswordPanelInspectable` – 버튼 클릭, 비밀번호 생성, 자릿수 분해, 정답 이벤트가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_CannonElement` – 인스펙션 모드에서 회전, 발사, 쿨다운, 투사체 풀 사용이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_CannonProjectile` – 발사, 충돌, 폭발, 스턴/파괴 태그 전송, 풀 반환이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_CannonProjectilePool` – 풀 초기화, 획득, 반환, 부족 시 강제 회수가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_DestructibleCacheActor` – TriggerTag 추가 시 파괴, 카오스 캐시 재생, VFX/SFX, 지연 삭제가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_DestructibleFloor` – 플레이어 오버랩 후 지연 파괴, Collision 비활성화가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_PuzzleReactionActor` – OneTime/Toggle/HoldActive 모드에 따른 Transform 애니메이션, AttachedActors 이동이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_ElevatorReactionActor` – 버튼 호출 시퀀스(문 열림/닫힘, 이동)가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_CableCarReactionActor` – 스플라인 경로 따라 이동, 토글 방향 전환이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_BunkerDoor` – 문 열림/닫힘 애니메이션, 퍼즐 잠금, 사운드가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_Valve` – 밸브 열림/닫힘에 따른 VFX/SFX, 데미지 존 스폰/제거가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_GasRoomPuzzle` – 전체 시퀀스(지연 시작, 카운트다운, 비밀번호 힌트, 가스 VFX, 데미지 존, 문 제어)가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_RollingBall` – 물리 시뮬레이션, 플레이어 충돌 데미지/넉백, 쿨다운, 리셋이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_BallTrigger` – Reset/PlayerDetection 타입에 따른 볼 제어가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_PinballBall` – 물리 시뮬레이션, 리셋이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_PinballTrigger` – Success/Fail 모드에 따른 체커 이벤트 전송 또는 볼 리셋이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_DamageVolume` – Overlap 시 지속 데미지 GameplayEffect 적용, 종료 시 제거가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_StunDamageVolume` – AI 스턴 타이머, 주기적 스턴 이벤트 전송이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_TraversableComponent` – 스플라인 기반 ledge 탐색, 반대 ledge 매핑이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_ShopManager` – 공유 자금 표시, 구매 처리, 아이템 스폰이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_VendingMachine` – 아이템 데이터 적용, 가격 표시, 구매 요청이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_MasterItem` – ItemID 기반 데이터 로드, 상호작용 시 인벤토리 추가, 파괴가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_PassiveContainer` – 패시브 아이템 사용 시 전체 플레이어에게 효과 적용, 기록이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_RevivealChipContainer` – 부활칩 사용 시 GS의 SharedReviveCount 증가가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_Sample_Fuel` – 오버랩 시 기차에 연료 추가, 소멸이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_Train` / `AO_newTrain` – 연료 속성 초기화, 추가/제거 Ability, 연료 부족 시 스테이지 실패가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_TrainDoor` – 문 슬라이드 애니메이션, 사운드, 복제가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_StageInteractable` – 연료+단서 조건에 따른 UI 표시, 출구 상호작용이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_RestInteractable` – 휴게소에서 다음 스테이지 이동이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_LobbyInteractable` – 레디 토글, 게임 시작, 초대 UI, 옷장 UI가 권한에 따라 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_LobbyReadyBoardActor` – 플레이어 목록, 레디 상태, 호스트 표시가 실시간으로 업데이트되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_CustomizingComponent` – 캐릭터 메시/헤어/의상 변경이 서버 RPC로 저장되고 복제되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_DummyCustomComponent` – 더미 캐릭터에서 커스터마이징 변경 후 저장이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_PlayerSoundDataAsset` – 메시 타입별 사운드 맵이 올바르게 로드되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_PlayerSoundSettings` – DeveloperSettings에서 DataAsset 경로가 올바르게 설정되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_GameUserSettings` – 커스텀 설정(볼륨, 업스케일링, 음성)이 저장/로드되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_GameSettingsManager` – 모든 설정 적용 함수가 정상 호출되고 델리게이트가 브로드캐스트되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_DelegateManager` – 설정 열기/닫기, 키바인딩 업데이트 델리게이트가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_MapRoutes` – 스테이지/로비/휴게소 맵 경로가 올바르게 정의되고 사용되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_GameInstance` – `ResetRun`, `TryAdvanceStageIndex`, 호스트 정보 관리가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_FuelData` – 초기 연료, 최대 연료, 필요 연료 값이 DataAsset에서 올바르게 로드되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_AddFuel_GameplayAbility` – `Event.Interaction.AddFuel` 트리거로 연료 추가가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_RemoveFuel_GameplayAbility` – 연료 감소 Ability가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_Fuel_AttributeSet` – `InitFromGameInstance`에서 GI의 연료 값을 올바르게 가져오는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_GameplayCueNotify_Burst_Fuel` – 연료 추가 시 파티클/사운드가 재생되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_GameplayCueNotify_Burst_Death` – 사망 시 사운드가 재생되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_GameplayCueNotify_Burst_DamageVolume` – 데미지 볼륨에서 피격 시 사운드가 재생되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_PlayerCharacter_AttributeSet` – 체력/스태미나/속도 속성이 올바르게 초기화되고 복제되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_PlayerCharacter_AttributeDefaults` – 기본 속성 값이 DataAsset에서 올바르게 로드되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_AIAttributeSet` – AI 이동 속도 속성이 올바르게 초기화되고 복제되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_InteractionGameplayAbility` – `OnSpawn` 정책으로 자동 활성화되는 어빌리티가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_InteractionGameplayTags` – 모든 상호작용 관련 태그가 올바르게 정의되고 사용되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_InteractionDataAsset` – 상호작용 프리셋이 올바르게 로드되고 사용되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_InteractionEffectSettings` – VFX/SFX 설정이 올바르게 적용되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_InteractionInfo` – 상호작용 정보 구조체가 올바르게 채워지고 비교 연산자가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_InteractionQuery` – 요청자 정보가 올바르게 전달되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_Interface_Interactable` – 모든 상호작용 가능 오브젝트가 인터페이스를 올바르게 구현하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_Interface_Inspectable` – 인스펙션 클릭 인터페이스가 올바르게 구현되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_Interface_InspectionCameraTypes` – 카메라 설정 인터페이스가 올바르게 구현되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_Interface_PuzzleElement` – 퍼즐 요소 인터페이스(리셋, 활성화)가 올바르게 구현되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_PlayerCharacter_MovementEnums` – 이동 관련 열거형이 올바르게 정의되고 사용되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_TraversalTypes` – 트래버설 체크 결과 구조체가 올바르게 사용되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_TraversalTransform` – 트래버설 트랜스폼 인터페이스가 올바르게 구현되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_MeleeHitEventPayload` – 히트 이벤트 페이로드가 올바르게 생성되고 사용되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_AITypes` – 공통 AI 공격 설정 구조체가 올바르게 사용되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_CollisionChannels` – 상호작용 트레이스 채널이 올바르게 정의되고 사용되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_Log` – 모든 로그 카테고리가 올바르게 선언되고 사용되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_InputModifier` – 슬롯 인덱스 입력 modifier가 올바르게 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_InventoryListener` – 인벤토리 변경 리스너 인터페이스가 올바르게 구현되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_TrainFuelListener` – 연료 변경 리스너 인터페이스가 올바르게 구현되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_FoleyAudioBankInterface` – Foley 오디오 뱅크 인터페이스가 올바르게 구현되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_PickupComponent` – AI 아이템 픽업/드롭, 물리 제어, 쿨다운이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_AIMemoryComponent` – 플레이어 위치 기억, 소리 감지, 메모리 유효 시간이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_AISubsystem` – 아이템 예약, 납치 상태, 쿨다운 정리가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_ItemDataAsset` – 아이템 데이터 테이블 에셋이 올바르게 로드되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_ItemManager` – 아이템 데이터 조회 싱글톤이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_struct_FItemBase` – 아이템 데이터 행 구조체가 올바르게 정의되고 사용되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_PlayerCharacter_AnimInstance` – 애니메이션 블루프린트 변수(속도, 상태, 궤적)가 올바르게 업데이트되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_PlayerCharacter` – 입력 바인딩, GAS 초기화, VOIP 등록, 사망 처리 등이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_PlayerController` – 설정 위젯 생성, 로딩 맵 이름 업데이트가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_PlayerController_MainMenu` – 메인 메뉴 위젯 생성, UI 입력 모드가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_PlayerController_Lobby` – 레디, 시작, 초대, 옷장 UI RPC가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_PlayerController_InGameBase` – 일시정지, 설정, 음성 채팅, 트래블 준비가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_PlayerController_Stage` – 스테이지 종료, 사망 UI, 관전, 부활 요청이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_PlayerController_Rest` – 휴게소 종료 요청이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_PlayerState` – 레디, 호스트, 생존, 커스터마이징, 인벤토리 저장/복원이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_GameMode` – 기본 게임모드 클래스가 올바르게 설정되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_GameMode_MainMenu` – 메인 메뉴 게임모드가 올바르게 설정되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_GameMode_Lobby` – 로비 게임모드가 플레이어 입장/퇴장, 레디, 시작을 올바르게 처리하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_GameMode_InGameBase` – 시임리스 트래블, 음성 채팅 동기화, 인벤토리 저장이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_GameMode_Stage` – 스테이지 시작/종료, 부활 큐, 전멸 평가가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_GameMode_Rest` – 휴게소 게임모드가 다음 스테이지 이동을 올바르게 처리하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_GameState` – 공유 부활 카운트, 스테이지 실패/클리어, 힌트 카운트 복제가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_HealthWidget` – 체력/최대체력 속성 변경 시 UI 업데이트가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_StaminaWidget` – 스태미나/최대스태미나 속성 변경 시 UI 업데이트가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_SpectateWidget` – 관전 대상 변경 시 이름, 체력, 스태미나 위젯 바인딩이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_UserWidget` – `PlayUISoundFromDataTable`이 올바르게 사운드를 재생하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_PauseMenuWidget` – 버튼 클릭 델리게이트가 정상 바인딩되고 ESC 키로 닫히는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_ConfirmReturnToMenuWidget` – 확인/취소 델리게이트가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_ConfirmQuitGameWidget` – 확인/취소 델리게이트가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_MainMenuWidget` – 호스트/조인/설정/종료 버튼이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_HostDialogWidget` – 방 이름/비밀번호 입력, 생성 버튼 활성화, HostSessionAuto 호출이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_LobbyListWidget` – 세션 검색, 페이지네이션, 필터, 조인, 비밀번호 다이얼로그가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_LobbyListEntryWidget` – 방 정보 표시, 조인 버튼이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_PasswordDialogWidget` – 비밀번호 입력, 검증, 조인이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_LobbyReadyBoardWidget` – 엔트리 목록 표시가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_LobbyReadyBoardRowWidget` – 플레이어 이름, 상태, 색상 표시가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_NameTagWidget` – 이름, 스케일, 말하기 표시가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_InteractionWidget` – 위젯 컨트롤러 설정이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_CameraProfile` – 카메라 설정 프로필이 태그로 올바르게 검색되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_CameraManagerComponent` – 상태 태그 변경 시 카메라 프로필 전환, 블렌딩이 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_PlayerSoundSubsystem` – 메시 타입별 사운드 조회가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_PlayerSoundSettings` – DeveloperSettings에서 DataAsset 경로가 올바르게 설정되는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_FoleyAudioBank` – 태그 기반 사운드 조회가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_OnlineSessionSubsystem` – 모든 세션 관련 함수(호스트, 찾기, 조인, 파괴, 초대)가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_OnlineSessionSubsystem` – 음성 채팅 시작/종료, Mute/Unmute가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_OnlineSessionSubsystem` – 네트워크 실패 처리, 세션 정리가 정상 작동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_OnlineSessionSubsystem` – `UpdateVoiceMember`가 생존 상태에 따라 Mute/Unmute를 올바르게 수행하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_OnlineSessionSubsystem` – `IsRemotePlayerTalking`이 올바르게 음성 감지를 반환하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_OnlineSessionSubsystem` – `ShowInviteUI`가 Steam 오버레이를 여는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_OnlineSessionSubsystem` – `SetSessionInGame`이 세션 설정을 올바르게 업데이트하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_OnlineSessionSubsystem` – `UpdateCurrentPlayers`가 세션 메타데이터를 올바르게 갱신하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_OnlineSessionSubsystem` – `GetServerNameByIndex`가 Base64 디코딩을 올바르게 수행하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_OnlineSessionSubsystem` – `VerifyPasswordAgainstIndex`가 MD5 해시 비교를 올바르게 수행하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_OnlineSessionSubsystem` – `IsInGameByIndex`가 게임 진행 중인 방을 올바르게 식별하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_OnlineSessionSubsystem` – `OnSessionUserInviteAccepted`가 초대 수락 시 세션 참가를 올바르게 처리하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_OnlineSessionSubsystem` – `OnDestroyThenRecreateSession`이 재호스트/초대 참가/메뉴 복귀를 올바르게 분기하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_OnlineSessionSubsystem` – `HandleNetworkFailure`가 모든 내부 상태를 리셋하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_OnlineSessionSubsystem` – `IsLocalHost`가 올바르게 호스트 여부를 판단하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_OnlineSessionSubsystem` – `HostSessionAuto`/`FindSessionsAuto`가 NULL OSS 여부에 따라 LAN/Online을 자동 선택하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_OnlineSessionSubsystem` – `CancelFind`가 검색을 중단하고 델리게이트를 정리하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_OnlineSessionSubsystem` – `OnCreateSessionComplete`가 성공 시 로비로 이동하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_OnlineSessionSubsystem` – `OnFindSessionsComplete`가 중복 결과를 제거하고 유효한 세션만 남기는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_OnlineSessionSubsystem` – `OnJoinSessionComplete`가 성공 시 `ClientTravel`을 호출하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_OnlineSessionSubsystem` – `DestroyCurrentSession`가 호스트/클라이언트 경로를 올바르게 분기하는가? |
| 싱글플레이 | 기능 | P2-Medium | `AO_OnlineSessionSubsystem` – `bOpInProgress` 플래그가 중복 호출을 방지하는가? |
| 싱글플레이 | 기능 | P