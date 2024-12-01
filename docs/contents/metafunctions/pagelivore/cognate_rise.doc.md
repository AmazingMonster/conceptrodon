<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateRise`

<p style='text-align: right;'><a href="../../../index.md#list-modifications-3">To Index</a></p>

## Description

`Pagelivore::CognateRise` accepts an operation and returns a function.
When invoked, the function sorts the arguments in ascending order and instantiates the operation with the result.

<pre><code>   Operation
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> Operation&lt;V<sub>i<sub>0</sub></sub> &lt; V<sub>i<sub>1</sub></sub> &lt; ... &lt; V<sub>i<sub>n</sub></sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateRise ::   template<auto...> class...
              -> template<auto...>
```

## Structure

```C++
template<template<auto...> class>
struct CognateRise
{
    template<auto...>
    alias Rail = RESULT;
};
```

## Examples

We will sort `2, 2, 1, 0` and use the result to instantiate `Operation`.

```C++
template<auto...>
struct Operation;

using SupposedResult = Operation<0, 1, 2, 2>;

template<auto...Args>
using Metafunction = CognateRise<Operation>
::Page<Args...>;

using Result = Metafunction<0, 1, 2, 2>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`CognateRise` is inspired by the talk [Adapting C++20 Ranges Algorithms for Most Metaprogramming Needs in Fewer Than 1,000 Lines of Code](https://youtu.be/69PuizjrgBM?list=PLPqbaGB3rnNmIaWPvuu4U6LWt1XooNi-L) from Daisy Hollman and Kris Jusiak.

The primary mechanism is implemented within the helper function `arise`.
The talk [Understanding The constexpr 2-Step](https://youtu.be/_AefJX66io8?list=PLPqbaGB3rnNmIaWPvuu4U6LWt1XooNi-L) by Jason Turner provides a relatively detailed explanation of the usage of `std::array`. Here, we will only walk through general ideas.

```C++
template<template<auto...> class Operation, auto...Variables>
static consteval auto arise()
{    
    // `std::index_sequence<I...>` is created
    // for the length of `Variables...`.
    return []<size_t...I>(std::index_sequence<I...>)
    {
        constexpr auto sorted = []()
        {
            std::array original {Variables...};
            // `original` will be reused for the result.
            std::ranges::sort(original);
            return original;
        }();
        // We use `std::type_identity` to avoid construct
        // an object of type `Operation<*>`.
        return std::type_identity<Operation<sorted.at(I)...>> {};
    }(std::make_index_sequence<sizeof...(Variables)>{});
};
```

Finally, we will make an interface to accept arguments:

```C++
template<template<auto...> class Operation>
struct CognateRise
{
    template<auto...Variables>
    using Page = decltype(arise<Operation, Variables...>())
    ::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIM9KuADJ4DJgAcj4ARpjE/gDspAAOqAqETgwe3r7%2B0ilpjgIhYZEsMXFmiXaYDhlCBEzEBFk%2BfgG2mPaFDPWNBMUR0bEJtg1NLTntCmP9oYNlw5UAlLaoXsTI7BzmAMyhyN5YANQmO25ejrSEAJ6n2CYaAIK7%2B4eYJ2eNxEy3O/dPLwYBy8x1ObjEwBIhAQLDuD2eZj2QLeHzcyGm6CwVDhAKeAHoAFREglHRp4JRHYkEvHwgiYFhJAx0sF0hlMzBgpgXVAAOj5dyOByYCgURwA8klYkxuqRSdy%2BTyAGpkphRegKHGPabSvDIQUCaaYABuYjlRFJxHJmAgS3hJniFiOTpOT2dRzxeJOADYNBiQCBQlhVAB9JQARy8jE2YIAkgq4T6juTBcRMNLMOh4W6PUd%2BMQjgQEO96EZC0dUFRvRplZbVer4z6eVnnamCOsGCcAKxWTsAETBaQAXphgwQFTG7hA/QGGEHQ5gI1GOWc4/y/rbXc77VZN26nWgGIbVEl81zzQoSHT0B9e12e72bc29ycHU/n87p18fuXLcBQqbtxrPA60wBR43ifsdh3R53z3HMTB9KE/2YWgEI0I4AHc6FoI4YiOVMvCUa88wLIt8NArxaDHN9YOnb4jFA/0LyaCAkP/WhbSgmj31bdsfzwZCxFOaDYPtB9OJE98cwAdXeQj3jQ6cCGuSVgzwLBBBuNCC1QUkjVQdT9UPAhiC8BxuKdHNDHLKJtBqAhy0rZTJSrCUpW6MF4z%2BNCm13PdeOIDslJUkd1MYRxlLBNzvg8s5mKvHlpQgGMli8%2B4/hfKwIOEt8xKnAh0H9FgmAAa1C2dMBDcNIyBZc3CHTAKwVCAgJAhROPuV8IIku1sq43FHkJYkjg8YBmDpAAlK1KWJGknlZRl0xZelFuZT55TXbBBQMEVxUlGKMk1aZTIcEbUDG9MpqUXrJKdBb2U5DalRVNVQM1N1CNCYAjmUJhgAUnZbywA5nOtMlrrOaKdQEWVWtesDNptDcYOdf1QZygE%2Bug%2BEhqpPGqTmwaqSOAAVUCCFFAmcfxmmiUJ2kVoe9aiDS%2BFjrMhyodi7Gnk%2BowjiELwknyDMJooqibz29zDrODRZS4WUzEVuF%2BueebGaW5neT5R5iGADVvN5tJ%2BYAWUwBoqC8IFukl0bxswK66q5mX/kef1fv%2BsFdf11nVfhPnvrFhRKIc05bzNi2rdqAQwTlo4FaOJXE5VnmtQaRxkGDYUlBY6cFFYEdhTBIOQ9lQXhdSUXxYIO4JI4FZaE4TteD8DgtFIVBODcaxrCOC91k2E5ER4UgCE0euVhKkBO3iHkvUkABOHZ4i9YeuDMSpEkbjhJF4FgJA0OXW/bzuOF4BQQDlse2/r0g4FgGBEBANYCCSC5yEoNAGToWJwgLzhVAAA4vQAFp55HGAMgPUUgeRmF4BmQgUJCoK34IIEQYh2BSBkIIRQKh1A31ILoBWGFvhJE4DwBuTcW7jw7pwMUFw34OQrEcIBoDwGQOgZIWBRwIAeG/vQfMuwuBLF4NfLQKwIBIC/kkH%2BZAKAQGkbIkAwApBKxoFRWIF8IBRBoVEf8xBrjkN4Ho5gBixS2XskY0gX82CCDFAwWghiCFYCiF4YA4JaC0AvtwXgWBipGHEM4vAqZahGkYgQyqNQLhbBHqEOk2925XCiN8AxHgsA0JMngfePjSBhOIFESuvZ6SGGAFcIw48VhUAMPrRUeBMAYTcq3EeqDhCiHEFglpuC1A0KIfoEpKAe6WH0HgKIF9IArFQEkbo3iQEYjDqYSw1gzAnzyZaLAYybQdC6BkFws4Jh%2BAVsEOYpRyh6HyOkAQ%2ByzmpAuQwAYJzhgK2qNHHoMwrlPM6PZOoMx7lDDiE8t5nhWh6G1E0X5Cx/krH7hsTBlCODN1IMfXgp8WHALAZICBUD45cLMDw3AiDBHDxEaPCpKwixMCwHETZU9JA7B5EveIkgNCSACD6DQnYvQL30JwXepB947C4HPLgXpAEL0AcKzskguCdiXl6RFNDT7n0viSm%2BEjH6SOfgw9%2B8jFECL/mwTgjQWBGniCApg20SnxwXjyQV7cEFEDWXoFp6D2nSE6UobpBDdBKxIUwMhPi4UIqRbQjg9DX4XEchaY1przVCn5lwa1tqeF8JkQIoeOwzDErEbfDVurYgfwUagfhwwjUmpAXGlRC8uBy3UXSYgWidEEJMY0JxI9m1mIsQ4KxNjwr2McTQlxbiPFeKsX4kpgT274BCY4MJ3i7WqCiXSKxcTOg0KSSk64aStjt0ydkkeeSClKCKf40pX0Kl8GqQoWp9TGlWOdW0zBbrZBdPwe3b1fTykLKsEMpJGyJlTIyDMuZgMv1LJWbENZjFxlbK%2Bc4CArh3mkCOSUP51yCgZEQ%2Bc7o4LTkfO2QIXo4wgU5Dw7B15fQcOPNGH0RDoLZgoYhRIKFawYVMe5fC6hBCUWlpjRa%2BNiaeToQgPih16bhGiNJaQcllLKBwt5fy61zL4gyviPEHYLLJDzwVsGxVthlXZrVfADVL9GEFrzcQfVWwjXgJYAoI0eojQJp5OyaY8D8AOvUk62QLrH3YPkB619OgQA7FIL6/1FD2NBoVXQrVTDKzWYxbZ%2BzRxHPWpcw5XhRbU2xHTTsLN57c1ZdkWZorAiQD2eFsGVLwZ0tZ2ICweefA6B1obbo/RrbjHtfMXZLtOSe12IcU4ydmBXHuLECOnJY6Anbt8cEr5s6aGROQNE5dghV0EPXS2rdGTLR7t4AewpxSAlntVRev6V66kNMlE03g96MESCfTggLPTgsfuMIMmwv74D/umZwPEfpQOWGWci1ZYU/0wZebs9wxGDlIdnJR/5yQbndEw8jjICOQWfJeYR5oMPMf4fI2C45qGAU0bx6TonDHcPMYHrCyLnGT6cCjTZuzDmnPpbxe5kgYn8uqrJWmGTmzt7yf8NanYOxOydmZdWjQ4uV6APlVxzgSqr6SZpWYHkEuNCr2XiKwBqmzAK23jsBnyLlcqvEXCuBivGdnwtxPXJmidmSCAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/pagelivore/cognate_rise.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_rise.test.hpp)
