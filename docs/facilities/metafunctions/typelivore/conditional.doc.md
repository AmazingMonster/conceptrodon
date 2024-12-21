<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Conditional`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-conditional">To Index</a></p>

## Description

`Typelivore::Conditional` accepts two elements and returns several functions.
Check out **Examples** for more details.
Overall, `Conditional` yields one of the two elements according to the boolean evaluation of a condition.

<pre><code>   IfTrue, IfFalse
-> Arg
-> Arg ? IfTrue : IfFalse</code></pre>

<pre><code>   IfTrue, IfFalse
-> Arg
-> Arg::value ? IfTrue : IfFalse</code></pre>

<pre><code>   IfTrue, IfFalse
-> Preds...
-> Args...
-> (...&&Preds&lt;Args...&gt;::value) ?
   IfTrue : IfFalse</code></pre>

## Type Signature

```Haskell
Conditional
 :: typename...
 -> template<auto...>
```

```Haskell
Conditional
 :: typename...
 -> template<typename...>
```

```Haskell
Conditional
 :: typename... 
 -> template<typename...> class...
 -> template<typename...>
```

```Haskell
Conditional
 :: typename... 
 -> template<auto...> class...
 -> template<auto...>
```

## Structure

```C++
template<typename, typename>
struct Conditional
{
    template<auto...>
    alias Page = RESULT;

    template<typename...>
    alias Mold = RESULT;

    template<template<typename...> class...>
    alias Road
    {
        template<typename...>
        alias Mold = RESULT;
    };

    template<template<auto...> class...>
    alias Rail
    {
        template<auto...>
        alias Page = RESULT;
    };
};
```

## Examples

We will see four examples that present different use cases of `Typelivore::Conditional`:

```C++
struct IfTrue;

struct IfFalse;

using Select = Conditional<IfTrue, IfFalse>;
```

- The template member `Page` of `Select` is a function that returns `IfTrue` if all arguments can be evaluated as `true`.
Otherwise, it returns `IfFalse`.

```C++
static_assert(std::same_as<Select::Page<1, 2>, IfTrue>);
static_assert(std::same_as<Select::Page<0, 2>, IfFalse>);
```

- The template member `Mold` of `Select` is a function that returns `IfTrue` if the value results of the arguments can all be evaluated as `true`.
Otherwise, it returns `IfFalse`.

```C++
static_assert(std::same_as
<
    Select::Mold
    <
        std::integral_constant<int, 1>, 
        std::integral_constant<int, 2>
    >, 
    IfTrue
>);

static_assert(std::same_as
<
    Select::Mold
    <
        std::integral_constant<int, 0>, 
        std::integral_constant<int, 2>
    >, 
    IfFalse
>);
```

- `Select::Road` accepts a list of predicates and returns a function.
When invoked, the function returns `IfTrue` if the argument list satisfies all of the predicates;
otherwise, the function returns `IfFalse`.

```C++
struct VoidInt;

template<typename...>
struct VoidTester: public std::false_type {};

template<>
struct VoidTester<void>: public std::true_type {};

template<>
struct VoidTester<VoidInt>: public std::true_type {};

template<typename...>
struct IntTester: public std::false_type {};

template<>
struct IntTester<int>: public std::true_type {};

template<>
struct IntTester<VoidInt>: public std::true_type {};

template<typename...Args>
using Metafunction = Select
::Road<VoidTester, IntTester>
::Mold<Args...>;

static_assert(std::same_as<Metafunction<int>, IfFalse>);
static_assert(std::same_as<Metafunction<void>, IfFalse>);
static_assert(std::same_as<Metafunction<VoidInt>, IfTrue>);
static_assert(std::same_as<Select::Road<>::Mold<>, IfTrue>);
```

- `Select::Rail` accepts a list of predicates and returns a function.
When invoked, the function returns `IfTrue` if the argument list satisfies all of the predicates;
otherwise, the function returns `IfFalse`.

```C++
template<auto...>
struct NonpositiveTester: public std::false_type {};

template<auto I>
requires (I <= 0)
struct NonpositiveTester<I>: public std::true_type {};

template<auto...>
struct NonnegativeTester: public std::false_type {};

template<auto I>
requires (0 <= I)
struct NonnegativeTester<I>: public std::true_type {};

template<auto...Args>
using Metafunction_1 = Select
::Rail<NonpositiveTester, NonnegativeTester>
::Page<Args...>;

static_assert(std::same_as<Metafunction_1<-1>, IfFalse>);
static_assert(std::same_as<Metafunction_1<1>, IfFalse>);
static_assert(std::same_as<Metafunction_1<0>, IfTrue>);
static_assert(std::same_as<Select::Rail<>::Page<>, IfTrue>);
```

## Implementation

The implementation is straightforward. [Check out this test to see how it works.](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEjaSuADJ4DJgAcj4ARpjEEmYA7KQADqgKhE4MHt6%2B/ilpGQIhYZEsMXFcibaY9o4CQgRMxATZPn5cAXaYDpkNTQTFEdGx8UkKjc2tuR22EwOhQ2UjlQkAlLaoXsTI7BwEmCzJBvsmAMxuBACeyYysmADUAJJUACrEXpik91c3zGxPVAAYmIlGdsCYNABBcbvBz3DwMfB1Zi0CGQkwJKxQ%2B4474HI5ME7nJheIhgtG4%2B4wrxwgAimEadHuGKsCVpZyx6OxuP2h2OmDObhJRCe5O5OOImAAjl48JKFKLxVSCLCCPd6YzUedHmLIZSWfcvOkjN9rg8zrSAW8PhzmWyOWiKTz8fzBcLUKLTuClZKZXLMAqIGAwI9Vk6cdS6QymHRBTqveG7RZDcbgKabszTpbnsDaKDTsmMeyC46oaWuXrnXzCQLiaTUAA6JuQ4CSg6MAgKXWUo2hNPKJjAc1Z9XR2PnCBNhvmABss/GhLwyAA%2BqJxoKoqhPGCIC222xBApVmGvSAQD9a5zy%2BXKbyCUSLma/pgp9h6AfO93cb2TQBZTzoJmloajGWpuJOTazvOjSOCua4EBuW5atgEBvu2h5ngAbmIHzHmCZ4Xg6ZbERWiZ3q65zkTWgoXs%2BU5gvcyAGAoChTsokr4KI%2BxdgmSqRmq7GoEQABKqBMOgiYsomt4utRlFPncr7vh2PHepWlI4j%2Bab/rQgEWqOmqChB05mHOpkLrBq5MOu5ybtuXoQOxmCcTWPFuGhH6sZBp4gNh3iYHhPmESWSpFkRFYydWD5UdFClsPRXqMcxXkNk5LncV%2BmmpvconiUB9yCSJYkSecaVLq5CXgiF6nMiRN5VvetYXLJD7upVSXWSlZVcQGmXKqqBXEEJqDCaBkmYtJDUUUK9ZTgAak0eBMFE9CqZNWV9gVg7DsBY5gcZUHmTBS5WTZbh2chjkceVGXnAtxBLStAaVVhOEBSe2AEWa4X6va1X6kqMVNUDbqzd52AdSxbHXT1a1KlpOWgflhUjWNpUwxV4PhWF1VogA9AAVETxMk3j%2BPEy82BCC8xNk1ChMk4zdOkWYpyhExXhYJmbhoAwOzJJ%2BvEVvxVrvJe5YizmILiyRCNCDU3RqvpCJIpkYhxq8YtfFLea1lVV703j9wvAGaoaBLx0rp1sQEBA4zoGeCh3Mu1mCvLtRngOQ6ClwXxmGC2uazaXonpyFkndbzR2wQDsgE7bAu257uK5722CgE9z%2B16ge5vm2Ch%2BWeNGyb4z3FwFuLlbLE29Hsfx5gieOucibJw4Z46RJoXN0qlL22eoT7K2YirgIC6CIKA9fOX2e1TVvcx/3giYEPtAjwwY8Ieck%2BZ31Aez5SzzWgKZYh9jULh1XShR33cfO67J9uC3CttyAHeSd3c%2B4jfA/L8Qw%2B8xvCeggvjmxnutZUscf4rzXoArewCd5C31GApUOtQQn3zmfSERdjamx3iREWc1UB4HQI8ceuMoQg3kr8RSWNz4qhpGqQhxCS77DiPcZIXgVpLggWeKg0tlwXiTDjA2kJKGPyFgQoh6AWGxEFJhKR%2BF2GcNoNwm%2B9CG6CKkn9ERYjdSSOYabWRd0pGkM3p9JRXDkA8PPGLARZohHaPLGI2iNDpwSPoXCUxMi2EcMsdYvhus7EZi0cWHRLUmp6I8WqLxhjiBALMSACxKirFqNsZoiajiSK6PcQNGJ4wjFuCYSQsh5jfHJOseooJ5oMmhKceEmicUXzNmIMAOGkIEa/mjFQLwfNkT5VbghKEZ5colUKVI7x2tBDeN1O3ACgpIQtJSuSch0JLaJyvrbG%2B9dG7nE6Y0bpvTMjxL3qgvWBc6GV3WTXLZd83J7KYAcnoAg5EKJnqcsE5zVmXMjpshet8E6u12V0npTyGCCiKaYk5QcznhQvlc6%2BfztmArcAM4ZxVBT4VfnM5ubzoUfMwdglh9xTh1Kik1NqtDVkDWUAURwmFMDeMSWU1RfyAlKCqQ42pWT6l1hFPGNSvpZTynuBADQ3MnhhjodS2leB6XTO1Io5lKS/mVPSayLlFYxEUrcWpEW4QBBhGAIuOVsSmXKJZbHNlGj7EhMwVq%2BsnoBXSiFQGEVYqMUjlDGiPVBrl7GoZbEuMirzXKtjqqm1NS7U8pmkQKcCzWm6g6cCw5AhlxcH6c/QZkJhlozcDS9IdKA35LIPcfVDBDX%2BvlWpVO3tzjxqWQmFZcKfm10drcwU9zHnIjTenKFucYXVWbdXBFdd21Av2SC7t083AAFpp7YBztLfFg61ktpuQCu5ybQU9vOPOwOR9l1h1XcO35o6N1u0zTm8c4jPogC9hE3FB7T4Fg4OsWgnAACsvA/DcF4KgTgj9LDWCpJsbY5pWY8FIAQTQr71gAGsQAfskA2DQkguAJFOBoD9GhTIzjMAADnw/oTgkheAsH8AEH9WhSD/o4LwBQIAAjQY4FodYcBYAwEQCATYBAOEEHIJQNAhw6CxHCHcTgqh8MzhnTOSQ9xgDICsVIBsZheDOUICQYheh%2BCCBEGIdgUgZCCEUCodQLGdB6AAO5/2SJwHgb7P3fpgzRzgAB5UkfH7ioCoPcST0nZPycU2XZDZgRUeGE/QYgzIIOrF4Mx1jpAIBICE8kETZAKAQBS2lkAwApBmD4HQVhDGIBRGc1EUITRLh2d4OV5gxBLiuaiNoFOv7SBCY/K5hgtAqvmdIFgKIXhgBCloHmarfWDiGGAOIXr%2BBJQ9HpQx3rmBVDdFJLsSDP9329ZUVEP%2B9WPBYGcyqPA5HWv0uIJuJQ9IWCTZUUYGD6wqAGFaXNPAmBLOud%2BGNnTwhRDiEMz9kzahnO6F9gYe7pggOWH0HgKIDHIDrFQALTIi2Z32wtJDqwlgzDUdQOdh6WB4cQHWF0UFLhERTHaIEREgxSjlD0KkAtmRKcM5lUUBYdPljVFqL0OYLPfak%2BRH0ZotPhgVFmP0fnEuRcc7FxIEnoGdjy%2BIxwL9pAqN/s4L5qTMm5MKaUyFkVuANNRfMKcLgsWoMPfWAgTA4kRjE9IAhyQpwGwAE5TgJEkKhswkgZwaCwzON3KvSOkHI%2BbhsM4uAznw27/D0ekNcA/R7mc6vnO0fo4xq35m2OcaS9xjzpIBOZdQBF0T4mOBNBYJhBIM6mAdRNFwN3DYuAobU0iTTDtfY/b0/96QgOlDA967ofL1mmC2d/Q51XTneu0fc7x0kXmfNV5r3XhvaYm8t5Q2F0vqXIvRdOGYS38XX2JeS7vtLxesuRZACv2vTFJtN5mDQWgRXKCld67VyrY2v/1ca81tuVrdrDsTrbrZzfrQbYbUbVrLAG7IwabajWbRWWVAMZzZbVbfYMbTbZzHbPbS4A7XYajY7U7SDc7S7TAa7W7PsB7PgZ7BQV7d7T7Rgb7WQXvAzfvWQIHMzajEffQSbFAawawGHOHeARHZHUeTgNHGODHQQ7HXHfHYhVAhHbnZA5wCAVwKXYIWXJYcXRnQoLITwNoVnJndnEoOXAXTNXnSXQw6YFQ0FYXeYMwnQvQBcSYGwqnVwxwxYenC3DYLYJXXwrbNXDXFzDge4O/NfB/RvZvVvMVVCDvU3GLOLa3UgW3e3OIR3LbUPcPZvVDBIZPBIDDSQX3WTX2EIjPWwLPE/XPeAfPHjPjK/C/SLMTNgTgKvALFgBQTCKxTCTffkcYdvE3LTbvVgv7dgozeQQfbgizU4UgMfCfezFXYI9PNzQvNUbzcI4gFgDoronovo1yNUCAcLPfWIA/U4Y/Gg/Pa/WIRosvOIbo5IZIZcXot3ZcfoggF2LY2TArV/WIYrD/ajX/HrSDIE//FrSDYAwQUAnrRAzAAbIbMQaAyDWA27Qg3gJA%2BbVApbFbZANbLApeLbajXAyrAgo7B6Eg3gMgtICgibeA6gnPWgwcegt7D7L7VrHvMYiQDg4zKYkHEAWY8HYwWQmwHbInMQ5ERbPGPuTHawHHP9BQwnUQuw5EcndwdwvQLQpwnw/IEwgwnIKnPQ5EUXZwiwnneoPndU001QhgBw407UzwqXTwu05YBXfwgzKfZY2fLXdouTTo7o%2B4F4hsd4o3BIg/C3ZInPG3O3LADIqfbIkAMwZvU4U4D9bDNDAPZMhIGPNPL0ujSopjFI53D9d3D9fDUyN3SQN3DDT3LgAUzgU4GfXHTgCM1jKfVTHMpsvM6o9Yc7dIZwSQIAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/conditional.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/conditional.test.hpp)
