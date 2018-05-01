import cv2
import numpy as np
import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(16,GPIO.OUT)
GPIO.setup(20,GPIO.OUT)
GPIO.setup(21,GPIO.OUT)


c=0
c1=0
c2=0
c3=0
cap= cv2.VideoCapture(0)
##while(cap.isOpened()):
##    ret,frame=cap.read();
##    if (ret):
##        break
##    else:
##        cap.release()
##        cap=cv2.VideoCapture(0)
##        
while(cap.isOpened()):
    ret,frame=cap.read()
    if ret:
        hsv=cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)
    
        #print hsv[0:2,0:2] 
        lower_red=np.array([150,150,80])
        upper_red=np.array([180,255,155])
    
        lower_blue=np.array([50,40,130])
        upper_blue=np.array([150,75,160])
    
        lower_golden=np.array([12,30,150])
        upper_golden=np.array([25,75,250])
    
        mask1=cv2.inRange(hsv,lower_blue,upper_blue)
        res1=cv2.bitwise_and(frame,frame,mask=mask1)

        mask=cv2.inRange(hsv,lower_golden,upper_golden)
        res=cv2.bitwise_and(frame,frame,mask=mask)

        mask2=cv2.inRange(hsv,lower_red,upper_red)
        res2=cv2.bitwise_and(frame,frame,mask=mask2)
    
        kernel2=np.ones((5,5),np.uint8)
        erosion2=cv2.erode(mask2,kernel2,1)
        dilation2=cv2.dilate(mask2,kernel2,1)

        kernel1=np.ones((15,15),np.float32)/255
        smoothed=cv2.filter2D(res1,-1,kernel1)
    
        erosion1=cv2.erode(mask1,kernel1,1)
        dilation1=cv2.dilate(mask1,kernel1,1)
        

        kernel=np.ones((5,5),np.uint8)
        erosion=cv2.erode(mask,kernel,1)
        dilation=cv2.dilate(mask,kernel,1)

        mask1 = np.asarray(mask1)
        mask = np.asarray(mask)
        mask2 = np.asarray(mask2)
     
        p1=np.count_nonzero(mask1==255)
        p2=np.count_nonzero(mask2==255)
        p3=np.count_nonzero(mask==255)
   
        if(p1>3000):
            print "blue"
            c=c+1
        
        elif(p2>3000):
            print "red"
            c1=c1+1
        elif(p3>3000):
            print "golden"
            c2=c2+1
        else:
            print "no color"
            c3=c3+1
        if c==10:
            GPIO.output(16,GPIO.HIGH)
            GPIO.output(20,GPIO.LOW)
            GPIO.output(21,GPIO.LOW)
            c=0
        elif c1==10:
            GPIO.output(16,GPIO.LOW)
            GPIO.output(20,GPIO.HIGH)
            GPIO.output(21,GPIO.LOW)
            c1=0
        elif c2==10:
            GPIO.output(16,GPIO.LOW)
            GPIO.output(20,GPIO.LOW)
            GPIO.output(21,GPIO.HIGH)
            c2=0
        else :
            GPIO.output(16,GPIO.LOW)
            GPIO.output(20,GPIO.LOW)
            GPIO.output(21,GPIO.LOW)
            c3=0
        cv2.imshow('frame',frame) 
        p1=0
        p2=0
        p3=0
        k=cv2.waitKey(0) & 0xFF
        if k==27:
            break
    else:
        print ret

cap.release()
cv2.destroyAllWindows()
