<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::IsSame`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-is-same">To Index</a></p>

## Description

`Varybivore::IsSame` accepts a target and a list of variables.
It returns true if the target is the same as every variable;
otherwise, it returns false.

<pre><code>   Target, V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (Target `same as` V<sub>0</sub>) && (Target `same as` V<sub>1</sub>) && ... && (Target `same as` V<sub>n</sub>)</code></pre>

## Type Signature

```Haskell
IsSame
 :: auto...
 -> auto
```

## Structure

```C++
template<auto...>
struct IsSame
{
    static constexpr bool value
    {RESULT};
};

template<auto...>
constexpr bool IsSame_v
{RESULT};
```

## Examples

```C++
static_assert(IsSame<1, 1, 1, 1>::value);
static_assert(! IsSame<1, 1.0, 1>::value);
```

## Implementation

We will implement `IsSame` using `Varybivore::SolitaryIsSame`.

Here's the entire implementation:

```C++
template<auto Target, auto...Variables>
struct IsSame
{
    static constexpr bool value
    {(...&&SolitaryIsSame<Variables, Target>::value)};
};

template<auto Target, auto...Variables>
constexpr bool IsSame_v
{(...&&SolitaryIsSame<Variables, Target>::value)};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISQDMpK4AMngMmAByPgBGmMQgAUEADqgKhE4MHt6%2B/ilpGQJhEdEscQlJtpj2jgJCBEzEBNk%2BfoFVNZn1jQTFUbHxiUEKDU0tue0jPX2l5UMAlLaoXsTI7BwA9ABUO7t7%2BwdbGyYaAILbuwDUACKYya6MyHiYCpd7x2cXh9/7H6cnpwImBYyQMQJMATcTC8RFIl2hRAh2ABI2IXgclyEnkIjQAngBJBRCViYAEmADsFkuU0cyEuaAYI0wqmSxEuMVQnkuADcxF5MJcKRYqGIlBTrhCqeLJWSzkCQWDSZCEahLgA1Rp4JgxehIlEENEYrG0HHEAlEkkQtwa4hanWYOE2u26gLIs5C6kNWn0gRMllsjlc3neAVCg386UBKXkiVR2XnH6J34Ar5bS74hXAxhezJvXZ/VNJn5/AHy0FMcHKmGqgAqjWAmAIcJVADo207tfQFHqzqj0QR0xa2GTKQDLuPPRW8HSGX7WezObQeXzSWcJ4LKRA2y3zAA2PfG03m4nDyEd%2B0KOF14gNghIkAgYP8%2BaRqzumMy91y4HlytQ6uXNet7NtW27nl2PanLOQL%2BguXKEiemAAPrciOFhbm2e4HtiozHpaZ6ap2LxXvWjb3o%2BK4vh%2BcZfgmRbvCmeyXNgqisKCAoMZ89Gcf8vY5sgSFMAoShNBACH4W4XBwlJlwyVw5FPpgL40acNLToJwnxAQEBgGAg6IVacktho0kKZRkocIstCcAArLwfgcFopCoJwbjWNY1LLKsoZmAEPCkAQmiWYsADWIA2ZIxkABxmGYACccVcDZGhRVFXDkuS0jWRwki8CwEgaCZDlOS5HC8AoIAmYFjmWaQcCwDAiAgMsBDJDC5CUGgIJ0PEkQkpwqhRbuAC0u6SJcwDIHSUgtmYvCYPgRC2ugej8IIIhiOwUgyIIigqOoNWkLoUkAO7EEwyScDwVm2fZQXOZwADyMJtQOqBUJcg0jWNE1TbJkVmJcEAeN19BsuYfnzLw1VaIsEBIF1yQ9WQFAQIjyMgMAUhmHwdBAsQFUQDE90xOEeJXbwpPMGaj0xNomAOBTpBdWwgiPQwtC4vdWAxF4wBQrQtAVdwvBYCwhjAOIh34MQDOONyLz3cyDMwus/nhEC2VOSaMTnWaHhYPdBp4PlIukArxAckotzi0YJpGEFixUAYwAKGqzwnY99wOf5a3CKI4jbX7e1qPdx36BLKDuZY%2Bh4DEFWQIsqDJLUjKcMNIzoBC1ymJY1hmCVFvLYricdHLmQuAw7ieK0eihOE/RlIMUmpOkqfjH4LcFKnMwDAkUl2OXdSjM0Ne5AP1RDww3RNL3Tf97YI8d3oUyzw3szN4sCheWsEg3RwdmkMVvClZ9Q2jeNk3TQDQO4IQJCCr5XBQwFjuLAgmBMFgCQQKFeQtnFAImUNCSDMJIXchUbK7jivoTguVSD5T8i2XcXBdxRTimlXcEUkqAN3Efe6pVyqVVfjVOGjV4bNReu1VG6MwZ9TYJwRoLBuTkmGkwekBgjCyTii2Lgxl5qLRIHgFaUk/YbUDtIYOShQ6HV0DjM6F0Kb70PsfB6HBnqtRhJcd6Z9vrjWQJw4A3DeHGSBiDJGYNH4BDMC/GGtUKG0PiB1NGqBQaDAMRLLgiUTI0FoPjQmxNDpU3JmbYJNM6ZyyZizbM7NObc0wLzfmYghZMzFhLKWTkZblwVsLJyytkCqyZhrao90dZ61xAbdYTljam38hbK2mAbbpPCKAUhfAXZuw9l7RgTMxEBy2pI2QIcDpOTkRHB2ucrAxx1gnX%2BzkU6ZGFhnAgWcAg52jhYAuJ8i7CJLnMweDgK4QFcMvKS9cSh9z0K3QoWQx6d1INcnu69LkT06MPHopyy6HPeWvC588V5LzuQC6Yzz/nPyWCsXe4LsoqIIZwXRF8OES2MXwjQt9BHgyfrYt%2BpAP5f0GHM7K8DEE8JAeSGycUMoBFAeAyQUlVGENsMQuxZD4AUJaq9ZxjjiD0PWEwn6LAFDcjpNyLxLZFQjAEffZaq1ZDiIGTteQ0iRk6ESKQBRl0RbKLuodUqGjXraI%2BqoAVQqRViolQOYGriLHxCsQEbFbSHHWuRly51YNHzIGSMkFCXikIWqQsayReN4gBJJmTM0TMwm4lpvTRmZtolsw5lzaWCS%2BYCxSWbNJdsqmizwLLQ5OSlaqBVkCIpggSmHTKXiSpRtbS1N4PUtIjTgTNIdm052TBXbu0wJ7b2vS5X9IkIM3ayqw5qsMVHPO0y46zKTgs30nANiZ0nVMzZhd4jF1nV81Oldq45Huecxucwu5t0yJ8x5mQ57Hu3V0QF%2B6V6T2%2BdPEeV7m6Lw%2BUCgeL7QXHq3jvLa2r8G6vhYGy4grhU8nNRWF4lq75LSsc/aGOK8Xf0oPvYlIB4otiSDZZKdLCpJHJGgoDJVOBEKqjisKkgbIAPSuSQqUVJCJS4DFMweDsoBB1aRsqJDYb7zmiRk%2BZHePBXNiGiukggA%3D)$Done$

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/is_same/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/is_same.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/is_same.test.hpp)
