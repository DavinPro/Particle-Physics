<h1 align="center">
	Particle Physics
</h1>

<div align="center">
	A very simple particle physics simulator. <br><br>
	<img src="resources/demo.gif" width=600>
</div>

<p align="center">
  <a href="#purpose">Purpose</a> •
  <a href="#installation">Installation</a> •
  <a href="#commands">Commands</a>
</p>

## Purpose
This project was created to learn how a quadtree can be used to store and optimize searching of positional data.
Simply drawing a quadree is no fun though, so I decided to implement some very simple physics and use
the quadtree for collision detection. 

During development I also learned about CMake and how to configure a project for platform-independent building using a make file. 

<br>

## Installation
### Prerequisites
- [CMake](https://cmake.org/) (version 3.21+)
- [SFML](https://www.sfml-dev.org/download.php)

### Windows with CMake
- Clone [this repo](https://github.com/DavinPro/Particle-Physics.git)
- Open CMake
- Set the source path to the location of the repo
- Set the build path

![paths](https://user-images.githubusercontent.com/70703647/144086045-5d80f3a7-8111-4d3d-b2ac-b84d6ff596a6.jpg)
- Click configure
- Select your IDE from generator list

![generator](https://user-images.githubusercontent.com/70703647/144086046-c42a3aa3-1791-4306-959b-c0cc9eac7d25.jpg)
- Click Finish

- Click Configure again to update red values

![configure](https://user-images.githubusercontent.com/70703647/144086041-b48ab204-72d3-4523-ac63-ff55ff84d510.jpg)
- Click Generate
- After generation, build the project through your IDE

<br>

## Commands
|Command|Action|
|---|---|
|**Q**|Toggle quadrants drawing|
|**Click & Drag**|Add particle with velocity of mouse drag|
