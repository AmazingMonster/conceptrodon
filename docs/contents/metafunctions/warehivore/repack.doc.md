<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Warehivore::Repack`

## Description

`Warehivore::Repack` accepts a list of packed warehouses and returns a function.
When invoked by an operation, the function concatenates the packed warehouses and instantiates the operation with the result.

<pre><code>   ...Warehouse<sub><i>i</i></sub>&lt;Containers<sub><i>i</i></sub>...&gt;...
-> Operation
-> Operation&lt;Containers<sub><i>0</i></sub>..., Containers<sub><i>1</i></sub>..., ...></code></pre>

## Type Signature

```Haskell
Repack ::   typename... 
         -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
struct Repack
{
    template<template<template<typename...> class...> class>
    alias Flow = RESULT;

    template<template<template<typename...> class...> class>
    alias UniFlow = RESULT;
};
```

## Examples

Here, we first concatenate `Warehouse_0<Con_0>`,  `Warehouse_1<Con_1, Con_2>` and `Warehouse_2<Con_3>`. Then we pack the result into `Warehouse`:

```C++
template<template<typename...> class...>
struct Warehouse;

template<template<typename...> class...>
struct Warehouse_0;

template<template<typename...> class...>
struct Warehouse_1;

template<template<typename...> class...>
struct Warehouse_2;

template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

using SupposedResult = Warehouse<Con_0, Con_1, Con_2, Con_3>;

using Result = Repack
<
    Warehouse_0<Con_0>, 
    Warehouse_1<Con_1, Con_2>,
    Warehouse_2<Con_3>
>::UniFlow<Warehouse>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Warehivore::Repack` is implemented similarly to [`Warehivore::TypicalPaste`](./typical_paste.doc.md). Intermediate results are kept in `Reverie`. After all containers are collected, the `Operation` will be invoked.

A simplified version will be as follows:

```C++
template<template<typename...> class...>
struct Reverie;

template<typename...>
struct Repack {};

// Base Case:

template<template<template<typename...> class...> class Warehouse, template<typename...> class...Containers>
struct Repack<Warehouse<Containers...>>
{
    template<template<template<typename...> class...> class Operation>
    using UniFlow = Operation<Containers...>;
};

// Recursive Case:

template
<
    template<template<typename...> class...> class WarehouseA,
    template<template<typename...> class...> class WarehouseB,
    template<typename...> class...ContainerAs, 
    template<typename...> class...ContainerBs,
    typename...Others
>
struct Repack<WarehouseA<ContainerAs...>, WarehouseB<ContainerBs...>, Others...>
{
    template<template<template<typename...> class...> class Operation>
    using UniFlow = Repack
    <
        Reverie<ContainerAs..., ContainerBs...>,
        Others...
    >::template UniFlow<Operation>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIADs/qQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwcBJgsaQa7JoFuu/uHmMenAJ5pjKyYAHTPx9gA1MgGCgrPj68mGgAghNiF4HG8AEqYABuCTwl0CViBAMBZwOTCOJwIt3ubF%2B/yBILBBEhmDSTGQAGs3iYklYkgARY5IwEogD0bLeFiYSjezTJIBRKLRFyuIoxCNOe3RmJud2YeJegXenx5PyVKq%2BCjeAHVWpgEOslKQ3uLZdj5Q98cqPlrfh5BEwIgkFATgQRQeCoeSqVc9cQDUbJQ6Ws7iOq/sq3bSWW846bpaKsYmJWKU%2BacQqnhrbWrrZq1W8APJ3YgYnJu%2BNvLxZIxvOQMPAAMVoqAA7jTAgzi6XywIriGnZFw/nmULGWPkUCOaTkBssrC%2Bbs0oKp6j05dkScUVWzZK92LM1ac6rvvnc99dfrDTXMIDSDv4wfk%2BdU1ij4rIwWzyetVeAzeSg2I%2BcbPnKuLZl%2BF4RoOYbAiaIEJq%2BGaWp%2BrzQfashDgkFgKA%2BQK7h%2BkFFgQCAukKUaEh6xKkj6lJ%2BteQasicsHDsC%2BYmv6ga3lYLFYWGuEccWpEuqOyJ0ohYFSRuh6oZB6GnhGCl/iWCR9gwlbxjWETAPWjYtu2nbdt6FL0QR8ZXIhVZQrCxDwgO/FsRGJqsThSnKvhgJVlWJFkSOLzmXGrwgCAe56c2rZtlcqllo0/yIuOTIJWubIAFTpRlmVsuyGUACrYEIuUZdl06ZWVqUlayyJmIEESfF4WCdm4aAMFsaQEK6lFVeuyH7jJ75yeeilie6noklxgEIiywr9VKvWyRBQ12hqKJEuCE1BgA%2Bhok7ddJ80DYtv55itVFjf%2B3FKJtXC7TNB1zTK%2B5EUtJ1fqt1HrYxt6bWYt1AlJz2naNNEOttf09Y9C1ZiNa0kqDN3JXts0Wkdb1nSDAg/eDAODUDsNvKDgTg9pdZCF4aTFJg6BQgoXi0CSxzdhtt4OQw20uZjXAc2zZjc5tRNRojKIk7pNN0wzXa0aZFFuIhzNXTtfFs4r2AIYFF2TddrPXXzv0eXLX1XXrbiE9GyohQ2EXtgxAFBvF01UeWyCbWqCQEBAEzoCFCgPC7nVuGL9MmmTFOZFTgcEK8yzMhwqy0Jw/i8H43C8KgnCy5Y1hvAo6ybJgNI1TwpAEJoserJSASSI8GiSFwSSBBo/gaGYABsLdmAAHB3%2BicJIvAsBIGgaKQydaKQaccLwCggMPJccFoqxwLAMCICA6wEGkXgEOQlBoPsdAJFEDycKoHctwAtC3khvMAyDIG8UiPGYvBU4QJB4F7XP8IIIhiOwUgyEEIoFQ6h546D0G2MsK4U5xwTknUu49OBFi3pvEkqAqBvFPhfK%2BN874PyrmYN4EAPD73oMQAugQuDLF4HPBepAIBID3mkA%2BZAKAQCYSwkAwApC8xoPTF0lBYgINiBEVo1xOBFxEcwYg1wiyxG0JgBwEjeB7zYIIIsDBaDiLAaQLAsQvDADcGIWg08U66L2IYYA4gdH4ADA4PAsJTFj0wKoRRW9thFwiLseOOjaB4FiGWGRHgsAII9HgAeZjbKxDDgyCxRg/FGFLqsKgBhgAKAAGrwjbKpZORdv7CFEOIAB%2BTgFqAQboLmBhEmmEzpYfQ/jp6QFWKgdqORTHn09ozGpVhLBmDHqgWydksCNIgKsOwijGguAYO4TwnQ9BhGdIsUYXNijZAENMPwKzMhrIYAsEYiQubjPsQIfoUxZkFEOfUCZfRJiDEWfsvQcwzn5E2bYW5eyqjLLGbnLYEhYEcETiPBBE9MFn0vtfW%2B99H6EIgLgN%2B5DzCUOocXJJqwyJMCwIkUZpAK6SECI8AAnIEJIkga5mEkC3Ie/gW4Ep7hwPupAB6UMeC3LgLcO4Eo7my/wtd/BEpbkCnRE8p4zxRWAxeK8GFrxQVvHe7DUCkMPsfDgrQWDQiSOfJguY6xcAJY8Lg1cX74CIEMvQ%2BTf5FOkCUpQZSdG6F5pApg0CeD/MBaPVOSCZVoIwaq9VmrtW6V1fq6uRCSHMLIRQswyLaGx3oYwhV4aEhyo4WQkAvqNWqiMLqrgw8%2BG7HDII4RoiZHKNIFIsRciFFKLMaoxgBANFaIQXogxRjaAmNLVgFgljrFj1sdcxxCCXFuN2KWrx9QEF%2BICWI4J2wx5hIiUXKJMS4lWJ0kkvgqSMlZJyaW81hT/5WtkKU0BY97X6EsSgaw1h6mxBGc01pAh2mdK7N06wfTU6DI/pgO9PRrnOAgK4DZ8zpkfKWFskoOQgPgZ2aB5Zv7jlNFuVB%2BDjRTl3IqA8w5SHzmvKeeh4YnyDnfI2L8qhdK3XAs4G8dN/rM2Br1QajQRC4UmooVQmhqLSDosxZQf5DKmV6prikAlSR66SHJVfLm7rEGT1sKKmNEr4BSvXqg5NCaWFHzYJwVVOCWAKGhPfaEQaLgTCNfCj%2BZrZAWoPYA%2BQNqT3gOCI651safEUaFZ6jeW83joOo8QFgun9OGeMxKCYob1MRsRYEaN66pUpqTWw%2BLiQDMU02kZglm0TMEBdv5q%2BfA6D5unhAIROjy0lrMWV2R8iJmltreozR2je2YH0YY4xpii6du7bO3gfb7EDp0UOucI6zFjp8WPSdgTrgztCXZBdvAl1KFiV2%2BJa7xUbqYGkzJmBsnyl3VZ/dEhD1APs%2BUkAwQqnGCvXUydP6WmNFMWyT2l7akWHfePT9wz4BjKuQhqZMyXnAfQLBg56RtmNGQ6sxowPHk/dQ9hgHlzegnPefcwjjz4dzKw/MVHYHiN5z%2BeR%2BBHmOB%2BYC9fPTBm3jpceFl5jxqSBsZi%2BKtFmAMWjGxT4/jIAzB6sCIEfwTda5Dz50kdlgr%2BmcBFbPTjuL/CEv8B3VuBLJAiZF1wc7nBAhE4l7JhT/zn7i49brzjtksjOEkEAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/warehivore/repack.hpp)
- [unit test](../../../../tests/unit/warehivore/repack.test.hpp)
