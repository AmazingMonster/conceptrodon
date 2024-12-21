<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Shuttle`

<p style='text-align: right;'><a href="../utilities.md#shuttle">To Index</a></p>

## Description

`Shuttle` accepts a list of variables and returns a function.
When invoked by an operation, the function instantiates the operation with the variables.

<pre><code>   Variables...
-> Operation
-> Operation&lt;Variables...&gt;</code></pre>

It also contains a regular function, `size`, which returns the total number of the variables.

<pre><code>size() -> sizeof...(Variables)</code></pre>

Check out **Examples** for all the abilities of `Shuttle`.

## Type Signature

```Haskell
Shuttle
 :: auto...
 -> template<template<auto...> class...>
```

## Structure

If `Shuttle` is instantiated by one variable:

```C++
template<auto>
struct Shuttle
{
    static constexpr auto size() -> size_t;

    template<template<auto...> class>
    alias Rail = RESULT;

    constexpr auto first();
};
```

If `Shuttle` is instantiated by two variables:

```C++
template<auto, auto>
struct Shuttle
{
    static constexpr auto size() -> size_t;

    template<template<auto...> class>
    alias Rail = RESULT;

    constexpr auto first();

    constexpr auto second();
};
```

If `Shuttle` is instantiated by three variables:

```C++
template<auto, auto, auto>
struct Shuttle
{
    static constexpr auto size() -> size_t;

    template<template<auto...> class>
    alias Rail = RESULT;

    constexpr auto first();

    constexpr auto second();

    constexpr auto third();
};
```

If `Shuttle` is instantiated by more than four variables:

```C++
template<auto, auto, auto, auto, auto...>
struct Shuttle
{
    static constexpr auto size() -> size_t;

    template<template<auto...> class>
    alias Rail = RESULT;

    constexpr auto first();

    constexpr auto second();

    constexpr auto third();

    constexpr auto fourth();
};
```

## Examples

- We will create a `Shuttle` with variables `0, 1, 2, 2`.
Then, we will transport the variables to `Operation`.

```C++
template<auto...>
struct Operation;

using PackedShuttle = Shuttle<nullptr, 1, 2, 2>;

using SupposedResult = Operation<nullptr, 1, 2, 2>;
using Result = PackedShuttle::Rail<Operation>;

static_assert(std::same_as<Result, SupposedResult>);
```

- We can check the size of a packed `Shuttle`.

```C++
static_assert(PackedShuttle::size() == 4);
```

- We can retrieve the first four variables of a packed `Shuttle` via regular member functions `first`, `second`, `third`, and `fourth`.

```C++
static_assert(PackedShuttle::first() == nullptr);
static_assert(PackedShuttle::second() == 1);
static_assert(PackedShuttle::third() == 2);
static_assert(PackedShuttle::fourth() == 2);
```

- If a packed `Shuttle` contains only `size_t`variables, then it inherits the corresponding `std::index_sequence`.

```C++
using PackedIndexShuttle = Shuttle
<
    static_cast<size_t>(0),
    static_cast<size_t>(1),
    static_cast<size_t>(2),
    static_cast<size_t>(2)
>;

template<size_t...I>
constexpr bool fun(std::index_sequence<I...>)
{return true;}

static_assert(fun(PackedIndexShuttle{}));
```

## Implementation

First, we will create a helper function that is responsible for the regular transportation functionalities.

```C++
template<auto...Variables>
struct Payload
{
    static constexpr size_t size() { return sizeof...(Variables); }

    template<template<auto...> class Sequence>
    struct Detail { using type = Sequence<Variables...>; };

    template<template<auto...> class...Sequences>
    using Rail = Detail<Sequences...>::type;
};
```

Second, we will create a helper function to retrieve the first four arguments.

```C++
template<auto...>
struct Payroll {};

template<auto First, auto...Others>
struct Payroll<First, Others...>
{
    static constexpr auto first() { return First; }
};

template<auto First, auto Second, auto...Others>
struct Payroll<First, Second, Others...>
{
    static constexpr auto first() { return First; }
    static constexpr auto second() { return Second; }
};

template<auto First, auto Second, auto Third, auto...Others>
struct Payroll<First, Second, Third, Others...>
{
    static constexpr auto first() { return First; }
    static constexpr auto second() { return Second; }
    static constexpr auto third() { return Third; }
};

template<auto First, auto Second, auto Third, auto Fourth, auto...Others>
struct Payroll<First, Second, Third, Fourth, Others...>
{
    static constexpr auto first() { return First; }
    static constexpr auto second() { return Second; }
    static constexpr auto third() { return Third; }
    static constexpr auto fourth() { return Fourth; }
};
```

Then, we create an interface inheriting the two helpers.

```C++
template<auto...Variables>
struct Shuttle
: public Payload<Variables...>
, public Payroll<Variables...> {};
```

If the variables are all of type `size_t`, we also inherit the corresponding `std::index_sequence`.

```C++
template<size_t...Indices>
struct Shuttle<Indices...>
: public std::index_sequence<Indices...>
, public Payload<Indices...>
, public Payroll<Indices...> {};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAAnADMpAAOqAqETgwe3r56KWmOAkEh4SxRMQm2mPYFDEIETMQEWT5%2BXJXVGXUNBEVhkdFxiQr1jc05bcPdvSVlgwCUtqhexMjsHObxwcjeWADUJvFuyMPoWFQH2CYaAIIbWzuY%2B4dejrSEAJ4XV7c3BJgsSQMfwObiYL1QADooQA1Bp4JgRegKL43YbELwOXbKJjvWioJjob4mADsVhuuwpu0mjmQuzQDGGmFUSWIVLwAC9MAB9AhszkQOb7Um7YiYAjLBh8zCoKhQiEQWHEeGIzAKOYHCxCgAiRPJlL%2BAKBmBBBsBTGBhzBRDlFzpBgUCl2QkwAEcvIxVijrpSqQR0ZitWKmHQhZqvGkjLsCO8ko8Dlqna73QxPYdFcqkTb4pd4pqSTrc7rvfr/maLW5TUaQVbIVDbdsmA65c63R7VV6feHgsBdgAlYO0J4JwP1OgglvJ1YKLPYEAgaOxjVFn2V83Gw6r8s1md2xuOidtjuUruRuQMPD9kPxxOtlPrtzphGZuvZpc3fNvn7XTf37cvy6on6GK8ti7zEJ4g4klYxIFmSX4/tW4K7AAYngxDDKQux/hCADyBAINEyKvoB/ogTi4G0LQIKoehBCYXhBHoTORKkt8PrUngtL0oyzKsjWuw0LRAqhiKYoSihaHDBq2osbBRYIZaSE0RhWFIc69LoJh2EMYRXposBWLkRB1GSXRiYafR%2BGEcx76sXqFIcVxAg8SyqlEAJpnCVBonisQkrKQQ0kfvZvrmpxdLOX8vFuagVKYBpXnCqKvmSupAiErmMm2XJ76/KWVaKe5AVaWp8XpSV7kACoIGhmkxXKOnoXpQGYqBFFUYcxXmeVuzVbVlmMdO/4sXB7H1DSEUMlFrn8YJwyJZqyXiQFQUwWxlKOZNLl8UhSgJYK3lLX53UMBleZrSFm3cdNO3ufhtULT54l9cQZ1Zbca2Frl375WuiFFaZFWxWlp1A71NWvWDyFLI0CBAw1VlNcR1z6a1RmUSZtGYSDdUvXV0PLPhA3WcNtmjRt43hddTIzUhc0EI9R3%2BaZq06pdlNOVNNO3bFe3pYzYnHTjrPrQ5HNbTdMVRhD6ACyl4O1SL7NhZz21S/whMIHLy0w/hSsfTl8G/Vu4Jyo%2BKpEQBKMtbyQgIC8BD0N8IC7EkXiIuFoF4gSILm8%2BEJephbse7SbXGWmcJPqqO5QR%2BX1G4af2HGknI8nKACSp2ce2yOo7b9sEI796Z/gU42dcLvB28tInHOwRYKoXJKLeqZuCX2dDQHyNB%2B71eGbi%2BIZW3Wdl6T1w9yH/ftSC7ej132ChnHcHfAA9AAVBvm9b9vK%2Br1vvXYEIlVCLsW%2B7zc6/b1fm/n1%2Bdwpg8TxHAIqxJAQlvycbv6m2Pee7DhsZiBhQEJ%2BPem8JK0V2NgVQrBASPDPkWE8PZsTIAANaYHQHbB29AhxOgLkXEEDAvCUTfmQXYbRdhmEwmYL48dvhIKdF4JIeQMG9lVMQ3k14AHRGAQwQhxDaCkMwhQqhlDaFwQYWwhQHDcEoPQZg/B4gQCXg6m4bhQCajiKLI5Lke5ogM1riABQrBuSNhBFIjh2MmEsPQBY2ggVszqjoRffeOMoEwMNPAm%2B2iOa6IdPoiAciMFYMLkolOmAvLxALAmSQTjl4uPAXjdxsCcEIO%2BjovRjRAlMDQcExR7AQD00idE3YRCSF%2Bjid8DJ/islBIUdggpfNTrFOvFwSpgEVZ%2BKULUnJ8iQlFznPdV6LSomUPadbTpmSGZ1P6UojWsMRkJjMOMsBG8UK6wQMkzxp9vHfQYXUkuTJZlxlGccokhxRahRpFyUQUlk4cm5A47AEANALEuTo25Di3DhJ5BcCAbTSDvN8Z8kEPynkQGWYC5W1yQX3NTuC5Z5yczxJ%2BoncsYKM5emptFCIqBPACS8AwCAhj65MibkmQ8hx04znVGTJmUZ0TrmgmzL81TukMyoIS7JuT0CHNUGc1iME5hxI4AsWgnAACsvA/AcC0KQVAnA3DWGsFSGGqx9hmHiDwUgBBNCioWKgkAEqNAQjMGYWIAAODQsQJUWoAGzxEkGYYkkg7X6E4JIXgLAJAaA0KQGVcqFUcF4AoEAfrdWytFaQOAsAYCIBAEsAgbs6IUAgGgAEdBoihBMZwVQ9qAC0drJC7GAMgWkUhTW8AwYQEgeB0B6H4IIEQYh2BSBkIIRQKh1CRtILoNoAB3IBSROA8DFZK6Ver5WcBwi8ZNuwZS7DzXawtxbS3lskKa3YEAPAZvoKyDYbTeARq0AsCASB01JEzWQVNF6r0gGAFIKhNB7GEUoBESdERggNHeCO3gn7mDEHeDhCI2h4oRu1emtgggcIMFoD%2BntWAIheGAKCSiobuC8CwCwQwwBxAIbQmBvAAA3VUk6mTxReGsbVwQ/jip7W8CIQDAMeCwJOv0eBvUYdICR4guKlCBmw0YN4Rg9ULCoAYYAChoR4EwP27hMrtWNuEKIcQbalOdrUJOvt%2BgcMoGVZYfQeAIihsgAsVAb8MjofzSceMphLDWDMIGnjSosAmYFO0QjzgICuDGK0UggRgh9FKAMNoeR0gCF87kVI4WGDTH6DECYVRPO1BGE0TwLQ9B2GS10RocXgsJdsKlyLExUt5dmAChQarW1jo4FK/1k6g2LoLUWktZbyEbrMFu3ANb92asPTq0TCwCIEgGO5w1kh4gQgSC6jQTrXW%2BolXa2I7qOCetIN6rVEI7VcDtRay1O2JWSC4BKhIbqA28CDSGsNA3I2nrjWehNs6XjkEoLevd2a2CcAaCwIjxJ81MF3JGLgsQIRcAhHK6tRAXMNtkM21T0h1NKE0z23QVDB1MGHRhmrdXztTo4DOpNLx51UCwsQH7f2AcNiByDsHGgt07svXujV8RllHtE9G89qBd3RBe2mrnjOBjfd%2B/mqnD7YhcD9c%2Bv46E30fq/YB39pB/3fuA6BhwivIOMAIDBuDk7EPIdQ7QdD2qsM4bw3K/AooHDEdIz28jyBKOK5o1USdDGmPvBY2sOV7HOPap43xzAAmzfdnZ%2BJpgknpOyfk4rpTcPW0I9kBp7tcrUc6ZE3ZqwBmGNubMxZ5ynBrMEAylqDPDmnPRBc6R0zHnrdeZ8%2Bl8Y/nTplZC8kaLNRitt/yBkFvBWsu15S90Tv/eag5Z6IFmYrfJijAb356f4/ijxYkAsSryxVjL5WzjhrnBSfk/%2B4DnswPQfg66/gKHzP%2BvHv1aQYbWAYjubo2tjbIPZvEhO8SYkjqzCuqO/Vntl3bBrsr87t4AHtE1k1ec3ss0c0OBvsWsWAFAiNaQiMj8jRhgq0z9a1602hY8VN49215Akdk8dAQBEh0dMdR1N8J1/9p0nteQF04Di0ECkDdgUCQc0DeRt1%2Bcr1md4g5g2dbsOcUBuC91ICRCBgkDmEuQ2CuQODdEyci0%2BA6BpdQ0IB30e1lcFcuNNCgMQMwMNcucoNtdYN4MLdMAkMUMxAjdFdTchMvdMMCNrcSN0MIdVAKM/gndBAXd6MjN3dPc2MlRfdeB/dUhA9/hg8RNBCw8I8ZM5NYwFNeBcCW0JAE8O0iCtNSC09jB9MbBs94Bc8ah0MV5a5S9LBHMLtnM60q93MR8MgXBTpO8AtF98sotu8ItZ9WiYte9MsksB8x9h9ejR9SsJ8l8Ssh8OixjcsRiWiKsqsN86Mt8aCOBd94DEDkDUC1xhhT8esL9%2BCbsT0htMARt78asn8QBzUIR4h4gJVjUjtfUrjiRds/9A1OArtw1BtSBxsQcP8NBgdZsuB4g7UJViQzBDsVt4hqCXjg19jr86MzBISLtXiYThVuNCI6jJAgA%3D%3D%3D)

## Links

- [source code](../../../conceptrodon/shuttle.hpp)
- [unit test](../../../tests/unit/utilities/shuttle.test.hpp)
