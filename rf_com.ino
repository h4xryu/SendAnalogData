
int cnt = 0;
bool start = false;
int curr_time;
String chk;
int runState;
bool chkgotcmd = false;
int timeoutCount = 0;

void send_data();


void setup() {
  Serial.begin(115200);
  Serial.setTimeout(1000);
  }

void loop() {
    

  while(Serial.available()){ //read datas from pc
    
    chk = Serial.readString();
    runState = chk.toInt();
    chkgotcmd = true;
    
  }
  if (runState) start = 1;
  if (!runState) start = 0;
  if (runState == 2) {
      cnt = 0;
      start = 0; 
  }

  if (start == 1) {
    send_data();
  }
}
  




void send_data(){ //100번 반복마다 ETX
  cnt += 1;
  Serial.print("@"); //1byte @: STX
  int data = analogRead(A0);
  Serial.print(data); // 데이터 사이즈는 0~2 byte 
  Serial.print("#"); // #: ETX
  delayMicroseconds(0.0334);
  
  if(cnt == 100){
    Serial.println("$"); //$ : 100개 출력 완료 
    cnt = 0;
    runState = 0; //시작 하라고 할 때까지 대기
  }
}