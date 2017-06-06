module Week01 where

d :: Float
d = 4.8

c :: Float
c = 3.14159 * d

-- d = 15.62  ~> error: multiple declarations

a :: Float
a = 3.14159 * r * r
  where
    r = d / 2.0

a' =
  let
    r = d / 2.0
  in
    3.14159 * r * r

sqr :: Integer -> Integer
sqr x = x * x

sumOfSquares :: Integer -> Integer -> Integer
sumOfSquares x y = sqr x + sqr y

sumOfCubes :: Integer -> Integer -> Integer
sumOfCubes x y = cube x + cube y
  where
    cube :: Integer -> Integer
    cube n = n * n * n

maxThree :: Integer -> Integer -> Integer -> Integer
maxThree x y z
  | x>=y && x>=z = x
  | y>=z         = y
  | otherwise    = z

reciprocal :: Float -> Float
reciprocal x
  | x == 0    = error "division by zero"
  | otherwise = 1.0 / x
