<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Travail`

<p style='text-align: right;'><a href="../utilities.md#travail">To Index</a></p>

## Description

`Travail` accepts a list of items and returns a function.
When invoked by an operation, the function instantiates the operation with the items.

<pre><code>   Items...
-> Operation
-> Operation&lt;Items...&gt;</code></pre>

It also contains a regular function, `size`, which returns the total number of the items.

<pre><code>size() -> sizeof...(Items)</code></pre>

## Type Signature

```Haskell
Travail
 :: template<template<template<auto...> class...> class...> class...
 -> template<template<template<template<template<auto...> class...> class...> class...> class...>
```

## Structure

```C++
template<template<template<template<auto...> class...> class...> class...>
struct Travail
{
    static constexpr auto size() -> size_t;

    template<template<template<template<template<auto...> class...> class...> class...> class>
    alias Calm = RESULT;
};
```

## Examples

- We will create a `Travail` with items `Item_0, Item_1, Item_2, Item_3`.
Then, we will transport the items to `Operation`.

```C++
/**** Items ****/
template<template<template<auto...> class...> class...>
struct Item_0;

template<template<template<auto...> class...> class...>
struct Item_1;

template<template<template<auto...> class...> class...>
struct Item_2;

template<template<template<auto...> class...> class...>
struct Item_3;

/**** Operation ****/
template<template<template<template<auto...> class...> class...> class...>
struct Operation;

/**** Packed Vessel ****/
using PackedTravail = Travail
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

/**** SuppsedResult ****/
using SupposedResult = Operation
<
    Item_0, 
    Item_1, 
    Item_2, 
    Item_3
>;

/**** Result ****/
using Result = PackedTravail::Calm<Operation>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

- We can check the size of a packed `Travail`.

```C++
static_assert(PackedTravail::size() == 4);
```

## Implementation

```C++
template<template<template<template<auto...> class...> class...> class...Items>
struct Travail
{
    static constexpr size_t size()
    { return sizeof...(Items); }

    template<template<template<template<template<auto...> class...> class...> class...> class Tranquil>
    struct Detail { using type = Tranquil<Items...>; };

    template<template<template<template<template<auto...> class...> class...> class...> class...Tranquil>
    using Calm = Detail<Tranquil...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDMpK4AMngMmAByPgBGmMQgAOwArKQADqgKhE4MHt6%2B/kEZWY4CYRHRLHEJKbaY9qUMQgRMxAR5Pn6BdQ05za0E5VGx8UmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMAXCyG8WFuJgCbmQE3QWCosOwIJBfwBWIOQMxtwAkiw0vQ2IImI0vodcdiaWd0VcCJgiQZGbC3IzmeTMGyOcSuTymXzWXCmF4iAA6SWo26QpgKBSS8XS2XyxXKgyqyX4jkKVEgibELwOW4AFWITAAbkw6OjElYrrdHbc5o5kDKBBNMKo0sRnXgAF6YAD6BD9gYgyxBTphdtuxEwBA2DDDmFQVEVEG1TIUkYCFhj93pl2jvJZ3Lhpf5FcFZYFnOF7JrVbcoolUoC2BlGoV7c7Kp7So7XblA/VI9N5oYAEcvDaO1GnQajaHHi06DH814skZbgQAJ7PGEBe4TwwzuduLMsUfzvMF2H24EOp2Vhuv8uN%2Bsf991oUf1uoGqQ79kBfbdqBw6aoOYEjoqZpnrOtB6s%2BjpbuEwC3C2tAsEeJ6rtaSFwvB06IaBIAgPuzwPrahZ5kWmK0ic1J3AAYngxATLc2CqKwxKYJSOIYoxAJAuiYIQlC/FsmgDBbGkBC6vOVxCXcV6fN8II/tWX6/rWIpioBvaQTeMFQchlxLsaV5Bho1HKQyTZvo537OWyAEQSBRmedB%2BoEIaVkckGXB2U%2BlxaZ%2Bf66c27leeBsWwb2vn%2BaG1lmCFmmudpkVZXpLYGR5cXQcZoFJcuBKBQE6W/EctwAPLPOaFIaQ5Ok5c24XhTFRXeWOZnAYV5mWaG9XxOSORVdcNXKEwyAANaYOgtwAGofHYAl0lcaE7tNc0LfBVrrrCJ77QR6JwgujrWRopAwih5VMkFN0XfdLBBmYT13dZlXKbej4qQctxCF4aRpEo6AAEofF4tChs1lxbRhQMg5kC2Qwo0OhkddUNWNAhnW4z1XR9xZOtZXDE9GqUU6TFVnWidH2ZNdxoxj61AgjtwszDuG3Dt83oCddDkVhLBsiNjXjb99E1SaHyw1SvljcgQYjvEBAQIi5EKKwwZymyXMEDdSPFKjUMw6iuZ/dVwn/MxANCJgMmLdxvH0Gz/024CRYungyuq20EB83t5oHbQWsBpgEa4VjkiWxwqxhxwyS8H4HBaKQqCcATljWM66ybFJYI8KQBCaPHqyzSAySSOKGgABxmGYACcTdcMk9d11wiSJNIieSLwLASBo12p%2BnmccLwCggNdpdp/HpBwLAMCICA6wEGkYrkJQaBEnQ8SRDrnCqHXABsAC0J%2BSLcwDIG6UjimYvALYQJB4Ogej8IIIhiOwUgyIIigVDqDnqQXQ5MADu5o0icB4AnTgydSCj14OPWqYoN6hjTLcY%2B59L7X1vrce%2BZhbgQA8LvegvpzABC4MsXgs8tCrAgEgHeaQ95kAoBAZhrCQDACkO9GgMN4hTwgDEMupAYjhFaHuGBvBxHMGIHuWqMRtCO1nsXHepICC1QYLQKRICsAxC8MALCtAp7cF4FgFghhgDiD0exFReALQfFEV6R2YptjF3CIyRO6daB4BiOaeRHgsCiL8ngQeZjSCOOIDEFGjxLFGF8UYMuqwqAGGAAoJa7xwEjVTsXT%2BwhRDiD/vkwBahRFgP0FYlA1hrD6D8VPSAqxUDyRyKYs%2BiIjqmBzpYMwY8onEDfk4xpPR7HOAgK4aYfhyahHCMMKooxybFGyAISZeglmNAWCMBI5M7CjKaJMdonhOh6F2Q4PoBzNnzO2bYA5qydkXNmYsBZqwFD5y2BIOBScU6iPHlg0%2BF8r43zvjXIhEBcAvwoUXGhJdkmrAQJgJgWAEgRlIJXQI4om4BB7hoSQZhJAn2HskE%2BTd9CcH7qQQeVDxQny4CfOuTdO4n2rm3TFJ9EE/M4JPaeMK54MOXow1eaDN7sM4eQg%2BbBOCtBYBaRIZ8mDDh3FwJu4ouC1yfvgIgAz37k3yd/Ip0gSlKDKSA3Q71IFMGgWYz5CCkEZ04Kg9eYpbiYOwQChVGElUqtrsQ0hLDyEwjBGYaFdD54CtFfELeHDUBkNGLKIwSquDXX4YyDilAREgNkZI6RYiJHyMUcohw2b1GME0do3R6d9GGOMaY4uFirE2IrXYs5jjTHpxccgNx2bPH1FEb4/xkignbHTqE8JxcokxKUHE%2Bt6Fkl8DSRkrJOTs26sKb/A1shSnAPTqaypSSulWEsHUmIDSUXNMaG0jpx593WF6cg/pgyT0vPqHslwDB3BHIKNMt9lyliLMyMs3IH6pnpH/Rsx5WyTnPrOQIfoUwgOQd6DBh5FQIP3IGHcm58xwNXI%2BWsDY7zqGkq%2BeykBvzXW4LjR65VqqNDEPBZqgNVDg2wtIPCxFowUV9wHiAAIyqcUpCbt3AIuL8WSHJra8eXKZ6zsXivNe6DI3huIOK7YUrcHXgtG6C0nqywTHVRCt%2BH9ZB6rXf/eQRqt06B46Qc1lrYFEZtRyjgDr0HOqoFg9TChNO3G08q3ToYSHRr9fERjARmO8oXkwoLrDFPRfISATTIMgy%2BaDP5oMqhL58DoCmoR6b06ZvkdmgrCilEqKLdGjRWidGiMrUYsQJjs11oSUO8xTbHAtucaoVxjIu2CB7SAvtAS9yDpCQM0dvBx2xKZNOpJEXUlMHSZkzA2Tni5N4Cun%2BEh10AIs%2BU6zBg901MPX2x9GcWkek4DsTW16el9PiFqoZKLTmNFfe%2B/IwGZkoZw3%2BkoOQMPrJyD%2BhZIzoP7PQ/BnZUHGiwcGNh39mG4PvZOchuZv6XlvN/ta75pHOAeavhprTOmuScTBRqkgjHqG0JY2xpFlBPnksHs3cUAQAjJHbmJ4eLPEh0pI2PTlthuUhuWBXfwyQMVd0SMPOukhW5cAbmYNlicAjY75xPHl9DPmP158g/nQvVhRKyM4SQQA%3D)

## Links

- [Example](../../code/facilities/utilities/travail/implementation.hpp)
- [Source code](../../../conceptrodon/travail.hpp)
