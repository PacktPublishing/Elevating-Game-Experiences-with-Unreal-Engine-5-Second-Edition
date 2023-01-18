


# Elevating Game Experiences with Unreal Engine 5 - Second Edition

<a href="https://www.packtpub.com/product/elevating-game-experiences-with-unreal-engine-5/9781803239866?utm_source=github&utm_medium=repository&utm_campaign=9781803239866"><img src="https://static.packt-cdn.com/products/9781803239866/cover/smaller" alt="Elevating Game Experiences with Unreal Engine 5 - Second Edition" height="256px" align="right"></a>

This is the code repository for [Elevating Game Experiences with Unreal Engine 5 - Second Edition](https://www.packtpub.com/product/elevating-game-experiences-with-unreal-engine-5/9781803239866?utm_source=github&utm_medium=repository&utm_campaign=9781803239866), published by Packt.

**Bring your game ideas to life using the new Unreal Engine 5 and C++**

## What is this book about?
Immerse yourself in the Unreal game projects with this book, written by four highly experienced industry professionals with many years of combined experience with Unreal Engine. Elevating Game Experiences with Unreal Engine 5 will walk you through the latest version of Unreal Engine by helping you get hands-on with the game creation projects.

This book covers the following exciting features: 
* Create a fully functional third-person character and enemies
* Implement navigation with keyboard, mouse, and gamepad
* Program logic and game mechanics with collision and particle effects
* Explore AI for games with Blackboards and behavior trees
* Build character animations with animation blueprints and montages

If you feel this book is for you, get your [copy](https://www.amazon.com/dp/1803239867) today!

<a href="https://www.packtpub.com/?utm_source=github&utm_medium=banner&utm_campaign=GitHubBanner"><img src="https://raw.githubusercontent.com/PacktPublishing/GitHub/master/GitHub.png" 
alt="https://www.packtpub.com/" border="5" /></a>


## Instructions and Navigations
All of the code is organized into folders. For example, Chapter03.

The code will look like the following:
```
// Spring arm component which will act as a placeholder for the player camera. This component is recommended to be used as it automatically controls how the
//camera handles situations where it becomes obstructed by geometry inside the level, etc
UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MyTPS_Cam, meta = (AllowPrivateAccess = "true"))
class USpringArmComponent* CameraBoom;
// Follow camera
UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MyTPS_Cam, meta = (AllowPrivateAccess = "true"))
class UCameraComponent* FollowCamera;
```

**Following is what you need for this book:**

This book is for game developers looking to get started with using Unreal Engine 5 for their game development projects. Anyone who has used Unreal Engine before and wants to consolidate, improve, and apply their skills will find this book useful. To better grasp the concepts explained in this book, prior knowledge of C++ basics such as variables, functions, classes, polymorphism, and pointers is required. For full compatibility with the IDE used in this book, a Windows system is recommended.

With the following software and hardware list you can run all code files present in the book (Chapter 1-18).

### Software and Hardware List

| Chapter  | Software required                   | OS required                        |
| -------- | ------------------------------------| -----------------------------------|
| 1-18     | Unreal Engine 5                     | Windows, Mac OS, and Linux       |


We also provide a PDF file that has color images of the screenshots/diagrams used in this book. [Click here to download it](https://packt.link/iAmVj).

<hr>

* You can download videos for Chapters 1, 3, 4-9, and 16-18 which will help to understand the chapters better. [Click here to download it](https://packt.link/1GnAS).
* You can download the Activities Solution file from [here](https://packt.link/6y0Pa)


### Related products <Other books you may enjoy>
* Unreal Engine 5 Character Creation, Animation, and Cinematics [[Packt]](https://www.packtpub.com/product/unreal-engine-5-character-creation-animation-and-cinematics/9781801812443?_ga=2.218140255.738679754.1661260461-1157268863.1584421665&utm_source=github&utm_medium=repository&utm_campaign=9781801812443) [[Amazon]](https://www.amazon.com/dp/1801812446)

* Blueprints Visual Scripting for Unreal Engine 5 - Third Edition [[Packt]](https://www.packtpub.com/product/blueprints-visual-scripting-for-unreal-engine-5/9781801811583?_ga=2.104787654.738679754.1661260461-1157268863.1584421665&utm_source=github&utm_medium=repository&utm_campaign=9781801811583) [[Amazon]](https://www.amazon.com/dp/180181158X)

## Get to Know the Authors
**Gonçalo Marques**
has been an active gamer since the age of 6. He has been using Unreal Engine since 2016 and has done freelance and consulting work using the engine. Gonçalo also released a free and open source plugin called UI Navigation, which has garnered an extremely positive reception with over 100,000 downloads and is still receiving frequent updates and fixes. Thanks to the development of this plugin, he became an Epic MegaGrant recipient. He is now working at Funcom ZPX, a game studio in Lisbon that has contributed to games such as Conan Exiles, Mutant Year Zero, and Moons of Madness. Gonçalo is currently working on a new Funcom game in the Dune universe.

**Devin Sherry**
is the principal technical designer at People Can Fly in Poland, having worked on Outriders and Outriders: Worldslayer using Unreal Engine 4. Before that, he worked on Aquanox: Deep Descent as a technical designer at the Digital Arrow studio in Serbia. With a decade of experience ranging from the Unreal Developers’ Kit to the newly released Unreal Engine 5, Devin is passionate about creating memorable experiences for players and bringing game mechanics to life.

**David Pereira**
started making games in 1998 when he learned how to use Clickteam’s The Games Factory. He graduated in computer science from FCT-UNL, where he learned about C++, OpenGL, and DirectX, which allowed him to create more complex games. After working in IT consulting for a few years, he joined Miniclip in Portugal where he worked on popular mobile games such as 8 Ball Pool, Gravity Guy 1 and Gravity Guy 2, Extreme Skater, iStunt2, Hambo, and many others. Since then, he has been the lead developer for MPC in the John Lewis Christmas VR Experience, worked on an earlier version of Mortal Shell, and did volunteer work teaching people with Asperger’s how to make games with Unreal Engine 4. Today, he’s working on his own game, a soon-to-be-announced first-person action RPG.

**Hammad Fozi**
comes from a gaming background and has been extensively working on Unreal Engine since 2017. He has been part of some very successful AAA projects such as Virtua FanCave (and Metaverse), Unnamed AAA Sci-Fi DJ Experience, Heroes and Generals, and Creed: Rise to Glory VR. Hammad has worked with teams who have had experience working at Ubisoft, Warner Bros. Games, 2K Games, and more! He has successfully helped teams consisting of 10–30 people to scale to 150+ in size over his very short yet impressive career. Hammad currently works as a senior C++ game developer and has extensive experience in working with VR and augmented reality, PC/PS5/Xbox/Android/iOS/macOS game development, and Web3/Metaverse/NFT systems (within Unreal Engine)


## Other books by the authors
* [Game Development Projects with Unreal Engine](https://www.packtpub.com/product/game-development-projects-with-unreal-engine/9781800209220?utm_source=github&utm_medium=repository&utm_campaign=9781800209220)
### Download a free PDF

 <i>If you have already purchased a print or Kindle version of this book, you can get a DRM-free PDF version at no cost.<br>Simply click on the link to claim your free PDF.</i>
<p align="center"> <a href="https://packt.link/free-ebook/9781803239866">https://packt.link/free-ebook/9781803239866 </a> </p>