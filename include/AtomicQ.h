#ifndef MASON_ATOMICQ_H
#define MASON_ATOMICQ_H

#include <mutex>
#include <vector>

template<class T> class AtomicQ {
public:
	AtomicQ() : lock() { }

	AtomicQ(const AtomicQ &a) : lock() { q = a.q; }

	void Push(T t) {
		std::lock_guard<std::mutex> l(lock);
		q.push_back(t);
	}

	template<typename Functor>
	void ForEach(Functor f) {
		std::lock_guard<std::mutex> l(lock);
		for (auto &x : q) f(x);
	}

	T Pop() {
		std::lock_guard<std::mutex> l(lock);
		return q.pop_back();
	}

	template<typename Functor>
	void Clear(Functor f) {
		std::lock_guard<std::mutex> l(lock);
		for (auto &x : q) f(x);
		q.clear();
	}

	void Clear() {
		std::lock_guard<std::mutex> l(lock);
		q.clear();
	}

private:
	std::vector<T> q;
	mutable std::mutex lock;
};

#endif
