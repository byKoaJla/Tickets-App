
#pragma once
#include <type_traits>

namespace Db {
    class Atom;

    template <typename  St>
    requires std::is_base_of_v<Atom, St>
    class Store;
};
