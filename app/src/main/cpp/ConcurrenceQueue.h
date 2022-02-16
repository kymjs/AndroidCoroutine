//
// Created by zhangtao on 2022/2/15.
//

#ifndef COROUTINE_CONCURRENCEQUEUE_H
#define COROUTINE_CONCURRENCEQUEUE_H


#include <queue>
#include <mutex>
#include <condition_variable>
#include <initializer_list>

template<typename T>
class ConcurrenceQueue {
private:
    // data_queue访问信号量
    mutable std::mutex mut;
    mutable std::condition_variable data_cond;
    using queue_type = std::queue<T>;
    queue_type data_queue;
public:
    using value_type = typename queue_type::value_type;
    using container_type = typename queue_type::container_type;

    ConcurrenceQueue() = default;

    ConcurrenceQueue(const ConcurrenceQueue &) = delete;

    ConcurrenceQueue &operator=(const ConcurrenceQueue &) = delete;

    /*
     * 使用迭代器为参数的构造函数,适用所有容器对象
     * */
    template<typename _InputIterator>
    ConcurrenceQueue(_InputIterator
                     first,
                     _InputIterator last
    ) {
        for (auto itor = first; itor != last; ++itor) {
            data_queue.push(*itor);
        }
    }

    explicit ConcurrenceQueue(const container_type &c) : data_queue(c) {}

    /*
     * 使用初始化列表为参数的构造函数
     * */
    ConcurrenceQueue(std::initializer_list <value_type> list) : ConcurrenceQueue(list.begin(), list.end()) {
    }

    /*
     * 将元素加入队列
     * */
    void push(const value_type &new_value) {
        std::lock_guard <std::mutex> lk(mut);
        data_queue.push(std::move(new_value));
        data_cond.notify_one();
    }

    /*
     * 从队列中弹出一个元素,如果队列为空就阻塞
     * */
    value_type pop() {
        std::unique_lock <std::mutex> lk(mut);
        data_cond.wait(lk, [this] { return !this->data_queue.empty(); });
        auto value = std::move(data_queue.front());
        data_queue.pop();
        return value;
    }

    /*
     * 从队列中弹出一个元素,如果队列为空返回false
     * */
    bool try_pop(value_type &value) {
        std::lock_guard <std::mutex> lk(mut);
        if (data_queue.empty())
            return false;
        value = std::move(data_queue.front());
        data_queue.pop();
        return true;
    }

    /*
     * 返回队列是否为空
     * */
    auto empty() const -> decltype(data_queue.empty()) {
        std::lock_guard <std::mutex> lk(mut);
        return data_queue.empty();
    }

    /*
     * 返回队列中元素数个
     * */
    auto size() const -> decltype(data_queue.size()) {
        std::lock_guard <std::mutex> lk(mut);
        return data_queue.size();
    }
};

#endif //COROUTINE_CONCURRENCEQUEUE_H
