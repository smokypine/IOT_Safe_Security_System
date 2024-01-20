int reset_button = 10;
int setting_button = 11;
String password[] = {"1234", NULL, NULL};
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

void setup() {
  // put your setup code here, to run once:
  pinMode(reset_button, INPUT); 
  pinMode(setting_button, INPUT); 


}

void loop() {
  // put your main code here, to run repeatedly:
  //리셋 버튼이 눌러지면!
  if(digitalRead(reset_button) == HIGH){
    for(int i = 0; i<password.length(); i++){
      password[i] = NULL;
    }
    password[0] = 1234;//기본 패스워드로 초기화
  }

  //세팅 버튼이 눌러지면!
  if(digitalRead(setting_button) == HIGH){
    setting_pushed = 1;
    if(setting_pushed == 1){
      setting_button_advice();
    }
  }

  //버튼이 눌린 이후 터미널로 입력하는 코드
  if(!myString.equals("")){//내 터미널에 아무것도 안 쳐졌을 때
    if(myString == '1' && setting_pushed == 1){
      Security_Clearance = 1;//1번 선택지가 눌렸을 때.
      myString == "";//myString 초기화
      Serial.println("Setting Security Clearance.");
      Serial.println("============================");
      Serial.println("1.Setting Level 1.");
      Serial.println("2.Setting Level 2.");
      Serial.println("3.Setting Level 3.");
      Serial.println("4.Back");
      Serial.println("============================");
    }
    if(myString == '1' && Security_Clearance == 1){//Setting Level 1
      //로그인에 password가 1개만 필요.
      myString = "";
    }
    if(myString == '2' && Security_Clearance == 1){//Setting Level 2
      //로그인에 password가 2개가 필요.
      myString = "";
    }
    if(myString == '3' && Security_Clearance == 1){//Setting Level 3
      //로그인에 password가 1개만 필요.
      myString = "";
    }
    if(myString == '4' && Security_Clearance == 1){//Setting Back
      myString = "";
      Security_Clearance = 0;
      setting_button_advice();
    }

    if(myString == "2" && setting_pushed == 1){
      Setting_Password = 1;//2번 선택지가 눌렸을 때.
      myString == "";//myString 초기화
      Serial.println("Setting Password.");
      Serial.println("============================");
      Serial.println("1.Add Password.");
      Serial.println("2.Change Password.");
      Serial.println("3.Remove Password.");
      Serial.println("4.Back");
      Serial.println("============================");
  }
  if(myString == "1" && Setting_Password == 1){
    //password 추가
    myString = "";
  }
  if(myString == "2" && Setting_Password == 1){
    //password 수정
    myString = "";
  }
  if(myString == "3" && Setting_Password == 1){
    //password 삭제
    myString = "";
  }
  if(myString == "4" && Setting_Password == 1){
    //기본 세팅메뉴로 돌아가기
    myString = "";
    Setting_Password = 0;
    setting_button_advice();
  }
  
  //3번. 경고음 수정이 눌러질 때
  if(myString == "3" && setting_pushed == 1){
    Setting_Warning_Sound = 1;
    myString == "";//myString 초기화
    Serial.println("Setting Warning Sound.");
    Serial.println("============================");
    Serial.println("1.Select Sound.");
    Serial.println("2.Back");
    Serial.println("============================");
  }
  //1.Setting_Warning_Sound -> Select Sound 선택
  if(myString == "1" && Setting_Warning_Sound == 1){
    //소리 선택.
    Select_Sound = 1;
    myString = "";
    select_sound_advice();
  }
  //1.Setting_Warning_Sound-> Select Sound 선택 -> SoundA선택
  if(myString == "A" && Select_Sound == 1){
    //음악 나오고 
    soundA = 1;
    myString = "";

    //질문지 출력.
    select_sound_advice2();
  }
  if(myString == "YES" && Select_Sound == 1 && soundA == 1 ){
    //부저 경고음 변경!
    soundA = 0;
    myString = "";
    select_sound_advice();
  }
  if(myString == "NO" && Select_Sound == 1 && soundA == 1 ){
    //부저 경고음 변경!
    soundA = 0;
    myString = "";
    select_sound_advice();
  }
 //1.Setting_Warning_Sound-> Select Sound -> SoundB선택
  if(myString == "B" && Select_Sound == 1){
    //음악 나오고 
    soundB = 1;
    myString = "";

    //질문지 출력.
    select_sound_advice2();
  }
  if(myString == "YES" && Select_Sound == 1 && soundB == 1 ){
    //부저 경고음 변경!
    soundB = 0;
    myString = "";
    select_sound_advice();
  }
  if(myString == "NO" && Select_Sound == 1 && soundB == 1 ){
    //부저 경고음 변경!
    soundB = 0;
    myString = "";
    select_sound_advice();
  }
  //1.Setting_Warning_Sound-> Select Sound -> SoundC선택
  if(myString == "B" && Select_Sound == 1){
    //음악 나오고 
    soundC = 1;
    myString = "";

    //질문지 출력.
    select_sound_advice2();
  }
  if(myString == "YES" && Select_Sound == 1 && soundC == 1 ){
    //부저 경고음 변경!
    soundC = 0;
    myString = "";
    select_sound_advice();
  }
  if(myString == "NO" && Select_Sound == 1 && soundC == 1 ){
    //부저 경고음 변경!
    soundC = 0;
    myString = "";
    select_sound_advice();
  }
   //2.Back선택
  if(myString == "2" && Setting_Warning_Sound == 1){
    myString = "";
    Setting_Warning_Sound = 0;
    setting_button_advice();
  }
}
void setting_button_advice(){
  Serial.println("This is User's Guide.\n");
  Serial.println("============================\n");
  Serial.println("1.Setting Security Clearance.\n");//보안등급 설정. 3등급까지 설정 가능.
  Serial.println("2.Setting Password.\n");//기초 비밀번호 설정, 비밀번호 추가, 삭제
  Serial.println("3.Setting Warning Sound.\n");//경보음 설정
  Serial.println("4.Quit\n");
  Serial.println("============================\n");
  Serial.println("Write number.\n");
}
void select_sound_advice(){
  Serial.println("Select Sound.");
  Serial.println("============================");
  Serial.println("A.Sound_A.");
  Serial.println("B.Sound_B.");
  Serial.println("C.Sound_C.");
  Serial.println("D.Back");
  Serial.println("============================");
  Serial.println("Write Alphabet(A/B/C/D)!");
}
void select_sound_advice2(){
  Serial.println("Would you like to Change the Alarm?");
  Serial.println("============================");
  Serial.println("1.YES");
  Serial.println("2.NO");
  Serial.println("============================");
  Serial.println("Write YES / NO");
}