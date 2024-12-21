<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Pagelivore::IsSpecializationOf`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#pagelivore-is-specialization-of">To Index</a></p>

## Description

`Pagelivore::IsSpecializationOf` accepts a sequence and returns a function.
When invoked by a type, the function returns true if the type is created by an instantiation of the sequence and returns false if otherwise.

<pre><code>   Sequence
-> Entity
-> Entity == Sequence&lt;Vs...&gt; ?
   true : false</code></pre>

## Type Signature

```Haskell
IsSpecializationOf ::   template<auto...> class...
                     -> typename...
                     -> auto 
```

## Structure

```C++
template<template<auto...> class>
struct IsSpecializationOf
{
    template<typename>
    alias Mold
    {
        static constexpr bool value
        {RESULT};
    };

    template<typename>
    static constexpr bool Mold_v
    {RESULT};
};
```

## Examples

We will check if `PackedVessel` is a specialization of `Seq_0` or `Seq_1`.

```C++
template<auto...>
struct Shuttle_0;

template<auto...>
struct Shuttle_1;

using PackedVessel = Shuttle_0<0, 1, 2, 2>;

template<auto...Args>
using Seq_0 = Shuttle_0<Args...>;

template<auto...Args>
using Seq_1 = Shuttle_1<Args...>;

static_assert(IsSpecializationOf<Seq_0>::Mold<PackedVessel>::value);
static_assert(! IsSpecializationOf<Seq_1>::Mold<PackedVessel>::value);
```

## Implementation

We will use partial template specialization to dissect a type.

Suppose the compiler discovers that the type is a packed vessel and deduces the vessel as the given sequence. In that case, the compiler will select the partial specialization instead of the primary template.

```C++
template<template<auto...> class Sequence>
struct IsSpecializationOf
{
    template<typename Type>
    struct ProtoMold
    { static constexpr bool value = false; };

    // This partial specialization will be chosen
    // if `Type` is deduced as `Sequence<Variables...>`.
    template<auto...Variables>
    struct ProtoMold<Sequence<Variables...>>
    { static constexpr bool value = true; };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<typename...Args>
    static constexpr bool Mold_v = ProtoMold<Args...>::value;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAOxcpK4AMngMmAByPgBGmMQgkhqkAA6oCoRODB7evnppGY4CYRHRLHEJZgCstpj2RQxCBEzEBDk%2BfoG19VlNLQQlUbHxickKza3teUHj/YNlFSDVAJS2qF7EyOwcBJgsKQa7JgDMbrv7h5gnbkxeRAB0jyfYANTIBgoKL0KYAI5ejC2zxMGgAguNiF4HC8AJIKIQpTDIPBiPAALyYDQA8lQQaCTP4rGCXiSXucDpirqcCABPRHMNgvAAqdKp2DxpJeEKhBBeymIqCIAFlPOgOaSCRYuc1HMg3gJxphVCliC8YqhPC8AG5iAEvE4AEReVDEShOUoJBvNePFJIA9HbmQg8F8Uv0UbQuYjkaiMQ0XgB3OieuJvBDpRi2l4Ol54Kj6gBsGhZiJMSdjXyw6ChmHQLyYXzTGh%2B/0BVLcADUWiiYvQFI97sCk43iaTyZdrrcHo8q8Qa3Xga2SdzofzBagRbQxacSwCGEDTr3%2B5h609juz11HJdLMXg5WgGIrlar1Zqdd5MPrjkaCJCqRb/FbjkT8UOyXsKUdqayGZgG6DgGITA9kYAgFEHUFOS8DIjBeSc80NPkBWFUVrgAoCQMEVdG03Z8bTfdtKWuWl6VYP9HlBYhgHAzc31mWV5UPXZjzVDVPXggB9LUryNMcUKnNCqOw54QBAc8AWtMFLUk19QTtAAqRSlOUlS7TxBSlOZFcwJeZS1LBDSVKMxT9NkwivxuO5UAbCCR15IQEDuAh6A4jQZLxczyy7ay13ZME7O%2BRyCGczAOK4dywWg8JgD5JhkAAa1zCsVzsHjAqcly3NOZIXiCF4zFIfLgTwqSwU8zsrP/ISIKi2CS1ctKHIy0KsrcSjqJs3CXw8j8O1ObyquomqYJi%2BquEaoKQrCwSOt8iLwRlPcOILJRWggOEESRD10V3AQcWueqsuwUT4OuZQ4sS9Bks%2BOoRLE3VMGWGT6KWlb4gICAwDAWF4W9ba/SyfaZz%2Bab1xO1DTnOhKkpS26wfui8nufDhVloTgql4PwOC0UhUE4NxrGsLl1k2S9zGOHhSAITQUdWeKQCqSR7g0SQuH8Y4NCqDQzATBMzAADn5/ROEkXgWAkDRkixnG8Y4XgFBAZJqexlHSDgWAYEQEB1gIFI7nISg0H2Oh4kiMjOFUfmEwAWgTSQXmAZA5Ske4zF4XNCBIPB0D0fhBBEMR2CkGRBEUFR1BV0hdCCANiCYFJOB4VH0cxmncc4LE7j13lUHjS2bbth2ndypmzBeCAPGN%2BhVXJrhll4ZWtFWCAkCNlITbICgIDbjuQGAKQCpoWhdmIBWIBiNOYnCFoaUT3gp%2BYYgaSxGJtCRZXKaNthBCxBhaFnyOsBiLxgBuWhaAV7heCwFhDGAcRD7wICHDwLUVzTpUkTubZKfCXY0cjrQPAMQ45Lw8FgNOt48DiyvqQN%2BxB1RKANHsO%2BQCjA01WFQAw1EKx4EwAGLE9I54h2EKIcQwc/byCUGoNO0d9B3xQITSw%2BhgEK0gKsVAKQGiX2tuMacBpTCWGsGYGW8C%2BxYDYRAVYdh15ZBcAwdwngOh6FCOEIY5QRhBAKJkAQUw/BaPSDohg8xhgJBmHUWRAg%2BiTCUdMboljGgTAGGohYmjbBOL0XoWYrQTEaLMdIkmWwJDJw4BjUg0teCyxePnW29tHbO1LuXXAnsa5mApvXKmGDVgIEwEwLACQpGkHppIY49wACcxx/BJEkGYSQSZOYJjKcLDgotSDiwpvcBMXAEz8zKfzbpjMuBVAqQmcJadZby0VpklWzdNYt21lnfWXce7VzNmwTgLQWBan8NbJgbwDCwS4GU%2B4XBmbu3wEQcRvtZAB3IdIShYcaGR10AVWO8c54hLCRE9OHBM66zuC8XO%2BZiBbJ2Xs94d9crHNORoculd27V31GkswGTG6q3mSs%2BIBtu6oCriMTZ2zrYQqMEcrgyQh4jzHhPSOC8Z7ENpUvFea8HDEK3qBXe%2B805HxPmfC%2BxCb6oO2DjfAz9HBv0vjjT%2ByBv7EL/nUNOQCQEz3AUKhufYYGU3gYgzAyDb5GDQaAGZfBsEKFwfgwhjBiGUNuUHe5shHkRxxi8%2Bh6DBFWGYYqyRHCuFZB4Xww0brhGiPiOI9%2B7D7Ev2cBAVwnigiqNKKY/IhiGixtSMmrIvjFjmJ6FYjxtj9ERoaNY5xCa/FeLzbkAt3iS3qKzQEjYQS67NK%2BeMzgwLQW7P2ZCo5JzmZJIuSQJF6SG5ZNIDkvJIxCkANae045LN/DDP8OzGpdTWZjMjhM2wUy0WzPgPMnW2dsWYuIGs7YmzC4sAUFqOUWoe2XHGOclJ3trn%2BzIbakhDraEgGOKQN5Ccr6fNThujOiyc7xnPfbS917tR3spOMOFuKEXxCHccVFGC1at0Qx3I9WHq5iWQCkFIXEjkcXvQQZaIK7Z8DoJSyg1KcYMoPpTRjTL16stxdvAgHKD7CswMfU%2BYg%2BWwIFfq1VpARWyPFR/VQX9diysEPKwBwDQE0hVZA9VxCtURl1ag6K6GsFMBwXgghRDYHWrfRIO1odqGOp0N%2Bl1xgmE2E9fAb13DOB2j4YwoRlgRGRLEd7MNhSZGRr8NGhRqb421rcdolN%2Bak2FAzS4xN2aHHFtTSFotTjM1uOrRl7LyWy1NoUIEoOgH10yzbRBl4UGb2wd2PBiAyTLlDrriOmZ2Tcn5MoCEmdSxjnHGOFULmrNJaDf8D0irkTOCTKVqO4pVRylVH5jzMpkgyns0qVwH9ADjhAcq3LaZTcQluymz89rx24HxAyM4SQQA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/pagelivore/is_specialization_of.hpp)
- [unit test](../../../../tests/unit/metafunctions/pagelivore/is_specialization_of.test.hpp)
