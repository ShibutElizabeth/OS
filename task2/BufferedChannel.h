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
	explicit BufferedChannel(int size) : buffer_size_(size) {
		is_closed_ = false;
	}

	void Send(T value) {
		if (is_closed_) {
			std::runtime_error("closed");
			return;
		}

		if (buffer_size_ == size_) {
			full_mutex_.lock();
			while (buffer_size_ == size_) {}
			full_mutex_.unlock();
		}

		default_mutex_.lock();

		queue_.push(value);
		size_ = queue_.size();

		default_mutex_.unlock();
	}

	std::pair<T, bool> Recv() {
		if (is_closed_ && size_ == 0) {
			return { T(), false };
		}

		if (size_ == 0u) {
			empty_mutex_.lock();
			while (size_ == 0) {}
			empty_mutex_.unlock();
		}

		default_mutex_.lock();

		std::pair<T, bool> buff;
		buff = { queue_.front(), true };
		queue_.pop();
		size_ = queue_.size();

		default_mutex_.unlock();
		return buff;
	}

	void Close() {
		default_mutex_.lock();
		is_closed_ = true;
		default_mutex_.unlock();
	}

private:
	std::atomic_uint32_t size_;
	std::atomic_bool is_closed_;
	uint32_t buffer_size_;
	std::queue<T> queue_;
	std::mutex empty_mutex_;
	std::mutex full_mutex_;
	std::mutex default_mutex_;
};

#endif // BUFFERED_CHANNEL_H_