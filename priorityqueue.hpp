#include<vector>
#include<cstddef>
#include<stdexcept>
#include<functional>
#include<utility>

namespace priorityqueue {
    template<typename Value, typename Compare = std::less<Value>>
    class MaxPQ {
        std::size_t _capacity;
        std::size_t _size;

        Value* _values;
        Compare _comp;

        void swim(std::size_t k) {
            if(k >= _size) { throw std::out_of_range("out of bounds"); }

            while(k > 0 && _comp(_values[(k - 1) / 2], _values[k])) {
                std::swap(_values[k], _values[(k - 1) / 2]);
                k = (k - 1) / 2;
            }
        }

        void sink(std::size_t k) {
            if(k >= _size) { throw std::out_of_range("out of bounds"); }

            std::size_t n = _size;
            while(2 * k + 1 < n) {
                std::size_t j = 2 * k + 1;
                if(j + 1 < n && _comp(_values[j], _values[j + 1])) { ++j; }
                if(!_comp(_values[k], _values[j])) { break; }
                std::swap(_values[k], _values[j]);
                k = j;
            }
        }

        public:
            MaxPQ(std::size_t capacity = 10) : _capacity((capacity == 0) ? 10 : capacity), _size(0), _values(new Value[_capacity]) {
                for(std::size_t i = 0; i < _capacity; ++i) {
                    _values[i] = Value();
                }
            }

            MaxPQ(const std::vector<Value>& values) : _capacity((values.size() == 0) ? 10 : values.size()), _size(values.size()), _values(new Value[_capacity]) {
                for(std::size_t i = 0; i < _size; ++i) {
                    _values[i] = values[i];
                }
                if(_size > 1) {
                    for(std::size_t k = _size / 2; k > 0; --k) {
                        sink(k - 1);
                    }
                }
            }

            MaxPQ(const MaxPQ& other) : _capacity(other._capacity), _size(other._size), _values(new Value[other._capacity]) {
                for(std::size_t i = 0; i < other._size; ++i) {
                    _values[i] = other._values[i];
                }
            }

            MaxPQ(MaxPQ&& other) noexcept : _capacity(other._capacity), _size(other._size), _values(other._values) {
                other._capacity = 0;
                other._size = 0;
                other._values = nullptr;
            }

            MaxPQ& operator=(const MaxPQ& other) {
                if(this != &other) {
                    delete[] _values;

                    _capacity = other._capacity;
                    _size = other._size;
                    _values = new Value[other._capacity];

                    for(std::size_t i = 0; i < other._size; ++i) {
                        _values[i] = other._values[i];
                    }
                }
                return *this;
            }

            MaxPQ& operator=(MaxPQ&& other) noexcept {
                if(this != &other) {
                    delete[] _values;

                    _capacity = other._capacity;
                    _size = other._size;
                    _values = other._values;

                    other._capacity = 0;
                    other._size = 0;
                    other._values = nullptr;
                }
                return *this;
            }

            ~MaxPQ() {
                delete[] _values;
            }

            /// @brief Resizes the underlying array to the specified new capacity.
            void resize(std::size_t new_capacity) {
                if(new_capacity < _size) { throw std::invalid_argument("new capacity must be greater than or equal to the current size"); }

                if(new_capacity == 0) { throw std::invalid_argument("new capacity must be greater than 0"); }

                Value* new_values = new Value[new_capacity];
                for(std::size_t i = 0; i < _size; ++i) {
                    new_values[i] = _values[i];
                }

                delete[] _values;
                _values = new_values;
                _capacity = new_capacity;
            }

            /// @brief Inserts a new value into the priority queue.
            void push(const Value& value) {
                if(_size == _capacity) { resize(_capacity * 2); }

                _values[_size] = value;
                ++_size;
                swim(_size - 1);
            }

            /// @brief Removes and returns the maximum value from the priority queue.
            Value pop() {
                if(_size == 0) { throw std::runtime_error("Priority queue is empty"); }

                Value max_value = _values[0];
                std::swap(_values[0], _values[_size - 1]);
                --_size;
                if(_size > 0) { sink(0); }

                if(_size > 0 && _size == _capacity / 4) { resize(_capacity / 2); }

                return max_value;
            }

            /// @brief Returns the maximum value from the priority queue without removing it.
            const Value& max() const {
                if(_size == 0) { throw std::runtime_error("Priority queue is empty"); }

                return _values[0];
            }
            
            /// @brief Returns the maximum value from the priority queue without removing it.
            Value& max() {
                if(_size == 0) { throw std::runtime_error("Priority queue is empty"); }

                return _values[0];
            }

            bool is_empty() const { return _size == 0; }

            std::size_t size() const { return _size; }

            /// @brief Removes and returns a sample value from the priority queue.
            /// @param index The index of the value to remove.
            Value delSample(std::size_t index) {
                if(_size == 0) { throw std::runtime_error("Priority queue is empty"); }
                if(index >= _size) { throw std::out_of_range("out of bounds"); }

                Value sample_value = _values[index];
                std::swap(_values[index], _values[_size - 1]);
                --_size;
                
                if(index < _size) {
                    swim(index);
                    sink(index);
                }

                if(_size > 0 && _size == _capacity / 4) { resize(_capacity / 2); }

                return sample_value;
            }

            /// @brief Returns a const reference to the value at the specified index in the priority queue.
            const Value& operator[](std::size_t index) const {
                if(index >= _size) { throw std::out_of_range("out of bounds"); }

                return _values[index];
            }

            /// @brief Returns a reference to the value at the specified index in the priority queue.
            Value& operator[](std::size_t index) {
                if(index >= _size) { throw std::out_of_range("out of bounds"); }

                return _values[index];
            }

            std::size_t capacity() const { return _capacity; }
    };

    template<typename Value, typename Compare = std::greater<Value>>
    class MinPQ {
        std::size_t _capacity;
        std::size_t _size;

        Value* _values;
        Compare _comp;

        void swim(std::size_t k) {
            if(k >= _size) { throw std::out_of_range("out of bounds"); }

            while(k > 0 && _comp(_values[(k - 1) / 2], _values[k])) {
                std::swap(_values[k], _values[(k - 1) / 2]);
                k = (k - 1) / 2;
            }
        }

        void sink(std::size_t k) {
            if(k >= _size) { throw std::out_of_range("out of bounds"); }

            std::size_t n = _size;
            while(2 * k + 1 < n) {
                std::size_t j = 2 * k + 1;
                if(j + 1 < n && _comp(_values[j], _values[j + 1])) { ++j; }
                if(!_comp(_values[k], _values[j])) { break; }
                std::swap(_values[k], _values[j]);
                k = j;
            }
        }

        public:
            MinPQ(std::size_t capacity = 10) : _capacity((capacity == 0) ? 10 : capacity), _size(0), _values(new Value[_capacity]) {
                for(std::size_t i = 0; i < _capacity; ++i) {
                    _values[i] = Value();
                }
            }

            MinPQ(const std::vector<Value>& values) : _capacity((values.size() == 0) ? 10 : values.size()), _size(values.size()), _values(new Value[_capacity]) {
                for(std::size_t i = 0; i < _size; ++i) {
                    _values[i] = values[i];
                }
                if(_size > 1) {
                    for(std::size_t k = _size / 2; k > 0; --k) {
                        sink(k - 1);
                    }
                }
            }

            MinPQ(const MinPQ& other) : _capacity(other._capacity), _size(other._size), _values(new Value[other._capacity]) {
                for(std::size_t i = 0; i < other._size; ++i) {
                    _values[i] = other._values[i];
                }
            }

            MinPQ(MinPQ&& other) noexcept : _capacity(other._capacity), _size(other._size), _values(other._values) {
                other._capacity = 0;
                other._size = 0;
                other._values = nullptr;
            }

            MinPQ& operator=(const MinPQ& other) {
                if(this != &other) {
                    delete[] _values;

                    _capacity = other._capacity;
                    _size = other._size;
                    _values = new Value[other._capacity];

                    for(std::size_t i = 0; i < other._size; ++i) {
                        _values[i] = other._values[i];
                    }
                }
                return *this;
            }

            MinPQ& operator=(MinPQ&& other) noexcept {
                if(this != &other) {
                    delete[] _values;

                    _capacity = other._capacity;
                    _size = other._size;
                    _values = other._values;

                    other._capacity = 0;
                    other._size = 0;
                    other._values = nullptr;
                }
                return *this;
            }

            ~MinPQ() {
                delete[] _values;
            }

            /// @brief Resizes the underlying array to the specified new capacity.
            void resize(std::size_t new_capacity) {
                if(new_capacity < _size) { throw std::invalid_argument("new capacity must be greater than or equal to the current size"); }

                if(new_capacity == 0) { throw std::invalid_argument("new capacity must be greater than 0"); }

                Value* new_values = new Value[new_capacity];
                for(std::size_t i = 0; i < _size; ++i) {
                    new_values[i] = _values[i];
                }

                delete[] _values;
                _values = new_values;
                _capacity = new_capacity;
            }

            /// @brief Inserts a new value into the priority queue.
            void push(const Value& value) {
                if(_size == _capacity) { resize(_capacity * 2); }

                _values[_size] = value;
                ++_size;
                swim(_size - 1);
            }

            /// @brief Removes and returns the maximum value from the priority queue.
            Value pop() {
                if(_size == 0) { throw std::runtime_error("Priority queue is empty"); }

                Value max_value = _values[0];
                std::swap(_values[0], _values[_size - 1]);
                --_size;
                if(_size > 0) { sink(0); }

                if(_size > 0 && _size == _capacity / 4) { resize(_capacity / 2); }

                return max_value;
            }

            /// @brief Returns the minimum value from the priority queue without removing it.
            const Value& min() const {
                if(_size == 0) { throw std::runtime_error("Priority queue is empty"); }

                return _values[0];
            }
            
            /// @brief Returns the minimum value from the priority queue without removing it.
            Value& min() {
                if(_size == 0) { throw std::runtime_error("Priority queue is empty"); }

                return _values[0];
            }

            bool is_empty() const { return _size == 0; }

            std::size_t size() const { return _size; }

            /// @brief Removes and returns a sample value from the priority queue.
            /// @param index The index of the value to remove.
            Value delSample(std::size_t index) {
                if(_size == 0) { throw std::runtime_error("Priority queue is empty"); }
                if(index >= _size) { throw std::out_of_range("out of bounds"); }

                Value sample_value = _values[index];
                std::swap(_values[index], _values[_size - 1]);
                --_size;
                
                if(index < _size) {
                    swim(index);
                    sink(index);
                }

                if(_size > 0 && _size == _capacity / 4) { resize(_capacity / 2); }

                return sample_value;
            }

            /// @brief Returns a const reference to the value at the specified index in the priority queue.
            const Value& operator[](std::size_t index) const {
                if(index >= _size) { throw std::out_of_range("out of bounds"); }

                return _values[index];
            }

            /// @brief Returns a reference to the value at the specified index in the priority queue.
            Value& operator[](std::size_t index) {
                if(index >= _size) { throw std::out_of_range("out of bounds"); }

                return _values[index];
            }

            std::size_t capacity() const { return _capacity; }
    };

    /// @brief Sorts an array using the heap sort algorithm.
    /// @param array The array to sort.
    /// @param ascending Whether to sort in ascending order.
    template<typename Value>
    std::vector<Value> heapSort(const std::vector<Value>& array, bool ascending = true) {
        if(array.empty()) { return {}; }

        if(ascending) {
            MinPQ<Value> pq(array);
            std::vector<Value> sorted_values;

            while(!pq.is_empty()) { sorted_values.push_back(pq.pop()); }

            return sorted_values;
        } 
        else {
            MaxPQ<Value> pq(array);
            std::vector<Value> sorted_values;

            while(!pq.is_empty()) { sorted_values.push_back(pq.pop()); }

            return sorted_values;
        }
    }

    /// @brief Converts between maximum and minimum priority queues.
    /// @param max_pq should be empty if min_to_max is true, otherwise it will be filled with the values from min_pq.
    /// @param min_pq should be empty if min_to_max is false, otherwise it will be filled with the values from max_pq.
    template<typename Value>
    void convert(priorityqueue::MaxPQ<Value>& max_pq, priorityqueue::MinPQ<Value>& min_pq, bool min_to_max = true) {
        if(min_to_max) {
            if(!max_pq.is_empty()) { throw std::invalid_argument("max_pq must be empty when converting from min_pq to max_pq"); }

            while(!min_pq.is_empty()) {
                max_pq.push(min_pq.pop());
            }
        } 
        else {
            if(!min_pq.is_empty()) { throw std::invalid_argument("min_pq must be empty when converting from max_pq to min_pq"); }

            while(!max_pq.is_empty()) {
                min_pq.push(max_pq.pop());
            }
        }
    }
}
