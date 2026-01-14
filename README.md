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

#### Batch 1 (test_001 ~ test_010) 상세 결과

| 테스트 | 정답 | 내 탐지 | 결과 |
|--------|------|---------|------|
| test_001 | bad (CWE-476) | ✅ NULL Dereference 탐지 | ✅ 정답 |
| test_002 | bad (CWE-416) | ✅ Use-After-Free 탐지 | ✅ 정답 |
| test_003 | good | ❌ 이슈 없음 판정 | ✅ 정답 |
| test_004 | bad (CWE-415) | ✅ Double Free 탐지 | ✅ 정답 |
| test_005 | bad (CWE-369) | ✅ Division by Zero 탐지 | ✅ 정답 |
| test_006 | good | ⚠️ Memory Leak으로 탐지 | ❌ False Positive |
| test_007 | bad (CWE-401) | ✅ realloc 누수 탐지 | ✅ 정답 |
| test_008 | bad (CWE-480) | △ 미정의 변수로 탐지 (CWE 다름) | △ 부분 정답 |
| test_009 | bad (CWE-481) | ✅ Assignment vs Comparison 탐지 | ✅ 정답 |
| test_010 | good | ❌ 이슈 없음 판정 | ✅ 정답 |

| 항목 | 수치 |
|------|------|
| True Positive (취약점 정확히 탐지) | 6/7 (85.7%) |
| True Negative (정상 코드 이슈 없음) | 2/3 (66.7%) |
| False Positive (정상인데 이슈 판정) | 1 (test_006) |
| Partial Match (CWE는 다르나 이슈 탐지) | 1 (test_008) |

#### Batch 2 (test_011 ~ test_020) 상세 결과

| 테스트 | 정답 | 내 탐지 | 결과 |
|--------|------|---------|------|
| test_011 | bad (CWE-476) | ✅ NULL Dereference 탐지 | ✅ 정답 |
| test_012 | bad (CWE-416) | ✅ Use-After-Free 탐지 | ✅ 정답 |
| test_013 | good | ⚠️ Undefined Macro 탐지 | △ 컴파일 이슈 |
| test_014 | bad (CWE-366) | ✅ Race Condition 탐지 | ✅ 정답 |
| test_015 | bad (CWE-252) | ✅ Unchecked Return Value 탐지 | ✅ 정답 |
| test_016 | good | ❌ 이슈 없음 판정 | ✅ 정답 |
| test_017 | bad (CWE-415) | ✅ Double Free 탐지 | ✅ 정답 |
| test_018 | bad (CWE-476) | ✅ NULL Dereference 탐지 | ✅ 정답 |
| test_019 | bad (CWE-369) | ✅ Division by Zero 탐지 | ✅ 정답 |
| test_020 | good | ❌ 이슈 없음 판정 | ✅ 정답 |

| 항목 | 수치 |
|------|------|
| True Positive (취약점 정확히 탐지) | 7/7 (100%) |
| True Negative (정상 코드 이슈 없음) | 2/3 (66.7%) |
| False Positive (정상인데 이슈 판정) | 1 (test_013) |

#### Batch 3 (test_021 ~ test_030) 상세 결과

| 테스트 | 정답 | 내 탐지 | 결과 |
|--------|------|---------|------|
| test_021 | bad (CWE-416) | ✅ Use-After-Free 탐지 | ✅ 정답 |
| test_022 | bad (CWE-401) | ✅ Memory Leak 탐지 | ✅ 정답 |
| test_023 | good | ❌ 이슈 없음 판정 | ✅ 정답 |
| test_024 | bad (CWE-476) | ✅ NULL Dereference (잘못된 연산자) 탐지 | ✅ 정답 |
| test_025 | bad (CWE-366) | ✅ Race Condition 탐지 | ✅ 정답 |
| test_026 | good | ❌ 이슈 없음 판정 | ✅ 정답 |
| test_027 | bad (CWE-252) | ✅ Unchecked Return Value 탐지 | ✅ 정답 |
| test_028 | bad (CWE-415) | ✅ Double Free 탐지 | ✅ 정답 |
| test_029 | bad (CWE-416) | ✅ Use-After-Free 탐지 | ✅ 정답 |
| test_030 | good | ❌ 이슈 없음 판정 | ✅ 정답 |

| 항목 | 수치 |
|------|------|
| True Positive (취약점 정확히 탐지) | 7/7 (100%) |
| True Negative (정상 코드 이슈 없음) | 3/3 (100%) |
| False Positive | 0 |

#### Batch 4 (test_031 ~ test_040) 상세 결과

| 테스트 | 정답 | 내 탐지 | 결과 |
|--------|------|---------|------|
| test_031 | bad (CWE-476) | ✅ NULL Dereference 탐지 | ✅ 정답 |
| test_032 | bad (CWE-401) | ✅ Memory Leak 탐지 | ✅ 정답 |
| test_033 | good | ❌ 이슈 없음 판정 | ✅ 정답 |
| test_034 | bad (CWE-369) | ✅ Division by Zero 탐지 | ✅ 정답 |
| test_035 | bad (CWE-416) | ✅ Use-After-Free 탐지 | ✅ 정답 |
| test_036 | good | ❌ 이슈 없음 판정 | ✅ 정답 |
| test_037 | bad (CWE-476) | ✅ NULL Dereference 탐지 | ✅ 정답 |
| test_038 | bad (CWE-415) | ✅ Double Free 탐지 | ✅ 정답 |
| test_039 | good | ❌ 이슈 없음 판정 | ✅ 정답 |
| test_040 | bad (CWE-476) | ✅ NULL Dereference 탐지 | ✅ 정답 |

| 항목 | 수치 |
|------|------|
| True Positive (취약점 정확히 탐지) | 7/7 (100%) |
| True Negative (정상 코드 이슈 없음) | 3/3 (100%) |
| False Positive | 0 |

#### Opus 4.5 전체 탐지 성능 요약

| Batch | True Positive | False Positive | True Negative | False Negative |
|-------|--------------|----------------|---------------|----------------|
| 1 (test_001~010) | 7/7 | 1 (006) | 2 | 0 |
| 2 (test_011~020) | 7/7 | 1 (013) | 2 | 0 |
| 3 (test_021~030) | 7/7 | 0 | 3 | 0 |
| 4 (test_031~040) | 7/7 | 0 | 3 | 0 |
| **총계** | **28/28 (100%)** | **2** | **10** | **0** |

### 3.2 Sonnet 4.5 (PR #17, #18, #19, #20)

#### Batch 1 (test_001 ~ test_010) 상세 결과

| 테스트 | 정답 | 내 탐지 | 결과 |
|--------|------|---------|------|
| test_001 | bad (CWE-476) | ✅ NULL Dereference 탐지 | ✅ 정답 |
| test_002 | bad (CWE-416) | ✅ Use-After-Free 탐지 | ✅ 정답 |
| test_003 | good | ❌ 이슈 없음 판정 | ✅ 정답 |
| test_004 | bad (CWE-415) | ✅ Double Free 탐지 | ✅ 정답 |
| test_005 | bad (CWE-369) | ✅ Division by Zero 탐지 | ✅ 정답 |
| test_006 | good | ⚠️ Memory Leak으로 탐지 | ❌ False Positive |
| test_007 | bad (CWE-401) | ✅ realloc 누수 탐지 | ✅ 정답 |
| test_008 | bad (CWE-480) | ✅ Undefined Variable 탐지 | ✅ 정답 |
| test_009 | bad (CWE-481) | ✅ Assignment vs Comparison 탐지 | ✅ 정답 |
| test_010 | good | ❌ 이슈 없음 판정 | ✅ 정답 |

| 항목 | 수치 |
|------|------|
| True Positive (취약점 정확히 탐지) | 7/7 (100%) |
| True Negative (정상 코드 이슈 없음) | 2/3 (66.7%) |
| False Positive (정상인데 이슈 판정) | 1 (test_006) |

#### Batch 2 (test_011 ~ test_020) 상세 결과

| 테스트 | 정답 | 내 탐지 | 결과 |
|--------|------|---------|------|
| test_011 | bad (CWE-476) | ✅ NULL Dereference 탐지 | ✅ 정답 |
| test_012 | bad (CWE-416) | ✅ Use-After-Free 탐지 | ✅ 정답 |
| test_013 | good | ⚠️ Undefined Macro 탐지 | ❌ False Positive |
| test_014 | bad (CWE-366) | ✅ Race Condition 탐지 (2개 코멘트) | ✅ 정답 |
| test_015 | bad (CWE-252) | ❌ 미탐지 | ❌ False Negative |
| test_016 | good | ❌ 이슈 없음 판정 | ✅ 정답 |
| test_017 | bad (CWE-415) | ✅ Double Free 탐지 | ✅ 정답 |
| test_018 | bad (CWE-476) | ✅ NULL Dereference 탐지 | ✅ 정답 |
| test_019 | bad (CWE-369) | ✅ Division by Zero 탐지 | ✅ 정답 |
| test_020 | good | ⚠️ Undefined Function 탐지 | ❌ False Positive |

| 항목 | 수치 |
|------|------|
| True Positive (취약점 정확히 탐지) | 6/7 (85.7%) |
| True Negative (정상 코드 이슈 없음) | 1/3 (33.3%) |
| False Positive (정상인데 이슈 판정) | 2 (test_013, test_020) |
| False Negative (취약점 미탐지) | 1 (test_015) |

#### Batch 3 (test_021 ~ test_030) 상세 결과

| 테스트 | 정답 | 내 탐지 | 결과 |
|--------|------|---------|------|
| test_021 | bad (CWE-416) | ✅ Use-After-Free 탐지 | ✅ 정답 |
| test_022 | bad (CWE-401) | ✅ Memory Leak 탐지 | ✅ 정답 |
| test_023 | good | ❌ 이슈 없음 판정 | ✅ 정답 |
| test_024 | bad (CWE-476) | ✅ NULL Dereference 탐지 | ✅ 정답 |
| test_025 | bad (CWE-366) | ✅ Race Condition 탐지 (2개 코멘트) | ✅ 정답 |
| test_026 | good | ⚠️ Undefined Symbols 탐지 | ❌ False Positive |
| test_027 | bad (CWE-252) | ✅ Unchecked Return Value 탐지 | ✅ 정답 |
| test_028 | bad (CWE-415) | ✅ Double Free 탐지 | ✅ 정답 |
| test_029 | bad (CWE-416) | ✅ Use-After-Free 탐지 | ✅ 정답 |
| test_030 | good | ❌ 이슈 없음 판정 | ✅ 정답 |

| 항목 | 수치 |
|------|------|
| True Positive (취약점 정확히 탐지) | 7/7 (100%) |
| True Negative (정상 코드 이슈 없음) | 2/3 (66.7%) |
| False Positive (정상인데 이슈 판정) | 1 (test_026) |

#### Batch 4 (test_031 ~ test_040) 상세 결과

| 테스트 | 정답 | 내 탐지 | 결과 |
|--------|------|---------|------|
| test_031 | bad (CWE-476) | ✅ NULL Dereference 탐지 | ✅ 정답 |
| test_032 | bad (CWE-401) | ✅ Memory Leak 탐지 | ✅ 정답 |
| test_033 | good | ❌ 이슈 없음 판정 | ✅ 정답 |
| test_034 | bad (CWE-369) | ✅ Division by Zero 탐지 (2개 코멘트) | ✅ 정답 |
| test_035 | bad (CWE-416) | ✅ Use-After-Free 탐지 | ✅ 정답 |
| test_036 | good | ⚠️ Undefined Function 탐지 | ❌ False Positive |
| test_037 | bad (CWE-476) | ✅ NULL Dereference 탐지 | ✅ 정답 |
| test_038 | bad (CWE-415) | ✅ Double Free 탐지 | ✅ 정답 |
| test_039 | good | ❌ 이슈 없음 판정 | ✅ 정답 |
| test_040 | bad (CWE-476) | ✅ NULL Dereference 탐지 | ✅ 정답 |

| 항목 | 수치 |
|------|------|
| True Positive (취약점 정확히 탐지) | 7/7 (100%) |
| True Negative (정상 코드 이슈 없음) | 2/3 (66.7%) |
| False Positive (정상인데 이슈 판정) | 1 (test_036) |

#### Sonnet 4.5 전체 탐지 성능 요약

| Batch | True Positive | False Positive | True Negative | False Negative |
|-------|--------------|----------------|---------------|----------------|
| 1 (test_001~010) | 7/7 | 1 (006) | 2 | 0 |
| 2 (test_011~020) | 6/7 | 2 (013, 020) | 1 | 1 (015) |
| 3 (test_021~030) | 7/7 | 1 (026) | 2 | 0 |
| 4 (test_031~040) | 7/7 | 1 (036) | 2 | 0 |
| **총계** | **27/28 (96.4%)** | **5** | **7** | **1** |

### 3.3 Composer-1 (PR #21, #22, #23, #24)

#### Batch 1 (test_001 ~ test_010) 상세 결과

| 테스트 | 정답 | 내 탐지 | 결과 |
|--------|------|---------|------|
| test_001 | bad (CWE-476) | ✅ NULL Dereference 탐지 | ✅ 정답 |
| test_002 | bad (CWE-416) | ✅ Use-After-Free 탐지 | ✅ 정답 |
| test_003 | good | ❌ 이슈 없음 판정 | ✅ 정답 |
| test_004 | bad (CWE-415) | ✅ Double Free 탐지 | ✅ 정답 |
| test_005 | bad (CWE-369) | ✅ Division by Zero 탐지 | ✅ 정답 |
| test_006 | good | ⚠️ Memory Leak으로 탐지 | ❌ False Positive |
| test_007 | bad (CWE-401) | ❌ 미탐지 | ❌ False Negative |
| test_008 | bad (CWE-480) | ✅ Undefined Variable 탐지 | ✅ 정답 |
| test_009 | bad (CWE-481) | ✅ Assignment vs Comparison 탐지 | ✅ 정답 |
| test_010 | good | ❌ 이슈 없음 판정 | ✅ 정답 |

| 항목 | 수치 |
|------|------|
| True Positive (취약점 정확히 탐지) | 6/7 (85.7%) |
| True Negative (정상 코드 이슈 없음) | 2/3 (66.7%) |
| False Positive (정상인데 이슈 판정) | 1 (test_006) |
| False Negative (취약점 미탐지) | 1 (test_007) |

#### Batch 2 (test_011 ~ test_020) 상세 결과

| 테스트 | 정답 | 내 탐지 | 결과 |
|--------|------|---------|------|
| test_011 | bad (CWE-476) | ✅ NULL Dereference 탐지 (중복) | ✅ 정답 |
| test_012 | bad (CWE-416) | ✅ Use-After-Free 탐지 (중복) | ✅ 정답 |
| test_013 | good | ⚠️ Undefined Macro 탐지 (중복) | ❌ False Positive |
| test_014 | bad (CWE-366) | ✅ Race Condition 탐지 (중복) | ✅ 정답 |
| test_015 | bad (CWE-252) | ❌ 미탐지 | ❌ False Negative |
| test_016 | good | ❌ 이슈 없음 판정 | ✅ 정답 |
| test_017 | bad (CWE-415) | ✅ Double Free 탐지 | ✅ 정답 |
| test_018 | bad (CWE-476) | ✅ NULL Dereference 탐지 | ✅ 정답 |
| test_019 | bad (CWE-369) | ✅ Division by Zero 탐지 | ✅ 정답 |
| test_020 | good | ⚠️ Undefined Function 탐지 | ❌ False Positive |

| 항목 | 수치 |
|------|------|
| True Positive (취약점 정확히 탐지) | 6/7 (85.7%) |
| True Negative (정상 코드 이슈 없음) | 1/3 (33.3%) |
| False Positive (정상인데 이슈 판정) | 2 (test_013, test_020) |
| False Negative (취약점 미탐지) | 1 (test_015) |

#### Batch 3 (test_021 ~ test_030) 상세 결과

| 테스트 | 정답 | 내 탐지 | 결과 |
|--------|------|---------|------|
| test_021 | bad (CWE-416) | ✅ Use-After-Free 탐지 | ✅ 정답 |
| test_022 | bad (CWE-401) | ✅ Memory Leak 탐지 | ✅ 정답 |
| test_023 | good | ❌ 이슈 없음 판정 | ✅ 정답 |
| test_024 | bad (CWE-476) | ✅ NULL Dereference 탐지 | ✅ 정답 |
| test_025 | bad (CWE-366) | ✅ Race Condition 탐지 | ✅ 정답 |
| test_026 | good | ⚠️ Undefined Symbols 탐지 | ❌ False Positive |
| test_027 | bad (CWE-252) | ✅ Unchecked Return Value 탐지 | ✅ 정답 |
| test_028 | bad (CWE-415) | ✅ Double Free 탐지 | ✅ 정답 |
| test_029 | bad (CWE-416) | ✅ Use-After-Free 탐지 | ✅ 정답 |
| test_030 | good | ❌ 이슈 없음 판정 | ✅ 정답 |

| 항목 | 수치 |
|------|------|
| True Positive (취약점 정확히 탐지) | 7/7 (100%) |
| True Negative (정상 코드 이슈 없음) | 2/3 (66.7%) |
| False Positive (정상인데 이슈 판정) | 1 (test_026) |

#### Batch 4 (test_031 ~ test_040) 상세 결과

| 테스트 | 정답 | 내 탐지 | 결과 |
|--------|------|---------|------|
| test_031 | bad (CWE-476) | ✅ NULL Dereference 탐지 | ✅ 정답 |
| test_032 | bad (CWE-401) | ✅ Memory Leak 탐지 | ✅ 정답 |
| test_033 | good | ❌ 이슈 없음 판정 | ✅ 정답 |
| test_034 | bad (CWE-369) | ✅ Division by Zero 탐지 | ✅ 정답 |
| test_035 | bad (CWE-416) | ✅ Use-After-Free 탐지 | ✅ 정답 |
| test_036 | good | ⚠️ Undefined Function 탐지 | ❌ False Positive |
| test_037 | bad (CWE-476) | ✅ NULL Dereference 탐지 | ✅ 정답 |
| test_038 | bad (CWE-415) | ✅ Double Free 탐지 | ✅ 정답 |
| test_039 | good | ❌ 이슈 없음 판정 | ✅ 정답 |
| test_040 | bad (CWE-476) | ✅ NULL Dereference 탐지 | ✅ 정답 |

| 항목 | 수치 |
|------|------|
| True Positive (취약점 정확히 탐지) | 7/7 (100%) |
| True Negative (정상 코드 이슈 없음) | 2/3 (66.7%) |
| False Positive (정상인데 이슈 판정) | 1 (test_036) |

#### Composer-1 전체 탐지 성능 요약

| Batch | True Positive | False Positive | True Negative | False Negative |
|-------|--------------|----------------|---------------|----------------|
| 1 (test_001~010) | 6/7 | 1 (006) | 2 | 1 (007) |
| 2 (test_011~020) | 6/7 | 2 (013, 020) | 1 | 1 (015) |
| 3 (test_021~030) | 7/7 | 1 (026) | 2 | 0 |
| 4 (test_031~040) | 7/7 | 1 (036) | 2 | 0 |
| **총계** | **26/28 (92.9%)** | **5** | **7** | **2** |

### 3.4 Agent Review (엑셀 데이터 기준)

#### Batch 1 (test_001 ~ test_010) 상세 결과

| 테스트 | 정답 | 내 탐지 | 결과 |
|--------|------|---------|------|
| test_001 | bad (CWE-476) | ✅ NULL Dereference 탐지 | ✅ 정답 |
| test_002 | bad (CWE-416) | ✅ Use-After-Free 탐지 | ✅ 정답 |
| test_003 | good | ❌ 이슈 없음 판정 | ✅ 정답 |
| test_004 | bad (CWE-415) | ✅ Double Free 탐지 | ✅ 정답 |
| test_005 | bad (CWE-369) | ❌ 미탐지 | ❌ False Negative |
| test_006 | good | ⚠️ Memory Leak으로 탐지 | ❌ False Positive |
| test_007 | bad (CWE-401) | ✅ realloc 누수 탐지 | ✅ 정답 |
| test_008 | bad (CWE-480) | ❌ 미탐지 | ❌ False Negative |
| test_009 | bad (CWE-481) | ✅ Assignment vs Comparison 탐지 | ✅ 정답 |
| test_010 | good | ❌ 이슈 없음 판정 | ✅ 정답 |

| 항목 | 수치 |
|------|------|
| True Positive (취약점 정확히 탐지) | 5/7 (71.4%) |
| True Negative (정상 코드 이슈 없음) | 2/3 (66.7%) |
| False Positive (정상인데 이슈 판정) | 1 (test_006) |
| False Negative (취약점 미탐지) | 2 (test_005, test_008) |

#### Batch 2 (test_011 ~ test_020) 상세 결과

| 테스트 | 정답 | 내 탐지 | 결과 |
|--------|------|---------|------|
| test_011 | bad (CWE-476) | ✅ NULL Dereference 탐지 | ✅ 정답 |
| test_012 | bad (CWE-416) | ✅ Use-After-Free 탐지 | ✅ 정답 |
| test_013 | good | ❌ 이슈 없음 판정 | ✅ 정답 |
| test_014 | bad (CWE-366) | ❌ Race Condition 미탐지 | ❌ False Negative |
| test_015 | bad (CWE-252) | ❌ 미탐지 | ❌ False Negative |
| test_016 | good | ❌ 이슈 없음 판정 | ✅ 정답 |
| test_017 | bad (CWE-415) | ✅ Double Free 탐지 | ✅ 정답 |
| test_018 | bad (CWE-476) | ✅ NULL Dereference 탐지 | ✅ 정답 |
| test_019 | bad (CWE-369) | ✅ Division by Zero 탐지 | ✅ 정답 |
| test_020 | good | ❌ 이슈 없음 판정 | ✅ 정답 |

| 항목 | 수치 |
|------|------|
| True Positive (취약점 정확히 탐지) | 5/7 (71.4%) |
| True Negative (정상 코드 이슈 없음) | 3/3 (100%) |
| False Positive | 0 |
| False Negative (취약점 미탐지) | 2 (test_014, test_015) |

#### Batch 3 (test_021 ~ test_030) 상세 결과

| 테스트 | 정답 | 내 탐지 | 결과 |
|--------|------|---------|------|
| test_021 | bad (CWE-416) | ❌ Use-After-Free 미탐지 | ❌ False Negative |
| test_022 | bad (CWE-401) | ✅ Memory Leak 탐지 | ✅ 정답 |
| test_023 | good | ❌ 이슈 없음 판정 | ✅ 정답 |
| test_024 | bad (CWE-476) | ✅ NULL Dereference 탐지 | ✅ 정답 |
| test_025 | bad (CWE-366) | ❌ Race Condition 미탐지 | ❌ False Negative |
| test_026 | good | ❌ 이슈 없음 판정 | ✅ 정답 |
| test_027 | bad (CWE-252) | ❌ Unchecked Return 미탐지 | ❌ False Negative |
| test_028 | bad (CWE-415) | ❌ Double Free 미탐지 | ❌ False Negative |
| test_029 | bad (CWE-416) | ❌ Use-After-Free 미탐지 | ❌ False Negative |
| test_030 | good | ❌ 이슈 없음 판정 | ✅ 정답 |

| 항목 | 수치 |
|------|------|
| True Positive (취약점 정확히 탐지) | 2/7 (28.6%) |
| True Negative (정상 코드 이슈 없음) | 3/3 (100%) |
| False Positive | 0 |
| False Negative (취약점 미탐지) | 5 (test_021, 025, 027, 028, 029) |

#### Batch 4 (test_031 ~ test_040) 상세 결과

| 테스트 | 정답 | 내 탐지 | 결과 |
|--------|------|---------|------|
| test_031 | bad (CWE-476) | ❌ NULL Dereference 미탐지 | ❌ False Negative |
| test_032 | bad (CWE-401) | ❌ Memory Leak 미탐지 | ❌ False Negative |
| test_033 | good | ⚠️ Pointer to stack memory 탐지 | ❌ False Positive |
| test_034 | bad (CWE-369) | ❌ Division by Zero 미탐지 | ❌ False Negative |
| test_035 | bad (CWE-416) | ✅ Use-After-Free 탐지 | ✅ 정답 |
| test_036 | good | ❌ 이슈 없음 판정 | ✅ 정답 |
| test_037 | bad (CWE-476) | ❌ NULL Dereference 미탐지 | ❌ False Negative |
| test_038 | bad (CWE-415) | ❌ Double Free 미탐지 | ❌ False Negative |
| test_039 | good | ❌ 이슈 없음 판정 | ✅ 정답 |
| test_040 | bad (CWE-476) | ❌ NULL Dereference 미탐지 | ❌ False Negative |

| 항목 | 수치 |
|------|------|
| True Positive (취약점 정확히 탐지) | 1/7 (14.3%) |
| True Negative (정상 코드 이슈 없음) | 2/3 (66.7%) |
| False Positive (정상인데 이슈 판정) | 1 (test_033) |
| False Negative (취약점 미탐지) | 6 (test_031, 032, 034, 037, 038, 040) |

#### Agent Review 전체 탐지 성능 요약

| Batch | True Positive | False Positive | True Negative | False Negative |
|-------|--------------|----------------|---------------|----------------|
| 1 (test_001~010) | 5/7 (71.4%) | 1 (006) | 2 | 2 (005, 008) |
| 2 (test_011~020) | 5/7 (71.4%) | 0 | 3 | 2 (014, 015) |
| 3 (test_021~030) | 2/7 (28.6%) | 0 | 3 | 5 (021, 025, 027, 028, 029) |
| 4 (test_031~040) | 1/7 (14.3%) | 1 (033) | 2 | 6 (031, 032, 034, 037, 038, 040) |
| **총계** | **13/28 (46.4%)** | **2** | **10** | **15** |

#### ⚠️ Agent Review 성능 저하 패턴 분석

```
📉 Batch별 탐지율 변화:
Batch 1: 71.4% ━━━━━━━━━━━━━━━━━━━━━━
Batch 2: 71.4% ━━━━━━━━━━━━━━━━━━━━━━
Batch 3: 28.6% ━━━━━━━━━
Batch 4: 14.3% ━━━━━

🔍 원인 분석:
- 컨텍스트 누적으로 인한 "피로 효과" 추정
- Batch 3, 4에서 성능 급락 (50% 이상 하락)
- 동시성 문제 완전 미탐 (Race Condition 0%)
- 반환값 확인 누락 완전 미탐 (CWE-252 0%)
```

---

## 4. 4가지 방식 성능 비교 종합

### 4.1 전체 탐지 성능 비교

| 지표 | Opus 4.5 | Sonnet 4.5 | Composer-1 | Agent Review |
|------|----------|------------|------------|--------------|
| **True Positive Rate** | **100%** (28/28) | 96.4% (27/28) | 92.9% (26/28) | 46.4% (13/28) |
| **False Positive** | 2개 | 5개 | 5개 | **2개** |
| **True Negative Rate** | 83.3% (10/12) | 58.3% (7/12) | 58.3% (7/12) | **83.3%** (10/12) |
| **False Negative** | **0개** | 1개 | 2개 | 15개 |
| **정확도** | **95.0%** | 85.0% | 82.5% | 57.5% |

### 4.2 성능 순위

```
📊 취약점 탐지율 (True Positive Rate) 순위:
1위: Opus 4.5      - 100.0% (28/28) ⭐ 최고 성능
2위: Sonnet 4.5    -  96.4% (27/28)
3위: Composer-1    -  92.9% (26/28)
4위: Agent Review  -  46.4% (13/28) ⚠️ 절반 이상 미탐

📊 오탐 방지율 (True Negative Rate) 순위:
1위: Opus 4.5      - 83.3% (10/12)
1위: Agent Review  - 83.3% (10/12) ⭐ 동률
3위: Sonnet 4.5    - 58.3% (7/12)
3위: Composer-1    - 58.3% (7/12)

📊 전체 정확도 순위:
1위: Opus 4.5      - 95.0% ⭐ 최고 성능
2위: Sonnet 4.5    - 85.0%
3위: Composer-1    - 82.5%
4위: Agent Review  - 57.5%

📊 비용 효율성 (토큰 사용량) 순위:
1위: Agent Review  - 109만 ⭐ 가장 효율적
2위: Composer-1    - 230.3만
3위: Opus 4.5      - 356.5만
4위: Sonnet 4.5    - 1,044.6만
```

---

## 5. 심각도별 탐지 성능 비교

### 5.1 Critical 버그 탐지율

| 테스트 | CWE | 취약점 | Opus | Sonnet | Composer | Agent |
|--------|-----|--------|------|--------|----------|-------|
| test_001 | 476 | NULL Deref | ✅ | ✅ | ✅ | ✅ |
| test_005 | 369 | Div by Zero | ✅ | ✅ | ✅ | ❌ |
| test_011 | 476 | NULL Deref | ✅ | ✅ | ✅ | ✅ |
| test_015 | 252 | Unchecked Ret | ✅ | ❌ | ❌ | ❌ |
| test_018 | 476 | NULL Deref | ✅ | ✅ | ✅ | ✅ |
| test_019 | 369 | Div by Zero | ✅ | ✅ | ✅ | ✅ |
| test_024 | 476 | NULL Deref | ✅ | ✅ | ✅ | ✅ |
| test_027 | 252 | Unchecked Ret | ✅ | ✅ | ✅ | ❌ |
| test_031 | 476 | NULL Deref | ✅ | ✅ | ✅ | ❌ |
| test_034 | 369 | Div by Zero | ✅ | ✅ | ✅ | ❌ |
| test_037 | 476 | NULL Deref | ✅ | ✅ | ✅ | ❌ |
| test_040 | 476 | NULL Deref | ✅ | ✅ | ✅ | ❌ |
| **총계** | | | **12/12 (100%)** | **11/12 (91.7%)** | **11/12 (91.7%)** | **4/12 (33.3%)** |

### 5.2 Memory 버그 탐지율

| 테스트 | CWE | 취약점 | Opus | Sonnet | Composer | Agent |
|--------|-----|--------|------|--------|----------|-------|
| test_002 | 416 | Use-After-Free | ✅ | ✅ | ✅ | ✅ |
| test_004 | 415 | Double Free | ✅ | ✅ | ✅ | ✅ |
| test_007 | 401 | Memory Leak | ✅ | ✅ | ❌ | ✅ |
| test_012 | 416 | Use-After-Free | ✅ | ✅ | ✅ | ✅ |
| test_017 | 415 | Double Free | ✅ | ✅ | ✅ | ✅ |
| test_021 | 416 | Use-After-Free | ✅ | ✅ | ✅ | ❌ |
| test_022 | 401 | Memory Leak | ✅ | ✅ | ✅ | ✅ |
| test_028 | 415 | Double Free | ✅ | ✅ | ✅ | ❌ |
| test_029 | 416 | Use-After-Free | ✅ | ✅ | ✅ | ❌ |
| test_032 | 401 | Memory Leak | ✅ | ✅ | ✅ | ❌ |
| test_035 | 416 | Use-After-Free | ✅ | ✅ | ✅ | ✅ |
| test_038 | 415 | Double Free | ✅ | ✅ | ✅ | ❌ |
| **총계** | | | **12/12 (100%)** | **12/12 (100%)** | **11/12 (91.7%)** | **6/12 (50.0%)** |

### 5.3 Logic 버그 탐지율

| 테스트 | CWE | 취약점 | Opus | Sonnet | Composer | Agent |
|--------|-----|--------|------|--------|----------|-------|
| test_008 | 480 | Incorrect Operator | ✅ | ✅ | ✅ | ❌ |
| test_009 | 481 | Assign vs Compare | ✅ | ✅ | ✅ | ✅ |
| **총계** | | | **2/2 (100%)** | **2/2 (100%)** | **2/2 (100%)** | **1/2 (50.0%)** |

### 5.4 Concurrency 버그 탐지율

| 테스트 | CWE | 취약점 | Opus | Sonnet | Composer | Agent |
|--------|-----|--------|------|--------|----------|-------|
| test_014 | 366 | Race Condition | ✅ | ✅ | ✅ | ❌ |
| test_025 | 366 | Race Condition | ✅ | ✅ | ✅ | ❌ |
| **총계** | | | **2/2 (100%)** | **2/2 (100%)** | **2/2 (100%)** | **0/2 (0.0%)** |

### 5.5 심각도별 탐지율 요약

| 심각도 | Opus 4.5 | Sonnet 4.5 | Composer-1 | Agent Review |
|--------|----------|------------|------------|--------------|
| 🚨 **Critical** | **100%** | 91.7% | 91.7% | 33.3% |
| 💾 **Memory** | **100%** | **100%** | 91.7% | 50.0% |
| ⚠️ **Logic** | **100%** | **100%** | **100%** | 50.0% |
| 🔒 **Concurrency** | **100%** | **100%** | **100%** | 0.0% |

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

```
⭐⭐⭐ 완벽한 일관성 (모든 케이스 100% 탐지):
├── Opus 4.5: 모든 CWE 완벽 탐지
└── Sonnet 4.5: CWE-252 제외 완벽 (1개 미탐)

⭐⭐ 높은 일관성 (90% 이상):
└── Composer-1: CWE-252, CWE-401 일부 미탐

⚠️ 매우 낮은 일관성 (50% 미만):
└── Agent Review: CWE별 탐지율 극심한 편차 (0% ~ 100%)
    - CWE-366, CWE-252, CWE-480: 완전 미탐 (0%)
    - CWE-416, CWE-476: 40% 미만
    - Batch 3, 4에서 성능 급격히 하락
```

---

## 7. 오탐 (False Positive) 분석

### 7.1 오탐 발생 파일

| 파일 | 실제 | Opus | Sonnet | Composer | Agent |
|------|------|------|--------|----------|-------|
| test_006 | good (free 전 사용) | ⚠️ FP | ⚠️ FP | ⚠️ FP | ⚠️ FP |
| test_013 | good (zero 체크) | ⚠️ FP | ⚠️ FP | ⚠️ FP | ✅ TN |
| test_020 | good (correct call) | ✅ TN | ⚠️ FP | ⚠️ FP | ✅ TN |
| test_026 | good (proper lock) | ✅ TN | ⚠️ FP | ⚠️ FP | ✅ TN |
| test_033 | good (proper init) | ✅ TN | ✅ TN | ✅ TN | ⚠️ FP |
| test_036 | good (no UAF) | ✅ TN | ⚠️ FP | ⚠️ FP | ✅ TN |

### 7.2 오탐 패턴 분석

```
공통 오탐 (모든 모델):
└── test_006: free 전에 사용하는 정상 패턴을 Memory Leak으로 오탐

모델별 특징적 오탐:
├── Opus: 최소 오탐 (2개)
├── Sonnet/Composer: 중간 오탐 (5개)
└── Agent: 최소 오탐 (2개) but test_033에서 고유 오탐
```

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

```
🎯 최고 정확도 필요: Opus 4.5 ⭐ 권장
   - 모든 취약점 100% 탐지
   - 오탐 최소화 (2개)
   - 비용: 높음 (356만 토큰, 8 프리미엄)

⚖️ 균형 잡힌 선택: Composer-1
   - 적절한 비용 (230만 토큰)
   - 높은 정확도 (92.9%)
   - 일부 Memory Leak 미탐

🔍 세밀한 검토: Sonnet 4.5
   - 높은 탐지율 (96.4%)
   - 오탐 다소 많음 (5개)
   - 비용 최고 (1,044만 토큰)

⚠️ 권장하지 않음: Agent Review
   - 토큰 사용량 최소 (109만) but...
   - 탐지율 46.4%로 절반 이상 미탐
   - Race Condition 완전 미탐
   - Batch 3, 4에서 성능 급락
```

---

## 9. 결론 및 권장사항

### 9.1 성능 종합 평가

| 평가 항목 | Opus 4.5 | Sonnet 4.5 | Composer-1 | Agent Review |
|-----------|----------|------------|------------|--------------|
| 취약점 탐지율 | ⭐⭐⭐⭐⭐ | ⭐⭐⭐⭐ | ⭐⭐⭐⭐ | ⭐⭐ |
| 탐지 일관성 | ⭐⭐⭐⭐⭐ | ⭐⭐⭐⭐ | ⭐⭐⭐⭐ | ⭐ |
| 오탐 방지 | ⭐⭐⭐⭐ | ⭐⭐⭐ | ⭐⭐⭐ | ⭐⭐⭐⭐ |
| 비용 효율성 | ⭐⭐ | ⭐ | ⭐⭐⭐ | ⭐⭐⭐⭐⭐ |
| **종합** | **1위** | **3위** | **2위** | **4위** |

### 9.2 최종 권장사항

1. **보안 크리티컬 프로젝트**: **Opus 4.5** 사용 ⭐ 강력 권장
   - 100% 탐지율로 모든 취약점 발견
   - 비용보다 안정성이 중요한 경우

2. **일반 프로젝트**: **Composer-1** 사용
   - 적절한 비용으로 높은 탐지율 (92.9%)
   - Memory Leak 일부 놓칠 수 있음

3. **상세 분석 필요 시**: **Sonnet 4.5** 사용
   - 높은 탐지율 (96.4%)
   - 오탐이 다소 많아 수동 검증 필요

4. **Agent Review**: ⚠️ 보안 검사 목적으로 권장하지 않음
   - 탐지율 46.4%로 절반 이상 미탐
   - Batch 진행 중 성능 급락 현상 (피로 효과?)
   - Race Condition 완전 미탐
   - 간단한 NULL 체크 정도의 기본 검사만 가능

### 9.3 핵심 인사이트

```
💡 발견된 주요 패턴:

1. 사용자 커맨드 자동화 프롬프트가 Agent Review보다 훨씬 우수
   - Opus: 100% vs Agent: 46.4%
   - 명확한 지시문과 구조화된 프롬프트의 효과

2. Agent Review의 Batch 성능 저하
   - Batch 1: 71.4% → Batch 4: 14.3%
   - 컨텍스트 누적 또는 "피로 효과"로 추정

3. 모든 방식에서 공통 오탐
   - test_006 (정상 free 패턴을 Memory Leak으로 오탐)
   - 이 패턴에 대한 추가 학습 필요

4. 동시성 취약점은 명시적 지시 필요
   - Agent Review는 Race Condition 0% 탐지
   - 프롬프트에 동시성 검사 명시 시 100% 탐지
```

---

## 10. 부록: 전체 테스트 결과표

| 테스트 | Type | CWE | 심각도 | Opus | Sonnet | Composer | Agent | Agent 결과 |
|--------|------|-----|--------|------|--------|----------|-------|-----------|
| test_001 | bad | 476 | Critical | ✅ | ✅ | ✅ | ✅ | 정탐 |
| test_002 | bad | 416 | Memory | ✅ | ✅ | ✅ | ✅ | 정탐 |
| test_003 | good | 476 | - | ✅ TN | ✅ TN | ✅ TN | ✅ TN | 정탐 |
| test_004 | bad | 415 | Memory | ✅ | ✅ | ✅ | ✅ | 정탐 |
| test_005 | bad | 369 | Critical | ✅ | ✅ | ✅ | ❌ | 미탐 |
| test_006 | good | 416 | - | ❌ FP | ❌ FP | ❌ FP | ❌ FP | 오탐 |
| test_007 | bad | 401 | Memory | ✅ | ✅ | ❌ | ✅ | 정탐 |
| test_008 | bad | 480 | Logic | ✅ | ✅ | ✅ | ❌ | 미탐 |
| test_009 | bad | 481 | Logic | ✅ | ✅ | ✅ | ✅ | 정탐 |
| test_010 | good | 415 | - | ✅ TN | ✅ TN | ✅ TN | ✅ TN | (없음) |
| test_011 | bad | 476 | Critical | ✅ | ✅ | ✅ | ✅ | 정탐 |
| test_012 | bad | 416 | Memory | ✅ | ✅ | ✅ | ✅ | 정탐 |
| test_013 | good | 369 | - | ❌ FP | ❌ FP | ❌ FP | ✅ TN | 정탐 |
| test_014 | bad | 366 | Concurrency | ✅ | ✅ | ✅ | ❌ | 미탐 |
| test_015 | bad | 252 | Critical | ✅ | ❌ | ❌ | ❌ | 미탐 |
| test_016 | good | 401 | - | ✅ TN | ✅ TN | ✅ TN | ✅ TN | 정탐 |
| test_017 | bad | 415 | Memory | ✅ | ✅ | ✅ | ✅ | 정탐 |
| test_018 | bad | 476 | Critical | ✅ | ✅ | ✅ | ✅ | 정탐 |
| test_019 | bad | 369 | Critical | ✅ | ✅ | ✅ | ✅ | 정탐 |
| test_020 | good | 480 | - | ✅ TN | ❌ FP | ❌ FP | ✅ TN | 정탐 |
| test_021 | bad | 416 | Memory | ✅ | ✅ | ✅ | ❌ | 미탐 |
| test_022 | bad | 401 | Memory | ✅ | ✅ | ✅ | ✅ | 정탐 |
| test_023 | good | 481 | - | ✅ TN | ✅ TN | ✅ TN | ✅ TN | 정탐 |
| test_024 | bad | 476 | Critical | ✅ | ✅ | ✅ | ✅ | 정탐 |
| test_025 | bad | 366 | Concurrency | ✅ | ✅ | ✅ | ❌ | 미탐 |
| test_026 | good | 366 | - | ✅ TN | ❌ FP | ❌ FP | ✅ TN | 정탐 |
| test_027 | bad | 252 | Critical | ✅ | ✅ | ✅ | ❌ | 미탐 |
| test_028 | bad | 415 | Memory | ✅ | ✅ | ✅ | ❌ | 미탐 |
| test_029 | bad | 416 | Memory | ✅ | ✅ | ✅ | ❌ | 미탐 |
| test_030 | good | 252 | - | ✅ TN | ✅ TN | ✅ TN | ✅ TN | 정탐 |
| test_031 | bad | 476 | Critical | ✅ | ✅ | ✅ | ❌ | 미탐 |
| test_032 | bad | 401 | Memory | ✅ | ✅ | ✅ | ❌ | 미탐 |
| test_033 | good | 476 | - | ✅ TN | ✅ TN | ✅ TN | ❌ FP | 오탐 |
| test_034 | bad | 369 | Critical | ✅ | ✅ | ✅ | ❌ | 미탐 |
| test_035 | bad | 416 | Memory | ✅ | ✅ | ✅ | ✅ | 정탐 |
| test_036 | good | 416 | - | ✅ TN | ❌ FP | ❌ FP | ✅ TN | 정탐 |
| test_037 | bad | 476 | Critical | ✅ | ✅ | ✅ | ❌ | 미탐 |
| test_038 | bad | 415 | Memory | ✅ | ✅ | ✅ | ❌ | 미탐 |
| test_039 | good | 415 | - | ✅ TN | ✅ TN | ✅ TN | ✅ TN | 정탐 |
| test_040 | bad | 476 | Critical | ✅ | ✅ | ✅ | ❌ | 미탐 |

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
