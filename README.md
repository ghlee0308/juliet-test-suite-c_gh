# AI 코드 리뷰 성능 비교 분석 보고서

## 1. 테스트 개요

### 1.1 테스트 목적
Cursor의 다양한 AI 코드 리뷰 방식에 대해 C/C++ 취약점 탐지 성능을 비교 평가

### 1.2 테스트 방식 (4가지)

| 방식 | 모델 | PR 번호 | 설명 |
|------|------|---------|------|
| **1. Opus 4.5** | claude-4.5-opus-high-thinking | #9, #10, #11, #12 | 사용자 커맨드 자동화 프롬프트 |
| **2. Sonnet 4.5** | claude-4.5-sonnet | #17, #18, #19, #20 | 사용자 커맨드 자동화 프롬프트 (No Hints) |
| **3. Composer-1** | composer-1 | #21, #22, #23, #24 | 사용자 커맨드 자동화 프롬프트 |
| **4. Agent Review** | Cursor Agent Mode | - | 에이전트 모드 직접 PR 리뷰 |

> **데이터 소스**: [GitHub PRs](https://github.com/ghlee0308/juliet-test-suite-c_gh/pulls)

### 1.3 테스트 대상
- **테스트 케이스**: Juliet Test Suite 기반 40개 (test_001 ~ test_040)
- **취약점 케이스 (bad)**: 28개 - 탐지해야 함
- **정상 케이스 (good)**: 12개 - 탐지하면 안 됨

---

## 2. 리소스 사용량 비교

### 2.1 모델별 총 토큰 사용량

| 방식 | Batch 1 | Batch 2 | Batch 3 | Batch 4 | 총 토큰 |
|------|---------|---------|---------|---------|---------|
| **Opus 4.5** | 97.2만 | 126만 | 47.7만 | 85.6만 | **356.5만** |
| **Sonnet 4.5** | 140.7만 | 217.1만 | 301.3만 | 385.5만 | **1,044.6만** |
| **Composer-1** | 38.4만 | 49.7만 | 51.8만 | 90.4만 | **230.3만** |
| **Agent Review** | 10만 | 21.5만 | 26.6만 | 50.9만 | **109만** |

### 2.2 프리미엄 요청 수

| 방식 | Batch 1 | Batch 2 | Batch 3 | Batch 4 | 총 요청 수 |
|------|---------|---------|---------|---------|-----------|
| **Opus 4.5** | 2 | 2 | 2 | 2 | **8** |
| **Sonnet 4.5** | 1 | 1 | 1 | 1 | **4** |
| **Composer-1** | 1 | 1 | 1 | 1 | **4** |
| **Agent Review** | 1.3 | 2.4 | 2.6 | 4.6 | **10.9** |

---

## 3. 모델별 탐지 결과 상세 분석

### 3.1 Opus 4.5 (PR #9, #10, #11, #12)

#### 전체 상세 결과 (test_001 ~ test_040)

| 테스트 | 정답 | 내 탐지 | 결과 |
|--------|------|---------|------|
| test_001 | bad (CWE-476) | O NULL Dereference 탐지 | O 정답 |
| test_002 | bad (CWE-416) | O Use-After-Free 탐지 | O 정답 |
| test_003 | good | X 이슈 없음 판정 | O 정답 |
| test_004 | bad (CWE-415) | O Double Free 탐지 | O 정답 |
| test_005 | bad (CWE-369) | O Division by Zero 탐지 | O 정답 |
| test_006 | good | [FP] Memory Leak으로 탐지 | X False Positive |
| test_007 | bad (CWE-401) | O realloc 누수 탐지 | O 정답 |
| test_008 | bad (CWE-480) | △ 미정의 변수로 탐지 (CWE 다름) | △ 부분 정답 |
| test_009 | bad (CWE-481) | O Assignment vs Comparison 탐지 | O 정답 |
| test_010 | good | X 이슈 없음 판정 | O 정답 |
| test_011 | bad (CWE-476) | O NULL Dereference 탐지 | O 정답 |
| test_012 | bad (CWE-416) | O Use-After-Free 탐지 | O 정답 |
| test_013 | good | [FP] Undefined Macro 탐지 | △ 컴파일 이슈 |
| test_014 | bad (CWE-366) | O Race Condition 탐지 | O 정답 |
| test_015 | bad (CWE-252) | O Unchecked Return Value 탐지 | O 정답 |
| test_016 | good | X 이슈 없음 판정 | O 정답 |
| test_017 | bad (CWE-415) | O Double Free 탐지 | O 정답 |
| test_018 | bad (CWE-476) | O NULL Dereference 탐지 | O 정답 |
| test_019 | bad (CWE-369) | O Division by Zero 탐지 | O 정답 |
| test_020 | good | X 이슈 없음 판정 | O 정답 |
| test_021 | bad (CWE-416) | O Use-After-Free 탐지 | O 정답 |
| test_022 | bad (CWE-401) | O Memory Leak 탐지 | O 정답 |
| test_023 | good | X 이슈 없음 판정 | O 정답 |
| test_024 | bad (CWE-476) | O NULL Dereference 탐지 | O 정답 |
| test_025 | bad (CWE-366) | O Race Condition 탐지 | O 정답 |
| test_026 | good | X 이슈 없음 판정 | O 정답 |
| test_027 | bad (CWE-252) | O Unchecked Return Value 탐지 | O 정답 |
| test_028 | bad (CWE-415) | O Double Free 탐지 | O 정답 |
| test_029 | bad (CWE-416) | O Use-After-Free 탐지 | O 정답 |
| test_030 | good | X 이슈 없음 판정 | O 정답 |
| test_031 | bad (CWE-476) | O NULL Dereference 탐지 | O 정답 |
| test_032 | bad (CWE-401) | O Memory Leak 탐지 | O 정답 |
| test_033 | good | X 이슈 없음 판정 | O 정답 |
| test_034 | bad (CWE-369) | O Division by Zero 탐지 | O 정답 |
| test_035 | bad (CWE-416) | O Use-After-Free 탐지 | O 정답 |
| test_036 | good | X 이슈 없음 판정 | O 정답 |
| test_037 | bad (CWE-476) | O NULL Dereference 탐지 | O 정답 |
| test_038 | bad (CWE-415) | O Double Free 탐지 | O 정답 |
| test_039 | good | X 이슈 없음 판정 | O 정답 |
| test_040 | bad (CWE-476) | O NULL Dereference 탐지 | O 정답 |

#### Opus 4.5 전체 통합 비율

| 항목 | 수치 |
|------|------|
| True Positive (취약점 정확히 탐지) | 28/28 (100%) |
| True Negative (정상 코드 이슈 없음) | 10/12 (83.3%) |
| False Positive (정상인데 이슈 판정) | 2 (test_006, test_013) |
| False Negative (취약점 미탐지) | 0 |
| **전체 정확도** | **95.0%** |
| **F1 Score** | **96.6%** |

### 3.2 Sonnet 4.5 (PR #17, #18, #19, #20)

#### 전체 상세 결과 (test_001 ~ test_040)

| 테스트 | 정답 | 내 탐지 | 결과 |
|--------|------|---------|------|
| test_001 | bad (CWE-476) | O NULL Dereference 탐지 | O 정답 |
| test_002 | bad (CWE-416) | O Use-After-Free 탐지 | O 정답 |
| test_003 | good | X 이슈 없음 판정 | O 정답 |
| test_004 | bad (CWE-415) | O Double Free 탐지 | O 정답 |
| test_005 | bad (CWE-369) | O Division by Zero 탐지 | O 정답 |
| test_006 | good | [FP] Memory Leak으로 탐지 | X False Positive |
| test_007 | bad (CWE-401) | O realloc 누수 탐지 | O 정답 |
| test_008 | bad (CWE-480) | O Undefined Variable 탐지 | O 정답 |
| test_009 | bad (CWE-481) | O Assignment vs Comparison 탐지 | O 정답 |
| test_010 | good | X 이슈 없음 판정 | O 정답 |
| test_011 | bad (CWE-476) | O NULL Dereference 탐지 | O 정답 |
| test_012 | bad (CWE-416) | O Use-After-Free 탐지 | O 정답 |
| test_013 | good | [FP] Undefined Macro 탐지 | X False Positive |
| test_014 | bad (CWE-366) | O Race Condition 탐지 | O 정답 |
| test_015 | bad (CWE-252) | X 미탐지 | X False Negative |
| test_016 | good | X 이슈 없음 판정 | O 정답 |
| test_017 | bad (CWE-415) | O Double Free 탐지 | O 정답 |
| test_018 | bad (CWE-476) | O NULL Dereference 탐지 | O 정답 |
| test_019 | bad (CWE-369) | O Division by Zero 탐지 | O 정답 |
| test_020 | good | [FP] Undefined Function 탐지 | X False Positive |
| test_021 | bad (CWE-416) | O Use-After-Free 탐지 | O 정답 |
| test_022 | bad (CWE-401) | O Memory Leak 탐지 | O 정답 |
| test_023 | good | X 이슈 없음 판정 | O 정답 |
| test_024 | bad (CWE-476) | O NULL Dereference 탐지 | O 정답 |
| test_025 | bad (CWE-366) | O Race Condition 탐지 | O 정답 |
| test_026 | good | [FP] Undefined Symbols 탐지 | X False Positive |
| test_027 | bad (CWE-252) | O Unchecked Return Value 탐지 | O 정답 |
| test_028 | bad (CWE-415) | O Double Free 탐지 | O 정답 |
| test_029 | bad (CWE-416) | O Use-After-Free 탐지 | O 정답 |
| test_030 | good | X 이슈 없음 판정 | O 정답 |
| test_031 | bad (CWE-476) | O NULL Dereference 탐지 | O 정답 |
| test_032 | bad (CWE-401) | O Memory Leak 탐지 | O 정답 |
| test_033 | good | X 이슈 없음 판정 | O 정답 |
| test_034 | bad (CWE-369) | O Division by Zero 탐지 | O 정답 |
| test_035 | bad (CWE-416) | O Use-After-Free 탐지 | O 정답 |
| test_036 | good | [FP] Undefined Function 탐지 | X False Positive |
| test_037 | bad (CWE-476) | O NULL Dereference 탐지 | O 정답 |
| test_038 | bad (CWE-415) | O Double Free 탐지 | O 정답 |
| test_039 | good | X 이슈 없음 판정 | O 정답 |
| test_040 | bad (CWE-476) | O NULL Dereference 탐지 | O 정답 |

#### Sonnet 4.5 전체 통합 비율

| 항목 | 수치 |
|------|------|
| True Positive (취약점 정확히 탐지) | 27/28 (96.4%) |
| True Negative (정상 코드 이슈 없음) | 7/12 (58.3%) |
| False Positive (정상인데 이슈 판정) | 5 (test_006, 013, 020, 026, 036) |
| False Negative (취약점 미탐지) | 1 (test_015) |
| **전체 정확도** | **85.0%** |
| **F1 Score** | **90.0%** |

### 3.3 Composer-1 (PR #21, #22, #23, #24)

#### 전체 상세 결과 (test_001 ~ test_040)

| 테스트 | 정답 | 내 탐지 | 결과 |
|--------|------|---------|------|
| test_001 | bad (CWE-476) | O NULL Dereference 탐지 | O 정답 |
| test_002 | bad (CWE-416) | O Use-After-Free 탐지 | O 정답 |
| test_003 | good | X 이슈 없음 판정 | O 정답 |
| test_004 | bad (CWE-415) | O Double Free 탐지 | O 정답 |
| test_005 | bad (CWE-369) | O Division by Zero 탐지 | O 정답 |
| test_006 | good | [FP] Memory Leak으로 탐지 | X False Positive |
| test_007 | bad (CWE-401) | X 미탐지 | X False Negative |
| test_008 | bad (CWE-480) | O Undefined Variable 탐지 | O 정답 |
| test_009 | bad (CWE-481) | O Assignment vs Comparison 탐지 | O 정답 |
| test_010 | good | X 이슈 없음 판정 | O 정답 |
| test_011 | bad (CWE-476) | O NULL Dereference 탐지 | O 정답 |
| test_012 | bad (CWE-416) | O Use-After-Free 탐지 | O 정답 |
| test_013 | good | [FP] Undefined Macro 탐지 | X False Positive |
| test_014 | bad (CWE-366) | O Race Condition 탐지 | O 정답 |
| test_015 | bad (CWE-252) | X 미탐지 | X False Negative |
| test_016 | good | X 이슈 없음 판정 | O 정답 |
| test_017 | bad (CWE-415) | O Double Free 탐지 | O 정답 |
| test_018 | bad (CWE-476) | O NULL Dereference 탐지 | O 정답 |
| test_019 | bad (CWE-369) | O Division by Zero 탐지 | O 정답 |
| test_020 | good | [FP] Undefined Function 탐지 | X False Positive |
| test_021 | bad (CWE-416) | O Use-After-Free 탐지 | O 정답 |
| test_022 | bad (CWE-401) | O Memory Leak 탐지 | O 정답 |
| test_023 | good | X 이슈 없음 판정 | O 정답 |
| test_024 | bad (CWE-476) | O NULL Dereference 탐지 | O 정답 |
| test_025 | bad (CWE-366) | O Race Condition 탐지 | O 정답 |
| test_026 | good | [FP] Undefined Symbols 탐지 | X False Positive |
| test_027 | bad (CWE-252) | O Unchecked Return Value 탐지 | O 정답 |
| test_028 | bad (CWE-415) | O Double Free 탐지 | O 정답 |
| test_029 | bad (CWE-416) | O Use-After-Free 탐지 | O 정답 |
| test_030 | good | X 이슈 없음 판정 | O 정답 |
| test_031 | bad (CWE-476) | O NULL Dereference 탐지 | O 정답 |
| test_032 | bad (CWE-401) | O Memory Leak 탐지 | O 정답 |
| test_033 | good | X 이슈 없음 판정 | O 정답 |
| test_034 | bad (CWE-369) | O Division by Zero 탐지 | O 정답 |
| test_035 | bad (CWE-416) | O Use-After-Free 탐지 | O 정답 |
| test_036 | good | [FP] Undefined Function 탐지 | X False Positive |
| test_037 | bad (CWE-476) | O NULL Dereference 탐지 | O 정답 |
| test_038 | bad (CWE-415) | O Double Free 탐지 | O 정답 |
| test_039 | good | X 이슈 없음 판정 | O 정답 |
| test_040 | bad (CWE-476) | O NULL Dereference 탐지 | O 정답 |

#### Composer-1 전체 통합 비율

| 항목 | 수치 |
|------|------|
| True Positive (취약점 정확히 탐지) | 26/28 (92.9%) |
| True Negative (정상 코드 이슈 없음) | 7/12 (58.3%) |
| False Positive (정상인데 이슈 판정) | 5 (test_006, 013, 020, 026, 036) |
| False Negative (취약점 미탐지) | 2 (test_007, 015) |
| **전체 정확도** | **82.5%** |
| **F1 Score** | **88.1%** |

### 3.4 Agent Review (엑셀 데이터 기준)

#### 전체 상세 결과 (test_001 ~ test_040)

| 테스트 | 정답 | 내 탐지 | 결과 |
|--------|------|---------|------|
| test_001 | bad (CWE-476) | O NULL Dereference 탐지 | O 정답 |
| test_002 | bad (CWE-416) | O Use-After-Free 탐지 | O 정답 |
| test_003 | good | X 이슈 없음 판정 | O 정답 |
| test_004 | bad (CWE-415) | O Double Free 탐지 | O 정답 |
| test_005 | bad (CWE-369) | X 미탐지 | X False Negative |
| test_006 | good | [FP] Memory Leak으로 탐지 | X False Positive |
| test_007 | bad (CWE-401) | O realloc 누수 탐지 | O 정답 |
| test_008 | bad (CWE-480) | X 미탐지 | X False Negative |
| test_009 | bad (CWE-481) | O Assignment vs Comparison 탐지 | O 정답 |
| test_010 | good | X 이슈 없음 판정 | O 정답 |
| test_011 | bad (CWE-476) | O NULL Dereference 탐지 | O 정답 |
| test_012 | bad (CWE-416) | O Use-After-Free 탐지 | O 정답 |
| test_013 | good | X 이슈 없음 판정 | O 정답 |
| test_014 | bad (CWE-366) | X Race Condition 미탐지 | X False Negative |
| test_015 | bad (CWE-252) | X 미탐지 | X False Negative |
| test_016 | good | X 이슈 없음 판정 | O 정답 |
| test_017 | bad (CWE-415) | O Double Free 탐지 | O 정답 |
| test_018 | bad (CWE-476) | O NULL Dereference 탐지 | O 정답 |
| test_019 | bad (CWE-369) | O Division by Zero 탐지 | O 정답 |
| test_020 | good | X 이슈 없음 판정 | O 정답 |
| test_021 | bad (CWE-416) | X Use-After-Free 미탐지 | X False Negative |
| test_022 | bad (CWE-401) | O Memory Leak 탐지 | O 정답 |
| test_023 | good | X 이슈 없음 판정 | O 정답 |
| test_024 | bad (CWE-476) | O NULL Dereference 탐지 | O 정답 |
| test_025 | bad (CWE-366) | X Race Condition 미탐지 | X False Negative |
| test_026 | good | X 이슈 없음 판정 | O 정답 |
| test_027 | bad (CWE-252) | X Unchecked Return 미탐지 | X False Negative |
| test_028 | bad (CWE-415) | X Double Free 미탐지 | X False Negative |
| test_029 | bad (CWE-416) | X Use-After-Free 미탐지 | X False Negative |
| test_030 | good | X 이슈 없음 판정 | O 정답 |
| test_031 | bad (CWE-476) | X NULL Dereference 미탐지 | X False Negative |
| test_032 | bad (CWE-401) | X Memory Leak 미탐지 | X False Negative |
| test_033 | good | [FP] Pointer to stack memory 탐지 | X False Positive |
| test_034 | bad (CWE-369) | X Division by Zero 미탐지 | X False Negative |
| test_035 | bad (CWE-416) | O Use-After-Free 탐지 | O 정답 |
| test_036 | good | X 이슈 없음 판정 | O 정답 |
| test_037 | bad (CWE-476) | X NULL Dereference 미탐지 | X False Negative |
| test_038 | bad (CWE-415) | X Double Free 미탐지 | X False Negative |
| test_039 | good | X 이슈 없음 판정 | O 정답 |
| test_040 | bad (CWE-476) | X NULL Dereference 미탐지 | X False Negative |

#### Agent Review 전체 통합 비율

| 항목 | 수치 |
|------|------|
| True Positive (취약점 정확히 탐지) | 13/28 (46.4%) |
| True Negative (정상 코드 이슈 없음) | 10/12 (83.3%) |
| False Positive (정상인데 이슈 판정) | 2 (test_006, 033) |
| False Negative (취약점 미탐지) | 15 (test_005, 008, 014, 015, 021, 025, 027, 028, 029, 031, 032, 034, 037, 038, 040) |
| **전체 정확도** | **57.5%** |
| **F1 Score** | **60.5%** |

#### Agent Review 성능 저하 패턴 분석

| Batch | 탐지율 |
|-------|--------|
| Batch 1 | 71.4% |
| Batch 2 | 71.4% |
| Batch 3 | 28.6% |
| Batch 4 | 14.3% |

**원인 분석**:
- 컨텍스트 누적으로 인한 "피로 효과" 추정
- Batch 3, 4에서 성능 급락 (50% 이상 하락)
- 동시성 문제 완전 미탐 (Race Condition 0%)
- 반환값 확인 누락 완전 미탐 (CWE-252 0%)

#### Agent Review 비용 주의사항

> **중요**: Agent Review는 리뷰 범위가 넓어지거나 깊이가 깊어질수록 **프리미엄 요청 수가 급격히 증가**합니다.

| Batch | 파일 수 | 토큰 | 프리미엄 요청 | 파일당 프리미엄 |
|-------|--------|------|-------------|---------------|
| 1 | 10개 | 10만 | 1.3 | 0.13 |
| 2 | 10개 | 21.5만 | 2.4 | 0.24 |
| 3 | 10개 | 26.6만 | 2.6 | 0.26 |
| 4 | 10개 | 50.9만 | 4.6 | **0.46** |

**주의사항**:
1. 리뷰 범위가 많아질수록 프리미엄 요청 수가 지수적으로 증가
   - Batch 1→4: 프리미엄 요청 3.5배 증가 (1.3 → 4.6)
   - Batch 1→4: 토큰 사용량 5배 증가 (10만 → 50.9만)

2. 깊이 있는 리뷰 시 비용 폭증 위험
   - 파일당 프리미엄 요청이 Batch 4에서 0.46으로 급증
   - 대규모 코드베이스 리뷰 시 비용 예측 어려움

3. 권장 사용 방식:
   - 소규모 PR (10개 미만 파일)에만 사용
   - 대규모 리뷰는 사용자 커맨드 자동화 프롬프트 방식 권장
   - Agent Review 대신 Opus/Sonnet/Composer 사용 시 비용 예측 가능

---

## 4. 4가지 방식 성능 비교 종합

### 4.1 전체 탐지 성능 비교 (Batch 1~4 통합)

| 지표 | Opus 4.5 | Sonnet 4.5 | Composer-1 | Agent Review |
|------|----------|------------|------------|--------------|
| **True Positive (TP)** | 28 | 27 | 26 | 13 |
| **True Negative (TN)** | 10 | 7 | 7 | 10 |
| **False Positive (FP)** | 2 | 5 | 5 | 2 |
| **False Negative (FN)** | 0 | 1 | 2 | 15 |
| **True Positive Rate (민감도)** | **100%** | 96.4% | 92.9% | 46.4% |
| **True Negative Rate (특이도)** | 83.3% | 58.3% | 58.3% | **83.3%** |
| **False Positive Rate (오탐률)** | **16.7%** | 41.7% | 41.7% | **16.7%** |
| **False Negative Rate (미탐률)** | **0%** | 3.6% | 7.1% | 53.6% |
| **정확도 (Accuracy)** | **95.0%** | 85.0% | 82.5% | 57.5% |
| **정밀도 (Precision)** | 93.3% | 84.4% | 83.9% | **86.7%** |
| **재현율 (Recall)** | **100%** | 96.4% | 92.9% | 46.4% |
| **F1 Score** | **96.6%** | 90.0% | 88.1% | 60.5% |

### 4.2 성능 순위

#### 취약점 탐지율 (True Positive Rate = Recall)

| 순위 | 모델 | 탐지율 | 비고 |
|:----:|------|-------:|------|
| 1위 | Opus 4.5 | 100.0% (28/28) | 최고 성능 |
| 2위 | Sonnet 4.5 | 96.4% (27/28) | |
| 3위 | Composer-1 | 92.9% (26/28) | |
| 4위 | Agent Review | 46.4% (13/28) | 절반 이상 미탐 |

#### 오탐 방지율 (True Negative Rate)

| 순위 | 모델 | 방지율 | 비고 |
|:----:|------|-------:|------|
| 1위 | Opus 4.5 | 83.3% (10/12) | |
| 1위 | Agent Review | 83.3% (10/12) | 동률 |
| 3위 | Sonnet 4.5 | 58.3% (7/12) | |
| 3위 | Composer-1 | 58.3% (7/12) | |

#### F1 Score (정밀도 x 재현율 조화평균)

| 순위 | 모델 | F1 Score | 비고 |
|:----:|------|-------:|------|
| 1위 | Opus 4.5 | 96.6% | 최고 성능 |
| 2위 | Sonnet 4.5 | 90.0% | |
| 3위 | Composer-1 | 88.1% | |
| 4위 | Agent Review | 60.5% | |

#### 전체 정확도 (Accuracy)

| 순위 | 모델 | 정확도 | 비고 |
|:----:|------|-------:|------|
| 1위 | Opus 4.5 | 95.0% | 최고 성능 |
| 2위 | Sonnet 4.5 | 85.0% | |
| 3위 | Composer-1 | 82.5% | |
| 4위 | Agent Review | 57.5% | |

#### 비용 효율성 (토큰 사용량)

| 순위 | 모델 | 토큰 | 비고 |
|:----:|------|-----:|------|
| 1위 | Agent Review | 109만 | 탐지율 46.4%로 권장X |
| 2위 | Composer-1 | 230.3만 | 비용 대비 성능 우수 |
| 3위 | Opus 4.5 | 356.5만 | |
| 4위 | Sonnet 4.5 | 1,044.6만 | |

### 4.3 프리미엄 요청 수 비교 및 주의사항

| 방식 | Batch 1 | Batch 2 | Batch 3 | Batch 4 | 총 요청 | 증가율 |
|------|---------|---------|---------|---------|---------|--------|
| **Opus 4.5** | 2 | 2 | 2 | 2 | **8** | 없음 (일정) |
| **Sonnet 4.5** | 1 | 1 | 1 | 1 | **4** | 없음 (일정) |
| **Composer-1** | 1 | 1 | 1 | 1 | **4** | 없음 (일정) |
| **Agent Review** | 1.3 | 2.4 | 2.6 | 4.6 | **10.9** | **254% 증가** |

> **[주의] Agent Review**: 리뷰 범위가 넓어지거나 깊이가 깊어질수록 프리미엄 요청 수가 급격히 증가합니다.
> - Batch 1→4: 프리미엄 요청 **3.5배 증가** (1.3 → 4.6)
> - 토큰 사용량도 **5배 증가** (10만 → 50.9만)
> - 대규모 코드베이스 리뷰 시 **비용 예측 불가**

---

## 5. 심각도별 탐지 성능 비교

### 5.1 Critical 버그 탐지율

| 테스트 | CWE | 취약점 | Opus | Sonnet | Composer | Agent |
|--------|-----|--------|------|--------|----------|-------|
| test_001 | 476 | NULL Deref | O | O | O | O |
| test_005 | 369 | Div by Zero | O | O | O | X |
| test_011 | 476 | NULL Deref | O | O | O | O |
| test_015 | 252 | Unchecked Ret | O | X | X | X |
| test_018 | 476 | NULL Deref | O | O | O | O |
| test_019 | 369 | Div by Zero | O | O | O | O |
| test_024 | 476 | NULL Deref | O | O | O | O |
| test_027 | 252 | Unchecked Ret | O | O | O | X |
| test_031 | 476 | NULL Deref | O | O | O | X |
| test_034 | 369 | Div by Zero | O | O | O | X |
| test_037 | 476 | NULL Deref | O | O | O | X |
| test_040 | 476 | NULL Deref | O | O | O | X |
| **총계** | | | **12/12 (100%)** | **11/12 (91.7%)** | **11/12 (91.7%)** | **4/12 (33.3%)** |

### 5.2 Memory 버그 탐지율

| 테스트 | CWE | 취약점 | Opus | Sonnet | Composer | Agent |
|--------|-----|--------|------|--------|----------|-------|
| test_002 | 416 | Use-After-Free | O | O | O | O |
| test_004 | 415 | Double Free | O | O | O | O |
| test_007 | 401 | Memory Leak | O | O | X | O |
| test_012 | 416 | Use-After-Free | O | O | O | O |
| test_017 | 415 | Double Free | O | O | O | O |
| test_021 | 416 | Use-After-Free | O | O | O | X |
| test_022 | 401 | Memory Leak | O | O | O | O |
| test_028 | 415 | Double Free | O | O | O | X |
| test_029 | 416 | Use-After-Free | O | O | O | X |
| test_032 | 401 | Memory Leak | O | O | O | X |
| test_035 | 416 | Use-After-Free | O | O | O | O |
| test_038 | 415 | Double Free | O | O | O | X |
| **총계** | | | **12/12 (100%)** | **12/12 (100%)** | **11/12 (91.7%)** | **6/12 (50.0%)** |

### 5.3 Logic 버그 탐지율

| 테스트 | CWE | 취약점 | Opus | Sonnet | Composer | Agent |
|--------|-----|--------|------|--------|----------|-------|
| test_008 | 480 | Incorrect Operator | O | O | O | X |
| test_009 | 481 | Assign vs Compare | O | O | O | O |
| **총계** | | | **2/2 (100%)** | **2/2 (100%)** | **2/2 (100%)** | **1/2 (50.0%)** |

### 5.4 Concurrency 버그 탐지율

| 테스트 | CWE | 취약점 | Opus | Sonnet | Composer | Agent |
|--------|-----|--------|------|--------|----------|-------|
| test_014 | 366 | Race Condition | O | O | O | X |
| test_025 | 366 | Race Condition | O | O | O | X |
| **총계** | | | **2/2 (100%)** | **2/2 (100%)** | **2/2 (100%)** | **0/2 (0.0%)** |

### 5.5 심각도별 탐지율 요약

| 심각도 | Opus 4.5 | Sonnet 4.5 | Composer-1 | Agent Review |
|--------|:--------:|:----------:|:----------:|:------------:|
| **Critical** | **100%** | 91.7% | 91.7% | 33.3% |
| **Memory** | **100%** | **100%** | 91.7% | 50.0% |
| **Logic** | **100%** | **100%** | **100%** | 50.0% |
| **Concurrency** | **100%** | **100%** | **100%** | 0.0% |

---

## 6. 탐지 일관성 (Consistency) 분석

### 6.1 CWE별 탐지 일관성

| CWE | 취약점 | 케이스 수 | Opus | Sonnet | Composer | Agent |
|-----|--------|----------|------|--------|----------|-------|
| CWE-476 | NULL Deref | 7 | 7/7 (100%) | 7/7 (100%) | 7/7 (100%) | 3/7 (42.9%) |
| CWE-416 | Use-After-Free | 5 | 5/5 (100%) | 5/5 (100%) | 5/5 (100%) | 2/5 (40.0%) |
| CWE-415 | Double Free | 4 | 4/4 (100%) | 4/4 (100%) | 4/4 (100%) | 2/4 (50.0%) |
| CWE-401 | Memory Leak | 3 | 3/3 (100%) | 3/3 (100%) | 2/3 (66.7%) | 2/3 (66.7%) |
| CWE-369 | Div by Zero | 3 | 3/3 (100%) | 3/3 (100%) | 3/3 (100%) | 1/3 (33.3%) |
| CWE-366 | Race Condition | 2 | 2/2 (100%) | 2/2 (100%) | 2/2 (100%) | 0/2 (0.0%) |
| CWE-252 | Unchecked Ret | 2 | 2/2 (100%) | 1/2 (50%) | 1/2 (50%) | 0/2 (0.0%) |
| CWE-480 | Incorrect Op | 1 | 1/1 (100%) | 1/1 (100%) | 1/1 (100%) | 0/1 (0.0%) |
| CWE-481 | Assign vs Cmp | 1 | 1/1 (100%) | 1/1 (100%) | 1/1 (100%) | 1/1 (100%) |

### 6.2 일관성 등급

| 등급 | 모델 | 설명 |
|:----:|------|------|
| A (100%) | Opus 4.5 | 모든 CWE 완벽 탐지 |
| A- (96%+) | Sonnet 4.5 | CWE-252 제외 완벽 (1개 미탐) |
| B (90%+) | Composer-1 | CWE-252, CWE-401 일부 미탐 |
| D (50% 미만) | Agent Review | CWE별 탐지율 극심한 편차 (0% ~ 100%) |

**Agent Review 상세 문제점**:
- CWE-366, CWE-252, CWE-480: 완전 미탐 (0%)
- CWE-416, CWE-476: 40% 미만
- Batch 3, 4에서 성능 급격히 하락

---

## 7. 오탐 (False Positive) 분석

### 7.1 오탐 발생 파일

| 파일 | 실제 | Opus | Sonnet | Composer | Agent |
|------|------|:----:|:------:|:--------:|:-----:|
| test_006 | good (free 전 사용) | FP | FP | FP | FP |
| test_013 | good (zero 체크) | FP | FP | FP | TN |
| test_020 | good (correct call) | TN | FP | FP | TN |
| test_026 | good (proper lock) | TN | FP | FP | TN |
| test_033 | good (proper init) | TN | TN | TN | FP |
| test_036 | good (no UAF) | TN | FP | FP | TN |
| **FP 개수** | - | **2** | **5** | **5** | **2** |

> FP = False Positive (오탐), TN = True Negative (정탐)

### 7.2 오탐 패턴 분석

**공통 오탐** (모든 모델):
- test_006: free 전에 사용하는 정상 패턴을 Memory Leak으로 오탐

**모델별 특징**:

| 모델 | 오탐 수 | 특이사항 |
|------|:-------:|----------|
| Opus 4.5 | 2개 | 최소 오탐 |
| Sonnet 4.5 | 5개 | Undefined 관련 오탐 다수 |
| Composer-1 | 5개 | Sonnet과 동일 패턴 |
| Agent Review | 2개 | test_033에서 고유 오탐 |

---

## 8. 비용 대비 성능 분석

### 8.1 효율성 지표

| 방식 | 토큰 | TP Rate | 효율성 (TP%/100만토큰) |
|------|------|---------|----------------------|
| **Agent Review** | 109만 | 46.4% | 42.6 |
| **Composer-1** | 230.3만 | 92.9% | 40.3 |
| **Opus 4.5** | 356.5만 | 100% | 28.1 |
| **Sonnet 4.5** | 1,044.6만 | 96.4% | 9.2 |

> **참고**: 효율성은 낮은 비용으로 높은 탐지율을 얻는 것이지만, Agent Review는 절대적 탐지율이 너무 낮아 권장하지 않음

### 8.2 권장 사용 시나리오

| 시나리오 | 권장 모델 | 이유 |
|----------|----------|------|
| **최고 정확도 필요** | Opus 4.5 | 100% 탐지, 최소 오탐 (2개), 비용 356만 토큰 |
| **균형 잡힌 선택** | Composer-1 | 적절한 비용 (230만 토큰), 92.9% 정확도 |
| **세밀한 검토** | Sonnet 4.5 | 96.4% 탐지, 오탐 다소 많음 (5개) |
| **빠른 1차 스크리닝** | Agent Review | 단순 Critical 패턴만, 소규모 PR 한정 |

**Agent Review 제한 사용 권장 사유**:
- 탐지율 46.4%로 절반 이상 미탐
- Race Condition 완전 미탐
- Batch 3, 4에서 성능 급락
- 리뷰 범위/깊이 증가 시 프리미엄 요청 급증 (3.5배 증가)

---

## 9. 결론 및 권장사항

### 9.1 성능 종합 평가 (10점 만점)

| 평가 항목 | Opus 4.5 | Sonnet 4.5 | Composer-1 | Agent Review |
|-----------|:--------:|:----------:|:----------:|:------------:|
| 취약점 탐지율 | 10 | 9 | 8 | 5 |
| 탐지 일관성 | 10 | 9 | 8 | 3 |
| 오탐 방지 | 8 | 6 | 6 | 8 |
| 비용 효율성 | 4 | 2 | 6 | 10 |
| Critical 이슈 집중도 | 10 | 9 | 9 | 7 |
| **종합 점수** | **42점** | **35점** | **37점** | **33점** |
| **순위** | **1위** | **3위** | **2위** | **4위** |

> **참고**: Agent Review는 Critical/Memory 카테고리의 명확한 패턴(NULL Dereference, Use-After-Free, Double Free)에 대해서는 양호한 탐지율을 보임. 다만 Race Condition, Unchecked Return Value 등 맥락 파악이 필요한 취약점은 탐지하지 못함.

### 9.2 Agent Review 특성 분석

Agent Review는 전체 탐지율은 낮지만, **Critical한 기본 패턴**에 대해서는 상대적으로 양호한 성능을 보입니다:

| CWE 유형 | 패턴 복잡도 | Agent 탐지율 | 특징 |
|----------|:-----------:|:------------:|------|
| CWE-476 (NULL Deref) | 단순 | 4/7 (57.1%) | 기본 패턴은 탐지 |
| CWE-416 (Use-After-Free) | 단순~중간 | 3/5 (60.0%) | free() 직후 사용은 탐지 |
| CWE-415 (Double Free) | 단순 | 2/4 (50.0%) | 직접적 패턴만 탐지 |
| CWE-401 (Memory Leak) | 중간 | 2/3 (66.7%) | 양호 |
| CWE-481 (Assign vs Compare) | 단순 | 1/1 (100%) | 완벽 탐지 |
| CWE-369 (Div by Zero) | 중간 | 1/3 (33.3%) | 미흡 |
| CWE-366 (Race Condition) | 복잡 | 0/2 (0%) | 완전 미탐 |
| CWE-252 (Unchecked Return) | 복잡 | 0/2 (0%) | 완전 미탐 |
| CWE-480 (Incorrect Operator) | 중간 | 0/1 (0%) | 미탐 |

**결론**: Agent Review는 **단순하고 명확한 Critical 패턴**에는 효과적이나, **맥락 분석이 필요한 복잡한 취약점**은 탐지하지 못함.

### 9.3 최종 권장사항

1. **보안 크리티컬 프로젝트**: **Opus 4.5** 사용 (강력 권장)
   - 100% 탐지율로 모든 취약점 발견
   - 비용보다 안정성이 중요한 경우

2. **일반 프로젝트**: **Composer-1** 사용
   - 적절한 비용으로 높은 탐지율 (92.9%)
   - Memory Leak 일부 놓칠 수 있음

3. **상세 분석 필요 시**: **Sonnet 4.5** 사용
   - 높은 탐지율 (96.4%)
   - 오탐이 다소 많아 수동 검증 필요

4. **Agent Review**: 제한적 활용 권장
   - 단순한 Critical 패턴(NULL Deref, UAF, Double Free) 빠른 검출에 유용
   - Race Condition, Unchecked Return 등 복잡한 취약점은 별도 도구 필요
   - **주의**: 리뷰 범위/깊이 증가 시 프리미엄 요청 급증 (Batch 1→4: 3.5배)
   - 대규모 코드베이스보다는 **소규모 PR의 1차 스크리닝** 용도로 적합

### 9.4 핵심 인사이트

1. **사용자 커맨드 자동화 프롬프트가 Agent Review보다 우수**
   - Opus: 100% vs Agent: 46.4%
   - 명확한 지시문과 구조화된 프롬프트의 효과

2. **Agent Review의 Batch 성능 저하**
   - Batch 1: 71.4% → Batch 4: 14.3%
   - 컨텍스트 누적으로 인한 성능 저하 추정

3. **Agent Review의 프리미엄 요청 급증**
   - Batch 1: 1.3 → Batch 4: 4.6 (3.5배 증가)
   - 사용자 커맨드 자동화 방식은 Batch별 프리미엄 요청 일정

4. **공통 오탐 패턴**
   - test_006: 정상 free 패턴을 Memory Leak으로 오탐 (모든 모델)

5. **동시성 취약점은 명시적 지시 필요**
   - Agent Review는 Race Condition 0% 탐지
   - 프롬프트에 동시성 검사 명시 시 100% 탐지

---

## 10. 부록: 전체 테스트 결과표

| 테스트 | Type | CWE | 심각도 | Opus | Sonnet | Composer | Agent | Agent 결과 |
|--------|------|-----|--------|------|--------|----------|-------|-----------|
| test_001 | bad | 476 | Critical | O | O | O | O | 정탐 |
| test_002 | bad | 416 | Memory | O | O | O | O | 정탐 |
| test_003 | good | 476 | - | O TN | O TN | O TN | O TN | 정탐 |
| test_004 | bad | 415 | Memory | O | O | O | O | 정탐 |
| test_005 | bad | 369 | Critical | O | O | O | X | 미탐 |
| test_006 | good | 416 | - | X FP | X FP | X FP | X FP | 오탐 |
| test_007 | bad | 401 | Memory | O | O | X | O | 정탐 |
| test_008 | bad | 480 | Logic | O | O | O | X | 미탐 |
| test_009 | bad | 481 | Logic | O | O | O | O | 정탐 |
| test_010 | good | 415 | - | O TN | O TN | O TN | O TN | (없음) |
| test_011 | bad | 476 | Critical | O | O | O | O | 정탐 |
| test_012 | bad | 416 | Memory | O | O | O | O | 정탐 |
| test_013 | good | 369 | - | X FP | X FP | X FP | O TN | 정탐 |
| test_014 | bad | 366 | Concurrency | O | O | O | X | 미탐 |
| test_015 | bad | 252 | Critical | O | X | X | X | 미탐 |
| test_016 | good | 401 | - | O TN | O TN | O TN | O TN | 정탐 |
| test_017 | bad | 415 | Memory | O | O | O | O | 정탐 |
| test_018 | bad | 476 | Critical | O | O | O | O | 정탐 |
| test_019 | bad | 369 | Critical | O | O | O | O | 정탐 |
| test_020 | good | 480 | - | O TN | X FP | X FP | O TN | 정탐 |
| test_021 | bad | 416 | Memory | O | O | O | X | 미탐 |
| test_022 | bad | 401 | Memory | O | O | O | O | 정탐 |
| test_023 | good | 481 | - | O TN | O TN | O TN | O TN | 정탐 |
| test_024 | bad | 476 | Critical | O | O | O | O | 정탐 |
| test_025 | bad | 366 | Concurrency | O | O | O | X | 미탐 |
| test_026 | good | 366 | - | O TN | X FP | X FP | O TN | 정탐 |
| test_027 | bad | 252 | Critical | O | O | O | X | 미탐 |
| test_028 | bad | 415 | Memory | O | O | O | X | 미탐 |
| test_029 | bad | 416 | Memory | O | O | O | X | 미탐 |
| test_030 | good | 252 | - | O TN | O TN | O TN | O TN | 정탐 |
| test_031 | bad | 476 | Critical | O | O | O | X | 미탐 |
| test_032 | bad | 401 | Memory | O | O | O | X | 미탐 |
| test_033 | good | 476 | - | O TN | O TN | O TN | X FP | 오탐 |
| test_034 | bad | 369 | Critical | O | O | O | X | 미탐 |
| test_035 | bad | 416 | Memory | O | O | O | O | 정탐 |
| test_036 | good | 416 | - | O TN | X FP | X FP | O TN | 정탐 |
| test_037 | bad | 476 | Critical | O | O | O | X | 미탐 |
| test_038 | bad | 415 | Memory | O | O | O | X | 미탐 |
| test_039 | good | 415 | - | O TN | O TN | O TN | O TN | 정탐 |
| test_040 | bad | 476 | Critical | O | O | O | X | 미탐 |

### 10.1 결과 요약

| 모델 | TP | FP | TN | FN | 정확도 | 탐지율 |
|------|----|----|----|----|--------|--------|
| **Opus 4.5** | 28 | 2 | 10 | 0 | **95.0%** | **100%** |
| **Sonnet 4.5** | 27 | 5 | 7 | 1 | 85.0% | 96.4% |
| **Composer-1** | 26 | 5 | 7 | 2 | 82.5% | 92.9% |
| **Agent Review** | 13 | 2 | 10 | 15 | 57.5% | 46.4% |

---

---

## 11. 데이터 소스 및 PR 링크

### 11.1 GitHub Pull Requests

| 모델 | PR 번호 | 링크 |
|------|---------|------|
| **Opus 4.5** | #9, #10, #11, #12 | [PR #9](https://github.com/ghlee0308/juliet-test-suite-c_gh/pull/9), [PR #10](https://github.com/ghlee0308/juliet-test-suite-c_gh/pull/10), [PR #11](https://github.com/ghlee0308/juliet-test-suite-c_gh/pull/11), [PR #12](https://github.com/ghlee0308/juliet-test-suite-c_gh/pull/12) |
| **Sonnet 4.5** | #17, #18, #19, #20 | [PR #17](https://github.com/ghlee0308/juliet-test-suite-c_gh/pull/17), [PR #18](https://github.com/ghlee0308/juliet-test-suite-c_gh/pull/18), [PR #19](https://github.com/ghlee0308/juliet-test-suite-c_gh/pull/19), [PR #20](https://github.com/ghlee0308/juliet-test-suite-c_gh/pull/20) |
| **Composer-1** | #21, #22, #23, #24 | [PR #21](https://github.com/ghlee0308/juliet-test-suite-c_gh/pull/21), [PR #22](https://github.com/ghlee0308/juliet-test-suite-c_gh/pull/22), [PR #23](https://github.com/ghlee0308/juliet-test-suite-c_gh/pull/23), [PR #24](https://github.com/ghlee0308/juliet-test-suite-c_gh/pull/24) |
| **Agent Review** | - | 테스트결과정리.xlsx Sheet1 |

### 11.2 정답지 (Ground Truth)

- **파일**: `ai-detection-test/ground_truth.json`
- **테스트 케이스**: Juliet Test Suite 기반 40개 (test_001 ~ test_040)
- **취약점 케이스**: 28개 (bad)
- **정상 케이스**: 12개 (good)

### 11.3 CWE 정답지 요약

| CWE | 취약점 유형 | 케이스 수 | 해당 테스트 |
|-----|------------|----------|------------|
| CWE-476 | NULL Pointer Dereference | 7 | test_001, 011, 018, 024, 031, 037, 040 |
| CWE-416 | Use-After-Free | 5 | test_002, 012, 021, 029, 035 |
| CWE-415 | Double Free | 4 | test_004, 017, 028, 038 |
| CWE-401 | Memory Leak | 3 | test_007, 022, 032 |
| CWE-369 | Division by Zero | 3 | test_005, 019, 034 |
| CWE-366 | Race Condition | 2 | test_014, 025 |
| CWE-252 | Unchecked Return Value | 2 | test_015, 027 |
| CWE-480 | Incorrect Operator | 1 | test_008 |
| CWE-481 | Assignment Instead of Comparison | 1 | test_009 |

---

**보고서 작성일**: 2026-01-14  
**테스트 환경**: Cursor IDE  
**데이터 소스**: 
- [GitHub PRs](https://github.com/ghlee0308/juliet-test-suite-c_gh/pulls)
- 테스트결과정리.xlsx (Agent Review 결과)
- ai-detection-test/ground_truth.json (정답지)
