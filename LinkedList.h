
#pragma once
#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>
#include <algorithm>

template <typename T>
class LinkedList {
    struct Node {
        T     val;
        Node* prev;
        Node* next;
        explicit Node(const T& v = T{}) : val(v), prev(this), next(this) {}
    };

    Node        head;     // sentinel ring: head.next -> first, head.prev -> last
    std::size_t n = 0;

    static void link(Node* a, Node* b) { a->next = b; b->prev = a; }

    void insert_between(Node* x, Node* left, Node* right) {
        link(left, x); link(x, right); ++n;
    }
    T remove_node(Node* x) {
        T v = std::move(x->val);
        link(x->prev, x->next);
        delete x; --n; return v;
    }
    // pos in [0..n] for insert (n -> &head), [0..n-1] for erase/update
    Node* node_at(std::size_t pos) const {
        if (pos > n) throw std::out_of_range("LinkedList::node_at");
        Node* p;
        if (pos <= n/2) { p = head.next; for (std::size_t i=0;i<pos;++i) p = p->next; }
        else            { p = const_cast<Node*>(&head); for (std::size_t i=n;i>pos;--i) p = p->prev; }
        return p; // when pos==n returns &head
    }

public:
    LinkedList() = default;
    ~LinkedList() { clear(); }

    bool        empty() const { return n == 0; }
    std::size_t size()  const { return n;     }

    void clear() {
        Node* cur = head.next;
        while (cur != &head) { Node* nxt = cur->next; delete cur; cur = nxt; }
        head.next = head.prev = &head; n = 0;
    }

    // ---- ends ----
    void push_front(const T& v) { insert_between(new Node(v), &head, head.next); }
    void push_back (const T& v) { insert_between(new Node(v), head.prev, &head); }

    T pop_front() {
        if (empty()) throw std::out_of_range("LinkedList::pop_front");
        return remove_node(head.next);
    }
    T pop_back() {
        if (empty()) throw std::out_of_range("LinkedList::pop_back");
        return remove_node(head.prev);
    }

    const T& front() const {
        if (empty()) throw std::out_of_range("LinkedList::front");
        return head.next->val;
    }
    const T& back() const {
        if (empty()) throw std::out_of_range("LinkedList::back");
        return head.prev->val;
    }

    // ---- index ops ----
    void insert_at(std::size_t pos, const T& v) {
        if (pos > n) throw std::out_of_range("LinkedList::insert_at");
        Node* where = node_at(pos);
        insert_between(new Node(v), where->prev, where);
    }
    T erase_at(std::size_t pos) {
        if (pos >= n) throw std::out_of_range("LinkedList::erase_at");
        return remove_node(node_at(pos));
    }
    void update_at(std::size_t pos, const T& v) {
        if (pos >= n) throw std::out_of_range("LinkedList::update_at");
        node_at(pos)->val = v;
    }

    // ---- rearrange: stable sort by < ----
    void rearrange() {
        if (n < 2) return;
        std::vector<T> tmp; tmp.reserve(n);
        for (Node* p=head.next; p!=&head; p=p->next) tmp.push_back(p->val);
        std::stable_sort(tmp.begin(), tmp.end());
        std::size_t i=0; for (Node* p=head.next; p!=&head; p=p->next) p->val = tmp[i++];
    }

    // ---- simple forward iterator (for internal use) ----
    struct iterator {
        Node* p;
        bool operator!=(const iterator& o) const { return p != o.p; }
        iterator& operator++() { p = p->next; return *this; }
        T& operator*() const { return p->val; }
    };
    iterator begin() { return iterator{head.next}; }
    iterator end()   { return iterator{const_cast<Node*>(&head)}; }
};
