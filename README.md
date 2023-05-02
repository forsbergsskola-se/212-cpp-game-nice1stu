Bob the Intergalactic Bog Cleaner  
  
Play WebGL version at  
https://developer0204.github.io/WebAssembly/  
(Note: The porting of the game to WebGL was not done by me but my much more talented friend Daniel. He also added the music when he ported the game to this webversion as I had run out of time and is NOT part of the assignment that I submitted, so do not give me marks for doing this, I don't want to claim credit for someting I didn't do)    
  
  Bob is a sanitation technician aboard a run down spaceship travelling the galaxy.  
  He has the inglorious job of having to maintain the cleanliness of the toilets onboard the ship.  
  It is challenging at the best of times, but when the ship loses artificial gravity, the sh#t really hits the fan. 
  Literally, the effluent from the bowels of the ship comes gushing out of the toilets,  
  and it's Bob's job as sanitation technician to ensure they don't overflow.  
  Armed with his trusty plunger and his lightning fast reflexes, he must abate the flow by plunging back the  
  excrement that threatens to overflow the toilets in zero G.  
  Can Bob succeed, will he literally drown in a floating sea of sh#t?  
  
This is a Whack-A-Mole like game where the player controls Bob, our titular character, as he runs from toilet to toilet,  
plunging back the pooh that threatens to overflow.

Coded in C++, graphics using SDL.  

ScreenShots:  
Start Screen - Pres [SPACE] to start game.
![Screenshot 2023-04-16 061811](https://user-images.githubusercontent.com/112468923/232266281-86d7b077-0ffa-4a18-ad72-c3501e08ffec.png)
  
Game Screen - Random toilets start overflowing.  
![BobToiletsOverflowing720p](https://user-images.githubusercontent.com/112468923/231916757-aa6e4aac-2226-470d-975e-22a584be138f.png)  
  
Fighting the overflow !  
![BobPlunging720p](https://user-images.githubusercontent.com/112468923/231916797-55e6b067-6263-4df1-86ec-a81fc7f74f59.png)  
  
It's getting critical !  
![BobMissionCritical720p](https://user-images.githubusercontent.com/112468923/231916810-eb992628-acec-42ff-a7af-08d650547f9f.png)  
  
Game Over  
![BobGameOver720p](https://user-images.githubusercontent.com/112468923/231916821-1c14fb71-b017-4172-83bc-841becf279d1.png)  
  
A look at the project folder structure  
![BobFolderStructure720p](https://user-images.githubusercontent.com/112468923/231916833-d8754b45-2af4-4396-b83a-cff58f78b1ad.png)

Link to YouTube video  
https://youtu.be/54h2x-Sj1m4  

Technical Note:  
Design Pattern
This game implements a SINGLETON Design pattern over several classes to ensure no more then one instance of that class occurs while providing access to that instance. In this case the Singleton pattern is created as Template class which other classes inherit from, guaranteeing no more then 1 instance of that class occurs in the game:  
InputHandler, RenderDevice, TextureHandler, Application are all Singletons inheriting from the Singleton Class.  

Function Pointer  
FUNCTION POINTER point to function rather then data.  
m_pPlumbingStartCallback points to a function that and passes in "m_CurrentTriggerID" as an argument which will set determine if the player is already plumbing or not.  

RunTime Polymorphism  
This is used several times in the code to allow how a method is implemented to be determined during run time. In these cases I have allowed for OVERLOADING of several methods depending on the arguments passed in during run time.  
void			RenderCopy					(CTexture* pTexture);  
void			RenderCopy					(CTexture* pTexture, const CVector2D& rPosition);  

static uint32_t	RandomUint	(void);  
static uint32_t	RandomUint	(const uint32_t Min, const uint32_t Max);  

CVector2D				(void);  
CVector2D				(const float X, const float Y);  
