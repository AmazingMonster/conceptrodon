<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Amidst`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-amidst">To Index</a></p>

## Description

`Varybivore::Amidst` accepts a list of variables and returns a function. When invoked by an index, the function returns the variable at the index from the list.

<pre><code>   V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>I</sub>, ..., V<sub>n</sub>
-> I
-> V<sub>I</sub></code></pre>

## Type Signature

```Haskell
Amidst
 :: auto...
 -> template<auto...>
```

## Structure

```C++
template<auto...>
struct Amidst
{
    template<auto>
    alias Page
    {
        static constexpr auto value {RESULT};
    };
};
```

## Examples

We will pick the variable at index `3` out of the list `0, 1, 2, 3`.

```C++
/**** Metafunction ****/
template<auto...Args>
using At = Amidst<0, 1, 2, 3>::Page<Args...>;

/**** Test ****/
static_assert(At<3>::value == 3);
```

## Implementation

We want to count variables one by one up to the desired index.
We will do this by pack expansion, meaning we will create a pack of the proper size and then expand the pack alongside the variables to enumerate.

We will use variadic functions for this purpose.
There are two ways to achieve it.

- First, we can use `void*` to declare unwanted parameters in the function signature, eventually reaching the target variable.

```C++
template<auto>
using VoidPointer = void*;

template<typename>
struct Midst {};

template<size_t...I>
struct Midst<std::index_sequence<I...>>
{
    // We use `VoidPointer<I>...` to enumerate unwanted arguments.
    static constexpr auto idyl(VoidPointer<I>..., auto* target, auto*...)
    { return target; }
};
```

To make it work, we need to turn variables into pointers. We will create a helper template for this purpose.

```C++
template<auto Variable>
struct Vay
{ static constexpr auto value {Variable}; };
```

Now, we can make pointers from variables by:

```C++
static_cast<Vay<Variables>*>(nullptr)
```

Finally, we will make a template that generates the `std::index_sequence` and translates the result.

```C++
template<auto...Variables>
struct Amidst
{
    template<size_t I>
    struct ProtoPage
    {
        static constexpr auto value 
        {
            std::remove_pointer_t
            <
                decltype
                (
                    Midst<std::make_index_sequence<I>>
                    ::idyl(static_cast<Vay<Variables>*>(nullptr)...)
                )
            >::value
        };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMzSrgAyeAyYAHI%2BAEaYxCAAbAAcpAAOqAqETgwe3r4B0umZjgKh4VEssfHJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlkTFxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYqa6MyHiYCjeHZ5fXJ39H3wu5yBZn8YWQ3iwNxM/jcXkctEIAE8YdhgeYwQwIV4oTC3MhxugsFRUeifocbgA1JhIz4HQEETAsVIGRl4pjw1BUlp4JjReiky7jYheBzclGXEwAdislxu8pus0cyBuaAY40wqlSxBuHKINwAbmIvJhoTLqcRefzMNK7jDZUCpXb/A7gb9/h79oD3TcAJLM%2BhsQRMBp0r1uz2R05kq4UymoPDoZQJwRxMPRy6MgMhm2wvWoQUXLyZIxUhNJlOMnUwu6G8u7e0xn0AWUT43TDKZLJzeIISKezDYheFooIN1b6Hb0qsTsbkszXdZubcmQAXpgAPoEAB0u99w4IIrFE/GeMJIBAYSwqg3SgAjiascvfbvt6T/GjJTLgQqbtttjcADqprFqaJgJBo8aJsmYRVni%2B4fq%2B4EaDc%2BqMD4cQ5jcXgMAA7oYjLoLqxDABhggKG%2BcoKkqeAqmqGpajq%2BY3ImSK0BAUEVrBcTwair6kLqnK7KhLTAJgBACfmuyvksP4KtONzEOJ6wMCJJHifaZp2l%2BzquuStwXCwbZjl8wJZt2bJ5pyr4Wla9AKAeR5joZxnot%2BVHyuZS5nng65bn6ha/iOYrKMQqBEMoTBiXJ8rTjFv6Ks0yqqgIDHaoJ%2BpGt4YEeQlcW5Ql1EEOgF5KSwqAGpu6TccQW7xYVsWwvVDW/lgEJ9k8zUtfKEBdd1v4ngQZ7FReLBMAA1puV6aremAPi8z7vp%2BFz9f1F6sexNHIBuoinrC1IovtPJ8vZqINh%2BEAMF4tC0Kkh5LDJfUtbJBUNaiF5ZSafW2nOK3ybOLoxr%2BXk9lZRCvhcwBKUyjAEA5H7xcWYTADckVidC/i1qF4WoGjy6Q9DQZw0hCOAzpv0RlG9KU/sNzYKorAsqapn6VTGZAqzwnNuJTBUDhDjZB2ZmLqDbj5hDJHw8tSOlhcY41jcLmTkNsIaAJXACWYAn%2BO9IB43iFySyTaJkxzsa3AAKu8JnU0KSW0RuTAKEorQQHLeI6x%2BH3GmBmMK/4skuhwKy0JwACsvB%2BBwWikKgnBuNY1iKmsGxgaCPCkAQmjBys40gGHkjbhoSRmGYACcZdcGHxdJFwUpStIoccJIvAsBIGhq1HMdxxwvAKCAatZ9HwekHAsAwIgIBrAQqTwuQlBoMydBxBErBbKoSQJAAtAkkg3MAyAqlI25mLwmD4EQlolRr/CCCIYjsFIMiCIoKjqMPpC6BruHEEwqScDwEO4dI7Z1jpwAA8vCWeY5UBUBuBvbeu996HxuMfMwNwIAeCXvQas6cli8CHloFYEAkCL1SMvMgFAIBkIoSAYAUgtY0FoFWfuEBoigOiGEFoSIAG8E4cwYgSJwHRG0JgBwvDSCLyJuAhgtAeEfywNELwwAxY3X7twXgWAxpGHEAovASkBaVXUTHTUYj4RbAztxJuMdETRF/oIjwWBQGHjwG3DRpBKrEGiBkTADxtHAEREYbOKwqAGGAAoSkbxcLgIHBI2%2BwhRDiCfvE1%2BahQFf30IYYwidLD6DwNEfukAVioDutkdRW9CQ1lMJYawZhu6eKvu8eAKw7BiIaC4Bg7hPAdD0CEMIQxKgjA1kULIAgph%2BGGRkUZDB5jDHiBrVpAsBB9EmN0/ICy6htN6BMAY/SFhDNsDs8ZehZitFmYM%2BZLSU6bAkEAjgEdSBd14D3eBm8d57wPkfQu6CIC4EICQaEeCCHBJWAgTATAsDxAgLnEAkh/DbjLv4BuGhJBmEkBBDQYcEhl30JwFupA27%2BC4NuBIXBkhl1rgkAuVdEUJEeaAnufcB6Z2CaPCeJCp5QLnlQmhODV5sE4C0FgBopRbyYKqAwpYuBl23MSkxF8SCJj0PE%2B%2BSTpApKUGkj%2BugtY/z/rwu5DynlgI4JAme8IbiwNeYgveEIsmoJlXKjBWDyE4MBf4Mw%2BCWXD2IaQ1A2C4jz2of611Iw7VGGlVwNWTCWGUHYR/fh3CJGJsEcI0R4j3FSNhjIuRoDFHKNUbQdRGctFZN0THfABjHBGNAaY5A5iJFWNAbY%2BxSJHFbBji4txGdPHeKUH4styNWWhKihEqJMTGBxNkKqx%2B6rZCpPfjHHVmSgnVKsLk2xhToWx1KalTgFTipVJyRYOpzyGmJiaUU7oWznAQFcMcjWfTyhzL0CMhoD60hTIaOcxYGyejLKOWsiZ16lmNB2T%2Bg5py2hAZOeBvZL6uBXPWDcxDuL7kgI/i8hB7yJX2ulbKouGC/mX3dYh4FPrQXgshZQO5%2BLCUypRVKMOZd66BDRbvDWxrGW2GZYQkeY9J7T2gUG3lK816CuICwJBLAFAGhVAafDS5xhnwVVfZV07EmzufvITVi6dABFIHq/%2BGjDUYe7hArlMC4GqGk7J%2BTimcztkwSGih7qA7kaIaPP1AbKELxczgkAcnUipA3ApsuG4lMEA3DZ9VdBY1sI4VwwRyaktCJEW0iRWbBA5vkRWzASiVFiCLRI0tOiO2aP0VsmtH860NvcU2j%2BLbuHtucZabtvBe0%2BIHToodPq%2BBhLHZgaJsT3Eqs0xIOdL9dPpIM5K7JNSN35K3cU3d6pODbHPGu2p9S4iNOWyB9pd7OkfqfQM39n7ijZA/W%2B7IEH5kHe2f0D9iyGgrN2c%2Bi5sGnswYWXBj7v6kOp1uWho1DLODwNs3Jw0DnGROeIwCjEZHvVEMoxCkY26m50ZAOXbc/h/Bh2rpIKNGg8dShqFxzgTLB4gtIHnSQYcEV1ylB3JIkhK5cBLmYOlTd/BmeeZT5HOc0On3pZhgXfGlgrE8ZkZwkggA%3D%3D%3D)

- Second, we can use concepts from C++20 to constrain the type of unwanted parameters in the function signature, eventually reaching the target variable.

```C++
template<typename, auto>
concept Prefix = true;

template<typename>
struct Midst {};

template<size_t...I>
struct Midst<std::index_sequence<I...>>
{
    // We use `Prefix<I> auto...` to enumerate unwanted arguments.
    static constexpr auto idyl(Prefix<I> auto..., auto target, auto...)
    { return target; }
};
```

`Prefix<I> auto` constrains the placeholder type `auto`. Assuming the deduced type is `T`, then `Prefix<I> auto` becomes `T`, and `Prefix<T, I>` is evaluated to determine the legitimacy of the instantiation.

Now, we make a template that generates the `std::index_sequence` and translates the result.

```C++
template<auto...Variables>
struct Amidst
{
    template<size_t I>
    struct ProtoPage
    {
        static constexpr auto value
        {
            Midst<std::make_index_sequence<I>>
            ::idyl(Variables...)
        };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMzSrgAyeAyYAHI%2BAEaYxCAAbAAcpAAOqAqETgwe3r4B0umZjgKh4VEssfHJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlkTFxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYqa6MyHiYCjeHZ5fXJ39H3wu5yBZn8YWQ3iwNxM/jcXkctEIAE8YdhgeYwQwIV4oTC3MhxugsFRUeifocbgA1JhIz4HQEETAsVIGRl4pjw1BUlp4JjReiky7jYheBzclGXEwAdislxu8pus0cyBuaAY40wqlSxBuHKINwAbmIvJhoTLqcRefzMNK7jDZUCpXb/A7gb9/h79oD3TcAJLM%2BhsQRMBp0r1uz2R05kq4U5TETA0VRh6OXRkBkM22EEJFPZhsUi6zmCi5qzapAg3eOJvDJmF3G4EEVZ13k24AWTw6HGKYZTJZmbxObzrCzaKFTdFlc73cr0qsTvtMfTA7ZsMyAC9MAB9AgAOgPvpLwqnNxn4zxhJAIDCWFU26UAEcTVis25fQe96T/OPHQ6FTc2zbDcADqppeEo0IJBo1ZJniR4/kWRCfiY0GNlyjA%2BHEmY3F4DAAO6GIy6C6sQwBYYIChfnKCpKngKpqhqWo6nqXJdkitAQLBtbwaiSGoJ%2BhasY2LTAJgBBCZyn5LMCAHzjcCYEOsDAiWR4n2madqSouLoxj6FwsF2PZfMCK6sm%2BrGfhaVr0Aox6TmKBlGQQ6IyrJCpmYO654Fuu5%2BiWAEnmK8aoEQyhMGJ7nyvOUUAYqzTKqqAhMdq/GGsapqxXJbk0XFcVXiACYsKgBo7ukYSMsQu5ZXl0KwjVtUKlgELDjauWNXFEANR1AHni564EOg14sEwADWO63pqD6YM%2BLxvghaI/t1PXyte7GcXRyDbqIF6wtSKJ7TyfK2aiuyohADBeLQtAVsQSzScttUye1jWoteRreG1FyvTp/4KraS6Su1nlrm4lkHhcwAJkyjAEHZS3tRBYTAFWEWZf4DYhWFaN4pD0NBnDKFLbp2nOq2sZRvSEa3NgqisCypomW2lOpkCzO7Ge4lMFQeEONkvamf25nslJENkfDv5I0YNwXHOGMy4Zs54hohZcIWZiFv4b0gOFkWwhc4tE4t5M%2BgAKu8lZMxcm3bkwChKK0ECy3iWs/u9GV1c6Db%2BDJLocCstCcAArLwfgcFopCoJwbjWNYiprBsmWgjwpAEJo/srKNIBB5Ie4aEkZhmAAnEXXBB/nSRcFKUrSIHHCSLwLASBoKthxHUccLwCggCrafh/7pBwLAMCICAawEKk8LkJQaDMnQcQRKOnCqEkCQALQJJINzAMgKpSHuZi8Jg%2BBEJaQ1q/wggiGI7BSDIgiKCo6j96Quhq/hxBMKknA8AHweh%2BnSOnAADy8JJ6VlQFQG4K916b23rvG4%2B8zA3AgB4Oe9AdQYi4EsXgfctArAgEgWeqR55kAoBAYhpCQDACkBrGgtBKrdwgNEQB0QwgtCRD/XgbDmDECRMA6I2hMAOC4aQWeBNgEMFoJwl%2BWBoheGAGDa63duC8CwCNIw4hZF4ATHzUqKiI6amEfCLYKcKp1EAYiaIn8%2BEeCwIApseAm6qNIKVYg0QMiYAeBo4AiIjDpxWFQAwwAFCUjePhYBeZRGX2EKIcQd8YmPzUIAt%2B%2BhDDGFjpYfQeBojd0gCsVAFZsgqLXoSesphLDWDMO3NxZ93jwBWHYYRDQXAMHcJ4DoegQhhCGJUEYasihZAEFMPwAyMhDIYPMYY8Q1ZNL5gIPokwOn5FmXUZpvQJgDB6QsfpthNkjL0LMVoUy%2BkzMaQnTYEg/4cBDqQNuvAO7QNXhvLeO89652QRAXAhASDQmTjg1OASVgIEwEwLA8QICZxAJIfwe4i7%2BBrhoSQZhJDQQ0EHBIRd9CcAbqQJu/guB7gSFwZIRdK4JBzmXeFCQ7mAI7l3HugL%2B4EJHoQseYCp7kMoRgxebBOAtBYAaKUa8mCqgMNLLgRc9yEsMSfEgXY9AxOvvE6QiSlDJJfroDWH8v5cOubc%2B5QCOCgInvCG4kCnmwK3hCdJiCpUypQWgkhGC/n%2BDMACvBA82XcriNPChqB0EjBtUYSVXAVb0MYZQFhL8eEcNEbGvhAihEiJceI2GkjpGALkQopRtAVEp3UekrREd8C6McPowBRjkAmNEeYuuEcrE2KRHYrYEdHHOJTm4jxShvFFuRgEvgwTQnhMiYwaJshlW31VbIJJz8I5arSf4ipVgslWLyZCyORTkqcFKYNcpmSLDVIebUrs9T8ndHWc4CArgDlq26eUaZehBkNFvWkcZDQTmLFWT0BZ%2BzlmjIvfMxomzP27KOW0f9hyQPbMfdg1Y6xLlwbrgaulnBLUvLFbayV0q84oO%2BafV12DcFAtICCsFIwN111xfiqVSKpRByLtXQIKLN5q0NfS2wjLPUsvgGy8e4C/U%2BuILyrYAq4EsAUAaFUBpsPmXGEfOVZ9FUTriVO%2B%2B8h1Vzp0AEUgOrv6qP1QAl%2BHcTXgPNVA1Q4nJPSdk5mHsqCA3OriK6n2xHmWDyIY50hgmvMYJAFJ1IqRtwyaLtuOTBBtyWdVXQSNzDWHsL4fGhL/DBHNNEWmwQGaZElswPIxRYg82iMLZo1taidHrIrS/KtNaXF1ssTkptLaHGWg7bwLtnje2aP7e5oJEVh2YAiVElxSrVMSGnQ/TTKSdPioyZU1dOT10FK3eqTg2wrzLqqTUuIdTFuAZadetpr7729K/W%2B4o2RX3PuyKBmZe2Nn9FfXMhoiytkPtOVBh7kHZnQbe1%2B85CHb6GdpcZtDUWbgSak4aWzjJ7P4d%2BVgj1JGyPgsoNc6jIBi57n8P4IO5dJBho0NjqUNR2OcAZb3EjWdJBBzhVXKULckiSFLlwAuZgaV138EZ9uZOmX4OuYfYH3PO684zq4uImRnCSCAA%3D%3D)

- Note that we only need to constrain the parameter types during concept expansion.
If we move the constraints to the template head, we don't need to define the function at all:

```C++
template<typename>
struct Midst {};

template<size_t...I>
struct Midst<std::index_sequence<I...>>
{
    template<Prefix<I>...Nah, typename Target, typename...>
    static constexpr auto idyl() -> Target;
};
```

`Prefix<I>...Nah` tells compilers that this function template is only allowed when `Nah` satisfies `Prefix<Nah, I>...`
In our case, since `Prefix` always evaluates to `true`, it constrains nothing.

We will use `Vay` defined above and write an `Amidst` compatible with this version of `Midst`:

```C++
template<auto...Variables>
struct Amidst
{
    template<size_t I>
    struct ProtoPage
    {
        static constexpr auto value
        {
            decltype
            (
                Midst<std::make_index_sequence<I>>
                ::template idyl<Vay<Variables>...>()
            )::value
        };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMzSrgAyeAyYAHI%2BAEaYxCAAbNIADqgKhE4MHt6%2BASlpGQKh4VEssfFJtpj2jgJCBEzEBNk%2BfoFVNZn1jQTFkTFxidIKDU0tue0jPX2l5UMAlLaoXsTI7BwA9ABUO7t7%2BwdbGyYaAILbuwDUACKYya6MyHiYCpd7x2cXh9/7H6cn/zM/jCyG8WEuJn8bi8jlohAAnpDsADzMCGKCvODIW5kCN0FgqEiUZ89pcAGpMeFvXZ/AiYFjJAx07FMGGocmNPBMaL0IlnEbELwODmIs4mADsVjOlxllymjmQlzQDBGmFUyWIl1ZREuADcxF5MBDJRTiFyeZgJddIVL/uLrf5bQCvj9XTs/i7LgBJBn0NiCJi1BjU93Ot3ho7E86k5TETA0VQhyNnOm%2BwOWqEEeH3ZhsUhatl807KtbJAiXWPxvCJyHXS4EQUZp0kq4AWTw6BGSdp9MZ6exWZzrAzyP5DaF5fbnfLEqs9ptUdTfeZUPSAC9MAB9AgAOj3XqLAonlynI2xeJAIDCWFUm6UAEdDeiM24vXud0T/KO7bbZfXe0yL6Vgm2IHl%2B74REwCD5oOjDDpcAAqjTAJgBAwdmcFsO%2BRZ/vKeCKsqqrqpq2rsh28K0BA8yXAAtEiiHIahC5ivOjpRp6pwsB2XbvACS6ASybLvqa5r0Aoh7jsKnHcQQKKSgCf78f2q54Bu27ejhspHsKsaoEQyhMChCmyrOxl/jKeEEQIREagWOr6t4lrSuZMqmc5Ll/lgoKwWZHkyhAvl%2BX%2Bp6yauBDoJeLBMAA1lu15qnemCPo8L5gciX6BUFMqXkpdKXORtDYhSiJQiJ3JiUi2FflRmUufMl4OYatXGg6v4maxzanIpAHKW4pHvqcwBxvSjAEOJGXuZcXjpEYFaGUatYVsQemoAZRlQoNw3%2BmNVXpU6HXsRGvEtjslzYKorCMkax3RkdoZiidWwnqhTBUF46JBt2fE9SufVCXupzEMA43ftNYTAJcpwzv4dbSdO2IaPmXD5mY%2Bb%2BEil5rS%2BgPA7tzH/I9iEvOWN2WZuTAKEoTQQFD2Lo1%2BDUGgtMOLf48w2hwiy0JwACsvB%2BBwWikKgnBuNY1hyssqwLUCPCkAQmic4s0UgDzkg7hoAAcZhmAAnLrXA81rmtcOK4rSNzHCSLwLASBoiMC0LIscLwCggIjCuC5zpBwLAMCICAywEMkMLkJQaAMnQcSQWwnCqJrCQ0UklzAMgipSDuZi8Jg%2BBEGaEXI/wggiGI7BSDIgiKCo6he6QujIwA7sQTDJJwPBc7z/OK8LnAAPIwiH5aoFQlzx4nyep%2Bn6tmJcEAeJH9CaqiXDzLwntaIsEBIBHyRR2QFAQDve8gMAUiozQtB0sQbsQNE3fRGEjTwm3vAP8wxDwr30TaJgDgv6QEdtq9wYLQZ%2BtcsDRC8MAPqtBaBu24LwLAUUjDiHAXgOMDg8C6heN3NUv8YTrDlmEOklshZwmiM3D%2BHgsDdwbHgW2CDSDYOINENImBbjIOAHCIwitFhUAMMDMkzwG69xzP/IuwhRDiHLhIquahu7130IYYw4tLD6DwNEN2kBFioDLJkeBNE8S1lMJYawZgnbMPzjg7RHRf5BhcAwdwnhWh6BCGEfoZRBjI1SOkIM4w/DeIKEGGYAx4jIzsHYrooxmjONyOE6okS6jRJCZ4sJthon%2BL0FMJoKS5gryWCsNYEgO4cD5qQR2vBnajwTknSQKc06XAzjPCAuBCAkAhLLVe8teGLAQJgJgWB4hUVICrSQ/gdy638ObDQkgzCSASPbHmCRdb6E4NbUgtt/BcB3AkLgCRNa6xNgkNWhtJkJHKd3Z2rt3bdK9pvf2W9A4D1DgfI%2Bi8Y7rEaCwXU4oaJMCVAYWaXBdY7m2ULHObT856AkSXaR0hZFKHkbXXQqMm4txfiUspFSe4cH7sHGElxh7VPHnU0EyjGkgrBbPeeu9F4dP8GYLp69vaPLeXEMOh9UAL0GGSowwKuCIwvlfG%2Bd9a5vyfv/cVH8v4/z/owwBo1gGgO7hAqBMC4H/yQco1BQt8AYMcNg%2BB4LVD4LpP/Yh1Ru7kMofCah6whZ0IYXLZhrClAcO1eDXhfABEKCEZgERYjGEwqkWXeFsg5E1yFiipRPCTFWDUeQrRwzdFBgMUYmGcazEWLiFYpNiwImYOcBAVwmTkZuJKKEvQPjChZFiQE0g1bgnuNmF42xhaGDdDGHWrJCT22dt6M2yt4SMnduHdMQdqTikFOllOy2WLLmcGJbUgF5LgWgo1rPVped6UrzXj00gfSBmDGGZbdZmyQUzPFDzXWZtAhzKSMjbFVzbA3OZfc%2BAjyg6Dw5Wy4gHzOBfOTiwBQupFS6jXYBEY2dc4kA7NC2QsLQ0V3kIiyNOgAikDRa3BBmKu612dniwehKR6qCAyBsDEH0xdjnly2lcR6Vsz3Xcn229aN7x/WxxeIBQPJGSJucDutNyQYIJuUj8K6DCsoKKoWUqwFy1kzKux/8FWCCVWA3VmBIHQLEBqxhWqUH2sQegyJhrcEmuQAQ81ghLW12tU/O1tCzROt4C6th7qUGeuY/wwyvrhGiMYOIhDIaJBhsrqhhRGHAUqNMQmjRebhZ6OspwDYF5M2WHMZUyxHZrHDILfY4tjjS2kHLR4vJDagmZCK42zIuTW15aiT0Ir9WknjorZOsdXacj1uyQOtreT81SyKfkudeGnaLrE5cYDoG9SUbpNRrd7Tl5Mv3YewZlASlnpAHrHc/h/A8yNpIAVGhdvin2Rc/DnBrke33aMnmEzTbintprSQBsuDazMOcy2/hRuVMu7cjeJSs7nbGy7f7SsmFxHSM4SQQA)

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/amidst/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/varybivore/amidst.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/amidst.test.hpp)
