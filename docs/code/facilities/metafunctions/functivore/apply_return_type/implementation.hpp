/************************/
/**** Implementation ****/
/************************/

template <typename Ret>
struct ApplyReturnType
{
    template<typename...Args>
    using Mold = Ret(Args...);
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

static_assert
(
    std::same_as
    <
        ApplyReturnType<int>::Mold<int, int*, int**>,
        int(int, int*, int**)
    >
);
