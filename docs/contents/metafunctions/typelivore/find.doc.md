<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Find`

## Description

`Typelivore::Find` accepts a list of elements and returns a function.
When invoked by predicates, the function returns the index of the first element that satisfies all predicates, or `-1` if it cannot find the element.

<pre><code>   Arguments...
-> Predicates...
-> Found ?
   index : -1</code></pre>

## Type Signature

```Haskell
Find ::   typename...
       -> template<typename...> class...
       -> auto
```

## Structure

```C++
template<typename...>
struct Find
{
    template<template<typename...> class...>
    alias Road = RESULT;

    template<template<typename...> class...>
    static constexpr std::make_signed_t<size_t>
    Road_v {RESULT};
};
```

## Examples

We will find the indices of `int**` and `void` in list `int，int*，int**，int***`.

```C++
template<typename Element>
struct IsIntDoubleStar
: public std::is_same<Element, int**> {};

template<typename Element>
struct IsVoid
: public std::is_same<Element, void> {};

template<template<typename...> class...Args>
using Metafunction = Find<int, int*, int**, int**>
::Road<Args...>;

static_assert(Metafunction<IsIntDoubleStar>::value == 2);
static_assert(Metafunction<IsVoid>::value == -1);
```

## Implementation

We will implement `Find` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<typename...>
struct Find
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
    { static constexpr auto value {-1}; };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

template<typename First>
struct Find<First>
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {   
        static constexpr auto value 
        {
            []() -> std::make_signed_t<size_t>
            {
                if constexpr ((...&&Predicates<First>::value))
                { return 0; }

                else
                { return -1; }
            }()
        };
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

template<typename First, typename Second, typename...Others>
struct Find<First, Second, Others...>
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {   
        static constexpr auto value 
        {
            []() -> std::make_signed_t<size_t>
            {
                if constexpr
                ((...&&Predicates<First>::value))
                { return 0; }

                else if constexpr
                ((...&&Predicates<Second>::value))
                { return 1; }

                else if constexpr
                (
                    Find<Others...>
                    ::template ProtoRoad<Predicates...>
                    ::value != -1
                )
                { 
                    return 2 + Find<Others...>
                    ::template ProtoRoad<Predicates...>
                    ::value; 
                }

                else
                { return -1; }
            }()
        };
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCAA7NIADqgKhE4MHt6%2BAaSp6Y4CoeFRLLHxSbaY9kUMQgRMxATZPn6BdpgOmQ1NBCWRMXGJ0gqNza25HeP9YYPlw0kAlLaoXsTI7Bzm/mHI3lgA1Cb%2Bbl6OtIQAnifYJhoAgjt7B5jHp8hj6FhUt/dPjwImBYyQMQJObgIV2SjFYmAAdIi/o8xsQvA5DgAxMLof4mBJWR6HYmHIEgsGYCFk0FMcGnKEw5hsRHw26HfZMBQKFnKYiYfCiIEKZEPEmHVHogiHXmoIgAJVQTFxRJJ%2BIs4sajmQ7IEY0wqmSxEOTHOqEOADcxF43mqALRcfEAERO6qdLrxKuJ1IpVOBNLpkOhsOZSP82HZBi5LIewD5wMYBGFYf%2BYq86SMhwVSvejulxFlqCzuNOMbjbEE3NDd38hKeCWdNY9D29tMp9KDTLe2OIYxFEox2IYxbc3d7yceapTJJbAZnbcDjLhLLZHKjiN5/LwgswSbuno1aIxMvliuVotVBNV%2B7FY1pW51DD1BqNJqIFqtNuvF9rYt/qoArFY/6OhASyHLabJfCAIAsEwADWmAAPrpMA4ToIhBAQukABeSGYeO55/mKk5fkRJJ4FQD5PoahxQMuZgAGzmAxG4Cq2SYjngPb4dg0GWt4mBLEsU5kX%2BaqHHyBDrAwhwaC6xz1k2olETUSgicp34SZgUnEDJ9ryW6pG/k6oHqcRimNvubqWQChGkn6Pr0g5rZUh2S5VhGnKVvCpaYPGFYiqm6bAJmp45nmBZFhCvn%2BYmy7JjZ1m1v8c6uYubBYlxYykKSbkZUIXQCOgOUMsGCKIgA8gQCBxLu/z9lKg7DqOBA5QVaBDjlVU1T28V7nWP7Ts5s7DfOpWdn1nlrvCrFbuxgUkg1EUnkq6nicSZmLZq94ddRL6mu%2BAnHEZJF2WRJiARdIFgRBYYaug0GwQhyF4Kh/IYVheC4R9BEaQpg1/cSFFUUCz60RA9FMYxs3bhxLW3HxH5CZtyniZJ0myQZikTkZZGqW8wO7aDNF0UijHMTD82nO1RUIyA/HWsjuNEWj2kYw6NYKc6ONnRp%2BOHITurE8QKOiRAot/U1ELdbVfUSxp0FzsthanhClNCnLzPKYjR1gGAJy5vpWu/sJxvma6ZtEejumHGYxyWJlQ7S9VstVvL2sgErx4q6tpzqzumu84Dhw69aBmWxt2O2cHxL4%2B7xmXtbekc66Ud/SZptB1z7pWRZyX7qlTnki57bpeVrJ3au3kxeWiYLcSaZhCFRbhd7UUlrGfm195fyJXnTYAPQAFQj6PY8D/8w8jwAKtgQjT6PE%2BPFPY/j02zwMPsXhHBC5x0NcIopaNaVlYc2D0LXfYEIeUoAJIKLfgiOms0T0L0IuPCAhzJF4r/3lBIA8AKGQnCCE59Yo5TCAQEebJJz9x5oXBcp9wGXwIkte%2BAA1VAeAzxfx/n/bUACgEgLYGAi%2BCYcrmmwcWcMcCGz52bMfIu/oxp5XLiuSM1diDADqo8RuGYACy2kmBUC8JvOo4UpanCgZAwQQ9ZHQPkQLORQ8RTQXbm4B43Ce4JQYbeLUiEvJxAIBAIRjRRHiMyBCe%2Bj8CDP1/m/cYdMGY2n8A2XMZhhI2X0VuQxXJjGmOERY7oAhrEKCwTg5xH4cwG3AlwLxFgOArFoJwf8vA/DcF4KgTgbhrDWHFGsDYNozD%2BB4KQAgmgkkrDgiAf8CR4T%2BAABwMQSP4FpGgmmtIAJyBBSRwSQvAWASA0BoUgGStCkGyRwXgCgQCjIqRwLQKw4CwBgIgEAawCA/1ahQCAaAQR0DiBEOEnBVDNNtAxSQhxgDIG1FIeEZheCbiIMQHBeh%2BCCBEGIdgUgZCCEUCodQiydB6AAO7ECYMkTgPBkmpPSZUyZnAKrnG2YcVAlEzkMQuVcm5dzJAPNoh4A59AjQ7HibwBZSzSAQCQPs5IhyyC7LpQykAwApBmD4HQIEPZKDRARdEMITQrjQt4AK5gxArgVWiNoLoCyyn7NrhVBgtBhXAtIFgaIXhgBuDELQWZmT1XAkMMAcQar8B8m6OaHcCL9RdHOFsMpUCagIsuNECFEqPBYARdfPAQyDVWuINENImBHRGqMJcIwlSVhUAMDwjBeBMCgoqoyEVfzhCiHEL8j58glBqARboLg%2BhjUoDyZYfQeBoizMgCsVAyQ6j6ttF8A2phLDWDMBM1AAbXlYCraBaotRMguCHJMPwhaQhzDKBUPQBQMgCBHdOtIs6GADEncMQtnQQn1BmPO9dNRZU9BmCuoY8R13bs8G0PQt5mhHoWCelYChCmbAkLCjgaSxkIqmYcTF2Lrm3MOPcu2EBcCEBIPbUpSwKVRpWDVJUww%2B01MkP4eEPSkgaEkGYSQDERn/gYl0/QnABmkCGaU%2BEDEuAMUaV0xp5H/ySC4P%2BHpDF31qqmTMuZ5So3UrWTSjZKLzjkEoMyklxy2CcCaCwc0CRbRME8hmLgXT4RcHhBM55JA3mFuzV8zN0hs0ArzWq3QHLwWQpFS%2Bt94yslIr41KdFxpiASakzJjkcmFNKY0IS1AxK4hgc8ZB4FyzaWefpSSgTeygssvE5J20zm2VdK4KMmgtBuWzIgHytVYqhWpoyxKqVMqHCpoVQmJVKqEUaq1Tq2gerU1YFguGrYEzzX7qtfqlTqg7VAlTU6vpEzXXuquJ6%2BrFLXl%2BrKQGoNShQ21ZNU3TjMamBxoTUmlNBrNMZp%2BTp2QemgUTMM0WyNLarBltdb2mtdbMgNqbW4g7baO1dpwda6t/b93OAgK4HdQQhw3qnYWmddR3u/cyF9tdT3N3vxaOe3Iu6B0CDB0Dk9tgz05FHQjvocPn2rHWE%2B%2BJ%2BHX3wpY5wOzDnpOyZCvJxTynaLAZeWB8lHH/PQcwLB%2BIfa%2BmEeIwptDCQGMJFaehzDdHmMds4Gx%2BZnGVnrM2ds0LQmjknI4OJy5hwWAKHNNqc0ZOKRjCefgF56m01afW2mrb%2Ba8jGahZkszeOhccGRVs84aLKIK6ucr1XFoNfsSlBAIlwXvM7H8BBunVKeMy8ZYJ8LJL6bIGSMkRC6uumIU1wQQx9nLmcqS7VXl/LBUSqy9nyV0rZUFc84q5VqqGuYE1dq3V%2Bqyk1eNaahrXEmvWrVba5A9rOuCGdWq3rQqBveuG6msbwbJv15m/5vgsbwmLeTYwVNq3vkSA2/83N22QW9OLddo7FaTuTLO7qTgA8oJb4sO2rJd2e3wHvXuzdQ73AQ%2BR%2BO0ox6F2FEyP9xddQ0dQ%2Be1uvo72N06hYcJ0X9T1/8H9L1D0QDb10cH1McflLdBdLMOBCdFcXc1d3chRPcqdQMyUA9KUqlSAYMsBmcX02cQAzAFN/B/B/x/w0N4sOl/AEgKMkDEVplbB2MCChJSAEMzBSMuB/BGJBCukyNGINAEgcd/ArdkC/MlkX1HlWDWNA9CCA10hnBJAgA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/find.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/find.test.hpp)
