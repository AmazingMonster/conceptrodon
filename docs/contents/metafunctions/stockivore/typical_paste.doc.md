<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Stockivore::TypicalPaste`

## Description

`Stockivore::TypicalPaste` accepts a list of packed stockrooms.
It concatenates them together and uses the first stockroom to hold the result.
<pre><code>   ...Stockroom<sub><i>i</i></sub>&lt;Sequences<sub><i>i</i></sub>...&gt;...
-> Stockroom<sub><i>0</i></sub>&lt;Sequences<sub><i>0</i></sub>..., Sequences<sub><i>1</i></sub>..., ...></code></pre>

## Type Signature

```Haskell
TypicalPaste :: typename... -> typename
```

## Structure

```C++
template<typename...>
struct TypicalPaste
{
    using type = RESULT;
};
```

## Examples

Here, we paste `Stockroom_0<Seq_0>`,  `Stockroom_1<Seq_1, Seq_2>` and `Stockroom_2<Seq_3>` together:

```C++
template<template<auto...> class...>
struct Stockroom_0;

template<template<auto...> class...>
struct Stockroom_1;

template<template<auto...> class...>
struct Stockroom_2;

template<auto...>
struct Seq_0;

template<auto...>
struct Seq_1;

template<auto...>
struct Seq_2;

template<auto...>
struct Seq_3;

using SupposedResult = Stockroom_0<Seq_0, Seq_1, Seq_2, Seq_3>;

using Result = TypicalPaste
<
    Stockroom_0<Seq_0>, 
    Stockroom_1<Seq_1, Seq_2>,
    Stockroom_2<Seq_3>
>::type;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `TypicalPaste` using recursion over the total number of packed stockrooms.

- **Base Case:** Handle several amounts directly;
- **Recursive Case:**
  1. Concatenate several packed stockrooms at the front directly and place the result into the first stockroom;
  2. Invoke `TypicalPaste` with the newly packed first stockroom and the unhandled stockrooms.

A simplified version will be as follows:

```C++
template<typename...>
struct TypicalPaste {};

// Base Case:

template<typename PackedStockroom>
struct TypicalPaste<PackedStockroom>
{
    using type = PackedStockroom;
};

// Recursive Case:

template
<
    template<template<auto...> class...> class StockroomA,
    template<template<auto...> class...> class StockroomB,
    template<auto...> class...SequenceAs, 
    template<auto...> class...SequenceBs,
    typename...Others
>
struct TypicalPaste<StockroomA<SequenceAs...>, StockroomB<SequenceBs...>, Others...>
{
    using type = typename TypicalPaste
    <
        StockroomA<SequenceAs..., SequenceBs...>,
        Others...
    >::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxHoADqgKhE4MHt6%2BcQlJAkEh4SxRMVy2mPaOAkIETMQEqT5%2BRXaYDskVVQQ5YZHRegqV1bXpDX3twZ353VwAlLaoXsTI7BwEmCyxBssmAMxuBACesYysmAB0p1vYJhoAgr3EXg4A1AAq%2B3iitMpMvZgPJgDsVj%2BABEtlZrpcrgB6SEPCxfH4VTCxEAQiHLVbrTBbHb7Q5sB6fZAAa0w6AqqGJxFQqBY5wht3uBGer3en2%2B2MJJLJREp1Npmwu4IBEIeooeXkSRgeewOv02QIJTGJpPJvJpoNRwI14Ou0IeACUmnNEgA3BHLZGo67otZMDbg7YisU2zHYl12rHbJheIinY7nB7IAwKBR%2BgNBr4KB6qolUmlXUhO0XujbbFOetze31nAWB4OhnPYPOR6M82N8mxJ6UrW2pzM%2B1Bh3MRkN%2BoSYACOXkYCxupF%2B1zF1YxHuxWcbheLrdO7a7PcwFgUicHztxzDYfoA8gQENEFKiBfSCHdHi9Ym8xGy6zG4ywrtjZ92GL2C/6Bf2bxWH52nwtF03sH7bdd2IV86SFMEriHCVgmAaVcTlBUZTxH4zwvD4vntKCxWxKsh0/eNvznZ9MBuP0Px/ed/0LZdsKHUVgL3MMV1Fc4QBAZDtXvLVNkgiFIQAKiE4SRMhfjhKebAhCeYSxN1ESFIEuT73BMxNmCIMvCwOU3DQEjYgIfdDx1K50zdGtXS9BsAKnMDjJuY9GVLClyxpAB9DQuLRCzRzTHy63HGyWzswUHJPJkCJYNyuC861/IzMyrOzN8i2CgCj3C5y1SisxYtM%2BKx2swsMqc2cPLyxL62S8CwtKztooqgqkonFKSseMrct4q18pHAKita64GXa%2BrNjymCpSELxYniJR0ENBQvFoJktgVSLyu2MqNAojtou2tyzD20bDy6kzxrg%2BbFuW%2BVmXPVlMKxB03CrNbPI2%2BrXsAgc6Ky1yopit6dqKaN6s6wDnrLW99qItyjtCtiONxPLejtN43MjaICAgXp0HYhQjjRoy3AupaPymmbSWJghzkmLiOGmWhOAAVl4PxuF4VBOCeyxrAeBRZnmH5zE2HhSAITQ6emIkQEZyRjg0SQuD%2BTYNEZjQzAANnVswAA5tf0ThJF4FgJA0LbWa0UgOY4XgFBALaxY4LRpjgWAYEQEBZgIWIfXISg0FWOholCI5OFUbX1YAWnVyQHmAZBkAeKRjjMXhSUIEg8Bxop%2BEEEQxHYKQZEERQVHUR2dD0AB3YgmGRNn6aZlnxctzhNx9b2mVQKgHjDyPo9j%2BPE9lswHggDwA/oYhfjUqZeAdp3SAgJB/fPSffYgFfA5iYApAOmglr3SgImbiJgiqXZOBF0/mGIXZNwibQmgdkX/bYQRNwYWgL/L0gsAiLxgCZloLQW2bNf4rEMMAcQP98DECfngM0oCLaYFUEaZYl9eDBGWAzH%2BtA8ARBrrfDwWBm7HjwMbMBZpiARASJgIEECjB4KMOLaYVADDAAUAANTwJgSum4DisxFjnYQ7wC7SGESXNQzddBFAMMw0w3NLD6HwbbSA0xUAGWSKAiO2MVoKKsJYMwFtUBUOIJnTAqiIDTEaM0ZwEBXADHqKQQIow8gFAyIkMoKRPB1A8VkBgHQ3ETGKKUFowxHE9BKPA8owxAldEKLYcJPjBiJLaHE8YhRrH8wWBIBuHBmakHNuzTgPdw5RxjnHBOScR4QFwOnKeQtZ6ixYdMXcTAsAxCsaQKWkhNjHAAJybD%2BJIeWZhJDq1NozdW/T9YcENqQY2wtjjqy4OrbW/TtarJllwRmgz1aFOblbG2dtmnl2dm7JeHt24%2BwoBvGkq8g4hw4FUFgJo/gRyYMWKUXB%2BnHC4HLVO%2BAiBmKzkXER%2BcJDiNkJIsuFtdAHWrrXDBeSClFJbhwNuXsfQPC7g8F5byPlfLgj8v5ctR7jweQ0tSZhJhzxYYvZe9yt7r03pPEA%2BL3kRiMD8rgW197LFAkfE%2BZ9b4YNINfc%2B99H4ODFa/RgBAP5f2bn/ABQCQFiqwCwSB0CLawPgYg5uKC0GLBFlgkozc8EEPPsQxYFsyEUJFlQmhSh6FasYbBelbCmAcO4bw/hjAxXCLzuIQuEilBSJ/vC/QkCUDWGsMoiIlj1GaIENo3R8p9HWCMezUx5ik0hOiX4exDB3DJKcS43I8S/FeIiUUGa/j0nuIaFE2xDBWj9DLZE0JMS0muKrUMNotbUnVEbRMLJcwclTFmaiw5JSOWEq5cS35/yNCjzqcC6ewtaWnKdq0zA7TuhdJwfMxZvz5Z/F2X8JWkgxnRyKGio5tgTnzzpovC5SBPYdxZUyyewc2CcBef3FgCgTQJxNCSzEvRAX1MznoINojIVgphdIkAmxSCIrrjwFFTcf5W0xR3HF3dAMx2A6Bh44HfmQaZGPH90RN2bG3S%2B52jKJ7RG/axmIoHppuQo25KjaNiAsGjnwOgArbYQGPj/CVoqwHSbvg/J%2BsqaRvwVZ/b%2BurMD/0AWIdVYDNXattbwPVzQDU/yNcgH0JrMGCHNbg/BhDdg2tIWYh1vAnW0Nddqj1Zy%2BDsK4TwvhAjA2yGDWIpD4bYUVzQ3I4wcalGWvzRorxoDITY1jYoiw2bLa5qwPmmxXiXAlqHRWsYTbSD1prZ2utmQvGjoSflsJg6qsFtbe2kYlaMk9CSWkJxyMR19s61OvmE6C7YYObhudgmgMgbAxBj0vQ11ApIJuppTG90Hs6Xkk9IAzC/M2JsRmqsFam3238NZ43jGcGOfbFp3SQCSEZgMxm2sNb9MkP0pWQyuDRc4JsHDl3rY7olrMlOF3imA7W6QKhiRnCSCAA)

## Links

- [source code](../../../../conceptrodon/stockivore/typical_paste.hpp)
- [unit test](../../../../tests/unit/stockivore/typical_paste.test.hpp)
