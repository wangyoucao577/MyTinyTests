
#include "heaps_test.h"

#include <iostream>
#include <queue>
#include <boost/heap/d_ary_heap.hpp>
#include <boost/heap/fibonacci_heap.hpp>

namespace heaps_test {
    struct HeapNode {
        int key;
        std::string payload;
    };

    bool operator< (const HeapNode& a, const HeapNode& b) {
        return a.key < b.key;
    }

    void heaps_test() {
        
        //NOTE: std::priority_queue and boost::heap::d_ary_heap have different
        // behavior while handle duplicate key: will have different order of duplicate key.

        std::vector<HeapNode> test_nodes;
        test_nodes.emplace_back(HeapNode{1, "node_1"});
        test_nodes.emplace_back(HeapNode{2, "node_2"});
        test_nodes.emplace_back(HeapNode{3, "node_3"});
        test_nodes.emplace_back(HeapNode{4, "node_4"});
        test_nodes.emplace_back(HeapNode{4, "node_4-duplicate"});
        test_nodes.emplace_back(HeapNode{5, "node_5"});

        // std::priority_queue
        std::priority_queue<HeapNode> std_pq;

        // boost::heap::d_ary_heap
        boost::heap::d_ary_heap<HeapNode, boost::heap::arity<2>> boost_2ary_heap;

        boost::heap::fibonacci_heap<HeapNode> boost_fibonacci_heap;

        for (auto &v: test_nodes) {
            std_pq.push(v);
            boost_2ary_heap.push(v);
            boost_fibonacci_heap.push(v);
        }

        std::cout << "std priority queue   : {";
        while (!std_pq.empty()) {
            std::cout << "{" << std_pq.top().key << "," << std_pq.top().payload << "},";
            std_pq.pop();
        }
        std::cout << "}" << std::endl;
        std::cout << "boost_2ary_heap      : {";
        while (!boost_2ary_heap.empty()) {
            std::cout << "{" << boost_2ary_heap.top().key << "," << boost_2ary_heap.top().payload << "},";
            boost_2ary_heap.pop();
        }
        std::cout << "}" << std::endl;
        std::cout << "boost_fibonacci_heap : {";
        while (!boost_fibonacci_heap.empty()) {
            std::cout << "{" << boost_fibonacci_heap.top().key << "," << boost_fibonacci_heap.top().payload << "},";
            boost_fibonacci_heap.pop();
        }
        std::cout << "}" << std::endl;

    }
}
