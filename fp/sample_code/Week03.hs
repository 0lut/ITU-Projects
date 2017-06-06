module Week03 where

import Prelude hiding (gcd, length)

simplify :: (Integer, Integer) -> (Integer, Integer)
simplify f = (n `div` g, d `div` g)
  where
    n = fst f
    d = snd f
    g = gcd n d

firstPlusThird :: [Integer] -> Integer
firstPlusThird xs = case xs of
    []        -> 0
    [x1]      -> x1
    [x1,_]    -> x1
    x1:_:x3:_ -> x1 + x3

nondecreasing :: [Integer] -> Bool
nondecreasing xs = case xs of
  []           -> True
  [x]          -> True
  x1:xs@(x2:_) -> x1 <= x2 && nondecreasing xs

data Person = Person String Integer
              deriving Show

data Month = Jan | Feb | Mar | Apr | May | Jun
           | Jul | Aug | Sep | Oct | Nov | Dec
             deriving Show

type Coords = (Float, Float)
type Length = Float

data Shape = Point     Coords
           | Circle    Coords Length 
           | Rectangle Coords Length Length
             deriving Show

daysInMonth :: Month -> Integer -> Integer
daysInMonth m y = case m of
    Apr -> 30
    Jun -> 30
    Sep -> 30
    Nov -> 30
    Feb -> if y `mod` 4 == 0 then 29 else 28
    _   -> 31

area :: Shape -> Float
area s = case s of
    Point     _     -> 0.0
    Circle    _ r   -> 3.14159 * r * r
    Rectangle _ h w -> h * w

gcd :: Integer -> Integer -> Integer
gcd x 0 = x
gcd x y = gcd y (x `mod` y)

gcd' :: (Integer, Integer) -> Integer
gcd' (x, 0) = x
gcd' (x, y) = gcd' (y, x `mod` y)

shift :: ((a, b), c) -> (a, (b, c))
shift ((x, y), z) = (x, (y, z))

third :: (a, b, c) -> c
third (_, _, z) = z

length :: [a] -> Int
length []     = 0
length (x:xs) = 1 + length xs

birthYear :: Person -> Integer
birthYear (Person _ y) = y

data PersonR = PersonR { fullname :: String, born :: Integer }
               deriving Show

quadrant :: Coords -> Integer
quadrant (x, y) = case (x>=0, y>=0) of
    (True,  True)  -> 1
    (False, True)  -> 2
    (False, False) -> 3
    (True,  False) -> 4

fibStep :: (Integer, Integer) -> (Integer, Integer)
fibStep (u, v) = (v, u + v)

fibPair :: Integer -> (Integer, Integer)
fibPair 1 = (1, 1)
fibPair n = fibStep (fibPair (n - 1))

fastFib n = fst (fibPair n)
