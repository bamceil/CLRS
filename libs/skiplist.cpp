#include "skiplist.hpp"

#include <iostream>
#include <random>

namespace CLRS {

void skip_list::insert(int value) {
    update_array updating(MAXLEVEL);
    pointer x = header_;

    for (int i = level_; i >= 0; --i) {
        while (x->next_[i] && x->next_[i]->value_ < value) x = x->next_[i];
        updating[i] = x;
    }
    x = x->next_[0];

    int newLevel = random_level();
    if (newLevel > level_) {
        for (int i = level_ + 1; i <= newLevel; ++i) {
            updating[i] = header_;
        }
        level_ = newLevel;
    }
    x.reset(new skip_list_node(newLevel + 1, value));
    for (int i = 0; i <= newLevel; ++i) {
        x->next_[i] = updating[i]->next_[i];
        updating[i]->next_[i] = x;
    }
    ++count_;
}

void skip_list::remove(int value) {
    update_array updating(MAXLEVEL);
    pointer x = header_;

    for (int i = level_; i >= 0; --i) {
        while (x->next_[i]->value_ < value) x = x->next_[i];
        updating[i] = x;
    }
    x = x->next_[0];

    if (x->value_ == value) {
        for (int i = 0; i <= level_; ++i) {
            if (updating[i]->next_[i] != x) break;
            updating[i]->next_[i] = x->next_[i];
        }
        x.reset();
        while (level_ > 0 && !header_->next_[level_]) level_ -= 1;
        --count_;
    }
}

bool skip_list::contains(int value) const {
    pointer x = header_;
    for (int i = level_; i >= 0; --i) {
        while (x->next_[i] && x->next_[i]->value_ < value) x = x->next_[i];
    }
    x = x->next_[0];
    return x->value_ == value;
}

template <typename Func>
void skip_list::walk(const Func& f) const {
    pointer x = header_->next_[0];
    while (x) {
        f(x->value_);
        x = x->next_[0];
    }
}

int skip_list::random_level() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, MAXLEVEL - 1);

    return dis(gen);
}

}  // namespace CLRS

int main(int argc, char const* argv[]) {
    using namespace std;
    using namespace CLRS;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(-1000, 1000);

    skip_list list;
    while (list.size() < 1000) list.insert(dis(gen));
    cout << "Size: " << list.size() << endl;

    for (int i = 0; i < 100; ++i) {
        list.remove(i);
    }
    cout << "Size: " << list.size() << endl;

    return 0;
}
