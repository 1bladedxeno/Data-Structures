namespace binarysearchtrees {
    template<typename Key, typename Value>
    class BST {
        struct Node {
            Key key;
            Value value;
            Node* left;
            Node* right;

            Node(Key k, Value v) : key(k), value(v), left(nullptr), right(nullptr) {}
        };

        Node* root;

        public:
            BST() : root(nullptr) {}

            ~BST() {
                clear(root);
            }

            void insert(const Value& key) {
                root = insert(root, key);
            }

            bool search(const Value& key) const {
                return search(root, key);
            }

            void remove(const Value& key) {
                root = remove(root, key);
            }
    };
}