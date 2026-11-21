#include<vector>

namespace unionfind {
    
    template<typename Value>
    class QuickFind {
        std::vector<Value> values;
        std::vector<int> id;

        public:
            QuickFind(int size) : values(size), id(size) {
                for(int i = 0; i < size; ++i) { id[i] = i; }
            }

            QuickFind(const std::vector<Value>& values) : values(values), id(values.size()) {
                for(int i = 0; i < values.size(); ++i) { id[i] = i; }
            }

            QuickFind(const std::vector<Value>& values, const std::vector<int>& id) : values(values), id(id) {}

            QuickFind() = default;

            ~QuickFind() = default;

            void insert(const Value& value) {
                values.push_back(value);
                id.push_back(values.size() - 1);
            }

            int find(int p) const {
                return id[p];
            }

            void union_sets(int p, int q) {
                int pid = find(p);
                int qid = find(q);
                if(pid == qid) { return; }
                for(int i = 0; i < id.size(); ++i) {
                    if(id[i] == pid) { id[i] = qid; }
                }
            }

            Value get_value(int index) const {
                return values[index];
            }

            Value& operator[](int index) {
                return values[index];
            }

            const Value& operator[](int index) const {
                return values[index];
            }

            Value& parent(int p) {
                return values[find(p)];
            }

            const Value& parent(int p) const {
                return values[find(p)];
            }
    };

    template<typename Value>
    class QuickUnion {
        std::vector<Value> values;
        std::vector<int> parent;

        public:
            QuickUnion(int size) : values(size), parent(size) {
                for(int i = 0; i < size; ++i) { parent[i] = i; }
            }

            QuickUnion(const std::vector<Value>& values) : values(values), parent(values.size()) {
                for(int i = 0; i < values.size(); ++i) { parent[i] = i; }
            }

            QuickUnion(const std::vector<Value>& values, const std::vector<int>& parent) : values(values), parent(parent) {}

            QuickUnion() = default;

            ~QuickUnion() = default;

            void insert(const Value& value) {
                values.push_back(value);
                parent.push_back(values.size() - 1);
            }

            int find(int p) const {
                while(p != parent[p]) { p = parent[p]; }
                return p;
            }

            void union_sets(int p, int q) {
                int rootP = find(p);
                int rootQ = find(q);
                if(rootP == rootQ) { return; }
                parent[rootP] = rootQ;
            }

            Value get_value(int index) const {
                return values[index];
            }

            Value& operator[](int index) {
                return values[index];
            }

            const Value& operator[](int index) const {
                return values[index];
            }

            Value& parent_value(int p) {
                return values[find(p)];
            }

            const Value& parent_value(int p) const {
                return values[find(p)];
            }
    };

    template<typename Value>
    class WeightedQuickUnion {
        std::vector<Value> values;
        std::vector<int> parent;
        std::vector<int> size;

        public:
            WeightedQuickUnion(int size) : values(size), parent(size), size(size, 1) {
                for(int i = 0; i < size; ++i) {
                    parent[i] = i;
                    size[i] = 1;
                }
            }

            WeightedQuickUnion(const std::vector<Value>& values) : values(values), parent(values.size()), size(values.size(), 1) {
                for(int i = 0; i < values.size(); ++i) {
                    parent[i] = i;
                    size[i] = 1;
                }
            }

            WeightedQuickUnion(const std::vector<Value>& values, const std::vector<int>& parent, const std::vector<int>& size) : values(values), parent(parent), size(size) {}

            WeightedQuickUnion() = default;

            ~WeightedQuickUnion() = default;

            void insert(const Value& value) {
                values.push_back(value);
                parent.push_back(values.size() - 1);
                size.push_back(1);
            }

            int find(int p) const {
                while(p != parent[p]) { p = parent[p]; }
                return p;
            }

            void union_sets(int p, int q) {
                int rootP = find(p);
                int rootQ = find(q);
                if(rootP == rootQ) { return; }
                if(size[rootP] < size[rootQ]) {
                    parent[rootP] = rootQ;
                    size[rootQ] += size[rootP];
                } else {
                    parent[rootQ] = rootP;
                    size[rootP] += size[rootQ];
                }
            }

            Value get_value(int index) const {
                return values[index];
            }

            Value& operator[](int index) {
                return values[index];
            }

            const Value& operator[](int index) const {
                return values[index];
            }

            Value& parent_value(int p) {
                return values[find(p)];
            }

            const Value& parent_value(int p) const {
                return values[find(p)];
            }

            int get_size(int p) const {
                return size[find(p)];
            }
    };
}