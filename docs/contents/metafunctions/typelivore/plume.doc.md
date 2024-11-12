<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Plume`

## Description

`Typelivore::Plume` accepts a list of elements.
Its first layer accepts a list of containers and returns a function.
When invoked by an operation, the function places the elements into the containers via a process similar to pack expansion;
then, it collects every packed container and instantiates the operation with the collection.

Check out **Examples** for more information.

<pre><code>   Element
-> ...Container<sub><i>i</i></sub>...
-> Operation
-> Operation&lt;...Container<sub><i>i</i></sub>&lt;Element&gt;...&gt;</code></pre>
<pre><code>   ...Element<sub><i>i</i></sub>...
-> Container
-> Operation
-> Operation&lt;...Container&lt;Element<sub><i>i</i></sub>&gt;...&gt;</code></pre>
<pre><code>   ...Element<sub><i>i</i></sub>...
-> ...Container<sub><i>i</i></sub>...
-> Operation
-> Operation<...Container<sub><i>i</i></sub>&lt;Element<sub><i>i</i></sub>&gt;...&gt;</code></pre>

## Type Signature

```Haskell
Plume ::   typename... 
        -> template<typename...> class...
        -> template<template<typename...>class...>
```

## Structure

```C++
template<typename>
struct Plume
{
    template<template<typename...> class...>
    alias Road
    {
        template<template<typename...> class>
        alias Road = RESULT;

        template<template<typename...> class>
        alias UniRoad = RESULT;
    };
};
```

```C++
template<typename...>
struct Plume
{
    template<template<typename...> class>
    alias Road
    {
        template<template<typename...> class>
        alias Road = RESULT;

        template<template<typename...> class>
        alias UniRoad = RESULT;
    };
};
```

```C++
template<typename...>
struct Plume
{
    template<template<typename...> class...>
    alias Road
    {
        template<template<typename...> class>
        alias Road = RESULT;

        template<template<typename...> class>
        alias UniRoad = RESULT;
    };
};
```

## Examples

We will see three examples that present different use cases of `Typelivore::Plume`:

- We will pack `int` into `ZeroStar`, `OneStar` and `TwoStars`.
Then, we will instantiate `Operation` with the results.

```C++
template<typename Element>
using ZeroStar  = Element;

template<typename Element>
using OneStar = Element*;

template<typename Element>
using TwoStars = Element**;

template<typename...>
struct Operation;

using SupposedResult = Operation<int, int*, int**>;

using Result = Plume<int>
::Road<ZeroStar, OneStar, TwoStars>
::Road<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We will use `OneStar` to pack each of `int`, `float`, and `double`.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
using SupposedResult_1 = Operation<int*, float*, double*>;

using Result_1 = Plume<int, float, double>
::Road<OneStar>
::Road<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We will pack `int`, `float`, and `double` into `ZeroStar`, `OneStar`, and `TwoStars` separately.
Then, we will collect `type` members of the results to instantiate `Operation`.

```C++
using SupposedResult_2 = Operation<int, float*, double**>;

using Result_2 = Plume<int, float, double>
::Road<ZeroStar, OneStar, TwoStars>
::Road<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Typelivore::Plume` separates cases according to the number of parameters.
The goal is to mimic the behavior of pack expansion in C++:

- If the user only provides one element, we pack the element in each container separately;

- If the user only provides one container, we use the container to pack each element separately;

- Otherwise, the number of elements shall match the number of containers.
We pack each element into its corresponding container.

[*Check out this test to see how it works.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgBykrgAyeAyYAHI%2BAEaYxBIaAGykAA6oCoRODB7evgGp6ZkCoeFRLLHxXEm2mPaOAkIETMQEOT5%2BXIF2mA5Zjc0EJZExcQnJCk0tbXmdtpODYcPlo1WJAJS2qF7EyOwcBJgsKQYHJgDMbgQAnimMrJgAdE/Y9GyCCufYJhoAghPEXgcAGplLlMN8fiYAOxWX5A%2BFAg5HE7gi5I45MU5om53NhPB6fIHIAwKBT4jwKNiOZAfM5fOEI/6Aggg4ioIgAJVQTHQQIhCL5ML5DIF8PRKPOl0OGKxlxxzDxT0JxKYpKBAHlbsRMVlPvzRfCmcCACKYJp0fUG6Gwn4Gg1eDJGRE4vlnY0arU6gSSilUvA0yUvQ6MAi07D4vVnG12wXG842y2i8WY1FS5EpyXXW4Kx5KulEklkp4/YDETDB956kWih1hYBArk813u03m2iSktliuhiN0kAgLOohPVgXJ2Vj1ODnO97AF1UKD1xL0MKu2u21p1yBh4Ru887uzVL%2Bori6%2Bs3%2B2luINvUOfGfxxPQuNRiGJieZ6US7HZ%2B4zudqs9qVXAUjRZZQ2U5bl0B9dI/VMOlHyFRNR0/DM0VQ8d5V/PNZxVNVD21Y9gLtUCgVbJgLRHBFrWQ9dHXrQdm0XQjdVPWDz3gq9XhDMN7xfKj4SfB9flosUMMncTMywxUCXzPCiweTtyxvMNRKBDd613JjyItC4lO7BTPn7QdhMhATEUk9D00wn8ZOVQtmOXYj7XooEtx3KCmIIpy2MpDjA24ys6T46NqKhZ9hzXMTrIkmKpNs3NZNwwtyXY6lVOrDSG08/dWXZVBdxgvz0pC19wtMiF32/XFMCBa8Q1XUjQR8VN6sEVcaOrKq0xlSdpMS%2Bz51S4qL2coEmoggqcura1hSipNLJ6r85QSv95McoiEPM0idPbczOvmmMssY3LvM2txANGi42oIO8cNMmMhP4szDoRbr3v6taUuLUtlJ4saBSyrTct2jtfoMmdjJxCrzPexap2wpL/wXM7WPpV74Sy9zgbdDbWIutKrq47s7qSh6woi18uvh%2BHPpw5HhrgjL5qBnLcfA/LCt8pnSpE8rnqpn4AHoACoxfFiWhYhUWxYAFWwIRZfFqXfhliXJcF8wzjCYkvCwV03DQBhdhSW8tpej6ErqwLbvNrKAC04lQfpiEE3Gbphn5LZq62Sbt1z1XCF2mJukXPe9nNfZvVcstlgB3Z3JgXXLQ7DgXfgjxHGoIAFgVR710%2BFoWgVlzAJiBDRBayoQvBSNIlHQDky68WgWVOz1zrCAhSCBLuRZ7vu06%2BQugeb1umOathJS71d%2By5txHbZF2e8DzBl5LhOXeZueoMlfOT2HyKJh1ZAAH15ziAgIAmdB%2BwUe5z8vJuFBb7ugRruv0kwRux9t7A1k9kLYupdy5cCrq5D%2B9dv7P1fqfLgXkO74z7j3KgtBuQEH7kCdAWxoj0CHp7UeL9W5wInmCaeggUFoMxD3bBXhcGonRjvHke8g6TFniAee%2B9IxHyaNSR%2BSgWjXwILfEA982CP0lDA1uPdIFfx/kQv%2BADC5AJLmXFkZhwF1nfrXKB8jYFmAQUeJBFCgSoPQZg2h9CxbcM0U6KRBBT4GNypPVMXdKHoJoTg%2Bg7D56L0Ts0FerCAkb38cQbeHDd4XC4QhQux8%2BEX0ETfO%2BD9VSSN/jInRcj7GfCURYDgGxaCcAAKy8D8NwXgqBOBuGsNYcaWwdi1S1jwUgBBND5I2AAaxAEUyQDwNCSC4FCM4GgikaDMIkRIZh/CBEKRwSQvAWAJA0KQMpWhSCVI4LwBQIBlmtI4FoDYcBYAwEQCALYBAUheG7hQCAaAjh0DiBEe4nBVD%2BESAAWkSJIIEwBkDICBFIB4ZheDf0ICQPAt8uAyEECIMQ7ApDQvkEoNQbTSC6ChXHbUKROA8AKcU0pqKNnqiuZclkqAqBAleR8r5Py/kAt6QYiAHh7n0Fdk0tYvA9kHNIBAJAdyUgPLIDc/lgqQDACkGYPgdADhhMoNEVF0QwjNCuDi3girmDECuOqaI2geh7OaXcm8gdaAqv2bwLA0QvDADcGIWg2zymkCwCwQwwBxBmsdXgMsvQABuZdUWYFUD0K5exmld1qKi2geBojak1R4LAqKc54EWQ631xBohf1NM6owkajBtI2KgpgwAFAADU8CYDjoeMpzT%2BAwtEOIBFNakUqHUO69F%2BgXUoBqZYfQUbtmQA2KgU2WR7XvJvvuUwlhrBmDWagVNxAIV%2Bv7TUOoWQXAMHcJ4doegQiLDKBUPQ9cijZE3TMAoGRjxDD3SsZdeq%2BjzGmB0G9vQGjzEvSMSocwBgPr0MfFob7liVA2AoepuwJB4o4CUlZhLOCUreZ875vz/mAsZbgMFbKzBnC4BylpeaNgIEwDyUYEBOkgEkGcB4ABOM4UJJD9LMJIRIGgRmJAo/oTg8zSCLMww8RIXBEj%2BAo/4PjPSuBFKo8kVZFTOBbJ2Ths1hyTm8rOSSq55BKAitZU8tgnBmgsG9VCd5TA5xOi4BRh4XA%2BkgvwEQedkLEWwvrdIRtihm2ot0JKzFTBsXlPA5ByT6zODEouVcoE5KgS6f04Z4z9ZTPmb6UCJlqAWVxD5Bhsw2GuX5J5XypLArWVqdubl0VEWDMqiMKZqoUrW5xG2RAeV7r1XKtVaQRrmrtW6ocM1w1IZjWmrWRaq1NraB2ua06l1br%2Buetvb6%2B1ayA1BoOM1sNsy1mRujcquNew1mJuTc01N6alCZvG3WPNfADBFtLeWytzXG0OfhU52QLmUWtpAJKgwuaJ1WG7WtvtxH1lDoECOsdbpPtTpnXOhdv2gO1Fvc4CArhv1Qp3aUd9B7CjHkR2eo9/791Qu6M%2BhgLtWgnsffj48ROcfXt/cT3IpPX27tR1hzY2xQNM9mX56DHBwvED0wZozZWYtmYsxoBLqGbOpcwxl3DpB8OEfiH92ZHGuNmf6VCMTUIhmSHo18qF/mNkyd2ado5pzzmkoKxpx5zyOC6ZpSwBQ3r/netiyiCYVm0MQr0Ldut93EVPZbWs3QZxSCee87itjEGCXuqJSpslFKbffLtw7oETuzMu5ZIl5L6GzhnCl/J7LKAiv5eFYX0YDu66nxT6fNP58edfKqzK2r9W1mtdNc0lv7W9VdaS0ahgJrUUDetba%2B1zSxvZq2%2BaqbPq/Xuvm8gYNS3BDhvdWtmNVxNsJvnbt3g%2B2M2HGO7mvPBaLtlordmG7sg7sSAe4IP3bmQBB/e8YLtNgfvwAHQDhg9qhZJNB5YadFSIcsAocn1jw10N1adt111KcP1D0McSc0dz0shoCf0YcCcidMcyc70BhkC8d714DcDsCGcAMwNmcGkSD2dI8Z0YN48gRE9HdncUxy4IAxcSAJcsNOVpdZcsB5dwMldXszNs8ilRkBkmNs8oR%2BMoMo9pNbBZNMs1gSNJAilKMil/BxkKNJAKMhlqMuAH9OAzhKCpNNk5MDlwNgVJCqCjC5CNhU0MhnBJAgA)

## Links

- [source code](../../../../conceptrodon/typelivore/plume.hpp)
- [unit test](../../../../tests/unit/typelivore/plume.test.hpp)
