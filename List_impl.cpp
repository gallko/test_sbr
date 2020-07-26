#include "List_impl.h"
#include <map>
#include <vector>
#include <iostream>

void List::Serialize(FILE *file) {
    std::map<ListNode *, int> map{{nullptr, -1}};
    std::vector<int> rand_list;

    fprintf(file, "%d;", count);

    int index = 0;
    for (ListNode* i = head; i != nullptr; i = i->next, ++index) {
        fprintf(file, "%lu:%s", i->data.size(), i->data.data());
        if (!i) {
            map[i] = index;
        }
    }

    for (ListNode* i = head; i != nullptr; i = i->next) {
        fprintf(file, "%d;", map[i->rand]);
    }

}

void List::Deserialize(FILE *file) {
    std::map<ListNode *, int> map{{nullptr, -1}};

    if (fscanf(file, "%d;", &count) != 1) {
        std::cerr << "File format error." << std::endl;
    }

    for (int i = 0; i < count; ++i) {
        size_t size = -1;
        if (fscanf(file, "%lu:", &size) != 1) {
            std::cerr << "File format error." << std::endl;
        }
        auto tmp = create_node_end();
        tmp->data.resize(size+1);
        if (fread((void *) tmp->data.c_str(), sizeof(char), size, file) != size) {
            std::cerr << "File format error." << std::endl;
        }
    }

    return;
}

List::List() {
    head = new ListNode();
    head->data = "First\n list";

    head->next = new ListNode();
    head->next->data = "Second \11\02list";
    head->next->rand = head;

    head->next->next = new ListNode();
    head->next->next->data = "3.list;";

    count = 3;
}

ListNode *List::create_node_end() {


    return nullptr;
}
