## 🎯 Project Goals
  This is a small project I started to increase my comfort with C++ software development. The goal of this project is to create an enviroment
  that makes it easier to start developing. While there already exists plenty of open-source low-friction game engines, the scope of this engine
  will be much smaller, focusing ONLY on 2D games for the foreseeable future.

  The project can be compiled by cloning this repository and either running the batch file to execute a G++ command, or with CMake

  Please note this project is very early in development

## Conway's Game of Life Demo
<img width="800" height="470" alt="image" src="https://github.com/user-attachments/assets/0cc0b92e-a68d-4f28-bca5-c749159ea8a3" />

I wrote a demo for this engine and decided to re-create conway's game of life. Cellular automata is a very interesting topic and I thought it'd be a
good first project for the engine since it doesn't require physics or collisions.

## Rigidbody / Collision engine Demo
<img width="796" height="472" alt="image" src="https://github.com/user-attachments/assets/140336fb-8168-4889-8b38-13a8d0118f1d" />

I also started work on a 2D physics system. Unfortunately this hasn't been worked on in a while, so it's still at a very early stage and not truly a full demo.
It does feature things like an elastic rope that allows you to drag the red circle around, but the rigidbodies only collide with the window, and not eachother.
There is also a basic implementation of gravity in the demo
