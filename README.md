# **Swerve Drive**
3D printed coaxial swerve drive! 

Demo Video: https://www.youtube.com/watch?v=bPC4PA_9ZH0
<img width="4000" height="3000" alt="thumbnail red bg" src="https://github.com/user-attachments/assets/423156e4-7c1d-4fa4-af0f-83c531c2e14a" />

## Build
<img width="713" height="494" alt="image" src="https://github.com/user-attachments/assets/835d5477-3cfa-43c1-b009-cf7b16bdfe60" />

Bill of Materials: https://docs.google.com/spreadsheets/d/1JbDlUu6udkqM81WZ7hx05DRgLwFBebW2xzIRILkRvEQ/edit?gid=0#gid=0

CAD Link: https://cad.onshape.com/documents/d429383bcee8295a505cbf1f/w/4cb76ce82d333762f6fc2bfa/e/bd259976b7240cf77be97213?renderMode=0&uiState=6a483284ef38c7be8f930ffd

It should be relatively easy to design your own frame rails to change the overall length/width of the drive base if you choose.

### **Printing**
The only thing that actually needs supports is the drive fork that has the bevel gear slot, since most printers should be able to do the other overhangs. Printed on my A1M just fine with standard settings.

Note: I did not print out the bellypan, I cut it out by hand from some high density cardboard I had lying around. I reccomend this as well since its easier to make holes to mount things and this part is pretty big.

### **Assembly**
Everything goes together exactly how it is in the CAD. Make sure to hot glue in the magnets into the encoder shaft.
As previously mentioned, I just placed my electronics and drilled mounting holes for them into the bellypan.

To secure the encoder column and thhe magnet, use hot glue. It is critical for the magnet to be secured properly for the encoder to track position correctly!

<img width="687" height="583" alt="image" src="https://github.com/user-attachments/assets/1edf287b-3155-4649-ad7e-a5341ab9d726" />


To increase traction on the wheels I just put some electrical tape around them.

<img width="4000" height="3000" alt="20260619_204038" src="https://github.com/user-attachments/assets/7fd05a8a-3d9e-4832-8f21-b375d1e3964c" />


## **Wiring**
<img width="1536" height="960" alt="drive motor wiring" src="https://github.com/user-attachments/assets/b3e07417-5668-42a5-b8eb-805b4a8da819" />
<img width="1536" height="960" alt="swerverivewiringiagram" src="https://github.com/user-attachments/assets/3a468f0f-2794-4419-9c5b-d880c90cd570" />

IMPORTANT: Adafruit motor shield by default uses 5 volt logic, but nucelos use 3.3 volt outputs so you must cut the trace and bridge the 3.3 volt logic pad as seen in the wiring diagram
Also important: The only thing that runs on 5 volts is the flysky reciever, everything else uses 3.3 volts (aside from the motors obviously which use 12 volts)

For the 12 volt power distribution, I just used some wagos to split up the power to all the drive motors and the adafruit motor shield in parallel.

After soldering the wires to the N20 motors, they have a tendency to break off, so I hot glued the connection. I also hot glued the encoder cables because dupont connectors aren't that great and even a slightly loose connection can throw the encoder readings off.

### **Written List of Pins:**
**Note:** Pins can change as wished by the user, but every input pin for an individual simpleFOC module (IN1, IN2, IN3) must be on the on the same hardware timer on the nucleo
#### FR Module: 
  EN- PA12
  
  IN1- PA11
  
  IN2- PA9
  
  IN3- PA10
  
  Encoder Out- PC1


#### FL Module: 
  EN- PB5
  
  IN1- PB6
  
  IN2- PB8
  
  IN3- PB9
  
  Encoder Out- PA4


#### BR Module: 
  EN- PC5
  
  IN1- PC6
  
  IN2- PC7
  
  IN3- PC8
  
  Encoder Out- PC2


#### BL Module: 
  EN- PC4
  
  IN1- PA0
  
  IN2- PA1
  
  IN3- PA15
  
  Encoder Out- PC0


## **Code**
Uploading is pretty straightforward, make sure you have the official STM32Cores and have set up the Arduino IDE for STM32 upload.

### **Libraries to Download**
- SimpleFOC (**Important: At the time of writing this, only the 2.3.5 version of the library works, the latest version, 2.4.0, does not work**)
- PID by Brett Beauregard
- Adafruit Motor Shield V2 Library
- MPU6050_Light by rfetick
- IBusBM by Bart Mellink

## Credits:
### Swerve Kinematics:
https://www.chiefdelphi.com/t/paper-4-wheel-independent-drive-independent-steering-swerve/107383
https://www.chiefdelphi.com/uploads/default/original/3X/8/c/8c0451987d09519712780ce18ce6755c21a0acc0.pdf

### AI Usage Declaration:
Gemini was used only for generating pinouts for the simpleFOCs and for minor debugging. All code was written by hand with inspiration from the aforementioned sources.
