#include <iostream>
#include <thread>
#include <functional>
#include <random>
#include <atomic>
#include <mutex>


std::mutex recordingTemp;

// Guest random selection
std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(-100, 70);
auto atmosphereTemperature = std::bind ( distribution, generator);


// I am using 480 here so that it each thread has a chance to run 60 times
std::atomic<int> index(480);
std::atomic<bool> addTheTemp(true);

// Tempature reader function
void tempReader()
{

    int highs[5] = {-100, -100, -100 , -100 , -100};
    int lows[5] = {70, 70, 70 , 70 , 70};
    int variance;
    

    while(index > 0)
    {
        // Take a temperature reading every "minute"
        int temp = atmosphereTemperature();
        // Stores in top 5 high or Top 5 low
        

        recordingTemp.lock();
        int i = 0;
        addTheTemp = true;
        while(i < 5){
            if(temp > highs[i] && temp != highs[i]){
                i++;
            }
            else{
                break;
            }
        }
        highs[i] = temp;
        for(i; i > 0; i--){
            highs[i - 1] = highs[i];
        }
        recordingTemp.unlock();


        // Gives the 10 "minute" interval with highest change
        index--;
        std::cout << index;
    }

    for(int i = 0; i < 5; i++){
        std::cout << highs;
    }
}

int main(){
    std::thread sensors[8];
    for (int i=0; i<10; i+=2) {
        sensors[i] = std::thread(tempReader);
    }
    for (auto& s : sensors) {
        s.join();
    }


    return 0;
}
