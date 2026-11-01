#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Node {
public:
    char ch;
    int freq;
    Node *left, *right;

    Node(char c, int f) {
        ch = c;
        freq = f;
        left = right = NULL;
    }
};

void printCodes(Node* root, string code) {
    if (!root) return;

    if (!root->left && !root->right) {
        cout << root->ch << " : ";
        cout << (code.length()==0 ? "0" : code) << endl;
        return;
    }

    printCodes(root->left, code + "0");
    printCodes(root->right, code + "1");
}

int main() {
    int n;
    cin >> n;

    vector<Node*> v;

    for (int i = 0; i < n; i++) {
        char ch;
        int freq;
        cin >> ch >> freq;

        v.push_back(new Node(ch, freq));
    }

    while (v.size() > 1) {
        sort(v.begin(), v.end(), [](Node* a, Node* b) {
            return a->freq < b->freq;
        });

        Node* left = v[0];
        Node* right = v[1];

        Node* parent = new Node('$', left->freq + right->freq);
        parent->left = left;
        parent->right = right;

        v.erase(v.begin(), v.begin() + 2);
        v.push_back(parent);
    }

    cout << "Huffman Codes:\n";
    printCodes(v[0], "");

    return 0;
}




// Enter number of characters: 4
// Enter character and frequency:
// A 5
// B 2
// C 1
// D 1



// Enter number of characters: 5
// Enter character and frequency:
// A 10
// B 20
// C 30
// D 40
// E 50