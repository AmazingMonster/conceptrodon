<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateFoldLeftFirst`

## Description

`Pagelivore::CognateFoldLeftFirst` accepts an operation and returns a function.
When invoked, the function left-folds its argument list using the operation with the first argument as the initiator.

<pre><code>   Operation
-> V<sub>0</sub>, V<sub>1</sub>, V<sub>2</sub>..., V<sub>n</sub>
-> Operation&lt;...
   Operation&lt;
   Operation&lt;
       V<sub>0</sub>, V<sub>1</sub>
   &gt;::value, V<sub>2</sub>
   &gt;::value
   ..., V<sub>n</sub>&gt;::value</code></pre>

## Type Signature

```Haskell
CognateFoldLeftFirst ::   template<auto...> class...
                       -> auto...
                       -> auto
```

## Structure

```C++
template<template<auto...> class...>
struct CognateFoldLeftFirst
{
    template<auto...>
    alias Page
    {
        static constexpr auto value
        {RESULT};
    };
        
    template<auto...>
    static constexpr auto Page_v 
    {RESULT};
};
```

## Examples

We will left-fold 1, 3, 4 and 3 using subtraction.
The process can be described as follows:

```C++
   ((1-3)-4)-3
-> (-2-4)-3
-> (-6)-3
-> -9
```

```C++
template<auto A, auto B>
struct Subtract
{
    static constexpr auto value
    { A-B };
};

template<auto...Args>
using Metafunction 
= CognateFoldLeftFirst<Subtract>::Page<Args...>;

static_assert(Metafunction<1, 3, 4, 3>::value == -9);
```

## Implementation

We will implement `CognateFoldLeftFirst` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<template<auto...> class Operation>
struct CognateFoldLeftFirst
{
    template<auto...Variables>
    struct ProtoPage {};

    // Base Case:

    // Fold once.
    template<auto Initiator, auto Variable>
    struct ProtoPage<Initiator, Variable>
    {
        static constexpr auto value 
        { Operation<Initiator, Variable>::value };
    };

    // Fold twice.
    template<auto Initiator, auto First, auto Second>
    struct ProtoPage<Initiator, First, Second>
    {
        static constexpr auto value {
            Operation<
            Operation<
                Initiator, First
            >::value, Second
            >::value
        };
    };

    // Recursive Case:

    // Fold twice, handle the first three parameters,
    // and recurse using the rest.
    template<auto Initiator, auto First, auto Second, auto...Others>
    struct ProtoPage<Initiator, First, Second, Others...>
    {
        static constexpr auto value {
            ProtoPage<
                Operation<
                Operation<
                    Initiator, First
                >::value, Second
                >::value, Others...
            >::value
        };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKzSrgAyeAyYAHI%2BAEaYxCAAbADspAAOqAqETgwe3r566ZmOAqHhUSyx8f4Jtpj2xQxCBEzEBLk%2BfoG19dlNLQSlkTFxiSkKza3t%2BVy2EwNhQxUj1QCUtqhexMjsHASYLKkGeyYAzG57B0eYp25MXkQAdE%2Bn2ADUyAYKCq8A8qlxTAaLxMGgAguNiF4HK8PMBmHsAGKedDBTBUAgIvDEcYg0EmJJWMGvYmvC6HQHXM53R5PABqLTwTGi9AUwKJJIhUIIr2UxFQRGUTGAmFe%2BKsSQAIqdCXj2cSAPTy14WJhKGGq9i43Ek16K15I2joV4CbYPbUkslXG7U1CvACSDCygJIpFeNte9OIjOZlOw5uJnOhvP5qEFwpuDqdRDIHoZTPobNBOrF/p1r3GgLwyHeAnGmFUqWIbvutoAbmIvCLU8mCb9/sRMwII47HM6Y57vQmTtgQCBy94q5Lpan8VKTjLU3qDUaCAB3LOYM1y0n7cnHKkl%2B0txnR13uzHYgh7zdCTBoBjoRM6wPc4MCoWUtyR1u7/VY8au0/ny/dkcE6scs0jjZueeYFkW7r9pWor/suaYkn8AJAmcAHwYhDbIW4qHwSSz47i6b6Hthybdr2UGYJ%2BZ4CJecE4S8ZEVtctHEqOw7Lqx45asueoAEpnpsmSliKtxKCAXFJiSU7IqS87bK6CCGOg9CkggIo0IeKnEJgIqpC0rCYHs2KkJOSqKa8WnIAJIpeJkRgqSKWnjEuEnEpaFLWpueFtseRCER%2Bxa%2BV%2B1E%2BagTwPD8BCqdiV6AZCQZ8ve4ZnF5r4Hv5QUXq6EVRQoYUxSxsEuWmGbATmDBgYWAVloxMEyjhaZ3qGD43MROHoY2DAtcx9V1kh2RdUVPU4SlBFpQQrXwfRfaMZR34TWmU3kVlkVxLlzzdSRPbTQO2EcXVJJ7eJOpueutwlmFoLAFp%2ByMAQrK/suNlhMAPIPqKJwSjyCVNUlbiXddbCCGtZq/pxYKHeDYLygAVLDcPwwj8q4jDcOvAAKpg4zfPDSNQwj%2BM4%2BJJ2Pu6oIhcqiY3q8QheNEBANg4WqFdeQFZmVFUQZu5F/hYryggAtLzEN4kOYOyqCxMeTSDygsQwD3X6YJPXZACyBlMFQXgMA42SiuDH0wqgcIUtOqLomNNw03TDPjaRIBho%2Bsvy3loMTmCJVZgA%2BqqSitBAavNJr2uYTMrwnK60hh4tNWnGOn38wAnCs0ocGstCcP4vB%2BBwWikKgnBYZY1jphsWxVmYJw8KQBCaKnawANYBJIDwaJIXBJCcGj%2BBoZgJAkZgABwD/onCSLwLASBoGikNnuf5xwvAKCA081znqekHAsAwIgIAbAQqT3OQlBoAcdBxBE%2BmcKoA8JPzCSSK8wDINmUgPGYvCYPg0Z4Ogej8IIIgxDsCkDIQQigVDqDXqQXQMxZwNlSJwHgacM5Z1rnnTgPx7gH25KgKgrxr633vo/Z%2BrxX5mFeBADwp96BFnMJXFYvBV5aDWBAJAJ9UhnzIBQCA7DOEgGAFIMwfA6CGSXhAaIaDohhBaAAT0QbwKRzBiAyJ%2BNEbQZ5V5VxPoDAgPwGC0DkVArA0QvDAFuLQWgS9uC8CwCwQwwBxBGKxBovAQkrG53zPxPY8jyCCDqGg2geBogNmUR4LAaD6Z4AntY0gQliDRAyJgCU%2Bx7GBKMLXNYVADDy1pHgTAs5ELZyrv/YQohxAgJKeAtQaCYH6HsSgaw1h9BBKXpANYqBUgNCsfzcYP4JSmCLpYMwc84leiwK0iAaw7AuOcBAVwUw/AzBCAscolQCgZCyAIBZ6yijZEGKskYMxpk6wEH0SYngOh6GOQ0M58wyjDHiEcuY2ynn9H2Q8iQUzS7bE%2BSPDgmcZ5oPnvgm%2Bd8H5Pxfs3chEBcCEBIKKCuXAGHVwyWsVSTAsDxEmaQRukgTgPATicJIkhW5mEkAkKe1QE5/LHqQCelcHgJC4AkAeCcB7MsCFwfwhKaiz14PPRey8UVrxYdvVhu8sGH24bwmhF82CcBaCwUsSR%2BZMHeAYOyXAE4PC4C3D%2BX8SA/z/rIQB5TpCVKUNUqBughFwKYAg6xyD/moKgfPTB%2B97jGjwYq5Vqr1X2NIdq3VGgKFUI4TQhFJwzDIqYevcVMq4hHx4agahIwfUqo%2BPYrVXBp40FoKIygEioGKNkT4ktyjVHqIcD47Rt09EGLQcY0x5jLE%2BNsaknYud8AWUcG4tBnjLLeJiWEPY6coGBOCbIsJnbGFemiVXOJCSlDJLsUYNJoARV8GyQoXJ%2BTCk%2BJKaa4B5rZBVMgbnG1dT0kDKsJYZp0QJntM6dkbpvTY43usMM/loyf6Y3gFMuoMy/BzIvC80gyz7lLEeWkDZDQwOFE2Qwd5UGrmAZOY0Z5FzpjdCA7c5DazXnnLyIs2YbyVkfKResTYPzKNjoBXy9BHA3TECVSqtVmbNVBpbhQ2F0ZI1IsYai0g6LMWUCdbS%2Bl2rW5JG5UkDukgyX3xmAxgVtghWxtFfAcVe9sFJoTcQOVOxFVEJYAoUs2ZSxaoeFccY%2Bq4VjONQAspx7QHyEteenQIBw52odUgv59GgUYMlTg71LGTNmYs1Zmz3JKEpvDXESNJwY0ZI3mwuLnC9PpZoX2ZAqRUie0swnT20XvZhfNSI1ahbJHSOUWWmrKi1EaJrSmnR9bDFdswCYsxYhW0xPbWumdpBu0uL7VAgd9wdhVxHf48dQSQkyOnREudPjF2JJXak56KWslCh3Xkgp/wim8EPc5iQJ6wHuZqV5q9xhGl3onY%2BvOz7cycHlL0hpgyLBfrzj%2B8Z/6cPoZcKBrDJGIOLAIzB3ZWzgc7MQ/hw5/2bmYeI6hnopy5hw%2BgxmIjlzCN3LB4cr51HgFOoC66zgzGWDhfM68Qr1mKTjB4wa2hiLksirRZgDFIxsVjokyAMw2qTgnH8N3NuU9BdJBZYCsnC81MryE7i/wBL/AD17gnSQCcO5Eq4OHMdJwXVz04IJtnfz35S4NzLjTaw4mZGcJIIAA)

## Links

- [source code](../../../../conceptrodon/pagelivore/cognate_fold_left_first.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_fold_left_first.test.hpp)
