<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::CognateObserve`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-cognate-observe">To Index</a></p>

## Description

`Pagelivore::CognateObserve` accepts an operation and returns a function.
When invoked, the function collects the indices of the arguments that can be evaluated to `true` and instantiates the operation with the collection.

<pre><code>   Operation
-> ..., true<sub>i<sub>0</sub></sub>, ..., true<sub>i<sub>1</sub></sub>, ..., true<sub>i<sub>n</sub></sub>, ...
-> Operation&lt;i<sub>0</sub>, i<sub>1</sub>, ..., i<sub>n</sub>&gt;</code></pre>

## Type Signature

```Haskell
CognateObserve ::   template<auto...> class...
                 -> template<auto...>
```

## Structure

```C++
template<template<auto...> class...>
struct CognateObserve
{
    template<auto...>
    alias Page = RESULT;
};
```

## Examples

We will observe `0, 1, nullptr, 3.0` and use the result to instantiate `Operation`.

```C++
template<auto...>
struct Operation;

using SupposedResult = Operation
<
    static_cast<size_t>(1),
    static_cast<size_t>(3)
>;

using Result = CognateObserve<Operation>::Page<0, 1, nullptr, 3.0>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`CognateObserve` is inspired by the talk [Adapting C++20 Ranges Algorithms for Most Metaprogramming Needs in Fewer Than 1,000 Lines of Code](https://youtu.be/69PuizjrgBM?list=PLPqbaGB3rnNmIaWPvuu4U6LWt1XooNi-L) from Daisy Hollman and Kris Jusiak.

The primary mechanism is implemented within the helper function `stare`.
The talk [Understanding The constexpr 2-Step](https://youtu.be/_AefJX66io8?list=PLPqbaGB3rnNmIaWPvuu4U6LWt1XooNi-L) by Jason Turner provides a relatively detailed explanation of the usage of `std::array`. Here, we will only walk through general ideas.

```C++
template<template<auto...> class Operation, bool...Phenomena>
static consteval auto stare()
{
    // `std::index_sequence<I...>` is created
    // for the length of `Phenomena...`.
    return []<size_t...I>(std::index_sequence<I...>)
    {
        
        // `std::index_sequence<I...>` is created
        // for the count of `true` in `Phenomena...`.
        return []<size_t...J>(std::index_sequence<J...>)
        {
            constexpr auto result = []()
            {
                // We make `std::array phenomena` so that
                // we can access items of `Phenomena...` using [index].
                std::array phenomena {Phenomena...};

                // We will sort `std::array indices`.
                std::array indices {I...};
                
                // We will use this comparison function to sort.
                auto comp = [&phenomena](size_t i, size_t j)
                {
                    return
                    // If `phenomena[i]` is `true` and
                    // `phenomena[j]` is false, then `i` is less than `j`.
                    // Therefore, an index of `true` is always less
                    // than an index of `false`.
                    // As a result, indices of `true` will
                    // assemble in the front of the array.
                        (phenomena[i] && ! phenomena[j])
                    // If `phenomena[i]` and `phenomena[j]` are both `true`,
                    // then we return `i < j` to preserve relative positions.
                    ||  (phenomena[i] && phenomena[j] && i < j);
                };
                
                // `indices` will be reused for the result.
                std::ranges::sort(indices, comp);
                
                // return the result.
                return indices;
            }();

            // `result` is a `std::array`.
            // We collect its front part,
            // which contains all the indices of `true`.
            // Then, we instantiate `Operation`.
            // We return `std::type_identity` to avoid constructing
            // an object of type `Operation<*>`.
            return std::type_identity<Operation<result.at(J)...>> {};
        }(std::make_index_sequence<(...+Phenomena)>{});
    }(std::make_index_sequence<sizeof...(Phenomena)>{});
};
```

Finally, we will make an interface to accept arguments:

```C++
template<template<auto...> class Operation>
struct CognateObserve
{
    template<auto...Phenomena>
    using Page = decltype
    (stare<Operation, static_cast<bool>(Phenomena)...>())
    ::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCAAbAAcpAAOqAqETgwe3r566ZmOAqHhUSyx8Qlctpj2xQxCBEzEBLk%2BfoF2mA7ZTS0EpZExcYkpCs2t7fk1EwND5ZWJXACUtqhexMjsHOb%2BYcjeWADUJv5uXo60hACeZ9gmGgCCewdHmKfnLcRMd/4Pz1eDEOXhOZzcYmAJEICBY90eLzM%2B2B70%2BbmQE3QWCo8MBzwImBYqQMBPBBKJJMw4KYl1QADoGfdjocmAoFMcAPKpOJMBqkY7RVCeBl05QIRioNjMXFPOaOZDMgQTTAANzExxpRGOc2ImAgKwRJgA7FZnsdzccAPSW04JDSYkAgMJYVQAfSUAEcvIxtuCAJIi%2BF2454dnIXW8zDoBEWq02/jEY4EcXHehGZPHVBUW0aMUSqVMQN2ukxi26gibBinACsVmrABFwZkAF6YV0EEV%2B%2B4QB1Ohgu92YL0%2BqnnAOM/4Gs0W42mp6x2OlhdxnO952YN2e73A0duccl/4mYOh5kRgnR6fL63HBNJlNoLyCTPZo8aAjEb2vkNV195hiSxhC0ZYslwXctKxrOtG3OFs2w7BkACluzXfsN0HYcd3BBDA0nUDFxNPDl0VBhlVUVJE01VBjl1BQvFoAhPnrSCTAbfVCOXWd2KI81rwAdQ%2BFgmAAaw%2BV9e2%2BX5jlScV/wLL8FCo5NeS47jrwAdw%2BUQqyYZBtjZY42AqOJ2SzHM/wA5giw0Y4vEyIxIPXVQWPrEtL24hdxOIH4bikmSLKYU4TXMgtAyNaC5xUoi%2BI%2BNS6FobUSAYsSCHQR0JJ8508D019XPndzl087zv3wPTAosfdjXCyKOLc/KeJtfjjli2h4tsj5kxPNAiRaUMBBvR9ej6rUFNaXK6oXSjFSJRjmLMBJpPzQDnJ7PBW3bEN%2BVg9btCnPLxvNTjav281wOIBhqvc68/RfO0FtkpbazwZyvxPV930/YNDAvPbjota9Xzu/yWIsbRnuPdkqDEJR%2BWTRgcye8HU0wfSlJ/O1QZAo7juvAAVcVdQTTB%2BUMYqN2fHN3qpRGxDU352XoNkLtUm1UY1KtHPJ19IdoJQcqZqKbVlDVqORuiCH5TLStMt6Pyp6zmtofmrxtVklAqehvzvD4qGIWRydhjUvN%2BMbfu4iBAbkx7nNOObzASY4wDAXzFulWtQYbXbTdjK6bo0C2HosJ6Gy/L6c3912QbB6yWg%2BQUMxlj6NFIJWF2vWGqw0kWKzO%2BG0WODHrK1cjkbiFUPl1Ek8DLqSMiyJUTa9wK3GNNxzXNvzLcD627bt537oj92mJ7uaQzznazjnU3KonlOU/%2Bu1JeRr8FYFcvMDa9AbxILWRdo%2BiG/23sfiMZHHRGggIEXhR%2BS61IDX8Sffrnm1TqrA2aLFg/xtf4qsqXh%2BLqVTYgAvEP1mY5g/vRF67IArJVSiAdKfMsapwappTw9QQwEAhrrJ8qQBjJ2Qd7G0akEBZQQMRZoYQYEtR3lfTmdpKZILAQLY4eNGD8kzlQ5ogg8CRhzFyHkDQmHjWilnCCcDHQEBuNyV0eAsA8KkV%2BLUTAVSoDkcRCYH5ehGAuteEmqBojaB6AxUyUjuT8O5D8IR5wcIPExsw5cP9exmLbHIxgjhFHnAEVY7I4JIEdl5BABCKxbFMk4mFGeyCgG9kEiJWRqFNxDm3L6c4EBAyWGCoBe%2BDwCJhXvo/A6YUewpUdLE1xCT0LJN3LBLMIoICZOYNk8J9Z8mGgiSAl4%2BJCTEkjGSbplJqS0lscyAw%2BlvG8l8YeZ4mivAOGOB4YAzACQcmiEoYgZc2kFKTP03pXwhkMgaUwGUsZbJhGAMcZQTBgCiX8ExLAhwXGgWKTHcE4y%2BTamaPKV0ogJjgkFJ4bshyQkTmwPqT2FpJHSNHBFdpEVniWgAFRIuRSi1FloESIuRaw5GWDjgovRfC1FRL8WGi6RSXZEJ9kHgBLKd6cy3mTLhU8U59khBeFSIUKMAAlUW9EZoMoEIac4oE5RZW%2BayAgTZVpwW7KsAhP1RXIHFb8mC0r2zdn8LteEHSEQsvOTyveSVbnzNQIsyMKy1kbK8ZYiZgr/iOkudc8ESdjg1GOAwOitBUjvn5P4OkGhtVMsVa6VWcQL69gUKwNsrJwQGrFvyNlHKMjct5ZK3CD8OBrFoJwasvA/AcC0KQVAnBm6WGsAlTY2wbb%2BB4KQAgmhM1rCEiAasRo6QJEkAATn8EaBISIuBcDMGYI0Rp9CcEkLwFgEgNBJ3zYW4tHBeAKBAEnetBbM2kDgLAGAiAQAbAIKkS45BKC3zoHECIUbOCqCSAkAAtB244wBdKuskHSMwvAoyEGhKlGo/BBAiDEOwKQMhBCKBUOoddpBdA1DUj8VInAeBZpzXmhtRbOAckuIekx2Zr13ofU%2BhUUg33HAgB4IkZ7Ex7FWLwNdWg1gQCQKe%2BgZAKAQCY6MYAUgzB8DoASYgy6IDRFQ9EMILQbgId4CJ5gxAbgrKMQ4CTpAupSgIByBgtBxOQawNELwwAIQtWXdwXgWBBJGHEFpvAupehl0M4WjcPRLg7FrWEAk2bIPXGiD8GTHgsCoffHgKdRnSBl2IIKJQ9ZCSGGANcIwDa1hUAMMABQAA1PAmA1ICPzbWv9whRDiGAzlsDahUPQf0FFlA1hrD6DwKs%2BAaxUDeuyIZ29mIzj1lMGWywZh50heIG45dkA1jdEGn4CArhph%2BBqCEMIwwjLxBqIUOuORPAdAKLXBoCwRjzdqPUPokw2grZmDt4xe35gzcWKMWY%2B2Jt6B1IMc7W2JBDY2FsIDSGOC5tIHO3gC7ji4fvZIR9z6iNmBI7gL9lH%2B0rBo3FtY4omBYHiPqUgzbJB%2Bu7UaSQGhJBmEkHaDQ1YEidrHRwCdpAp01vbVwZInakjU%2BrJILg1Zu0JC%2B6hhdS6V11ri5undDG92YaPax9jxAL1sE4C0FgKojS3oCiyeyXBO10i4P6j9%2BAiB9Z/SB3LgGJDSEK0oYrkHdDcdg0weDRn3ufe%2B2hjgGGD2XHJpL6XsuRlRddUrlX1lSOSlSBR6tZhofc/XfRxjvuKPHrY%2BH5jCDiBS5l/LzjnauBJxoPRYylAhOQak2JxTOeZNyeMYp5T7i1MadQ9p3T%2BmeaKZM1F8zhb8BWccDZ1D9nkCOcUy5uoqGPNeZuD5nYhb/OBdrSFsLmAIumei2cnnCWrkpbSxl7kWXeA5YA/l/XsgisQcLSbsrsWOtWEsNV2rg2i2NaVJwFrKU2tH%2BsN1n7vX%2Bt1eOyNlw/YbtTf7Jtuba2ijZBf5pDrbZC/5LCzB1AnYCD9BTCHaTZv4NAwH3ZlCPZXYDBAF3ZgGXbPaVpvYk7W7s6cCGzx6u6J4e7K7%2Bpg7q7bxUZB60aNqkDw6I6UDvZk4U5K7VhcD%2BCSC9pGjVj%2BAaD%2BBzQaCs424c62Bc70H0Z85ID7pYaR4i5i47CS4PosAKAqgKgqiK50iUgTBq4Q5yJ6Dr55ZAZb6gaG6746ABCkBm4W6Ib4EoaQYLr25YZO5x6qHqGaHaG6EMQ%2B7kbMbVqaow4h6bph7%2BFxAKHR6jAaEcquhaGdqug%2BEhruH668YZ6CbCaiYyZ55ZGyaGJF5BYl6CBl6aaN6YA6Z6ZiA15BZ15mZD7GaWYnat6Qbt6d5Bbd5uaFp95iaD5%2BZ9aj68Dj7JpT716z4hHz5JapbpaZaKbGG64Fbb4WElbWEGCH6VYn4eYDbI4NYNCGaWgOj35dY9ZxCa6nzn7DYNAf7uBwF6DTYoF/4LYgECBAGLYbYPYPEIGnawF5DwEXFfHIGzbgG2DXY3FoGtBYHzY4GvZPYOFs5OFEEqGA5qEaHHDxE6GRgTBUEQ7VrUbB50Zw6YAI6jDI5uZsEgBmBJB0g3qdp9rVgaB07VicFdrSBiGcCc6rqw4o4gA450j%2BB0l9o9rJBJAjpmA1Bub%2BCOHzpsl4kMFubvpwlSmLoykrBrAhaZDOCSBAA)

## Links

- [source code](../../../../conceptrodon/descend/pagelivore/cognate_observe.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/cognate_observe.test.hpp)
