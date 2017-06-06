module Week08 where

import Prelude hiding ((.), ($), curry, uncurry)

duBois :: Float -> Float -> Float
duBois h w = 0.007184 * (h ** 0.725) * (w ** 0.425)

boyd :: Float -> Float -> Float
boyd h w = 0.0333 * (h ** 0.3) * (w ** (0.6157 - 0.0188 * (logBase 10 w)))

bsa :: Integer -> (Float -> Float -> Float)
bsa age = if age < 3 then boyd else duBois

stepRange :: Integer -> Integer -> Integer -> [Integer]
stepRange step m n = [m, m + step .. n]

step1 :: Integer -> Integer -> [Integer]
step1 = stepRange 1

naturals :: Integer -> [Integer]
naturals = stepRange 1 0

curry :: ((a, b) -> c) -> a -> b -> c
curry f x y = f (x, y)

-- uncurry :: ???
uncurry = undefined

addT :: (Integer, Integer) -> Integer
addT (x, y) = x + y

addC :: Integer -> Integer -> Integer
addC = curry addT

addT' = uncurry addC

(.) :: (b -> c) -> (a -> b) -> a -> c
(.) f g x = f (g x)
infixr 9 .

second :: [a] -> a
second = head . tail

($) :: (a -> b) -> a -> b
f $ x = f x
infixr 0 $
