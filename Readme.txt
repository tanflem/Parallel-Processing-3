Problem 1:
Compile using: g++ -std=c++11 birthdayPresents.cpp -o present && ./present

For problem one I have three seperate files. Originally I tried using a lock free list from the C++ book. Then I ended up on a not lock queue implementation from my linked list. The first proggram

Problem 2:
Compile using: ++ -std=c++11 -pthread atmosphericTempReadingModule.cpp -o atmos && ./atmos


My idea for this one was to use a lock. So I set up this lock and but the array handling code in there. This was obviously the wrong direction.
By the end I had a working program but it was not any better than a single threaded implementation. I tried to update and change but by that point
it was already too late.
