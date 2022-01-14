

// khai bao chan relay

int relay1 = PA0; // den1
int relay2 = PA2;// den2
int relay3 = PA3;// quat
int relay4 = PA4;//khoa
// khai bao chan cam bien
int PIR = PA5;
int trangthai ;
// khai bao chan quang tro
int quangtro = PA6; //Thiết đặt chân analog đọc quang trở
int bientro = PA7; // Thiết đặt chân analog đọc biến trở
int trangthaiden;
// bien nhan du lieu
char inputdata = 0;  //Variable for storing received data

void setup()
{
  Serial1.begin(9600);                      //Sets the baud rate for bluetooth pins
  Serial1.print("HOME AUTOMATION WITH STM32\n");

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(PIR, INPUT);
  pinMode(buzzer, OUTPUT);


  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);

  trangthai = 0;
  trangthaiden =0;

}

void loop()
{
  int value = digitalRead(PIR);
  int giatriQuangtro = analogRead(quangtro);// đọc giá trị quang trở
  int giatriBientro =  analogRead(bientro);// đọc giá trị biến trở

  if (Serial1.available() > 0)   // Send data only when you receive data:
  {
    inputdata = Serial1.read();        //Read the incoming data & store into data
    // chuc nang chong trom
    if (inputdata == 'V')
    {
      Serial1.print("đã tắt chức năng cảnh báo\n");
      trangthai = 0;

    }

    if (inputdata == 'v')
    {
      Serial1.print("đã bật chức năng cảnh báo\n");

      trangthai = 1;
    }
    // chuc nang den auto
    if (inputdata == 'E')
    {
      Serial1.print("đã tắt chức năng den tu dong\n");
      trangthaiden = 0;

    }

    if (inputdata == 'e')
    {
      Serial1.print("đã bật chức năng den tu dong\n");
      trangthaiden = 1;
    }

       if (inputdata == 'a'&& trangthaiden==0)
    {
      digitalWrite(relay1, LOW);
      Serial1.print("den 1 mo \n");

    }

    if (inputdata == 'A'&& trangthaiden ==0)
    {
     digitalWrite(relay1, HIGH);
     Serial1.print("den 1 tat\n");
    }
    if (inputdata == 'B'&& trangthai==0)
    {
      digitalWrite(relay2, HIGH);
      Serial1.print("den2 tat\n");
    }

    if (inputdata == 'b'&&trangthai==0)
    {
      digitalWrite(relay2, LOW);
      Serial1.print("den 2 bat\n");
    }


    if (inputdata == 'C')
    {
      digitalWrite(relay3, HIGH);
      Serial1.print("quat bat\n");
    }

    if (inputdata == 'c')
    {
      digitalWrite(relay3, LOW);
      Serial1.print("quat tat\n");
    }


    if (inputdata == 'D')
    {
      digitalWrite(relay4, HIGH);
      Serial1.print("khoa dong\n");
    }

    if (inputdata == 'd')
    {
      digitalWrite(relay4, LOW);
      Serial1.print("khoa mo\n");
    }
  }
  // xư ly quang tro de bat tat den tu dong
  if (giatriQuangtro <= giatriBientro && trangthaiden==1) {
    digitalWrite(relay1, LOW);
     delay(3000);
  }  
  if(giatriQuangtro > giatriBientro && trangthaiden==1){
    digitalWrite(relay1, HIGH);
     delay(3000);
  }
// xử lý cảm biến
  if (value == HIGH && trangthai == 1) {
     digitalWrite(relay2, LOW);
    delay(3000);
  }
   if (value == LOW && trangthai == 1) {
    digitalWrite(relay2, HIGH);
    delay(3000);
  }

}
