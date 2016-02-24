 
short To_Read = 38;
short To_Write = 39;
short Chip_sel = 51;
short Enable_Stop1= 53;
short interrupt_pin = 43;
bool configured = false;
volatile int valid = 0;

//address
int add_0 = 22;
int add_1 = 23;
int add_2 = 24;
int add_3 = 25;
// data
//int data_pin_0 = 28;    int volatile data_0;
//int data_pin_1 = 29;    int volatile data_1;
//int data_pin_2 = 30;    int volatile data_2;
//int data_pin_3 = 31;    int volatile data_3;    
//int data_pin_4 = 32;    int volatile data_4;
//int data_pin_5 = 33;    int volatile data_5;
//int data_pin_6 = 34;    int volatile data_6;
//int data_pin_7 = 35;    int volatile data_7;

short data_pin_0 = 28;    short  data_0;
short data_pin_1 = 29;    short  data_1;
short data_pin_2 = 30;    short  data_2;
short data_pin_3 = 31;    short  data_3;    
short data_pin_4 = 32;    short  data_4;
short data_pin_5 = 33;    short  data_5;
short data_pin_6 = 34;    short  data_6;
short data_pin_7 = 35;    short  data_7;

// variables

int nk0=0 ,nk1=0 ,vk0=0 ,vk1=0;
float final_result = 0.0; 

// functions  
void Write_To_Register(int bit7, int bit6, int bit5, int bit4, int bit3, int bit2, int bit1, int bit0)
{
    digitalWrite(data_pin_0, bit0);
    digitalWrite(data_pin_1, bit1);
    digitalWrite(data_pin_2, bit2);
    digitalWrite(data_pin_3, bit3);
    digitalWrite(data_pin_4, bit4);
    digitalWrite(data_pin_5, bit5);
    digitalWrite(data_pin_6, bit6);
    digitalWrite(data_pin_7, bit7);
}
void Read_From_Register()
{
    data_0 = digitalRead(data_pin_0);
    data_1 = digitalRead(data_pin_1);
    data_2 = digitalRead(data_pin_2);
    data_3 = digitalRead(data_pin_3);
    data_4 = digitalRead(data_pin_4);
    data_5 = digitalRead(data_pin_5);
    data_6 = digitalRead(data_pin_6);
    data_7 = digitalRead(data_pin_7);
    

  
}
void Init_byte()
{
    data_0 = 0;
    data_1 = 0;
    data_2 = 0;
    data_3 = 0;
    data_4 = 0;
    data_5 = 0;
    data_6 = 0;
    data_7 = 0;
  
}
void Choose_Address(int bit3, int bit2, int bit1, int bit0)
{
    digitalWrite(add_0, bit0);  
    digitalWrite(add_1, bit1);
    digitalWrite(add_2, bit2);
    digitalWrite(add_3, bit3);
}
void Reset_Address_data()
{
    Choose_Address(0,0,0,0);
    Write_To_Register(0,0,0,0,0,0,0,0);
    
}
void Reset_Address()
{
    Choose_Address(0,0,0,0);
       
}

void Print_data()
{
    Serial.print(data_7);
    Serial.print(data_6);
    Serial.print(data_5);
    Serial.print(data_4);
    Serial.print(data_3);
    Serial.print(data_2);
    Serial.print(data_1);
    Serial.println(data_0);
}
void Prep_To_Write()
{
    digitalWrite(To_Read, HIGH); //low active 
    digitalWrite(Chip_sel, LOW); //low active
}
void Finish_Write()
{
    digitalWrite(To_Write, HIGH); //
    digitalWrite(Chip_sel, HIGH); //low active
   
 }
 void Prep_To_Read()
{  
    digitalWrite(To_Write, HIGH); // 
    digitalWrite(Chip_sel, LOW); //
}
void Finish_Read()
{
    digitalWrite(To_Read, HIGH); //low active
    digitalWrite(Chip_sel, HIGH);
}
int To_integer()
    {
      int result = 0, res[8];
      res[0]=data_0;
      res[1]=data_1;
      res[2]=data_2;
      res[3]=data_3;
      res[4]=data_4;
      res[5]=data_5;
      res[6]=data_6;
      res[7]=data_7;
      for(int i=0; i<8; i++)
      {
        if (res [i] != 0) 
        result += pow(2,i);
      }
      return result;
    }
    

void First_configuration()
{
   configured = true;
   Reset_Address_data();

    // REG 7 : Disable inputs while writing to control register
    Prep_To_Write();
    Serial.println("initialization of control registers ...");
    Choose_Address(0,1,1,1); //7
    Serial.println("setting REG 7");
    Write_To_Register(0,0,0,0,0,0,0,0);// for optimization we can use one hex number instead of 8 integer numbers, and test it in the function accordingly.
    digitalWrite(To_Write, LOW); // write is activated here
    delayMicroseconds(1);
    Finish_Write();
    Reset_Address_data();
    

    // REG 0 CALIBRATE - MULTIPLY
    Prep_To_Write();
    Choose_Address(0,0,0,0);
    Serial.println("setting REG 0");
    Write_To_Register(0,1,1,0,0,0,0,0);//0x60
    digitalWrite(To_Write, LOW); // write is activated here
    delayMicroseconds(1);
    Finish_Write();
    Reset_Address_data();
    
    // REG 2 Calculate Stop1 and Start 
    Prep_To_Write();
    Choose_Address(0,0,1,0);
    Serial.println("setting REG 2");
    Write_To_Register(0,0,0,0,0,0,0,1);//0x01
    digitalWrite(To_Write, LOW); // write is activated here
    delayMicroseconds(1);
    Finish_Write();
    Reset_Address_data();
       
     // REG 6 RETRIG_EN
    Prep_To_Write();
    Choose_Address(0,1,1,0);
    Serial.println("setting REG 6");
    Write_To_Register(0,0,1,0,0,0,0,1); //0x21
    digitalWrite(To_Write, LOW); // write is activated here
    delayMicroseconds(1);
    Finish_Write();
    Reset_Address_data(); 
       
    // REG 7
    Prep_To_Write();
    Choose_Address(0,1,1,1);
    Serial.println("setting REG 7");
    Write_To_Register(0,0,0,0,0,0,1,0); 
    digitalWrite(To_Write, LOW); // write is activated here
    delayMicroseconds(1);
    Finish_Write();
    Reset_Address_data();   
       
    Serial.println("setting finnished"); 
   // digitalWrite(Start, LOW);
   // digitalWrite(Stop, LOW);
   // digitalWrite(Stop, HIGH);
}
void Configuration()
{
  
    configured = true;
    Reset_Address_data();
   
      // REG 11
    Prep_To_Write();
    Choose_Address(1,0,1,1);
    Serial.println("setting REG 11");
    Write_To_Register(1,0,1,0,0,1,1,1);//0xA7
    digitalWrite(To_Write, LOW); // write is activated here
    delayMicroseconds(1);
    Finish_Write();
    Reset_Address_data();
    //--*-----------------------------
    
    // REG 11 Init the ALU, BigALU and auto noise unit
    Prep_To_Write();
    Choose_Address(1,0,1,1);
    Serial.println("setting REG 11");
    Write_To_Register(0,0,0,0,0,1,1,1);//0x07
    digitalWrite(To_Write, LOW); // write is activated here
    delayMicroseconds(1);
    Finish_Write();
    Reset_Address_data();
    //*-------------------------------------
    
    // REG 0 
    Prep_To_Write();
    Choose_Address(0,0,0,0);
    Serial.println("setting REG 0");
    Write_To_Register(0,1,0,0,1,0,0,0);//0x48
    digitalWrite(To_Write, LOW); // write is activated here
    delayMicroseconds(1);
    Finish_Write();
    Reset_Address_data();
    
        //*-------------------------------------
    
    // REG 2
    Prep_To_Write();
    Choose_Address(0,0,1,0);
    Serial.println("setting REG 2");
    Write_To_Register(0,0,0,0,0,0,0,1);//0x21
    digitalWrite(To_Write, LOW); // write is activated here
    delayMicroseconds(1);
    Finish_Write();
    Reset_Address_data();
    
    //*-------------------------------------
    
    // REG 4
    Prep_To_Write();
    Choose_Address(0,1,0,0);
    Serial.println("setting REG 4");
    Write_To_Register(1,1,1,0,0,0,0,0);//0x00
    digitalWrite(To_Write, LOW); // write is activated here
    delayMicroseconds(1);
    Finish_Write();
    Reset_Address_data(); 
    
    //*-------------------------------------
    
    // REG 6 Retriger
    Prep_To_Write();
    Choose_Address(0,1,1,0);
    Serial.println("setting REG 6");
    Write_To_Register(0,0,1,0,0,0,0,1);//0x60
    digitalWrite(To_Write, LOW); // write is activated here
    delayMicroseconds(1);
    Finish_Write();
    Reset_Address_data();
    
    // REG 7
    Prep_To_Write();
    Choose_Address(0,1,1,1);
    Serial.println("setting REG 7");
    Write_To_Register(0,0,0,0,0,0,1,0);//0x02
    digitalWrite(To_Write, LOW); // write is activated here
    delayMicroseconds(1);
    Finish_Write();
    Reset_Address_data(); 
    
}

void setup() {
  Serial.begin(9600);
  
  pinMode(To_Read,OUTPUT);
  pinMode(To_Write,OUTPUT);
  pinMode(Chip_sel,OUTPUT);

  
  pinMode(interrupt_pin,INPUT);
 // pinMode(Start,OUTPUT);
 // pinMode(Stop,OUTPUT);
  pinMode(add_0,OUTPUT);
  pinMode(add_1,OUTPUT);
  pinMode(add_2,OUTPUT);
  pinMode(add_3,OUTPUT);
  pinMode(data_pin_0,OUTPUT);
  pinMode(data_pin_1,OUTPUT);
  pinMode(data_pin_2,OUTPUT);
  pinMode(data_pin_3,OUTPUT);
  pinMode(data_pin_4,OUTPUT);
  pinMode(data_pin_5,OUTPUT);
  pinMode(data_pin_6,OUTPUT);
  pinMode(data_pin_7,OUTPUT); 


   digitalWrite(To_Write, HIGH); //
   digitalWrite(To_Read, HIGH); //
   digitalWrite(Chip_sel, HIGH); //

 }

void loop() {

   if(configured == false)
   {
      Configuration();
   }
   else
   {

    // make the data bus as inputs to read the results
    pinMode(data_pin_0,INPUT);
    pinMode(data_pin_1,INPUT);
    pinMode(data_pin_2,INPUT);
    pinMode(data_pin_3,INPUT);
    pinMode(data_pin_4,INPUT);
    pinMode(data_pin_5,INPUT);
    pinMode(data_pin_6,INPUT);
    pinMode(data_pin_7,INPUT); 
    delayMicroseconds(1);  
    
  
    while (valid==0)
      {
        valid = digitalRead(interrupt_pin);
      }
      
          
    delayMicroseconds(1);// 3ns  time, the ALU needs for calculation
         
    Init_byte(); 
    Prep_To_Read();
    Choose_Address(0,0,0,0);
    Serial.println("Reading result register 0 strobe 1");
    digitalWrite(To_Read, LOW); //low active 
    Read_From_Register();
    Finish_Read();
    Reset_Address();
    nk0 = (To_integer()& 0x00003FC0)>>6;
   // Print_data();
    //Init_byte();  
    
    
    Prep_To_Read();
    Choose_Address(0,0,0,0);
    Serial.println("Reading result register 0 strobe 2");
    digitalWrite(To_Read, LOW); //low active 
    Read_From_Register();
    Finish_Read();
    Reset_Address();
    nk1 = (To_integer()& 0x00003FC0)>>6;
   // Print_data();
    //Init_byte();  
       
    Prep_To_Read();
    Choose_Address(0,0,0,0);
    Serial.println("Reading result register 0 strobe 3");
    digitalWrite(To_Read, LOW); //low active 
    Read_From_Register();
    Finish_Read();
    Reset_Address();
    vk0 = (To_integer()& 0x00003FC0)>>6;
    //Print_data();
    //Init_byte();  
    
    
    Prep_To_Read();
    Choose_Address(0,0,0,0);
    Serial.println("Reading result register 0 strobe 4");
    digitalWrite(To_Read, LOW); //low active 
    Read_From_Register();
    Finish_Read();
    Reset_Address();
    vk1 = (To_integer()& 0x00003FC0)>>6;
    //Init_byte();  

    
    Serial.println(nk0);
    Serial.println(nk1);
    Serial.println(vk0);
    Serial.println(vk1);
 

/*    vk1 = vk1 * 256;
    vk1 = vk1 | vk0;
    
    Serial.print("vk1 = ");
    Serial.println(vk1);
    nk1 = nk1 * 256;
    nk1 = nk1 | nk0;
    Serial.print("nk1 = ");
    Serial.println( nk1);
  
    
    final_result = 0.0; 
    final_result = 500.0 * ((float)(vk1) + (((float)(nk1)) / 65536.0));
    float positions = final_result * 0.005570866;
    Serial.println("-----------------------------------------------");
    Serial.println(final_result);
    Serial.println("position in inch");
    Serial.println(positions);
    Serial.println("position in cm");
    Serial.println(positions * 2.54);
    //Serial.println("result = %6.3fns\n",final_result); 
    Serial.println("-----------------------------------------------"); 
*/

    // make the data bus as output
    pinMode(data_pin_0,OUTPUT);
    pinMode(data_pin_1,OUTPUT);
    pinMode(data_pin_2,OUTPUT);
    pinMode(data_pin_3,OUTPUT);
    pinMode(data_pin_4,OUTPUT);
    pinMode(data_pin_5,OUTPUT);
    pinMode(data_pin_6,OUTPUT);
    pinMode(data_pin_7,OUTPUT);
    delayMicroseconds(1);  

        // REG 11 Init the ALU, BigALU and auto noise unit
    Prep_To_Write();
    Choose_Address(1,0,1,1);
    Serial.println("setting REG 11");
    Write_To_Register(0,0,0,0,0,1,1,1);
    digitalWrite(To_Write, LOW); // write is activated here
    delayMicroseconds(1);
    Finish_Write();
    Reset_Address_data();

    valid =0;
    
 
  }
 
}




