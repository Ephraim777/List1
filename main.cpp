#include <catch2/catch_test_macros.hpp>

#define CATCH_CONFIG_RUNNER
#include <cstdint>

#include <iostream>

struct ListNode
{
public:
    ListNode(int value, ListNode* prev = nullptr, ListNode* next = nullptr)
        : value(value), prev(prev), next(next)
    {
        if (prev != nullptr) prev->next = this;
        if (next != nullptr) next->prev = this;
    }

public:
    int value;
    ListNode* prev;
    ListNode* next;
};


class List
{
public:
    List()
        : m_head(new ListNode(static_cast<int>(0))), m_size(0),
        m_tail(new ListNode(0, m_head))
    {
    }

    virtual ~List()
    {
        Clear();
        delete m_head;
        delete m_tail;
    }

    bool Empty() { return m_size == 0; }

    unsigned long Size() { return m_size; }

    void PushFront(int value)
    {
        new ListNode(value, m_head, m_head->next);
        ++m_size;
    }

    void PushBack(int value)
    {
        new ListNode(value, m_tail->prev, m_tail);
        ++m_size;
    }

    int PopFront()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_head->next->next);
        int ret = node->value;
        delete node;
        return ret;
    }

    int PopBack()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_tail);
        int ret = node->value;
        delete node;
        return ret;
    }

    void Clear()
    {
        auto current = m_head->next;
        while (current != m_tail)
        {
            current = current->next;
            delete extractPrev(current);
       

        }
    }

private:
    ListNode* extractPrev(ListNode* node)
    {
        auto target = node->prev;
        target->prev->next = target->next;
        target->next->prev = target->prev;
        --m_size;
        return target;
    }

private:
    ListNode* m_head;
    ListNode* m_tail;
    unsigned long m_size;
};

TEST_CASE("Testing", "List") {

    SECTION("Test Empty")
    {
        List MyList;
        INFO("List is not empty\n");
        CHECK(MyList.Empty());

    }

    SECTION("Test size")
    {
       
        List MyList;
        MyList.PushFront(1);
        INFO("Expected size: 1, Actual size: " << MyList.Size());
        CHECK(MyList.Size() == 1);
    }

    SECTION("Test clear")
    {

        List MyList;
        MyList.PushFront(1);
        INFO("Expected size: 1, Actual size: " << MyList.Size());
        CHECK(MyList.Size() == 1);
        MyList.PushBack(3);
        MyList.PushBack(4);
        MyList.PushBack(5);
        MyList.PushBack(6);
        MyList.PushBack(7);
        MyList.Clear();
        INFO("Expected size: 0, Actual size: " << MyList.Size());
        CHECK(MyList.Size() == 0);
        


    }
    
}
