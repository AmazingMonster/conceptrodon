-- Copyright 2024 Feng Mofan
-- SPDX-License-Identifier: Apache-2.0

module Main where

-- typename
data Typename

-- auto
data Auto

-- *...
data Ellipsis a = Empty | Dots a (Ellipsis a)

-- template<*>
data Template a

-- Template instantiation
instantiate :: Template a -> a -> Typename
instantiate = undefined

-- Metafunction reinterpretation
reinterpret :: (Ellipsis a -> b) -> Template (Ellipsis a)
reinterpret = undefined

-- fun
fun
 :: Ellipsis Typename
 -> Ellipsis (Template (Ellipsis Typename))
 -> Ellipsis Auto
 -> Ellipsis (Template (Ellipsis Auto))
 -> Auto
fun = undefined

-- reinterpretedFun
reinterpretedFun :: Template (Ellipsis Typename)
reinterpretedFun = reinterpret fun

-- gun
gun
 :: Ellipsis Typename
 -> Typename
gun = undefined

-- pun
pun
 :: Ellipsis (Template (Ellipsis Typename))
 -> Template (Ellipsis Typename)
pun = undefined

-- ellipsisGun
ellipsisGun :: Ellipsis Typename -> Ellipsis Typename
ellipsisGun =  (`Dots` Empty) . gun

-- Compose `gun` with `fun`
funGun
 :: Ellipsis Typename
 -> Ellipsis (Template (Ellipsis Typename))
 -> Ellipsis Auto
 -> Ellipsis (Template (Ellipsis Auto))
 -> Auto
funGun = fun . (`Dots` Empty) . gun

-- void
void :: Typename
void = undefined

-- Instantiate `funGun` by `void`
voidifiedFunGun
 :: Ellipsis (Template (Ellipsis Typename))
 -> Ellipsis Auto
 -> Ellipsis (Template (Ellipsis Auto))
 -> Auto
voidifiedFunGun = funGun $ Dots void Empty

-- Compose `pun` with `voidifedFunGun`
funGunPun
 :: Ellipsis (Template (Ellipsis Typename))
 -> Ellipsis Auto
 -> Ellipsis (Template (Ellipsis Auto))
 -> Auto
funGunPun = voidifiedFunGun . (`Dots` Empty) . pun

-- Error silencer
main :: IO ()
main = return ()