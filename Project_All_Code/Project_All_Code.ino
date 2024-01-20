// 블루투스와 아두이노를 연결하여 비밀번호를 입력하면 led에 불이 들어오는 코드. + 모터 연동
#include <SoftwareSerial.h>//블루투스
#include <Servo.h>//모터제어

//블루투스
int bluetoothTx = 2;//Tx(보내는 핀 설정)
int bluetoothRx = 3;//Rx(받는 핀 설정)
SoftwareSerial mySerial(bluetoothTx, bluetoothRx);//시리얼 통신을 위한 객체선언
String myString="";//핸드폰에서 입력한 비밀번호를 받는 문자열
String myString2 = "";
String myString3 = "";
String myString_lock2 = "";
String myString_lock3 = "";

int LED = 9;
int count = 0; // 
int LED_ON = 0;
int GREEN_LED = 8;//녹색
int GREEN_LED_ON = 0;

//진동감지센서
int Shake_Sensor = 4;

//모터
int motor_control = 12;
Servo servo;
int value=0;

//경고부저
int speakerPin = 7;
int numTones = 6;
int tones[] = {523};//진동감지센서
int tones1[] = {523, 523};//비밀번호
int tones2[] = {261, 330, 392, 523};
int tones3[] = {523, 392, 330, 261};

//버튼기능
int reset_button = 10;
int setting_button = 11;
String password[3] = {"1234", "2345", "3456"};
int size = sizeof(password)/sizeof(String);

//세팅버튼을 눌렀을 때 그것이 눌러졌음을 고정하기 위해
int setting_pushed = 0;
//세팅버튼에서 1번선택지
int Security_Clearance = 0;
//세팅버튼에서 2번선택지
int Setting_Password = 0;
//세팅버튼에서 3번선택지
int Setting_Warning_Sound = 0;
int Select_Sound = 0;
int soundA = 0;
int soundB = 0;
int soundC = 0;
//보안레벨
int password_level1 = 1;//기본 보안 레벨.
int password_level2 = 0;
int password_level3 = 0;
//비밀번호 수정
int passwordCount = 0;

//기본 터미널 화면
int ter_count = 0;

void setup() {
  //블루투스
  Serial.begin(9600); 
  mySerial.begin(9600);
  delay(100);
  pinMode(LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  //모터
  servo.attach(motor_control);
  //진동센서
  pinMode(Shake_Sensor, INPUT);
  //버튼
  pinMode(reset_button, INPUT_PULLUP); 
  pinMode(setting_button, INPUT_PULLUP); 

  mySerial.println("======================"); delay(100);
  mySerial.println("This is KIM's Safe Security System."); delay(100);
  terminal_advice();
  mySerial.println("======================"); delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  char cmd;
  while(mySerial.available()){
    cmd = (char)mySerial.read();
    myString += cmd;
    delay(5);//수신 문자열 끊임 방지
    //mySerial.write("ABC");
  }
  

  //리셋 버튼이 눌러지면
  if(digitalRead(reset_button) == HIGH){
    password[0] = "1234";
    password[1] = "2345";
    password[2] = "3456";
    //보안레벨도 초기화
    password_level1 = 1;
    password_level2 = 0;
    password_level3 = 0;
    mySerial.println("*********************");delay(100);
    mySerial.println("[[Locker has Resetted!!!]]");delay(100);
    mySerial.println("*********************");delay(100);
    delay(500);
    terminal_advice();
  }
  //세팅 버튼이 눌러지면!
  if(digitalRead(setting_button) == HIGH){
    setting_pushed = 1;
    if(setting_pushed == 1){
      setting_button_advice();  
    }
    delay(500);
  }

  if(!myString.equals("")){

    if(myString == "1" && setting_pushed == 1 && Security_Clearance == 0 && Setting_Password == 0 && Setting_Warning_Sound == 0){
      Security_Clearance = 1;//1번 선택지가 눌렸을 때.
      setting_security_advice();
      myString == "";//myString 초기화
    }
    else if(myString == "1" && Security_Clearance == 1){//Setting Level 1
      //로그인에 password가 1개만 필요.
      password_level1 = 1;
      password_level2 = 0;
      password_level3 = 0;
      setting_security_advice(); delay(100);
      mySerial.println("*********************"); delay(100);
      mySerial.println("Setting Security LV.1"); delay(100);
      mySerial.println("*********************"); delay(100);
      myString = "";
    }
    else if(myString == "2" && Security_Clearance == 1){//Setting Level 2
      //로그인에 password가 2개가 필요.
      password_level1 = 0;
      password_level2 = 1;
      password_level3 = 0;
      setting_security_advice();delay(100);
      mySerial.println("*********************");delay(100);
      mySerial.println("Setting Security LV.2");delay(100);
      mySerial.println("*********************");delay(100);
      myString = "";
    }
    else if(myString == "3" && Security_Clearance == 1){//Setting Level 3
      //로그인에 password가 1개만 필요.
      password_level1 = 0;
      password_level2 = 0;
      password_level3 = 1;
      setting_security_advice();delay(100);
      mySerial.println("*********************");delay(100);
      mySerial.println("Setting Security LV.3");delay(100);
      mySerial.println("*********************");delay(100);
      myString = "";
    }
    else if(myString == "4" && Security_Clearance == 1){//Setting Back
      myString = "";
      Security_Clearance = 0;
      setting_button_advice();
    }
    
    //2. 비밀번호 설정
    else if(myString == "2" && setting_pushed == 1 && Security_Clearance == 0 && Setting_Password == 0 && Setting_Warning_Sound == 0){
      Setting_Password = 1;
      myString == "";//myString 초기화
      setting_password_advice();
    }
    //1. 현재 비밀번호 확인
    else if(myString == "1" && setting_pushed == 1 && Security_Clearance == 0 && Setting_Password == 1 && Setting_Warning_Sound == 0){
      setting_password_advice();delay(100);
      mySerial.println("============================");delay(100);
      mySerial.println("Current Password : [[" + password[0] + "]], [[" + password[1] + "]], [[" + password[2] + "]]");delay(100);
      mySerial.println("============================");delay(100);
      myString == "";      
    }
    //2. password[0] 수정
    else if(myString == "2" && setting_pushed == 1 && Security_Clearance == 0 && Setting_Password == 1 && Setting_Warning_Sound == 0){
      passwordCount = 1;//1번 비밀번호일 경우
      setting_password_advice2(0);
      myString = "";
    }
    //myString에 패스워드가 입력되었다면?
    else if(setting_pushed == 1 && Security_Clearance == 0 && Setting_Password == 1 && passwordCount == 1){
      passwordCount = 0;//passwordCount 초기화
      password[0] = myString;
      setting_password_advice();delay(100);
      mySerial.println("*********************");delay(100);
      mySerial.println("Password One has Changed!");delay(100);
      mySerial.println("Current Password : [[" + password[0] + "]]");delay(100);
      mySerial.println("*********************");delay(100);
      myString = "";

    }
    //3. password[1]
    else if(myString == "3" && setting_pushed == 1 && Security_Clearance == 0 && Setting_Password == 1 && Setting_Warning_Sound == 0){
      passwordCount = 2;//2번 비밀번호일 경우
      setting_password_advice2(1);
      myString = "";
    }
    //myString에 패스워드가 입력되었다면?
    else if(setting_pushed == 1 && Security_Clearance == 0 && Setting_Password == 1 && passwordCount == 2){
      passwordCount = 0;//passwordCount 초기화
      password[1] = myString;
      setting_password_advice();delay(100);
      mySerial.println("*********************");delay(100);
      mySerial.println("Password Two has Changed!");delay(100);
      mySerial.println("Current Password : [[" + password[1] + "]]");delay(100);
      mySerial.println("*********************");delay(100);
      myString = "";
    }
    //4. password[2]
    else if(myString == "4" && setting_pushed == 1 && Security_Clearance == 0 && Setting_Password == 1 && Setting_Warning_Sound == 0){
      passwordCount = 3;//3번 비밀번호일 경우
      setting_password_advice2(2);
      myString = "";
    }
    //myString에 패스워드가 입력되었다면?
    else if(setting_pushed == 1 && Security_Clearance == 0 && Setting_Password == 1 && passwordCount == 3){
      password[2] = myString;
      setting_password_advice();delay(100);
      mySerial.println("*********************");delay(100);
      mySerial.println("Password Three has Changed!");delay(100);
      mySerial.println("Current Password : [[" + password[2] + "]]");delay(100);
      mySerial.println("*********************");delay(100);
      myString = "";
      passwordCount = 0;
    }
    else if(myString == "5" && setting_pushed == 1 && Security_Clearance == 0 && Setting_Password == 1){
      //기본 세팅메뉴로 돌아가기
      myString = "";
      Setting_Password = 0;
      setting_button_advice();
    }

    //3번. 세팅 버튼 화면에서 3. quit이 눌러졌을 때
    else if(myString == "3" && setting_pushed == 1 && Security_Clearance == 0 && Setting_Password == 0 && Setting_Warning_Sound == 0){
      setting_pushed = 0;
      mySerial.println("Setting finished!");delay(100);
      terminal_advice();
    }

    else if(password_level1 == 1 && setting_pushed == 0){
      if(myString == password[0]){
        if(count == 0){
          count++;
          open();
        }
        else if(count==1){
          close();
          count = 0;
        }
      }
      else{
        mySerial.println("Wrong Password. Write again.");delay(100);
        myString = ""; // 잘못된 비밀번호 입력 시 myString 초기화
        passwordAlarm();
        terminal_advice();
      }
    }
    //보안 레벨이 2일 때
    else if(password_level2 == 1 && myString2 == "" && setting_pushed == 0){//1번째 입력
      if(myString == password[0]){
        mySerial.println("Password 1 has been certified. Please Enter Password 2.");delay(100);
        myString2 = myString;
        myString = "";
        terminal_advice();
      }
      else{
        mySerial.println("Wrong Password. Write again.");
        delay(100);
        myString = ""; // 잘못된 비밀번호 입력 시 myString 초기화
        passwordAlarm();
        terminal_advice();
      }
    }
    else if(password_level2 == 1 && myString2 == password[0] && count == 0 && setting_pushed == 0){//2번째 입력. 잠금 해제
      if(myString == password[1]){
        if(count == 0){
          count++;
          //LED의 ON, OFF 여부로 확인.
          open();
        }
      }
      else{
        mySerial.println("Wrong Password. Write again.");delay(100);
        passwordAlarm();
        myString = ""; // 잘못된 비밀번호 입력 시 myString 초기화
        terminal_advice();
      }
    }
    else if(password_level2 == 1 && myString2 == password[0] && count == 1 && setting_pushed == 0){//1번 비밀번호 입력 성공
      if(myString == password[0]){
        mySerial.println("Password 1 has been certified. Please Enter Password 2.");delay(100);
        count++;
        myString = "";
        terminal_advice();
      }
      else{
        mySerial.println("Wrong Password. Write again.");delay(100);
        passwordAlarm();
        myString = ""; // 잘못된 비밀번호 입력 시 myString 초기화
        terminal_advice();
      }
    }
    else if(password_level2 == 1 && myString2 == password[0] && count == 2 && setting_pushed == 0){//2번 비밀번호 입력 성공
      if(myString == password[1]){
        count = 0;
        myString2 = "";
        myString = "";
        close();
      }
      else{
        mySerial.println("Wrong Password. Write again.");delay(100);
        passwordAlarm();
        myString = ""; // 잘못된 비밀번호 입력 시 myString 초기화
        terminal_advice();
      }
    }
    

    //보안레벨이 3일때
    else if (password_level3 == 1 && myString3 == "" && setting_pushed == 0) {//1번 입력
      if (myString == password[0]) {
        mySerial.println("Password 1 has been certified. Please enter Password 2.");delay(100);
        myString3 = myString;
        myString = "";
        terminal_advice();
      }
      else {
        mySerial.println("Wrong Password. Write again.");delay(100);
        passwordAlarm();
        myString = ""; // 잘못된 비밀번호 입력 시 myString 초기화
        terminal_advice();
      }
    }
    else if (password_level3 == 1 && myString3 == password[0] && count == 0 && setting_pushed == 0) {//2번 입력
      if (myString == password[1]) {
        mySerial.println("Password 2 has been certified. Please enter Password 3.");delay(100);
        count++;
        myString = "";
      }
      else {
        mySerial.println("Wrong Password. Write again.");delay(100);
        passwordAlarm();
        myString = ""; // 잘못된 비밀번호 입력 시 myString 초기화
        terminal_advice();
      }
    }
    else if (password_level3 == 1 && myString3 == password[0] && count == 1 && setting_pushed == 0) {//3번 입력
      if (myString == password[2]) {
        if (count == 1) {
          Serial.println("");
          count++;
          open();
        }
      }
      else {
        mySerial.println("Wrong Password. Write again.");delay(100);
        passwordAlarm();
        myString = ""; // 잘못된 비밀번호 입력 시 myString 초기화
        terminal_advice();
      }
    }
    else if (password_level3 == 1 && myString3 == password[0] && count == 2 && setting_pushed == 0) {//1번 입력
      if (myString == password[0]) {
        mySerial.println("Password 1 has been certified. Please enter Password 2.");delay(100);
        count++;
        myString = "";
        terminal_advice();
      }
      else {
        mySerial.println("Wrong Password. Write again.");delay(100);
        passwordAlarm();
        myString = ""; // 잘못된 비밀번호 입력 시 myString 초기화
        terminal_advice();
      }
    }
    else if (password_level3 == 1 && myString3 == password[0] && count == 3 && setting_pushed == 0) {//2번 입력
      if (myString == password[1]) {
        mySerial.println("Password 2 has been certified. Please enter Password 3.");delay(100);
        count++;
        myString = "";
        terminal_advice();
      }
      else {
        mySerial.println("Wrong Password. Write again.");delay(100);
        passwordAlarm();
        myString = ""; // 잘못된 비밀번호 입력 시 myString 초기화
        terminal_advice();
      }
    }
    else if (password_level3 == 1 && myString3 == password[0] && count == 4 && setting_pushed == 0) {//3번 입력
      if (myString == password[2]) {
        count = 0;
        myString3 = "";
        myString = "";
        close();
      }
      else {
        mySerial.println("Wrong Password. Write again.");delay(100);
        passwordAlarm();
        myString = ""; // 잘못된 비밀번호 입력 시 myString 초기화
        terminal_advice();
      }
    }
  }
  if(LED_ON == 0){
    if(digitalRead(Shake_Sensor) == HIGH){

      mySerial.println("SomeOne is Shaking The Safe!!!!");delay(100);
      for (int i = 0; i < numTones; i++){
        tone(speakerPin, tones[i]); //경고 부저가 울린다.
        delay(100);
        digitalWrite(LED, LOW);
        delay(100);
        digitalWrite(LED, HIGH);
        delay(100);
        digitalWrite(LED, LOW);
        delay(100);
        digitalWrite(LED, HIGH);
        delay(100);
        digitalWrite(LED, LOW);
        delay(100);
      }
      noTone(speakerPin);
      delay(500);
    }
  }
  myString = "";
}
void terminal_advice(){
  mySerial.println("Please Write your Password : ");delay(100);
}
void setting_button_advice(){
  mySerial.println("This is User's Guide.");delay(100);
  mySerial.println("============================");delay(100);
  mySerial.println("1.Setting Security Clearance.");//보안등급 설정. 3등급까지 설정 가능.
  delay(100);
  mySerial.println("2.Setting Password.");// 비밀번호 변경
  delay(100);
  mySerial.println("3.Quit");delay(100);
  mySerial.println("============================");delay(100);
}
void setting_security_advice(){
  mySerial.println("Setting Security Clearance.");delay(100);
  mySerial.println("=============");delay(100);
  mySerial.println("1.Setting Level 1.");delay(100);
  mySerial.println("2.Setting Level 2.");delay(100);
  mySerial.println("3.Setting Level 3.");delay(100);
  mySerial.println("4.Back");delay(100);
  mySerial.println("=============");delay(100);
}
void setting_password_advice(){
  mySerial.println("Setting Password.");delay(100);
  mySerial.println("============================");delay(100);
  mySerial.println("1.Check Current Password.");delay(100);
  mySerial.println("2.Change Password One.");delay(100);
  mySerial.println("3.Change Password Two.");delay(100);
  mySerial.println("4.Change Password Three.");delay(100);
  mySerial.println("5.Back");delay(100);
  mySerial.println("============================");delay(100);
}
void setting_password_advice2(int i){
  mySerial.println("============================");delay(100);
  mySerial.println("Current Password : " + password[i]);delay(100);
  mySerial.println("============================");delay(100);
  mySerial.println("Please Enter new Password : ");  delay(100);
}
void passwordAlarm(){
  for (int i = 0; i < 2; i++){
    tone(speakerPin, tones1[i]); //경고 부저가 울린다.
    if(LED_ON == 0){
      digitalWrite(LED, HIGH);
      delay(100);
      digitalWrite(LED, LOW);
      delay(100);
    }
    else if(LED_ON == 1){
      digitalWrite(LED, LOW);
      delay(100);
      digitalWrite(LED, HIGH);
      delay(100);
    }
    noTone(speakerPin);
    delay(50);
  }
  noTone(speakerPin);
  delay(500);
}
void passwordAlarm_correct(){
  for (int i = 0; i < 4; i++){
    tone(speakerPin, tones2[i]); //경고 부저가 울린다.
    delay(300);
    noTone(speakerPin);
    delay(50);
  }
  noTone(speakerPin);
  delay(500);
}
void passwordAlarm_lock(){
  for (int i = 0; i < 4; i++){
    tone(speakerPin, tones3[i]); //경고 부저가 울린다.
    delay(300);
    noTone(speakerPin);
    delay(50);
  }
  noTone(speakerPin);
  delay(500);
}
void open(){
   //LED의 ON, OFF 여부로 확인.
  digitalWrite(LED, LOW);
  LED_ON = 0;
  digitalWrite(GREEN_LED, HIGH);
  GREEN_LED_ON = 1;
  myString="";
  value=90;
  servo.write(value); //value값의 각도로 회전. ex) value가 90이라면 90도 회전
  passwordAlarm_correct();
  mySerial.println("Password has been certified");delay(100);
}
void close(){
  digitalWrite(LED, HIGH); // LED로 비밀번호의 입력여부를 알기 때문에 LOW일 경우 비밀번호가 입력되지 않은 상황.
  LED_ON = 1; // 비밀번호가 입력되지 않은 상황이란 의미
  digitalWrite(GREEN_LED, LOW);
  GREEN_LED_ON = 0;
  myString="";
  value=0;
  servo.write(value); //value값의 각도로 회전. ex) value가 90이라면 90도 회전
  passwordAlarm_lock();
  mySerial.println("Password has been certified. Lock again.");delay(100);
  terminal_advice();
}