## 프로젝트 개요
2022년에 Bluetooth를 이용해 원격으로 금고를 제어할 수 있는 프로그램을 아두이노(Arduino)를 이용해 구현하였습니다.

## 활용 기술
```
Arduino
Bluetooth
```

## 코드 실행
```
Project_All_Code.ino
```

## 하드웨어
### 1. 기능별 사용 부품 목록 
1.	금고 잠금/열림 기능 : 9g 미니 서브모터 SG-90 1개
2.	블루투스 통신 기능 : HC-06 모듈 1개
3.	진동을 통한 절도 여부 파악 기능 : 진동센서 1개, 
4.	리셋 버튼/세팅 버튼 : 푸시버튼 2개, 10K 저항 2개
5.	경고음 기능 : 수동 부저 1개, S8050 NPN 트랜지스터 1개, 10K 저항 1개
6.	금고 잠금/열림 상태 표시 기능 : 빨간색/녹색 LED 1개, 1K 저항 2개<br/><br/>

### 2. 제작과정 & 구현 결과
<img src = "./figure/제작과정1.png" width="80%"><br/>
- 아두이노와 브래드보드에 세팅을 마치고 단열재를 이용해 금고를 제작함.
- 벽면엔 금고의 잠금장치 역할을 할 서보 모터가 들어가는 공간을 구현함.<br/>

<img src = "./figure/제작과정2.png" width="80%"><br/>
- 금고 정면 우측 상단에 금고의 잠금 여부를 표시하는 2개의 LED 핀을 부착함.
- 금고 내부 좌측에 금고의 잠금을 제어하는 서보 모터를 부착함.
- 금고 내부 하단 중앙에 금고의 진동 여부를 파악하는 진동센서 부착.
- 원격 조정을 위한 HC-06 블루투스 모듈을 금고 내부에 설치함.
- 금고의 비밀번호를 리셋/세팅하는 푸시버튼을 금고 내부에 설치함.<br/><br/>

## 소프트웨어


## 메뉴별 기능
<img src = "./figure/organization.png" width="80%"><br/>

## 메뉴별 권한
<img src = "./figure/authority.png" width="80%"><br/>

## 사이트 기능
### 1. 메인 페이지
#### 1-1. 헤더
<img src = "./figure/Header.png" width="80%"><br/>
- Index 페이지와 header 페이지를 따로 분리하여 구현함.
- 회원 가입 링크를 클릭하면 회원 가입 페이지로 이동함.<br/><br/>

<img src = "./figure/join_membership.png" width="80%"><br/>
- 회원 가입 버튼을 클릭하면 입력한 데이터가 DB에 저장되고 index.jsp 페이지로 돌아감.
- 리셋 버튼을 클릭하면 textfield에 입력한 모든 내용이 리셋됨.<br/><br/><br/>

#### 1-2. index 페이지
<img src = "./figure/Main_Page.png" width="80%"><br/>
- <%@ include file="./header.jsp" %> 코드를 이용해 헤더 파일을 index 페이지에 불러옴.
- 위와 마찬가지 방법을 이용해 footer.jsp 파일을 index 페이지 최하단에 include 함.
- 로그인 시 로그아웃/마이페이지(root로 로그인시 관리자 페이지) 기능 지원.<br/><br/>

<img src = "./figure/Trip_Packages.png" width="80%"><br/>
- 로그인 한 상태에서 예약하기 버튼을 클릭시 해당 회원 명의로 DB에 예약정보가 추가됨.<br/><br/>

### 2. 마이 페이지/관리자 페이지
#### 2-1. 마이 페이지
<img src = "./figure/mypage.png" width="80%"><br/>
- 내 정보 보기/수정 과 내 예약 관리(보기/수정) 의 기능들을 지원함.
- 보안을 위해 해당 회원의 2차 인증 기능을 구현함.<br/><br/>

<img src = "./figure/mypage2.png" width="80%"><br/>
- 내 예약 관리에선 해당 회원의 예약 열람/추가/수정/취소 와 같은 총 4가지 기능 지원.<br/><br/>

#### 2-2. 관리자 페이지
<img src = "./figure/admin_page00.png" width="80%"><br/>
- 관리자 페이지는 회원 관리/여행지 관리/예약 관리/프로모션 관리 의 총 4가지 페이지로 구성되어 있음.<br/><br/>

<img src = "./figure/admin_page01.png" width="80%"><br/>
- 회원 관리 페이지에서는 회원 추가/수정/삭제 의 3가지 기능을 지원.
- 회원 관리 페이지에서는 default로 설정된 일반 이외에 '관리자' 역할을 설정할 수 있음.<br/><br/>

<img src = "./figure/admin_page02.png" width="80%"><br/>
- 여행지 관리 페이지에서는 여행지 추가/수정/삭제 의 3가지 기능을 지원
- 여행 방식의 default는 '패키지'지만 '자유' 여행 또한 설정 가능.<br/><br/>

<img src = "./figure/admin_page03.png" width="80%"><br/>
- 예약 관리 페이지에서는 예약 추가/수정/삭제 의 3가지 기능을 지원.
- 예약을 위해 필요한 사용자 코드/아이디, 여행지 코드, 프로모션 코드는 각각 회원목록/여행목록/프로모션 목록 버튼을 눌러 확인 가능.<br/><br/>

<img src = "./figure/admin_page04.png" width="80%"><br/>
- 프로모션 관리 페이지에서는 프로모션 추가/수정/삭제 의 3가지 기능을 지원.<br/><br/>

## 서블릿 구성
크게 5가지 목적을 가진 대분류로 나눔.
### 1. 회원가입/로그인/로그아웃 기능
```
JoinController.java (회원가입)
LoginController.java (로그인)
LogoutController.java (로그아웃)
```

### 2. 관리자/마이페이지 회원 관리
```
MemberDAO.java (회원가입 및 관리를 위한 function 모음)
MemberDTO.java (MemberDAO.java에서 쓰는 데이터의 set/get)
MemberMyPageController.java (마이페이지에서 사용자의 정보를 출력/수정하는 기능)

MemberController.java (관리자 페이지의 회원 추가 기능)
MemberChangeController.java (관리자 페이지의 회원 수정 기능)
MemberDeleteController.java (관리자 페이지의 회원 삭제 기능)
```

### 3. 관리자 페이지 여행지 관리
```
DestinationDAO.java (여행지 관리를 위한 function 모음)
DestinationDTO.java (DestinationDAO.java에서 쓰는 데이터의 set/get)

DestinationController.java (관리자 페이지의 여행지 추가 기능)
DestinationChangeController.java (관리자 페이지의 여행지 수정 기능)
DestinationDeleteController.java (관리자 페이지의 여행지 삭제 기능)
```

### 4. 관리자 페이지 프로모션 관리
```
PromotionDAO.java (프로모션 관리를 위한 function 모음)
PromotionDTO.java (PromotionDAO.java에서 쓰는 데이터의 set/get)

PromotionController.java (관리자 페이지의 프로모션 추가 기능)
PromotionChangeController.java (관리자 페이지의 프로모션 수정 기능)
PromotionDeleteController.java (관리자 페이지의 프로모션 삭제 기능)
```

### 5. 관리자/마이페이지 예약 관리
```
ReservationDAO.java (예약을 위한 function 모음)
ReservationDTO.java (ReservationDAO.java에서 쓰는 데이터의 set/get)
ReservationMyPageController.java (마이페이지에서 사용자의 예약 정보를 출력하는 기능)

ReservationController.java (관리자 페이지의 예약 추가 기능)
ReservationChangeController.java (관리자 페이지의 예약 수정 기능)
ReservationDeleteController.java (관리자 페이지의 예약 삭제 기능)
```

## 결론
- html로 구현된 정적 웹페이지를 apache tomcat과 JSP를 이용하여 동적 웹페이지로 재구현.
- Database를 조합하여 데이터의 삽입/수정/삭제 와 로그인/회원가입 기능 구현.<br/><br/>

## 향후 목표
1) UI/UX를 고려하여 디자인 개선.
2) header.jsp에 구현한 여행지 메뉴 및 하위 메뉴를 DB에서 출력되는 방식으로 수정.
3) 하드코딩된 여행지 정보 테이블의 정보 및 이미지를 DB에서 출력되는 방식으로 수정.
4) 로그인 실패 시 발생하는 이벤트 JSP를 구현.
5) 관리자 페이지의 DB select(검색) 기능 구현.
<br/>
