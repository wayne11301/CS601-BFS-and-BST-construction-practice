/*
Team members:
Name: Yi-Nong Wei, Vijayalaxmi Patil
*/

#include <iostream>
#include <queue>
#include <string>

using namespace std;

class node {
public:
    int val = NULL;
    node* ptrleft = nullptr;
    node* ptrright = nullptr;

    void add_value(int target) {
        if (target > val) {
            ptrright = new node();
            ptrright->val = target;
        }
        if (target < val) {
            ptrleft = new node();
            ptrleft->val = target;
        }
    }
};

// convert input string to integer
int get_number(string line) {
    int sum = 0, temp;
    char token;
    for (int i = 0; i < line.length(); i++) {
        if (line[i] != ',') {
            sum = sum * 10;
            token = line[i];
            temp = (int)token - '0';
            sum += temp;
        }
        else {
            break;
        }
    }
    return sum;
}

//print every node in the tree, debug purpose
void print(queue<node*> unvisit) {
    if (unvisit.front() == nullptr) return;
    while (!unvisit.empty()) {
        cout << unvisit.front()->val<<" ";
        if (unvisit.front()->ptrleft != nullptr) {
            unvisit.push(unvisit.front()->ptrleft);
        }

        if (unvisit.front()->ptrright != nullptr) {
            unvisit.push(unvisit.front()->ptrright);
        }
        unvisit.pop();
    }
}

//required bfs, return nullptr if target not fund, return a pointer to the target node if found.
node* bfs(node* root, int target) {
    if (root->val == NULL) return nullptr;

    queue<node*> unvisit;
    unvisit.push(root);

    while (!unvisit.empty()) {
        int to_compare = unvisit.front()->val;
        if (to_compare == target) return unvisit.front();
        if (unvisit.front()->ptrleft != nullptr) {
            unvisit.push(root->ptrleft);
        }

        if (unvisit.front()->ptrright != nullptr) {
            unvisit.push(root->ptrright);
        }
        unvisit.pop();
        if(!unvisit.empty()) root = unvisit.front();
    }
    return nullptr;
}


int main()
{
    bool first = true;
    string line;
    node* root = new node;
    node* current = new node;
    int front_int;
    int back_int;
    int target_int=0;
    int comma_position = 0;

    //queue<node*> tree;

    //prompt
    cout << "Please enter your tree: (enter * to stop expanding the tree)" << endl;

    while (getline(cin, line)) {
        if (line.front() == '*') {
            break;
        }

        //get the position of the 2nd integer in the input string
        for (int i = 0; i < line.length(); i++) {
            comma_position++;
            if (line[i] == ',') break;
        }

        front_int = get_number(line);
        back_int = get_number(line.substr(comma_position));

        //insert root
        if (first == true) {
            root->val = front_int;
            root->add_value(back_int);
            first = false;
        }
        //not root, insert edges to the tree
        else {
            current = bfs(root, front_int);
            current->add_value(back_int);
        }
        comma_position = 0;
    }

    //tree.push(root);
    //print(tree);

    cout << endl << "Please enter your target number: (enter # to start searching)" << endl;

    //get target integer
    while (getline(cin, line)) {
        if (line.front() == '#') break;
        target_int = get_number(line);
    }

    //find if there is a match
    current = bfs(root, target_int);

    //if no match
    if (current == nullptr) {
        cout << "Target value not found"<<endl;
    }
    //if there is match
    else {
        cout << "Target value found"<<endl;
    }

}

