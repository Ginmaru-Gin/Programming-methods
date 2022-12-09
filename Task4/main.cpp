#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
#include <utility>

using   std::vector,
        std::pair,
        std::cout,
        std::cin,
        std::endl;


template <typename Type>
Type max_square (vector<pair<Type, Type>>& boxes) {
    size_t boxes_count = boxes.size();
    std::stack<int> st;
    st.push(0);

    vector<pair<Type, Type>> bounds(boxes_count);
    bounds[0] = {0, boxes[0].first};
    for (int i = 1; i < boxes_count; ++i) {
        bounds[i].first = bounds[i - 1].second;
        bounds[i].second = bounds[i].first + boxes[i].first;

        while (not st.empty() and boxes[i].second < boxes[st.top()].second) {
            bounds[i].first = bounds[st.top()].first;
            st.pop();
        }
        if (st.empty()) {
            st.push(i);
            continue;
        }
        if (boxes[i].second > boxes[st.top()].second) {
            bounds[st.top()].second = bounds[i].second;
            st.push(i);
        }
        else {
            bounds[i].first = bounds[st.top()].first;
            bounds[st.top()].second = bounds[i].second;
        }
    }

    Type result = 0;
    for (int i = 0; i < boxes_count; ++i) {
        result = std::max(result, (bounds[i].second - bounds[i].first) * boxes[i].second);
    }
    return result;
};

template <typename Type>
vector<pair<Type, Type>> input_boxes(std::istream& istream = cin) {
    unsigned count;
    vector<pair<Type, Type>> boxes;

    cout << "Enter count of boxes" << endl;
    istream >> count;
    cout << "Enter " << count << " boxes (pairs of width and height values separated by a space):" << endl;
    for (int i = 0; i < count; ++i) {
        Type width, height;
        istream >> width >> height;
        boxes.emplace_back(pair{width, height});
    }
    return boxes;
}

template <typename Type>
void print_boxes(vector<pair<Type, Type>>& boxes){
    for (auto box : boxes) {
        cout << box.first << ", " << box.second << endl;
    }
}

int main() {
    auto boxes = input_boxes<int> ();
    vector<int> v {1,2,6,3,4};
    cout << max_square(boxes) << endl;
    return 0;
}
