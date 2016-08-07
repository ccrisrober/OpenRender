#ifndef TIMER_H
#define TIMER_H

#include <ctime>
#include <iomanip>

class Timer {
public:
	Timer() : running(false), start_clock(0), start_time(0), acc_time(0) { }

	double elapsed_time();
	void start(const char* msg = 0);
	void SetToZero();
	void restart(const char* msg = 0);
	void stop(const char* msg = 0);
	float check();

	void wait(int waitTime);

private:
	bool running;
	clock_t start_clock;
	time_t start_time;
	double acc_time;
};


inline double Timer::elapsed_time() {
  time_t acc_sec = time(0) - start_time;
  if (acc_sec < 3600)
    return (clock() - start_clock) / (1.0 * CLOCKS_PER_SEC);
  else
    return (1.0 * acc_sec);
}

inline void Timer::start(const char* msg) {
  // Return immediately if the timer is already running
  if (running) return;

  // Set timer status to running and set the start time
  running = true;
  start_clock = clock();
  start_time = time(0);

} 

inline void Timer::restart(const char* msg) {
  // Set timer status to running, reset accumulated time, and set start time
  running = true;
  acc_time = 0;
  start_clock = clock();
  start_time = time(0);

} 

inline void Timer::SetToZero() {
	acc_time = 0;
}

// Stop the timer 

inline void Timer::stop(const char* msg) {
  // Compute accumulated running time and set timer status to not running
  if (running) acc_time += elapsed_time();
  running = false;

} 

inline float Timer::check() {
   return (float) acc_time + (running ? elapsed_time() : 0);
} 

inline void Timer::wait(int waitTime) {
	for(int i = waitTime; i > 0; --i) {
		//do nothing
	}
}

extern Timer* gTimer;


#endif /* TIMER_H */