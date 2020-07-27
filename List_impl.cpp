#include "List_impl.h"
#include <map>
#include <utility>
#include <vector>
#include <iostream>
#include <cassert>

namespace {
    constexpr int NULLPTR_SYMBOL = -1;
}

void List::Serialize(FILE *file) {
    std::map<ListNode *, size_t> map{{nullptr, NULLPTR_SYMBOL}};
    fwrite(&count, sizeof(int), 1, file);
    if (ferror(file)) {
        throw std::runtime_error("I/O error.");
    }

    size_t index = 0;
    for (ListNode* it = head; it != nullptr; it = it->next, ++index) {
        size_t size = it->data.size();
        fwrite(&size, sizeof(size), 1, file);
        if (ferror(file)) {
            throw std::runtime_error("I/O error.");
        }

        fwrite(it->data.data(), sizeof(char), it->data.size(), file);
        if (ferror(file)) {
            throw std::runtime_error("I/O error.");
        }

        map[it] = index;
    }

    for (ListNode* i = head; i != nullptr; i = i->next) {
        fwrite(&map[i->rand], sizeof(size_t), 1, file);
        if (ferror(file)) {
            throw std::runtime_error("I/O error.");
        }
    }
}

void List::Deserialize(FILE *file) {
    clear();
    std::vector<ListNode *> list;
    int tmp_count = 0;

    fread(&tmp_count, sizeof(int), 1, file);
    if (ferror(file)) {
        throw std::runtime_error("I/O error.");
    }
    if (tmp_count < 0) {
        clear();
        throw std::runtime_error("File format error.");
    }

    list.reserve(tmp_count);
    for (int i = 0; i < tmp_count; ++i) {
        size_t size = -1;
        fread(&size, sizeof(size), 1, file);
        if (ferror(file)) {
            clear();
            throw std::runtime_error("I/O error.");
        }
        auto tmp = create_node_tail();
        tmp->data.resize(size+1);
        list.push_back(tmp);

        fread((void *) tmp->data.c_str(), sizeof(char), size, file);
        if (ferror(file)) {
            clear();
            throw std::runtime_error("I/O error.");
        }
    }
    
    auto it_node = head;
    for (int i = 0; i < tmp_count; ++i, it_node = it_node->next) {
        size_t index;
        fread(&index, sizeof(size_t), 1, file);

        if (index == NULLPTR_SYMBOL) {
            continue;
        } else if (index > tmp_count) {
            clear();
            throw std::runtime_error("File format error.");
        }
        it_node->rand = list[index];
    }

    assert(tmp_count == count);
}

List::List()
    : head(nullptr)
    , tail(nullptr)
    , count(0) {
    auto tmp = create_node_tail();
    tmp->data = "First list";

    tmp = create_node_tail();
    tmp->data = "Second list";
    auto tmp1 = tmp;

    tmp = create_node_tail();
    tmp->data = "Third.list";

    tmp = create_node_tail();
    tmp->data = "4 list";
    tmp->rand = tmp1;
}

ListNode *List::create_node_tail() {
    auto newNode = new ListNode();
    if (head) {
        tail->next = newNode;
        newNode->prev = tail;
    } else {
        head = newNode;
    }
    tail = newNode;
    newNode->rand = nullptr;
    ++count;
    return newNode;
}

void List::clear() {
    count = 0;
    while (head) {
        auto tmp = head;
        head = tmp->next;
        delete tmp;
    }
    tail = nullptr;
}

List::~List() {
    clear();
}
