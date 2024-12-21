<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::MakeSet`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-make-set">To Index</a></p>

## Description

`Varybivore::MakeSet` accepts a list of variables and returns a set that:

- contains every variable in the list;
- doesn't contain repetitive variables;
- preserves the relative order of the list.

The result will be stored in a `Shuttle`.

<pre><code>   Args...
-> Shuttle&lt;(make set)&lt;Args...&gt;&gt;</code></pre>

## Type Signature

```Haskell
MakeSet :: template<auto...>
```

## Structure

```C++
template<auto...>
alias MakeSet = Result;
```

## Examples

We will turn `0, 1, 2, 2` into a set.

```C++
template<auto...>
struct Shuttle;

using SupposedResult = Shuttle<0, 1, 2>;

using Result = MakeSet<0, 1, 2, 2>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`MakeSet` is implemented as a special case of `Varybivore::TypicalDiversity`:

```C++
template<auto...Variables>
using MakeSet = TypicalDiversity<>
::ProtoPage<Variables...>
::type;
```

[*Run this snippet on Godbolt*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEAQCcpAAOqAqETgwe3r4BwemZjgLhkTEs8Yn%2BKXaYDtlCBEzEBLk%2BfkG2mPYlDE0tBGXRcQnJts2t7fldCpNDESOVYzUAlLaoXsTI7BzmgRHI3lgA1CaBbl6OtIQAnufYJhoAgk/PBJgsqQYf525MV1QJwAai08ExYvQHm85sQvA4TgBZASoIgMe4vEwAdgsJzmTEcyBOaAYc0wqlSxBOAKIJwAbmIvJgzjjQcRwZDMNiACLnXE8vlvN4fL4/LkXGmoAB0MuhL1h8IIJyECCuBChgSsmJeIu%2BBPF/0BMqlAElSal6h90GyOfQFHLngqEQAVW6pPCiWjcvB0hLFW4gE6pLyQj1IlFo%2B4XM0KC0OTDWsEQu0PY1CnFvAD0mZOACV6ltMr6Tv8lCA3idKyddWK/pKTjG444jDbk5hSNSjTL83NW5z7YFHi8q3iCHCEcpiKjUMomMAucOq9itc8RyOvJkjNW3czztzR%2BgQCgBPg%2BmIK2vK38L5eR3NDyA8AoAPqxJhKZ%2BoKh/ZEMafov5G0tCJgD7DVsA7V13U9b1fWIf0HiPBlvHbM5F1vKsoI9MRYL9O4OxvDCTiwmCfTwggozcID40Tdk2wUY0O2o5tQKTTkHQwxCQAoi0jxrfUTknadZ3nP4ewIMDMAY2VBz4ndBXQlleU1IUXmzE4LHfZlS3YQj%2BN%2BCVAQbc1gJbNjwMIp0lSEogRINZiQMkjilwzRT103YBtwtM5An3e8jxJU9snPNylwuQiMP8x8XzfD8vx/CMBEohyzLo9jB0gt1sK9Mj4LuLjkKZAjQsvFU1Q1KiTJoyTpKlB5itXIjKzKgh1XsqqrRqxjjNjUzWLSiySp87A5ItBTGqvLFlJXPTPj1AzDSIY0aucysNxAwS513XzBKnWytr%2BLqZMeFTMSm8bhTm2tDKWmUVsHN51q3REmAAa0wIRMCVPdiKy0i4IQ8KHpeI8bJnA6LiOurgeeUbxRmtSACpkZR1HMyzFHnWwIRnRR9GkdRwn8deTEzAOBgji8U4/iuOh8phy7RX1Osu2hodHTHRVlVVVqNQR54ns8oQvFSIoEx7LxaG%2BnaWrav4NA7LgOzMaFTpJgWPLzKTJel/cXvez6CHlxXleV1X%2BfxQln3fJRWggKKFFYTBrYHNwJaljthdFjJxe1qWHlWPkOHWWhOH8Xg/A4LRSFQTg3Gsaw8U2bZdzJnhSAITRg/WV6AjMKUsTMSQAA5i/8DQkn8MwNAANmL4JQ44SReBYCQNAVyPo9jjheAUEAFczqPg9IOBYBgRAQE2AhgwIchKDQL46ASKInc4VRi5rgBaGvJBOYBkCJKQpTMXgE0IEg8EPJX%2BEEEQxHYKQZEERQVHUIfSF0JWAHdiCYVJOB4CHMOEcs4x04AAeSuDPE4X4Tjry3jvPeB8ThHzMCcCAHhF70CpPsLgqxeCDy0OsCASAF7umwXPCAZCl6JGAFIMwfA6AfHgpQWIoDYgRBaAGbgvAOHMGILccBsRtCWgAbwBebBBDgIYLQbh0csCxC8MAf4tBaB9x4aQLALBDDAHEO/fAxBgK%2BnUdHckBYPhiPIIIHooCbixF/gIjwWBQFjjwK3DRcFYg%2B25J8HRNwjBZ3WFQAwwAFDAjwJgL%2B4CLSR3TjfYQnoH7SHiS/NQoDP76B0SgBOlh9B4FiH3SA6xUCpD6Ooze949ymEsNYauvBUBwXZFgQpEB1h1AaM4CArhph%2BCVmERYFQqh6CKFkAQPThkZFGQwYYgyxhK3aX0AYUxPAdD0Asxo8wZmjESPM%2BY4zdmDC2csHZbTk47AkEAjg4dSCd3qZwOBG9t6733ofSQx90G4HPjgtO%2BCM6BPWAgTATAsCJFaaQXOkhAhSiSIELEkgNCSCLjXdu/ga4pEbs3UgrdAhcClDXLgdckjFwJf4SQXAaiBBrjc0B3de79z%2BUPYh48SGTygVcSh1DsErzYJwFoLA6RYk3kwYkBgtxcCSFKXFpjTwXyvk/BJ98JDJNkKkt%2B0ddAMJ/n/MRlzrm3LARwSB08rgwKoNSYg/LBXCqODolBEqpXoMweQhIZwyZmF%2BYQ4eLLOUJA5agLBYw%2BUCs3jaow4quAKxoFLP0rD2GcIEZYvhXChEiIcJYiRjACDSNkaAhRSiVFqMsVovxux5F4EMQ0YxoCzHICuLsdOEQPiN2jnYhxtwnGloIeydx6dPHeN8UYfxoBGV8BCWEiJUSYmWPiXfcQj8UlKDSe/DVmSAnVKsLkuxLTimlOyOUypvl121K7o0y%2BUl4BtJ6MBTp3SVn5D6QwdARyhlKxGX0fZaRJl9GfXM7ovQNmDA/esgQSyFjlG2WsvZd7ekTEOQMiDeCNhbHOYhxueqaX3KDVakVtrxWSqlBoD5Mrvk4o9f80ggLgVjDBRiluIBAgSoRViGoWIsSBERZIHeSt9W0tsPSz1TL4AsqnjPP1AbiDct2HyxBLAFB0iJHSPDYo5in2I5fPQM7ElKvlaq9J9HSBav/jw3VID37dyNdA2B0nd6yfk/SJT%2Bo5iOv9c6kjgQyMju9S5mhYnXMgHk6LZ8imkjPmUwQa2Fqd6MOjSwiAbD35JoTRoxLgjhGiI0RmqRMi5G8DzcosQhaNHFsHZ2zR5ajHnvfjWutljG02Pfq2rhHaXHdssX2pQPjtGDpAoE0dc5x2ROiYwadshZ1JJ04utVOh9OiuMDkmwW6L0x13QIdRmZ/JHssHUmOp7mlLeA34Lpj6P39PA8ciZxRsgfrfdkH9Oy/3Xv6FBvIMGDugbu5BwD0HPutA%2B4hhQZyH4mepWZzDkWbNyYUw5j4TmICfKICRvBBDyOUZBZQS5mLW5mAlYEQI/hy5kvbrjrEdcQdd04HSge5GIVYmPsxrgUgkhMZhVwLE%2BhOCBFM%2BTnuDKiGXJPmTu5POBPrABtkEAkggA)

## Links

- [source code](../../../../conceptrodon/descend/descend/varybivore/make_set.hpp)
- [unit test](../../../../tests/unit/metafunctions/varybivore/make_set.test.hpp)
