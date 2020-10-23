#pragma once
#include <queue>
#include <mutex>

template<typename T>
class tsqueue {
  protected:
    std::queue<T> m_queue;
    std::mutex<T> m_mtx;

  public:
    tsqueue() = default;

    tsqueue(const tsqueue<T>& o) = delete;
    tsqueue<T>& operator=(const tsqueue<T>& o) = delete;

    tsqueue(tsqueue<T>&& o) {
      *this = std::move(o);
    }

    tsqueue<T>& operator=(tsqueue<T>&& o) {
      std::scoped_lock l(m_mtx);
      m_queue = std::move(o.m_queue);
    }

    void push(const T& value) {
      std::scoped_lock l(m_mtx);
      m_queue.push(value);
    }

    template<class Args...>
    void emplace(Args&&... args) {
      std::scoped_lock l(m_mtx);
      m_queue.emplace(args);
    }

    auto pop() {
      std::scoped_lock l(m_mtx);
      auto value = m_queue.front();
      m_queue.pop();
      return value;
    }

    auto front() const {
      std::scoped_lock l(m_mtx);
      return m_queue.front();
    }

    auto back() const {
      std::scoped_lock l(m_mtx);
      return m_queue.back();
    }

    auto empty() const {
      std::scoped_lock l(m_mtx);
      return m_queue.empty();
    }

    auto size() const {
      std::scoped_lock l(m_mtx);
      return m_queue.size();
    }
};


