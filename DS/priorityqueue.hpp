#include<vector>

namespace priorityqueue {
    template<typename Value, typename Compare = std::less<Value>>
    class MaxPQ {
        std::vector<Value> values;
        Compare comp;

        void swim(int k) {
            while(k > 0 && comp(values[(k - 1) / 2], values[k])) {
                std::swap(values[k], values[(k - 1) / 2]);
                k = (k - 1) / 2;
            }
        }

        void sink(int k) {
            int n = values.size();
            while(2 * k + 1 < n) {
                int j = 2 * k + 1;
                if(j + 1 < n && comp(values[j], values[j + 1])) { ++j; }
                if(!comp(values[k], values[j])) { break; }
                std::swap(values[k], values[j]);
                k = j;
            }
        }

        public:
            MaxPQ(int size) : values(size) {}

            MaxPQ(const std::vector<Value>& values) : values(values) {}

            MaxPQ() = default;

            ~MaxPQ() = default;

            void enqueue(const Value& value) {
                values.push_back(value);
                swim(values.size() - 1);
            }

            Value dequeue() {
                if(values.empty()) { throw std::runtime_error("Priority queue is empty"); }
                Value max_value = values.front();
                std::swap(values.front(), values.back());
                values.pop_back();
                sink(0);
                return max_value;
            }

            const Value& get_max() const {
                return values.front();
            }
            
            Value& get_max() {
                return values.front();
            }

            bool is_empty() const {
                return values.empty();
            }

            int size() const {
                return values.size();
            }

            const Value& delSample(int index) const {
                if(values.empty()) { throw std::runtime_error("Priority queue is empty"); }
                
                Value sample_value = values[index];
                std::swap(values[index], values.back());
                values.pop_back();
                sink(index);

                return sample_value;
            }

            const Value& operator[](int index) const {
                return values[index];
            }

            Value& operator[](int index) {
                return values[index];
            }
    };

    template<typename Value, typename Compare = std::greater<Value>>
    class MinPQ {
        std::vector<Value> values;
        Compare comp;

        void swim(int k) {
            while(k > 0 && comp(values[(k - 1) / 2], values[k])) {
                std::swap(values[k], values[(k - 1) / 2]);
                k = (k - 1) / 2;
            }
        }

        void sink(int k) {
            int n = values.size();
            while(2 * k + 1 < n) {
                int j = 2 * k + 1;
                if(j + 1 < n && comp(values[j], values[j + 1])) { ++j; }
                if(!comp(values[k], values[j])) { break; }
                std::swap(values[k], values[j]);
                k = j;
            }
        }

        public:
            MinPQ(int size) : values(size) {}

            MinPQ(const std::vector<Value>& values) : values(values) {}

            MinPQ() = default;

            ~MinPQ() = default;

            void enqueue(const Value& value) {
                values.push_back(value);
                swim(values.size() - 1);
            }

            Value dequeue() {
                if(values.empty()) { throw std::runtime_error("Priority queue is empty"); }
                Value min_value = values.front();
                std::swap(values.front(), values.back());
                values.pop_back();
                sink(0);
                return min_value;
            }

            const Value& get_min() const {
                return values.front();
            }

            Value& get_min() {
                return values.front();
            }

            bool is_empty() const {
                return values.empty();
            }

            int size() const {
                return values.size();
            }

            const Value& delSample(int index) const {
                if(values.empty()) { throw std::runtime_error("Priority queue is empty"); }
                
                Value sample_value = values[index];
                std::swap(values[index], values.back());
                values.pop_back();
                sink(index);

                return sample_value;
            }

            const Value& operator[](int index) const {
                return values[index];
            }

            Value& operator[](int index) {
                return values[index];
            }
    };

    void heapsort(std::vector<int>& arr, bool ascending = true) {
        if(ascending) {
            MinPQ<int> pq(arr);
            for(int i = 0; i < arr.size(); ++i) {
                arr[i] = pq.dequeue();
            }
        } else {
            MaxPQ<int> pq(arr);
            for(int i = 0; i < arr.size(); ++i) {
                arr[i] = pq.dequeue();
            }
        }
    }
}