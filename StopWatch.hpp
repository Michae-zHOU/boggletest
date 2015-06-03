// Kyle Barron-Kraus <kbarronk>

#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>

template <class Clock = std::chrono::system_clock>
class StopWatch {
  public:
    StopWatch(bool start = true);
    
    void start();

    bool started() const;

    void stop();

    bool stopped() const;

    typename Clock::time_point startPoint() const;

    typename Clock::time_point stopPoint() const;

    typename Clock::duration duration() const;

    template <typename Rep = std::chrono::milliseconds>
    typename Rep::rep elapsed() const;

  private:
    bool started_;
    bool stopped_;
    typename Clock::time_point start_;
    typename Clock::time_point stop_;
};

template <class Clock>
inline StopWatch<Clock>::StopWatch(bool start) :
    started_(false), stopped_(false) {
    if (start)
        this->start();
}

template <class Clock>
inline void StopWatch<Clock>::start() {
    started_ = true;
    stopped_ = false;
    start_ = Clock::now();
}

template <class Clock>
inline bool StopWatch<Clock>::started() const {
    return started_;
}

template <class Clock>
inline void StopWatch<Clock>::stop() {
    if (!started_ || stopped_)
        return;
    
    stop_ = Clock::now();
    stopped_ = true;
}

template <class Clock>
inline bool StopWatch<Clock>::stopped() const {
    return stopped_;
}

template <class Clock>
inline typename Clock::time_point StopWatch<Clock>::startPoint() const {
    if (!started_)
        return Clock::time_point::min();
    return start_;
}

template <class Clock>
inline typename Clock::time_point StopWatch<Clock>::stopPoint() const {
    if (!stopped_)
        return Clock::time_point::min();
    return stop_;
}

template <class Clock>
inline typename Clock::duration StopWatch<Clock>::duration() const {
    if (!started_)
        Clock::duration::zero();
    if (!stopped_)
        return Clock::now() - start_;
    return stop_ - start_;
}

template <class Clock>
template <typename Rep>
inline typename Rep::rep StopWatch<Clock>::elapsed() const {
    return std::chrono::duration_cast<Rep>(duration()).count();
}

#endif // STOPWATCH_H