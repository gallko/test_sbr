#ifndef TEST_LIST_IMPL_H
#define TEST_LIST_IMPL_H

#include <string>

struct ListNode {
    ListNode*   prev;
    ListNode*   next;
    ListNode*   rand;

    std::string data;
};

class List {
public:
    List();
    void Serialize(FILE* file);
    void Deserialize(FILE* file);

    void push_back(const std::string& );

private:
    ListNode*   head;
    ListNode*   tail;
    int count;

    ListNode* create_node_end();
};


#endif //TEST_LIST_IMPL_H
