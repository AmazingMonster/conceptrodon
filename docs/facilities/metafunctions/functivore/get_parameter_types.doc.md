<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Functivore::GetParameterTypes`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#get_parameter_types">To Index</a></p>

## Description

`Functivore::GetParameterTypes` accepts a container such as the `std::tuple` and returns a metafunction.
When invoked by a function-like type, the metafunction returns its parameters collected by the previously provided container.

## Type Signature

```Haskell
GetParameterTypes
 :: template<template<typename...> class...>
 -> template<typename...> 
```

## Structure

```C++
template<template<typename...> class>
struct GetParameterTypes
{
    template<typename>
    alias Mold = RESULT;
};
```

## Examples

We will extract the parameters from several function-like types. The parameters will be collected by `DummyContainer`.

```C++
/**** functions ****/
inline int fun(int, int*){ return 0; }

/**** abominable functions ****/
using AbominableFun = int(int, int*) const;

/**** function pointers ****/
inline auto FunAddr { &fun };

/**** pointer to member functions ****/
struct Tester
{
    inline int fun(int, int*) const { return 0; }
};

/**** function objects ****/
struct FO
{
    int operator()(int, int*) const { return 0; }
};

/**** DummyContainer ****/
template<typename...>
struct DummyContainer;

/**** SupposedParameterTypes ****/
using SupposedParameterTypes = DummyContainer<int, int*>;

/**** Tests ****/
static_assert(std::same_as<GetParameterTypes<DummyContainer>::Mold<decltype(fun)>, SupposedParameterTypes>);
static_assert(std::same_as<GetParameterTypes<DummyContainer>::Mold<AbominableFun>, SupposedParameterTypes>);
static_assert(std::same_as<GetParameterTypes<DummyContainer>::Mold<decltype(FunAddr)>, SupposedParameterTypes>);
static_assert(std::same_as<GetParameterTypes<DummyContainer>::Mold<decltype(&Tester::fun)>, SupposedParameterTypes>);
static_assert(std::same_as<GetParameterTypes<DummyContainer>::Mold<FO>, SupposedParameterTypes>);
```

## Implementation

The implementation of `GetParameterTypes` relies on dissecting the structure of the function-like types into return types and parameter types using the metafunction `Analyzer`.

```C++
template<template<typename...> class Container>
struct GetParameterTypes
{ 
    template<typename...Args>
    using Mold = Analyzer<Args...>::template parameter_types<Container>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIABxcpK4AMngMmAByPgBGmMQSAMzSAA6oCoRODB7evgFBaRmOAmER0SxxCVzJtpj2xQxCBEzEBDk%2BfoG19VlNLQSlUbHxSdIKza3teV3j/YPllaMAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYKa6MyHiYCjeHZ5fXJ39H3wu5yBZkS4WQ3iwNxMiTcyHG%2BEEMOwwOBv12NwuzFoAE8AF7xT4HQEETAsFIGUnQ2EEHFPZhsZHA8bELwOTHY/HxZTEVBEWlPaEAdisQruMKsl2BpPJlMw1LcAsYrHlACVMARSDclQzMAA6A0XYjABRMy4stkEDliLnEHl8vl0zAwtzqggQI0mg16pZmoEi4E3IM3WaOZA3NAMcaYVQpYghgjoEAgLzhAiJMwAfStADcxF55SYRVwFS6boki%2BLEpKLsHoZc614MkZtU7MxlgMwCOtC4k7jc3R7jQpvb7q4HgxOg03wsAbsR3l5aARs07qf23RLUQ3gzKKUxSS693Kj07dd7kRGDAoPh5BExwvE/Y3m3OUi0VaTiKunh8Yf272aR9iBdT0RwNJlxylMUtylS5jwPXtFTPFUBw1LUdRVb0wL9C12SxG0CTtXl%2BSdF1BzA0cIwEcY/SLGs61DPBw0jaNY3jBFk1TQQM2zG4828Qti1LWEbgANmFNwbhLF0ywrGCoKBHdp1fVsnnbPBOwPHt1zQ91KINMcGMnZSbhnFsFwUJcVyVXTN0UqdtTJfdDxpZyTxpFC2AvRJsCvJgbxuQCHwiEDfMc8y3w/Ngvx/d5dOC4DQOHHyUQchSa2ldzENPelUIAMQYXCCFZfDOSIkAbhSLwYloZjrVxIj7VIp4XUKy96MrWClIuBDXOQvK2BudrwvNErLQa202oYXY/Uq6ravqgjGu5EjHVa2ERpRaDjKDJiWJo0l2ITJMUzTXjc3zZ1TM60y6xk2EyzMSTHLrCBXrrYMHrcOToQAVm22tPuB5bbWa9bnU2orfOTASCw%2BoNfRujLURRuDeuy/rMKGgBZMlCowrz5SaUruwXYrScmoiXTxlhCpuEnLR7ZNZtGi55pqurw1Bpq1qVGn8ehwHbqBvbmjDaioyOuMTq486s0uwTHJF4Gg2%2BssZKFH67uDd6deB9XRMSf7AdVz6edWh1%2BdhWmtthq6EZuJHReFKtMtMyL/JvOLdMZhwe26rqHPgzHIYG5UhvygB5P0FwAR1TSz50wBO8CTzqzDE6Pk1QJ5iAPEgICMrqxspi2wrcaO5qqzmlvKp9YSwCElXezPs5AXP4gL4gi7HYWA1M/bJbYmXOLOniFf4h3kd2z7Ne1l23sd%2B6RKkmSAeX4Ny5dJvlydVus6jnO8%2B73vkXtpX9ad5W0Z6l9Zy9hQff/YaY/St3tyuf5v4BNFDhuAAkrKMkjBxZZCJPsQE6If7/EBFlWUOU3IIKxkTVKj8gqyBCg3QGeErQAHENTKGihqeIAAVJ0podr1hdn1MO2N9SGmHM%2BYMnscaeHQLpbesIDJ6nPiAWhVViGxSVKaWEiVQqQUyrfP%2BMCvgyP2DcbAqhWAUnlHIn4sj1E9XMGCBgEIvBQhdJGTYKQCCiOFho24VAvB6IaB8LR4Q6oRBuGmG41iGAQDTFqNMuxfQimTmTBgNwNASldp/dENwmAxFQCwcIUT6BuJsQ4LI9jiTAk9hcaJsTmC1UwPlGxuk0yeMEN4wQvjh4EEDpYhR7jkkCCqqgNM8RUmQOBI4x8kSvBEGGjYi46B0DxnotCTO7iwnBy/rcNITT4zdLYBUQktS7EQNOMyca7JSHvC/KjWe7TnGuPccUzULiylLAqcKCwAT1hBJCdWMJ0EP7owiYs8BqAYjaEwA4FpKzS4TSrjtRyrjO75yID3JYhzSkEHKaxK0QyFyBOCaEku/oHk9QiXcHwLAcTiMJFo2huUI4MN4WzXB9wMVYswUlcZEShBeBSIUTA6AiH5ximQihyzASexpXS9IDKmWflZb%2BXS6KWCYuxRXLxxzIWSPCf/DZ4wvmAn2pmAKShWgQDHgoFUyrRFuAIQQPlLLiDkN/C6YVoqKUSJhiANhtB0A7w%2BXvJ41AbF9y1Fy%2BljKhECveMiYuY0DzMW1aq90GqtUBRdHqg1JCjUUNNWSsVfCbV2u4VkuJuT8lCzdbSj1UavzGp9b5P1FwlUqviCGxMyZNVsG1RGwhXqY0mthGa8l95KXYGTEm%2B1zd94Zr6QM11DNs08s9cy6N%2BbzFFpLTeMt6qK0gCrZgGtsJI31vHXGkVLagKWvbda9hXbHWYAPnKr8yZ3EDvdcO3N3qJ3dSncG2dp0F1Lt1XW0debY1NvjRa7BHa92bTftgLN3KlAjv5Q2gt2Ai0cBWLQTgf1eB%2BA4FoUgqBOA/UsNYEMawNiFlBDwUgBBNDQZWAAaxAH9RIeohR/T%2BkKLgf0zBcH8IELgZhpCwY4JIXgLAJAaA0KQRDyHUMcF4AoEA/HCNIeg6QOAsAYCIA7l06qmoKAQDQOSOg8RIgqk4KofwYkAC0YlJA3GAMgcMUg9RmF4AywgJA8BJiCPwQQIgxDsCkDIQQigVDqCk6QXQQQADu%2BcUicB4DBuDCGiMoc4FHJTXSbioCoDcPThnjOmfM9JSQVmbgQA8Bp%2Bggy8NLF4JJrQKwIBIHUykTTZBVPVdqyAYAUgzB8DoF%2BMTEAYjRZiHE4gOIwu8F68wfrUc3kfMk/h9TbBBBRwYLiaLWAYheGAG4MQtAxPcF4FgFghhgDiD8/gBcySczvGizGD5XStj4aaRx5DdUYj536x4LA0WSp4B41t0gp3iDRKUA8XbRgnGgCkysKgBgTQADU3iBajvSQbnnhCiHEB55z8glBqGiwF/Qe2UDWGsPoPAMQxOQBWLnOxnADMIn/KYDDlgzBCZ%2B8QBzZ3SfdAm1kFwDB3CeA6HoUIj4FgjAKOkTIAgph%2BBF0ULI8xhhVHZ3UxoEw2i87yEEOwHOBB9FaLL%2BZ8vZiTFV5L2wyvdeLC4CsBQ2HNgSAixweDAnovCZS/pozJmzMWey89CAuA7NFcSBb0rRGlgrAQJgJgWAEhF1IGRyQlGACciQhSSA0JINjYk%2BN/TEvH/QnAuOkB4wHvUYkuBiX8PHwIYk/qSHo4nsSju/PCdE%2BJgjweZPycq4pggynyCUAa4V7TbBOAtBYDmIUBmmD%2BRbFwePeouB6mQ7ZkFDm9Bo9cyj6QaPvOY787oVrwWmCha23bh3gneDCbi93hLSWXdpZMxCPb0lZ/z40Ll/LNXCvDIzCV1voOZNVZiQ/3iF7zU0AMawfyMBny4H4xoGXGaUoG6z82GxaAGy%2B2QNG3GwcAR2m1ATmwW0O0wGW1W3W023wx2z2wO2QyOw51O020X1UEu1JAR1u2iweye3JVez83e0%2B3wx%2Bz%2B0wABwoNnDb3ByYChxhzh0YARzX2R3c031kG3182Qz3xxyMDxzpxsAexJ2j3JxSUp2pz7FpysHp0Z3iGZywG0MtzqE1z8AgFcAl3525zN2F1IEKDF2yCNz0DcIaGcP12sMV21xV1yGNw1wCNN0Fzlz0ANyCL53V3CLKEiIt1WHWBtySI41Pyd04FvzdynznBnznwX1y19xBS/0D1/3K1D3D0j0oDt3z0L1n1T2o3jyFCFGSHTxrwbyE04Gbwkzb1kwUzWCvxUz7zAIHx0w4BH3SxYAUBzHDBzHyLlHGBs3wGX0c0R3XzkMR0UKxxAESFIAPyP3C1z3tyi0b1i3iytBv1UCmJmLmIWMQnGDf1GMJB0USB/zK2k07372APq2eISFmLpUzHmPj0zEWJXGuM33a3gK6x6z61QPw3QJxDG3eSwK%2BxwNm3m1QKoMIJWzW1oA2wR3IKBy2CoLThoLOz8wu2QCu2YMEDqFYKJ3YJexJNK2Zx4N4D4J5UEKB2EL/1EPEMwFh3hy%2BxkLcwkHkK8wxyUJ0F2NUOMHx0sEJ2J3gDJ1MT0J2E4iMOsAZ3PyZxZ0sIVwaC5x52CMcPQF8K8NFwaAcKl3cItPV38IaECJtMNN6HiKGD1yiOVxdOiPtMt2t3cxP1OK6I4BSxuNmP4nuNJEeJ9xWJIFKPeOD0qIjxGGjw4zqJADMFn0SESBo1T2gI0BzKFDL06PP26NsBbw%2BJDxjxAEkDEis0kDT38EkCFBY2Y2LOOMSGDLLJE3KOI2OOs1LJi17KrJWB%2BwyGcEkCAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/functivore/get_parameter_types/implementation.hpp)
- [Source code](../../../../conceptrodon/functivore/get_parameter_types.hpp)
- [Unit test](../../../../tests/unit/metafunctions/functivore/get_parameter_types.test.hpp)
