<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Raillivore::Conceal`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#raillivore-conceal">To Index</a></p>

## Description

`Raillivore::Conceal` accepts an operation and returns a function.
When invoked, the function instantiates the operation with the arguments and returns the result using alias member `type`.
Overall, `Conceal` turns an operation into its `Typical` counterpart.

<pre><code>   Oper
-> Args...
-> struct { using type=Oper&lt;Args...&gt;; }</code></pre>

## Type Signature

```Haskell
Conceal
 :: template<template<auto...> class...> class... 
 -> template<auto...> class...
 -> typename
```

## Structure

```C++
template<template<template<auto...> class...> class>
struct Conceal
{
    template<template<auto...> class...>
    alias Rail
    {
        using type = RESULT;
    };
};
```

## Examples

We will conceal `Operation`.

```C++
/**** Dummy Arguments ****/
template<auto...>
struct Seq_0;

template<auto...>
struct Seq_1;

template<auto...>
struct Seq_2;

template<auto...>
struct Seq_3;

/**** Operation ****/
template<template<auto...> class...>
struct Operation;

/**** SupposedResult ****/
using SupposedResult = Operation<Seq_2, Seq_3, Seq_0, Seq_1>;

/**** Metafunction ****/
template<template<auto...> class...Args>
using Metafunction = Conceal<Operation>
::Rail<Args...>;

/**** Result ****/
using Result = Metafunction<Seq_2, Seq_3, Seq_0, Seq_1>::type;

/**** Result ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

Here's the entire implementation of `Raillivore::Conceal`:

```C++
template<template<template<auto...> class...> class Operation>
struct Conceal
{
    template<template<auto...> class...Sequences>
    struct ProtoRail
    { using type = Operation<Sequences...>; };

    template<template<auto...> class...Sequences>
    using Rail = ProtoRail<Sequences...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAArGakAA6oCoRODB7evnrJqY4CQSHhLFEx8baY9vkMQgRMxASZPn5cFVXptfUEhWGR0XEJCnUNTdmtQ109xaUDAJS2qF7EyOwcAPQAVFvbO7t722smGgCCm9sA1ACSLIn0bIJM1ec7hydn%2Bx/7r8dHxwSYNwM/xMAGY3P9AY9MKDwQDblCYUwvEQAHRo0HYc7IAwKBRolEYrE4hTnADyiWij3SGN%2BQ2IXgc5w8DBWYl%2BJgA7FYTudeecIfDgWCBUDoWCkaj0SDMdimLj8UJMABHLyMFYKGk8vl0hkEc7KYioIgAJSYdF%2BfPOnIs5y8qSM/IAnhSrSCACJkinEKkCGGKlVqzB4qXYUE2zlusPsrW8kUI4Vw0WI5GofGE2XytH%2B1UsoOa46Wu3BYDnU10V0eg1G1Bl2h%2B5U59Vp6VRk4R1s/N6fD7fd4bc7YVSsW6YZ4HX597vjtttswg4LYrxYV1uNC5xIEDUtmenHbnN0%2BFiO87HYjAHyMTdjrbfONCtwS1Mh2kEemM/0AfQ0Hd%2Bd7FD5TZtQxOHV32VD8uB/E4/2TSUCW3Y5QL1T8zCgv5E3jAC4PzJDzk/EE0L7T1KSeF5fww%2B8YPFQCQyJOVg3g4DENfXViO9apCL3IQvESXJMHQY0gy8Wg9TIk4iwdbjeJSfjBIUYS9VBD1yRI6kwRQ0g8PAkFNM/DRdPAyCWxBblO13C4AFlMDqKgvBZUjp3QyFKIo/9HyAujMxRU9gC3JiJJLKybLshx0grJkBFZOswRU9i1KYkAQFrGEfIYmkTOjcytlLISROvDZvgCnL5LypTziCphbPstS3A0rSlQ/HT6q/AyGqM7BEoIZ0xVMic9zkhT8u%2BCZHGQD96OiAgICGdBEoUVhMHGrc3AGkTdJ4viBNyggMVmDsOHmWhOFiXg/A4LRSFQTg3GsaxzgURZllHcwQR4UgCE0A75gAaziSQUQ0AAOMwzAATlBrhYiBwGuA5DlpCOjhJF4FgJA0fSzouq6OF4BQQH0j7zoO0g4FgGBEBARYCESZFyEoNAbjoaJQgWzhVEBgA2ABaDnJHOYBkGQc4pBRMxeH4wgSDwWbWn4QQRDEdgpBkQRFBUdQidIXRWgAd29RJOB4Q7jtOz7Ls4UlkRpvVUCoc52e53n%2BcF4X/rMc4IA8Rn6GIK05y4WZeEJrR5ggJAGcSJmyAoCAI6jkBgCkBIaBE6I8YgCIzYiYJ6kdQ3eGz5hiEdUkIm0TAHHz0gGfuAhSQYWg881rAIi8YAH1oWg8e4XgsBYQxgHEZu8GICvHAANyDM3MFUCvkVWN7gn%2BRGLtoPAIm9YuPCwM3XzwVGe9ISfiAiGS3QBAe16MT75ioAxfIANTwTAdZUs63rl4RRHEZXP7VtQzba30APFAt1LD6HXnjSA8xUAbnSN3LmM0lKmEsNYMwWNj7EGllPaBbQx7pBcAwdwnhmj%2BCIVMPoMRWi5DSAIUYLQkgpFoQwChJR%2BjjEqPggQnQRgkLGHg0K3DhjdGCL0NhVDbDCPoXoCYDRWEzADgsJYKwJDGw4CdUgmNeDY3tpzHmfMBZCxFu7CAuBJa%2BxegHION95gIEwEwLAMQIA/RAJIEEKJQYgnhhoSQZhJAc3RrEDmoN9CcGRqQVGr0UQcy4BzQGoMYYc1iJISGniOaaLNtjXG%2BN3o3xJuTMOlMra0xjnHH2LM2CcHqCwceHIuZMDog6LgoMURcABuLfARAsEyxVl/RWEhpB/yUAAzWugEh6yYAbHuaiNFaPNhwS21NkTnFtrox2fNZRNJaW0jQHsvaRx9n7EEZhA65KJqHcOqBvbRDprHK5Bz%2BibMThDfSKd/jEHTpnTWhdc5Vx%2BcXUu5dK6HxrpeeujczYtzbh3LuVc%2B6X1WBdfAo9QqT27hdGec9/hVyXpUM2a8N6523oioOWCD5vWPqfJQ59%2B5GCvqAc5fB74KCfi/N%2BVdP4Kx/oM2Q/8NYXTGcA6%2BKCrDgIJVA5xl04ECAQUg90Iq0EYOiN0nBkq7BcL8BAVw0jWiBFEdMdhjC8jpB1Ua5h8jDXqsETUKRfCGFWuqDwkRRRKEyNtVke1wiLVUPmA9ZRSsZmm01joh2%2BjGklmaa0gGHszFdKOVYs5IdbH2McZQNR4TIktJ8RyWIoM4Ygl8f4lJGTg2cGyQTPJpMKZU2trcspzNWYcGqU7FgChx5C3HpG0UQwOnmOlnoTl38lY8tVsM/lOgQA6QmVMo2oT1FBqxhbYpNs7aqBbW2jtXaoRDD2fcqORyQSnODsTQp9bo70z3T7EA7beIfk7aDD83aCAfjXYMug7zPlZxzsXP536S5lzHlXUFghwVNyRZgVu7cxCwsPvCulJLSDIvwWi6es9kDzxxYIPFmsCWb0dMS3eZKq6UrPhfOlxY8l3yYI/Z%2Br8KTv14IO/pv9eVjsAZOoVxgwE2HFfAGB0qGDdzWDNUBqDLDoO0Zg7BErfWcOtYQ4hHqyHoG9TkJh1RTU0OqKpjh7QhFdFNQ6joXr9WuvGO60h5nJimfEaopRT07OI1mZkzg9t13tvOPelET6Y2dJIPGo9NjSB2Icf0SViMM0gDBiiEEIJYhQxSejWLHI4klsXTjWwOTj2zBcZIWIHjYYcnRoDSQEMuDAzMOkxGIIF3aLLYmr6c6xZpbqxl7L8xj6pGcJIIAA%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/raillivore/conceal.hpp)
- [unit test](../../../../tests/unit/metafunctions/raillivore/conceal.test.hpp)
