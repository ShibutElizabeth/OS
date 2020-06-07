#ifndef BUFFERED_CHANNEL_H_
#define BUFFERED_CHANNEL_H_

#include <thread>
#include <chrono>
#include <mutex>
#include <utility>
#include <queue>
#include <condition_variable>
#include <atomic>

template<class T>
class BufferedChannel {
public:
	explicit BufferedChannel(int size) {
		bufferSize = size;
		isClosed = false;
	}

	void Send(T value) {
		if (isClosed) {
			throw std::runtime_error("Channel is closed!");
		}
		std::unique_lock<std::mutex> locker(defaultMutex);
		fullQueue.wait(locker, [this]() {
			return bufferSize < myQueue.size() || isClosed;
		});
		if (isClosed) {
			throw std::runtime_error("Channel is closed!");
		}
		myQueue.push(std::move(value));
		emptyQueue.notify_one();
	}

	std::pair<T, bool> Recv() {
		std::unique_lock<std::mutex> locker(defaultMutex);
		if (isClosed) {
			if (!myQueue.empty()) {
				std::pair<T, bool> buff = { myQueue.front(), true };
				myQueue.pop();

				return buff;
			}
			else {
				return std::make_pair(T(), false);
			}
		}
		emptyQueue.wait(locker, [&]() {
			return !myQueue.empty() || isClosed;
		});

		if (!myQueue.empty()) {
			std::pair<T, bool> buff = { myQueue.front(), true };
			myQueue.pop();
			fullQueue.notify_one();
			return buff;
		}
		else  return  std::make_pair(T(), false);
	}

	void Close() {
		defaultMutex.lock();
		isClosed = true;
		defaultMutex.unlock();
		emptyQueue.notify_all();
		fullQueue.notify_all();
	}

private:
	std::atomic<bool> isClosed;
	std::atomic<int> bufferSize;
	std::queue<T> myQueue;
	std::mutex defaultMutex;
	std::condition_variable fullQueue;
	std::condition_variable emptyQueue;

};

#endif // BUFFERED_CHANNEL_H_
