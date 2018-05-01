/*  manual bot robocon 2018 
 *  microntroller-> arduino meaga 2560
 *   movements  base ->done
 *   rack piston -> done 
 *  stepper arm -> not done
 *  abbrivations mfl-> motor front left
 *               mfr->motor front right
 *               mrl->motor rear left 
 *               mrr->motor rear right 
 *               p ->positive
 *               n->negetive
 *               e-> enable
 *               nu1->pneumatic
 *               
 */

#include <SoftwareSerial.h>
#include <Cytron_PS2Shield.h>

Cytron_PS2Shield ps2(2,3);  //rx and tx 
//.............................motor.............................
#define mfl_p  1         
#define mfl_n   2
#define mfl_e  3
#define mfr_p  4 
#define mfr_n  5
#define mfr_e  6
#define  mrl_p  7
#define  mrl_n  8
#define  mrl_e  9
#define  mrr_p  10
#define  mrr_n   11
#define  mrr_e  12
//.............................. piston ..................................
#define nu1  13 

//........................................................................
int arr[]={mfl_p, mfl_n, mfl_e, mfr_p, mfr_n, mfr_e, mrl_p, mrl_n, mrl_e, mrr_p, mrr_n, mrr_e,nu1}; // make an  arry of all
void setup() 
{
int i=0;
for(i=0;i<13;i++)
{
  pinMode(arr[i],OUTPUT);  // makke all pin output  for motors
}
ps2.begin(9600);  // begin ps2
Serial.begin(9600); // begin serail communicarion 

}
//.................................main body........................................
void loop()
   {   
    // 123 is center reading of left y axis  132 is mid value of x axis
   if((ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS)<120)&&((ps2.readButton(PS2_JOYSTICK_LEFT_X_AXIS)>120)&&(ps2.readButton(PS2_JOYSTICK_LEFT_X_AXIS)<140)))   
       {
      while((ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS)<120)&&((ps2.readButton(PS2_JOYSTICK_LEFT_X_AXIS)>120)&&(ps2.readButton(PS2_JOYSTICK_LEFT_X_AXIS)<140)))  
        {
          motor_speed(map(ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS),0,123,255,0)); // check  this out or use subrataction logic
          motor_control(1,1,1,1);  //forward tested
        }
       }
     else if((ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS)>130)&&((ps2.readButton(PS2_JOYSTICK_LEFT_X_AXIS)>120)&&(ps2.readButton(PS2_JOYSTICK_LEFT_X_AXIS)<140)))   
       {
      while((ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS)>130)&&((ps2.readButton(PS2_JOYSTICK_LEFT_X_AXIS)>120)&&(ps2.readButton(PS2_JOYSTICK_LEFT_X_AXIS)<140)))  
        {
          motor_speed(map(ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS),123,255,0,255)); 
          motor_control(2,2,2,2);  //back tested
        }
      }
      
     else if((ps2.readButton(PS2_JOYSTICK_LEFT_X_AXIS)<128)&&((ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS)>118)&&(ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS)<140)))   
       {
      while((ps2.readButton(PS2_JOYSTICK_LEFT_X_AXIS)<128)&&((ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS)>118)&&(ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS)<140)))  
        {
          motor_speed(map(ps2.readButton(PS2_JOYSTICK_LEFT_X_AXIS),0,132,255,0)); // check  this out or use subrataction logic
          motor_control(2,1,1,2);  //left tested
        }
      }            
   else if((ps2.readButton(PS2_JOYSTICK_LEFT_X_AXIS)>140)&&((ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS)>120)&&(ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS)<140)))   
       {
      while((ps2.readButton(PS2_JOYSTICK_LEFT_X_AXIS)>140)&&((ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS)>120)&&(ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS)<140)))  
        {
          motor_speed(map(ps2.readButton(PS2_JOYSTICK_LEFT_X_AXIS),132,255,0,255)); 
          motor_control(1,2,2,1);  //right tested
        }
      }
      else if(ps2.readButton(PS2_JOYSTICK_LEFT_X_AXIS)>200 && ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS<10) )
        {
         while( ps2.readButton(PS2_JOYSTICK_LEFT_X_AXIS)>200 && ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS<10))
               {
                motor_speed(127); // send accordiing to ur wish  
                motor_control(1,0,0,1); // 45 degree  tested 
               }
        }   
         
         else if(ps2.readButton(PS2_JOYSTICK_LEFT_X_AXIS) <10 && ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS<10) )
        {
         while( ps2.readButton(PS2_JOYSTICK_LEFT_X_AXIS) <10 && ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS <10))
               {
                motor_speed(127); // send accordiing to ur wish  
                motor_control(0,1,1,0); // 135 degree  tested 
               }
        }    
          else if(ps2.readButton(PS2_JOYSTICK_LEFT_X_AXIS) <20 && ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS>200) )
               {
         while( ps2.readButton(PS2_JOYSTICK_LEFT_X_AXIS) <20 && ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS >200))
               {
                motor_speed(127); // send accordiing to ur wish  
                motor_control(2,0,0,2); // 225 degree  tested 
               }
        }    
        else if(ps2.readButton(PS2_JOYSTICK_LEFT_X_AXIS) >200 && ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS>200) )
               {
         while( ps2.readButton(PS2_JOYSTICK_LEFT_X_AXIS) >200 && ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS >200))
               {
                motor_speed(127); // send accordiing to ur wish  
                motor_control(0,2,2,0); // 315 degree  tested 
               }
        }
        else if(ps2.readButton(PS2_LEFT_1)==0)  // rotate left
            {
              motor_speed(127);
              motor_control(2,1,2,1);
              }
              else if(ps2.readButton(PS2_RIGHT_1)==0) //rotate right
            {
              motor_speed(127);
              motor_control(1,2,1,2);
              }   
        else if(ps2.readButton(PS2_UP)==0) // rack piston up  assumed : realy are driving them (active low relay module)
       {
        digitalWrite(nu1,0);
       } 
       else if(ps2.readButton(PS2_DOWN)==0) // rack piston down
       {
        digitalWrite(nu1,1);
        
       }      
 }    
//.....................................motor control.................
void motor_control(int mfl,int mfr,int mrl,int mrr)     
  {  
     switch(mfl)   // motor front left
      {
       case 0:  digitalWrite(mfl_p,0);
                digitalWrite(mfl_n,0);
          break;
        case 1:
               digitalWrite(mfl_p,1);
                digitalWrite(mfl_n,0);
          break; 
       case 2:
                digitalWrite(mfl_p,0);
                digitalWrite(mfl_n,1);
          break;    
       default: break;   
      }
     switch(mfr)   // motor front right
      {
       case 0: digitalWrite(mfr_p,0);
                digitalWrite(mfr_n,0);
          break;
        case 1:digitalWrite(mfr_p,1);
                digitalWrite(mfr_n,0);
          break; 
       case 2: digitalWrite(mfr_p,0);
                digitalWrite(mfr_n,1);
          break;    
       default: break;   
      } 
     switch(mrl)   // motor rare left
      {
       case 0:  digitalWrite(mrl_p,0);
                digitalWrite(mrl_n,0);
          break;
        case 1: digitalWrite(mrl_p,1);
                digitalWrite(mrl_n,0);
          break; 
       case 2:  digitalWrite(mrl_p,0);
                digitalWrite(mrl_n,1);
          break;    
       default: break;   
      }  
     switch(mrr)   // motor rare right
     {
       case 0:  digitalWrite(mrr_p,0);
                digitalWrite(mrr_n,0);
          break;
        case 1:  digitalWrite(mrr_p,1);
                digitalWrite(mrr_n,0);
          break; 
       case 2: digitalWrite(mrr_p,0);
                digitalWrite(mrr_n,1);
          break;    
       default: break;   
      }  
  }
//.......................................................................
//...................................motor speed.........................
  void motor_speed(int x)
    {
    analogWrite(mfl_e,x);
    analogWrite(mfr_e,x);
    analogWrite(mrl_e,x);
    analogWrite(mrr_e,x);
    }
//....................................................................


  
