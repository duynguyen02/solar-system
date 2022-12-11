# sudo apt-get install freeglut3
# sudo apt-get install freeglut3-dev
# sudo apt-get install mesa-utils

g++ main.cpp Imageloader.cpp Planet.cpp ScreenWriter.cpp SolarSystem.cpp -lglut -lGL -lGLU -lglfw -I./include -o main &&

./main;

if [ -f "main" ]
then
    rm main;
fi