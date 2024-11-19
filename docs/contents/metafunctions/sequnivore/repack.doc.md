<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Sequnivore::Repack`

## Description

`Sequnivore::Repack` accepts a list of packed sequences and returns a function.
When invoked by an operation, the function concatenates the packed sequences and instantiates the operation with the result.

<pre><code>   ...Sequence<sub><i>i</i></sub>&lt;Variables<sub><i>i</i></sub>...&gt;...
-> Operation
-> Operation&lt;Variables<sub><i>0</i></sub>..., Variables<sub><i>1</i></sub>..., ...></code></pre>

`Sequnivore::Repack` can also handle `std::integer_sequence`. The function first `static_cast` integers to `std::make_signed_t<size_t>`. Then, it uses the result to invoke an operation.
<pre><code>   ...Sequence<sub><i>i</i></sub>&lt;Type<sub><i>i</i></sub>, Variables<sub><i>i</i></sub>...&gt;...
-> Operation
-> Operation&lt;(size_t)Variables<sub><i>0</i></sub>..., (size_t)Variables<sub><i>1</i></sub>..., ...></code></pre>

## Type Signature

```Haskell
Repack :: typename... -> template<auto...>
```

## Structure

```C++
template<typename...>
struct Repack
{
    template<template<auto...> class>
    alias Rail = RESULT;

    template<template<auto...> class>
    using UniRail = RESULT;
};
```

## Examples

Here, we first concatenate `std::integer_sequence<int, 0>`,  `std::index_sequence<1, 2>` and `std::index_sequence<3>`. Then we pack the result into `Sequence`:

```C++
template<std::make_signed_t<std::size_t>...Args>
requires (sizeof...(Args) == 4)
struct Sequence;

using SupposedResult = Sequence<0, 1, 2, 3>;

using Result = Repack
<
    std::integer_sequence<int, 0>, 
    std::index_sequence<1, 2>,
    std::index_sequence<3>
>::Road<Sequence>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Sequnivore::Repack` is implemented similarly to [`Sequnivore::TypicalPaste`](./typical_paste.doc.md). Intermediate results are kept in `Shuttle` or `std::integer_sequence<std::make_signed_t<size_t>, *>`.
After all variables are collected, the `Operation` will be invoked.

A simplified version will be as follows:

```C++
#include <utility>

template<auto...>
struct Shuttle;

template<typename...>
struct Repack {};

// Base Case:

template<template<auto...> class Sequence, auto...Variables>
struct Repack<Sequence<Variables...>>
{
    template<template<auto...> class Operation>
    using UniRoad = Operation<Variables...>;
};

template<template<typename, auto...> class Sequence, typename Type, auto...Variables>
struct Repack<Sequence<Type, Variables...>>
{
    template<template<auto...> class Operation>
    using UniRoad = Operation<static_cast<std::size_t>(Variables)...>;
};

// Recursive Case:

template
<
    template<auto...> class SequenceA,
    template<auto...> class SequenceB,
    auto...VariableAs, 
    auto...VariableBs,
    typename...Others
>
struct Repack<SequenceA<VariableAs...>, SequenceB<VariableBs...>, Others...>
{
    template<template<typename...> class Operation>
    using UniRoad = Repack
    <
        Shuttle<VariableAs..., VariableBs...>,
        Others...
    >::template UniRoad<Operation>;
};

template
<
    template<typename, auto...> class SequenceA,
    template<typename, auto...> class SequenceB,
    typename TA,
    typename TB,
    auto...VariableAs, 
    auto...VariableBs,
    typename...Others
>
struct Repack<SequenceA<TA, VariableAs...>, SequenceB<TB, VariableBs...>, Others...>
{
    template<template<auto...> class Operation>
    using UniRoad = Repack
    <
        std::integer_sequence<std::make_signed_t<std::size_t>, VariableAs..., VariableBs...>,
        Others...
    >::template UniRoad<Operation>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIAAcZqQADqgKhE4MHt6%2BehlZjgLhkTEs8YkAbACctpj2JQxCBEzEBHk%2BfkENTTmt7QRl0XEJyakKbR1dBVy208MRo5XjdQCUtqhexMjsHOaBEcjeWADUJoFuXo60hACel9gmGgCCL68EmCxpBl%2BXbiYN1QADowU8PlNiF4HGchAgbgR6JcrG8Pl8fn9MACCPc0oxWJgwSCIW8oTCCGcAEqYNJMZAAawuAHYrMyACIoj4fAD0PLOFiYSjhXzSIG5bwxvyY/yuUqxAKBRGJTzOJyFCjhmAAjl5GHtSGclaCwQA1dp4JixegKUmvcmwml0xkAoQ6vUMPYA83ES3WzAKFWBZ7B7msj5nSNneUy7Fy77S2WA4FB7BqgwKTUAeXxxBlOTtUbOXiyRjOcgYeCpqCY6AugXZZxzCXzAm9FqtNtTXLRHJ770lCYV8cxsZxeIJbENxtT6Y1Wt1%2Bswhtx%2BOYbDOABUJ9OU2aO/7baGyQRoY7afSGa73UuAdv8YafX6u%2BDQ8f3uG3kWY0mf3Hk8qr5puqmZNrmrYMIWUYlhEwDlpW1a1vWjbNnmzQAlM%2BbIAA%2BqIUwYQQ6AgCAWQAF6YNhBBPBAT6dgG6zdoEqIfpyTESq8fLUpgyA7FkABumAirS4pooOo7/GiVwRlGf6KnuJLBnOoFuounqYK8pDSZGslXDOQFKZqKkensNhaUa8m0f69qGmZekgpZ9AWAomlfjJE7rkSYJZgQCAJLaknPCeZ6Uk6l7XqpezvFcDnqYGQGGkZS5WNFB6OXFCnYIa3m%2BcQ6V2iYn6vN%2BQ5jiOib/quk6eRlBlgS26HvkWMFlhWVY1nWlyNqFLquZGAJmUW8KIsiKW%2BnR9rEo%2BqWYE5qYuUVRZRtlfkqr19bYMRf7wW1tYAqhEEQmxvascx6IlRJUVuGZOluJVHm7oBNUgYZN5qRp13nRV7mEg9JpPRmL0RTN83ft9G6bu9a13YSW6mWtdkxdZFzwxZ01OSDblroSxLLbl3Lvg6IUXi6VyJW9d4aWciN5cGCWvSZd42FTaM05lTY%2BStQFhsxxXiRVn1yY9qrPXVaEFo10GlnBrWIR1DZcc6V5rf1a1FlMREgBEXzAAk2FKEDBEaywTAMhRWTAJE6CUYbxFkRRVG08zY1WelU3O2lc0DUtHO5atC19cGm2fdtst7eBDUhqdfZHQOHEAFQJ4nSc8ryiebtgQibonKdvDySf53HOexzd6vEcbpt63gFuYFbDtuKXJF4OR1vBsSrzEMAR6Be37p4MQAZnBAduoFQxIQO3nfrMhnVnJI6yQqeFILsZcanW8zVwUIXhpEUNc0goXi0JSM9k16VwaIa8xnKkZyBIda%2BvBvXEH0fyEK2FklXWtDda5gOvEHrem/4taGg0E8Gy39CLEQiFgVQgCDZXCvmYcBZkf4MFgfAleAI77vieMRGW7VwpYLfA/TCjgcIagSAQIeUCSKEmwkKAE%2B9D4EAStvXe6BmFHyePPJiHBNi0E4P4XgfhuC8FQJwK6lhrBnAUNsXYglDg8FIAQTQ/DNgMgCP4EEgR/BcDMEkDQgRqjMjqEESQ/h9CcEkLwFgEgNAX1EVoUgEiOC8AUCAC%2BqiOBaE2HAWAMBEAgG2AQNINxyCUDQD8OgCQoiEk4KoJI1QAC01RJBnGAMgZAZwpAgjMLwGuhASB4CIvMfgggRBiHYFIGQghFAqHUD4nQegADueYxRiIEUIkRaiXGcCzDcMJlIR5nESSktJGSsk5MkHkweHhon0GIBcMwgQuDrF4N43xpAIBICiWkGJZAKAQD2QckAwApCpBoEfPylBYi9NiBEdo9xODKIecwYg9wsyxG0NxbxyiolsEEFmBgtBnlNNIFgWIXhgCAloLQDxYiIXfEMMAcQ4L8D9wcHgASCLnGYFUNxG4%2BxlG/0EeCu4sQ8wfI8FgXpp48B2MRQJYgsRMiYHZMiowdwjBqM2FQAwndTR4EwC05sojlHlOEKIcQNTJX1LUL03Q8wDA8tMNIyw%2Bg8CxA8ZATYqA0jNARck9WnU1VWEsGYZxqBmW%2BiwDqiAmw7C/JyC4dBsw/DzDCMsCoVRCiZGyAId1frig5BGD68Y8wnVYoEIMGYnhuh6Cjc0WNSxyhjESJGxYQbM1DDDemiQjr5F7ALVYjgwjSBOPEZwUZSTUnpMydk3JZhB64CKUspR6yVG8s2L5Ws4wHWkE0ZIQIIJaiBGZJIDQkgzCSGqA4/wdRS02NIHY1ZIJqhcGqEkWoSRN3%2BEkFwfwY7qgVt6a49xniu1NL8YEnZwTBnhKOScxZcS2CcHaCwPizJklMDnGWLgtQQRcBBHi/ARBbV6ElZUmV0g5VKAVeC3QqQ2lMA6TwLpZaengtcQM0JNwzgjI/V%2Bn9f64IAaAyBuZqAFkJGWYEMwnbNn8O2bs6j%2BzFkROOWx05RHv3qiMABrgF8rlfFyrc%2B5jyPkvN4G8p5XyfkOGk6QAFjACDAtBb0yF0LYXwqU1gY2XL9jOIxc6nFvT8WEq%2BEp0lvSKVUvuDSozGzfSMuUcy1lSgOUGdRbBXlfABUKCFSKsVSmoPSuqbB2Q8rGnOKQ/oFFKBrDWE1dq%2BAeqDU5CNSahsZrrCWvETakpAY0t9Gdc4CArhs0hHQXm1YGb0j%2BuaFVooAaGC1d9ZGxoZWWhZvjXMUr0aeu5u9fmnNcb8geoWMNtNdWS1yJ2MWtZpby2Vr6RwI0xBP3ft/fxsjgHgMaBbWBkgdG1kbO7aQXtWBEgDrJcu1dgGp3MiPcyZkgRp2zoPae7DnAL1eL8/4oJIShmcefbE%2BJHAP0TJYAoPi2S%2BLkaxFMApx2INlNkNBiLtT5DwZi804IKG0PMbJSts9/SH3DKoBtlg0PYfw8R7GKYVGaPtpWYERjAPWMs9B9xxZIA4c72wgj2o2EkcEAYZttJfA6CiY8RAO54LZNScRUrz53zflKZU0CkFYLjOYChTCsQunEX6ZRWi4zfdTPFfBRZniVnEU2fJVq%2Bzjm6UuaU%2B5tlXmze%2Bevf5pggrhWirXKFjH4WJCRbqbjxVIBggquMEljVFL7XpcNZwHkpdcsWqtYVu1JWk0uoq26vrk2vUzY6w1kNgaS/Bta%2B1iNA3k29Ym4mrrg2U31/q5hcbCaxuppWB1wtC3qkYdJz99bUP0kw7h2cYXIIxdHbbadjn16e2YD7TdjD92QBmEA4EXR/gp1CaMeOrd32rW/dsJepj6wNEgEkDMtJSRmQAeqPRwIU7qj%2BEsWSwIWGL9uJXq%2BIYb5Ln5VqAE36bDMpZDOCSBAA)

## Links

- [source code](../../../../conceptrodon/descend/sequnivore/repack.hpp)
- [unit test](../../../../tests/unit/sequnivore/repack.test.hpp)
