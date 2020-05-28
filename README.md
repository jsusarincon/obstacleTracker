# ObstacleTracker
This code reads features obtained from a 360 image and cluster them based on the angle from the polar coordinates.

Data Format
The feature θ values as a comma-separated list of floating-point values. Yhe output are the θ values of cluster centers in the same format.


# Compiling the code
This code is written in C++ and can be compiled with cmake in any platform.

Steps:

1. Clone/Download the repository.
2. Make sure you have the obstacleTracker folder, the cMakeLists, and the example_data.
3. Create a folder to compile the program:
    mkdir build

4. Go inside it

    cd build

5. then run cmake and point to the parent directory
    
    cmake ..

6. and finally run build it

    cmake --build .

# Running the code

After creating succesfully the code go to the folder where the executable was created

    e.g. windows: obstacleTracker\Debug>obstacleTracker.exe E:\input0.txt

After the executable name please provide the path to find the input files, for our example they are at "E:\input0.txt", in case you forget to provide the argument the following message will be shown on the screen:

    "No path to the File was given, please specify the path as the first argument of the executable. "

If the program executes correctly it will create an text file with the centroids separated by comas where the executable is:

    e.g. build\obstacleTracker\Debug\output.txt
