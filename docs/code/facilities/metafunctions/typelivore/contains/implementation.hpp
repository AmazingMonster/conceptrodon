/**********************/
/**** Dependencies ****/
/**********************/

#include <type_traits>

/************************/
/**** Implementation ****/
/************************/

template<typename...Elements>
struct Contains
{
    template<typename Inspecting>
    struct ProtoMold
    {   
        static constexpr bool value 
        {(...||(std::is_same_v<Elements, Inspecting>))};
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

/*****************/
/**** Example ****/
/*****************/

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Contains<int, int*, int**, int**>
::Mold<Args...>;

/**** Tests ****/
static_assert(Metafunction<int*>::value);
static_assert(! Metafunction<void>::value);