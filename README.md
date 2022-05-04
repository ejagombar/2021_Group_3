 # 2021_Group_3

A 3D model viewer designed to run on Windows, MacOS and Linux able to render and perform basic manipulation to .stl files and custom .mod files.

[Project Documentation](https://ejagombar.github.io/2021_Group_3/) and
[GitHub](https://github.com/ejagombar/2021_Group_3)

[![Testing Status(latest by date)](https://img.shields.io/github/workflow/status/ejagombar/2021_Group_3/cmake-test)](https://github.com/ejagombar/2021_Group_3/actions/workflows/makes-test.yml/badge.svg)
# Task
The aim of this project is described below. As stated in the task sheet.
Your team has been asked by a client to develop and 3D model viewer that will form part of a larger CAD system  
  * The client needs software that can run on PCs running Windows, MacOS and Linux  
  * Your group only needs to develop for 1 of these but you are free to use any platform you choose.   
  * It must be able to visualise models in two formats:  
    * The standard STL format  
    * A proprietary “in-house” format that was used for their old products.
You will write a 3D Model Viewer application and deliver it in package/installer.  
  * In semester 1 you’ll need to write a custom library (more on this later) to allow it load the in-house model format  
  * The Model Viewer itself will be developed in semester 2.  
  * You must provide a report outlining how the software was developed, how the code is structured, and how the software can be operated.
  * Source code for both the library and viewer must also be submitted for assessment


# Group Members

 * Edward Agombar
 * Ben Richards
 * Dongkun Xu
 * Odiri Otite

# Repository Contents:
The repository was set up during the lab sessions, and contains 3 branches:

The first branch is the Main branch, which contains:
  * The ReadMe file to detail the project, which also links to the Doxygen page for the code written for the project, and shows the output of the tests in the repository.
  * The Doxygen files to run Doxygen in the repository.
  * The code files for the most stable “release ready” program, along with the CMakeLists file which builds the project, and the associated files such as the icons used in the program.
  * The MOD file library, which is built into the program, but unused as there was not enough time to integrate this 

The second branch is the “Version2” branch. This branch contains:
  * The code files for the object oriented version of the program. 
  * The code for the installer for the “Version2” program (called)
This version is a much better solution to the problem, with object oriented programming providing a solution to making the program scalable. This version of the program, however, is less stable as it was achieved late into the process and there was not enough time to fully work out bugs in the code and to add doxygen documentation for it. The decision was therefore made to use the stable version as the “Main program”, however the OOP program was  given its own branch so it could be demonstrated that the group understood and made considerable progress towards making the program scalable. The OOP program had begun to solve having an unlimited number of tabs, an unlimited number of rendered objects of all types (within reason) and keeping track of the filters applied to objects without using the hardcoding methods employed in the “Main program”. This was done with classes, using arrays of these classes and member functions to remove the reliance on the hard-coded methods which limited the “Main program”.

The third branch is the “gh-pages” branch which contains:
  * The code to run GH-pages which runs the tests on the MOD file library.

