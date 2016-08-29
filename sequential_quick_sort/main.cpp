#include <iostream>
#include <list>

template <typename T>
std::list<T> sequential_quick_sort(std::list<T> input)
{
    if ( input.empty() ) {
        return input;
    }
    
    std::list<T> rv;
    rv.splice(rv.begin(), input, input.begin());
    
    T const & pivot = *rv.begin();
    auto devide_point = std::partition(input.begin(), input.end(), [&](T const & t) {
        return t < pivot;
    });
    
    std::list<T> lower_part;
    lower_part.splice(lower_part.end(), input, input.begin(), devide_point);
    
    auto new_lower { sequential_quick_sort(std::move(lower_part)) };
    auto new_higher { sequential_quick_sort(std::move(input)) };
    
    rv.splice(rv.end(), new_higher);
    rv.splice(rv.begin(), new_lower);
    
    return rv;
}

int main(int argc, const char * argv[]) {
    
    std::list<ssize_t> list {5, 7, 3, 4, 1, 9, 2, 8, 10, 6};
    auto result = sequential_quick_sort(list);
    
    auto output_iterator = std::ostream_iterator<ssize_t>(std::cout, " ");
    std::copy(result.begin(), result.end(), output_iterator);
    
    return 0;
}
