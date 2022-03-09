# Disaster Squad 
Disaster Squad is a top-down real-time strategy game designed for players aged 12+.\
Our theme for this project was the United Nations Sustainable Development goal #13:
> **"Take urgent action to combat climate change and its impacts"**

## 
This game was developed by [Conor](https://github.com/Crexenic), [Dominik](https://github.com/DominikGodlewski) and [Merri](https://github.com/merri1) as part of our third year Project\
and Group Dynamics module at Limerick Institute of Technology. We were tasked with\
creating a game from scratch using C++ and the Simple and Fast Multimedia Library - [SFML](https://www.sfml-dev.org/download/sfml/2.5.1/).

#### For more information please visit the [Disaster Squad website](https://merri1.github.io/).

&nbsp;


## Installation
### Windows 10
- Tested and confirmed working on Windows 10.
1. Download and extract the latest Win10 zip file from the [releases page](https://github.com/Merri1/DisasterSquad/releases).
2. Open the **DisasterSquad\binary** folder.
3. Double click **Disaster_Squad.exe** to run game.  
&nbsp; 

### Linux
- Linux can run both the native Linux binary **and** the Windows executable.
#### Linux Native
1. Install [SFML v2.5.1](https://www.sfml-dev.org/download/sfml/2.5.1/) libraries, the command for this will depend on your distribution.

Operating System | Command
| :---------- | :----------
Ubuntu / Debian | ```sudo apt install libsfml-dev```
Arch Linux      | ```sudo pacman -S sfml```

2. Download and extract the latest linux zip file from the [releases page](https://github.com/Merri1/DisasterSquad/releases).
3. Navigate to **DisasterSquad/binary** folder and open the Terminal here.
4. Run the command ```./disaster-squad```

- Tested and confirmed working on Ubuntu 20.04 LTS and Arch Linux.
- More Linux SFML packages are [listed here](https://index.ros.org/d/sfml-dev/) if you would like to test a different distro.

#### Linux Steam Proton
1. Download and extract the latest Win10 zip file from the [releases page](https://github.com/Merri1/DisasterSquad/releases).
2. Follow [these short steps](https://help.steampowered.com/en/faqs/view/4B8B-9697-2338-40EC) to add **Disaster_Squad.exe** to your Steam Library.
3. Select Disaster Squad in your Steam Library and click the cog icon followed by 'Properties'.
4. Under compatibility enable Steam Play compatibility tool and from the drop down menu select\
```Proton 5.13```, ```Proton 6.3``` or ```Proton 7.0```.
6. You can now play the game from your Steam Library.
