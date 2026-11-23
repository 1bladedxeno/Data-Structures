#include<vector>
#include<stdexcept>

namespace unionfind {
    
    template<typename Value>
    class QuickFind {
        std::size_t _size;
        std::size_t _capacity;

        Value* _values;
        std::size_t* _id;

        public:
            QuickFind(std::size_t capacity = 10) : _size(0), _capacity((capacity == 0) ? 10 : capacity), _values(new Value[_capacity]), _id(new std::size_t[_capacity]) {
                for(std::size_t i = 0; i < _capacity; ++i) {
                    _id[i] = i;
                    _values[i] = Value();
                }
            }

            QuickFind(const QuickFind& other) : _size(other._size), _capacity(other._capacity), _values(new Value[other._capacity]), _id(new std::size_t[other._capacity]) {
                for(std::size_t i = 0; i < _size; ++i) {
                    this->_values[i] = other._values[i];
                    this->_id[i] = other._id[i];
                }
            }

            QuickFind(QuickFind&& other) noexcept : _size(other._size), _capacity(other._capacity), _values(other._values), _id(other._id) {
                other._values = nullptr;
                other._id = nullptr;
                other._size = 0;
                other._capacity = 0;
            }

            QuickFind& operator=(const QuickFind& other) {
                if(this != &other) {
                    delete[] _values;
                    delete[] _id;

                    _size = other._size;
                    _capacity = other._capacity;
                    _values = new Value[_capacity];
                    _id = new std::size_t[_capacity];

                    for(std::size_t i = 0; i < _size; ++i) {
                        this->_values[i] = other._values[i];
                        this->_id[i] = other._id[i];
                    }
                }
                return *this;
            }

            QuickFind& operator=(QuickFind&& other) noexcept {
                if(this != &other) {
                    delete[] _values;
                    delete[] _id;

                    _size = other._size;
                    _capacity = other._capacity;
                    _values = other._values;
                    _id = other._id;

                    other._values = nullptr;
                    other._id = nullptr;
                    other._size = 0;
                    other._capacity = 0;
                }
                return *this;
            }

            ~QuickFind() {
                delete[] _values;
                delete[] _id;
            }

            /// @brief Resizes the internal arrays to accommodate more elements O(n)
            /// @param new_capacity The new capacity for the internal arrays
            void resize(std::size_t new_capacity) {
                Value* new_values = new Value[new_capacity];
                std::size_t* new_id = new std::size_t[new_capacity];

                for(std::size_t i = 0; i < _size; ++i) {
                    new_values[i] = _values[i];
                    new_id[i] = _id[i];
                }

                delete[] _values;
                delete[] _id;

                _values = new_values;
                _id = new_id;
                _capacity = new_capacity;
            }

            /// @brief Inserts a new value into the data structure O(1)
            void insert(const Value& value) {
                if(_size >= _capacity) { resize(_capacity * 2); }

                _values[_size] = value;
                _id[_size] = _size;
                _size++;
            }

            /// @brief Finds the component identifier for the element at index p O(1)
            std::size_t find(std::size_t p) const {
                if(p >= _size) { throw std::out_of_range("Index out of bounds"); }

                return _id[p];
            }

            /// @brief Unifies the components containing elements at indices p and q O(n)
            void unify(std::size_t p, std::size_t q) {
                std::size_t pid = find(p);
                std::size_t qid = find(q);
                if(pid == qid) { return; }
                for(std::size_t i = 0; i < _size; ++i) {
                    if(_id[i] == pid) { _id[i] = qid; }
                }
            }

            /// @brief Returns the value associated with the element at index `index`
            Value value(std::size_t index) const {
                if(index >= _size) { throw std::out_of_range("Index out of bounds"); }
                return _values[index];
            }

            /// @brief Returns a reference to the value associated with the element at index `index`
            Value& operator[](std::size_t index) {
                if(index >= _size) { throw std::out_of_range("Index out of bounds"); }
                return _values[index];
            }

            /// @brief Returns a const reference to the value associated with the element at index `index`
            const Value& operator[](std::size_t index) const {
                if(index >= _size) { throw std::out_of_range("Index out of bounds"); }
                return _values[index];
            }

            /// @brief Returns a reference to the value associated with the parent of the element at index `p`
            Value& parent(std::size_t p) { return _values[find(p)]; }

            /// @brief Returns a const reference to the value associated with the parent of the element at index `p`
            const Value& parent(std::size_t p) const { return _values[find(p)]; }

            /// @brief Returns a vector containing all the values in the data structure
            std::vector<Value> values() const {
                std::vector<Value> Values(_size);
                for(std::size_t i = 0; i < _size; ++i) { Values[i] = _values[i]; }
                return Values;
            }

            std::size_t size() const { return _size; }

            std::size_t capacity() const { return _capacity; }
    };

    template<typename Value>
    class QuickUnion {
        std::size_t _size;
        std::size_t _capacity;

        Value* _values;
        std::size_t* _parent;

        public:
            QuickUnion(std::size_t capacity = 10) : _size(0), _capacity((capacity == 0) ? 10 : capacity), _values(new Value[_capacity]), _parent(new std::size_t[_capacity]) {
                for(std::size_t i = 0; i < _capacity; ++i) {
                    _parent[i] = i;
                    _values[i] = Value();
                }
            }

            QuickUnion(const QuickUnion& other) : _size(other._size), _capacity(other._capacity), _values(new Value[other._capacity]), _parent(new std::size_t[other._capacity]) {
                for(std::size_t i = 0; i < other._size; ++i) {
                    this->_values[i] = other._values[i];
                    this->_parent[i] = other._parent[i];
                }
            }

            QuickUnion(QuickUnion&& other) noexcept : _size(other._size), _capacity(other._capacity), _values(other._values), _parent(other._parent) {
                other._values = nullptr;
                other._parent = nullptr;
                other._size = 0;
                other._capacity = 0;
            }

            QuickUnion& operator=(const QuickUnion& other) {
                if(this != &other) {
                    delete[] _values;
                    delete[] _parent;

                    _size = other._size;
                    _capacity = other._capacity;
                    _values = new Value[_capacity];
                    _parent = new std::size_t[_capacity];

                    for(std::size_t i = 0; i < other._size; ++i) {
                        this->_values[i] = other._values[i];
                        this->_parent[i] = other._parent[i];
                    }
                }
                return *this;
            }

            QuickUnion& operator=(QuickUnion&& other) noexcept {
                if(this != &other) {
                    delete[] _values;
                    delete[] _parent;

                    _size = other._size;
                    _capacity = other._capacity;
                    _values = other._values;
                    _parent = other._parent;

                    other._values = nullptr;
                    other._parent = nullptr;
                    other._size = 0;
                    other._capacity = 0;
                }
                return *this;
            }

            ~QuickUnion() {
                delete[] _values;
                delete[] _parent;
            }

            /// @brief Resizes the data structure to accommodate more elements O(n)
            /// @param new_capacity The new capacity of the data structure
            void resize(std::size_t new_capacity) {
                Value* new_values = new Value[new_capacity];
                std::size_t* new_parent = new std::size_t[new_capacity];

                for(std::size_t i = 0; i < _size; ++i) {
                    new_values[i] = _values[i];
                    new_parent[i] = _parent[i];
                }

                delete[] _values;
                delete[] _parent;

                _values = new_values;
                _parent = new_parent;
                _capacity = new_capacity;
            }

            /// @brief Inserts a new value into the data structure O(1)
            void insert(const Value& value) {
                if(_size >= _capacity) { resize(_capacity * 2); }

                _values[_size] = value;
                _parent[_size] = _size;
                _size++;
            }

            /// @brief Finds the root of the element at index `p` O(n)
            std::size_t find(std::size_t p) const {
                if(p >= _size) { throw std::out_of_range("Index out of bounds"); }

                while(p != _parent[p]) { p = _parent[p]; }
                return p;
            }

            /// @brief Unifies the components containing elements at indices p and q O(n)
            void unify(std::size_t p, std::size_t q) {
                std::size_t rootP = find(p);
                std::size_t rootQ = find(q);
                if(rootP == rootQ) { return; }
                _parent[rootP] = rootQ;
            }

            /// @brief Returns the value associated with the element at index `index`
            Value value(std::size_t index) const {
                if(index >= _size) { throw std::out_of_range("Index out of bounds"); }

                return _values[index];
            }

            /// @brief Returns a reference to the value at the specified index
            Value& operator[](std::size_t index) {
                if(index >= _size) { throw std::out_of_range("Index out of bounds"); }
                return _values[index];
            }

            /// @brief Returns a const reference to the value at the specified index
            const Value& operator[](std::size_t index) const {
                if(index >= _size) { throw std::out_of_range("Index out of bounds"); }
                return _values[index];
            }

            /// @brief Returns a reference to the value associated with the parent of the element at index `p`
            Value& parent(std::size_t p) { return _values[find(p)]; }

            /// @brief Returns a const reference to the value associated with the parent of the element at index `p`
            const Value& parent(std::size_t p) const { return _values[find(p)]; }

            /// @brief Returns a vector containing all values in the data structure
            std::vector<Value> values() const { return std::vector<Value>(_values, _values + _size); }

            std::size_t size() const { return _size; }

            std::size_t capacity() const { return _capacity; }
    };

    template<typename Value>
    class WeightedQuickUnion {
        std::size_t _size;
        std::size_t _capacity;

        Value* _values;
        std::size_t* _parent;
        std::size_t* _sizes;

        public:
            WeightedQuickUnion(std::size_t capacity = 10) : _size(0), _capacity((capacity == 0) ? 10 : capacity) {
                _values = new Value[_capacity];
                _parent = new std::size_t[_capacity];
                _sizes = new std::size_t[_capacity];
                for(std::size_t i = 0; i < _capacity; ++i) {
                    _parent[i] = i;
                    _sizes[i] = 1;
                }
            }

            WeightedQuickUnion(const WeightedQuickUnion& other) : _size(other._size), _capacity(other._capacity) {
                _values = new Value[_capacity];
                _parent = new std::size_t[_capacity];
                _sizes = new std::size_t[_capacity];
                for(std::size_t i = 0; i < _size; ++i) {
                    _values[i] = other._values[i];
                    _parent[i] = other._parent[i];
                    _sizes[i] = other._sizes[i];
                }
            }

            WeightedQuickUnion(WeightedQuickUnion&& other) noexcept : _size(other._size), _capacity(other._capacity), _values(other._values), _parent(other._parent), _sizes(other._sizes) {
                other._values = nullptr;
                other._parent = nullptr;
                other._sizes = nullptr;
                other._size = 0;
                other._capacity = 0;
            }

            WeightedQuickUnion& operator=(const WeightedQuickUnion& other) {
                if(this != &other) {
                    delete[] _values;
                    delete[] _parent;
                    delete[] _sizes;

                    _size = other._size;
                    _capacity = other._capacity;
                    _values = new Value[_capacity];
                    _parent = new std::size_t[_capacity];
                    _sizes = new std::size_t[_capacity];

                    for(std::size_t i = 0; i < _size; ++i) {
                        _values[i] = other._values[i];
                        _parent[i] = other._parent[i];
                        _sizes[i] = other._sizes[i];
                    }
                }
                return *this;
            }

            WeightedQuickUnion& operator=(WeightedQuickUnion&& other) noexcept {
                if(this != &other) {
                    delete[] _values;
                    delete[] _parent;
                    delete[] _sizes;

                    _size = other._size;
                    _capacity = other._capacity;
                    _values = other._values;
                    _parent = other._parent;
                    _sizes = other._sizes;

                    other._values = nullptr;
                    other._parent = nullptr;
                    other._sizes = nullptr;
                    other._size = 0;
                    other._capacity = 0;
                }
                return *this;
            }

            ~WeightedQuickUnion() {
                delete[] _values;
                delete[] _parent;
                delete[] _sizes;
            }

            /// @brief Resizes the data structure to accommodate more elements O(n)
            /// @param new_capacity The new capacity of the data structure
            void resize(std::size_t new_capacity) {
                Value* new_values = new Value[new_capacity];
                std::size_t* new_parent = new std::size_t[new_capacity];
                std::size_t* new_sizes = new std::size_t[new_capacity];

                for(std::size_t i = 0; i < _size; ++i) {
                    new_values[i] = _values[i];
                    new_parent[i] = _parent[i];
                    new_sizes[i] = _sizes[i];
                }

                delete[] _values;
                delete[] _parent;
                delete[] _sizes;

                _values = new_values;
                _parent = new_parent;
                _sizes = new_sizes;
                _capacity = new_capacity;
            }

            /// @brief Inserts a new value into the data structure O(1)
            void insert(const Value& value) {
                if(_size >= _capacity) { resize(_capacity * 2); }

                _values[_size] = value;
                _parent[_size] = _size;
                _sizes[_size] = 1;
                ++_size;
            }

            /// @brief Finds the root of the element at index `p` O(log(n))
            std::size_t find(std::size_t p) const {
                if(p >= _size) { throw std::out_of_range("Index out of bounds"); }

                std::size_t root = p;
                while(root != _parent[root]) { root = _parent[root]; }

                while(p != root) {
                    std::size_t next = _parent[p];
                    _parent[p] = root;
                    p = next;
                }

                return root;
            }

            /// @brief Unifies the components containing elements at indices p and q O(log(n))
            void unify(std::size_t p, std::size_t q) {
                std::size_t rootP = find(p);
                std::size_t rootQ = find(q);
                if(rootP == rootQ) { return; }
                if(_sizes[rootP] < _sizes[rootQ]) {
                    _parent[rootP] = rootQ;
                    _sizes[rootQ] += _sizes[rootP];
                } else {
                    _parent[rootQ] = rootP;
                    _sizes[rootP] += _sizes[rootQ];
                }
            }

            /// @brief Returns the value associated with the element at index `index`
            Value value(std::size_t index) const {
                if(index >= _size) { throw std::out_of_range("Index out of bounds"); }
                
                return _values[index];
            }

            /// @brief Returns a reference to the value at the specified index
            Value& operator[](std::size_t index) {
                if(index >= _size) { throw std::out_of_range("Index out of bounds"); }

                return _values[index];
            }

            /// @brief Returns a const reference to the value at the specified index
            const Value& operator[](std::size_t index) const {
                if(index >= _size) { throw std::out_of_range("Index out of bounds"); }

                return _values[index];
            }

            /// @brief Returns a reference to the value associated with the parent of the element at index `p`
            Value& parent(std::size_t p) { return _values[find(p)]; }

            /// @brief Returns a const reference to the value associated with the parent of the element at index `p`
            const Value& parent(std::size_t p) const { return _values[find(p)]; }

            /// @brief Returns the size of the component containing the element at index `p`
            std::size_t sizeOf(std::size_t p) const { return _sizes[find(p)]; }

            /// @brief Returns a vector containing all values in the data structure
            std::vector<Value> values() const { return std::vector<Value>(_values, _values + _size); }

            std::size_t size() const { return _size; }

            std::size_t capacity() const { return _capacity; }
    };
}
