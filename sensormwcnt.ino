/* 
   Monitoring the direction of strain carbon nano tubes based strain sensor 
   by arduino microcontroller

   Arduino A0 to A3 = input from MWCNT sensor
   Arduino D11,D10,D9,D4 = output to LED driver ICs


   Created : 04/2015
   Modified : 11/2015
   By : Mohan Gopal Tripathi


*/



//define variables
//mapped_value_downed variables -- sensor dependent
float maximum_value = 0 ; // enter maximum_value = maximum sensor reading
float minimum_value = 1023 ; // enter minimum_value = minimum sensor reading
//define variables
float start_value1 = 0 ; // sensor value at normal position
float start_value2 = 0 ;
float start_value3 = 0 ;
float start_value4 = 0 ;

float smooth_value1 = 0 ; // smoothed value will stored in this variable
float smooth_value2 = 0 ;
float smooth_value3 = 0 ;
float smooth_value4 = 0 ;
int thresold_1 = 30;      // depends on the strain sensor
int thresold_2 = 40;
int thresold_3 = 20;
int thresold_4 = 20;

void setup() {

Serial.begin(9600);                            // initialize serial communications at 9600 bps:
pinMode(9,OUTPUT);                             // for DOWN motion
pinMode(10,OUTPUT);                            // for UP motion
pinMode(11,OUTPUT);                            // for right motion
pinMode(12,OUTPUT);                            // for left motion

float temp1=0,temp2=0,temp3=0,temp4=0;
float sum1 = 0,sum2 = 0,sum3 = 0,sum4 = 0;


               // ---------------read the analog initial smooth value------------------- //


for(int i=0;i<10;i++)
{
temp1 = analogRead(A0);
sum1 = sum1 + temp1; 
temp2 = analogRead(A1);
sum2 = sum2 + temp2; 
temp3 = analogRead(A2);
sum3 = sum3 + temp3;
temp4 = analogRead(A3);
sum4 = sum4 + temp4; 
}
start_value1=sum1/10; // taking initial value for start for noram position without strain
start_value2=sum2/10;
start_value3=sum3/10;
start_value4=sum4/10;
}

void smoothing()
{ 
float temp1=0,temp2=0,temp3=0,temp4=0;
float sum1 = 0,sum2 = 0,sum3 = 0,sum4 = 0;


                //--------------------read the analog input value for smoothing----------------------//


                
for(int i=0;i<10;i++)
{
temp1 = analogRead(A0);
sum1 = sum1 + temp1; 
temp2 = analogRead(A1);
sum2 = sum2 + temp2; 
temp3 = analogRead(A2);
sum3 = sum3 + temp3;
temp4 = analogRead(A3);
sum4 = sum4 + temp4; 
}
smooth_value1 =sum1/10;
smooth_value2 =sum2/10;
smooth_value3 =sum3/10;
smooth_value4 =sum4/10;
}


void loop() {
                                                
smoothing();                                  // calling function smoothing to get smooth_value
float current_value1 = smooth_value1;         // current_value will get difference with normal position or start_value
float current_value2 = smooth_value2;
float current_value3 = smooth_value3;
float current_value4 = smooth_value4;

float mapped_value_1 = 0 ;                    // for mapping the range of differnce
float mapped_value_2 = 0 ; 
float mapped_value_3 = 0 ;
float mapped_value_4 = 0 ;


             //-------------------self calibration for maximum & minimum value------------//
             
  
  if(current_value1 > maximum_value)// if we have a larger value than the maximum value, maximum value will updated
    { maximum_value = current_value1;}
  else if(current_value1 < minimum_value) // if we have a smaller value than the minimum value, minimum value will updated
    { minimum_value = current_value1;}
  if(current_value2 > maximum_value)
    { maximum_value = current_value2;}
  else if(current_value2 < minimum_value) // if we have a smaller value than the minimum value, minimum
    { minimum_value = current_value2;}
  if(current_value3 > maximum_value)
    { maximum_value = current_value3;}
  else if(current_value3 < minimum_value) // if we have a smaller value than the minimum value, minimum
    { minimum_value = current_value3;}  
  if(current_value4 > maximum_value) 
    { maximum_value = current_value4;}
  else if(current_value4 < minimum_value) // if we have a smaller value than the minimum value, minimum
    { minimum_value = current_value4;}  
    
//-------------------condition for 1st direction---------------------//


if(current_value1 - start_value1 > thresold_1)              //set threshold value for down leds
{mapped_value_1=map(current_value1-start_value1-thresold_1,minimum_value,maximum_value-start_value1-thresold_1,0,255);} // mapping difference to 0-255

//--------------------condition for 2nd direction-----------------------//


if(current_value2 -start_value2 > thresold_2) //set thresold value for up leds
{mapped_value_2=map(current_value2-start_value2-thresold_2,minimum_value,maximum_value-start_value2-thresold_2,0,255);}


//-------------------condition for 3rd direction---------------------//


if(current_value3 - start_value3 > thresold_3) //set threshold value for right leds
{mapped_value_3=map(current_value3-start_value3-thresold_3,minimum_value,maximum_value-start_value3-thresold_3,0,255);} // mapping difference to 0-255

//--------------------condition for 4th direction-----------------------//


if(current_value3 - start_value3>thresold_4) //set thresold value for left leds

{mapped_value_4=map(current_value4-start_value4-thresold_4,minimum_value,maximum_value-start_value4-thresold_4,0,255);}

if(mapped_value_1 > mapped_value_2 && mapped_value_1 > mapped_value_3 && mapped_value_1 > mapped_value_4 )
{
analogWrite(10,0);
analogWrite(11,0);
analogWrite(12,0);
analogWrite(9,mapped_value_1);}
else if (mapped_value_2 > mapped_value_1 && mapped_value_2 > mapped_value_3 && mapped_value_2 > mapped_value_4)
{
analogWrite(9,0);
analogWrite(11,0);
analogWrite(12,0);
analogWrite(10,mapped_value_2);}
else if (mapped_value_3 > mapped_value_1 && mapped_value_3 > mapped_value_2 && mapped_value_3 > mapped_value_4)
{
analogWrite(9,0);
analogWrite(10,0);
analogWrite(12,0);
analogWrite(11,mapped_value_3);}
else if (mapped_value_4 > mapped_value_1 && mapped_value_4 > mapped_value_2 && mapped_value_4 > mapped_value_3)
{
analogWrite(9,0);
analogWrite(10,0); 
analogWrite(11,0);
analogWrite(12,mapped_value_4);}

else
{
analogWrite(9,0);// no LED will glow
analogWrite(10,0); // no LED will glow
analogWrite(11,0);
analogWrite(12,0);
}
Serial.print("\n sv1= ");
Serial.print(start_value1);
Serial.print("\t down_motion=");
Serial.print(mapped_value_1);
Serial.print("\t sv2=");
Serial.print(start_value2);
Serial.print("\t up_motion=");
Serial.print(mapped_value_2);
Serial.print("\t sv3=");
Serial.print(start_value3);
Serial.print("\t right_motion=");
Serial.print(mapped_value_3);
Serial.print("\t sv4=");
Serial.print(start_value4);
Serial.print("\t left_motion=");
Serial.print(mapped_value_4);
delay(1000);

}
