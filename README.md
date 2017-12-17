# 3dEngine
3D Engine made by Roger Busquets Duran and Sergi Parra Ramirez for the 3D engines subject in the videogame degree at CITM.

Link to the Github Repository ![https://github.com/rogerbusquets97/3D-Engine](https://github.com/rogerbusquets97/3D-Engine)

**Roger Busquets**'s Github page ![https://github.com/rogerbusquets97](https://github.com/rogerbusquets97)

**Sergi Parra**'s Github page ![https://github.com/t3m1X](https://github.com/t3m1X)

### Main Menu Bar

### File

**Quit (Alt + F4)**_: Exits the application.

**Save Scene**_: Allows you to save the scene in a .json file.

**Load Scene**_: Loads a previously saved .json file



### View

**Configuration(C)**_: Shows the customizable properties for each module (camera, renderer, input, application and hardware for now).

**Properties (P)**_: Shows info about the current object in scene (transform, geometry and texture).

**Geometry**_: Open a menu that allows you to create several basic primitives.

**Console (C)**_: Allows to turn on and off the console (it is visible at the beggining of the application)

**Play&Pause**_: Enables and disables the time manager panel.


### Help

**Documentation**_: Opens the following link to the wiki : ![https://github.com/rogerbusquets97/3D-Engine/wiki](https://github.com/rogerbusquets97/3D-Engine/wiki)

**Report bug**_: Opens the following link to github issues: ![https://github.com/rogerbusquets97/3D-Engine/issues](https://github.com/rogerbusquets97/3D-Engine/issues)

**Github repository**_: Opens the following to to the github repository : ![https://github.com/rogerbusquets97/3D-Engine](https://github.com/rogerbusquets97/3D-Engine)

**Download latest**_: Opens the following link to the latests release : ![https://github.com/rogerbusquets97/3D-Engine/releases](https://github.com/rogerbusquets97/3D-Engine/releases)


## About

Opens the the about window that shows information about the engine (the name of the creators, libraries used and the license)

## Scene Info - Audio Engine

The release contains a saved scene named "test.json". If the scene is loaded there will appear a very simple scene with few audio elements in order to check the audio functionallity. One of the objects (Arrow), is moveable so when pressing play
it will move with arrow keys, as well as the camera object that will move with wasd. In order to hear something when playing the scene is necessary to go to one of the objects that contains an audio source components and specify which event to play
pressing send, so the event will be played when the game starts.(So you can check each event separetely or all together, though it will sound weird, make sure you don't have different events displayed together in the UI since if there are two "Play" buttons at the same time ImGui won't be able to perform the action). There are three events able. The "Play_Blend" event will trigger two background musics that will blend in a loop.
The Play_Short_Music event will trigger a 3D sound (spatial audio will be obvious when playing the scene and moving around). The Play_spell4 will trigger an FX also with 3D positioning. 
All the audios were set to loop infinitely in the Wwise editor in order to check the engines functionallity, but in a real context, except from the songs, FXs should not loop. The "send" button is also for testing purposes, in a real situation those events can be
played by using the SendEvent function from the AudioSource component. 

General volume can be changed from the configuration panel, and the application can be also muted. 



## License
MIT License

Copyright (c) 2017 Roger Busquets Duran and Sergi Parra Ramirez

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
