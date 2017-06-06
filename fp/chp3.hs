
add = \(x,y) ->  x+y
add' x y =  x+y
makeTup x y =(x,y)


abs' x = if x>0 then x else -x



signum' n | n>0 = 1
          | n == 0 = 0
          | otherwise = -1
          
abs'' ::Int -> Int
abs'' x | x >= 0 = x
        | True = -x

prod :: (Num a) => [a] -> a
prod [] = 1
prod (x:xs) =  x * prod xs

 

capital :: String -> String  
capital "" = "Empty string, whoops!"  
capital all@(x:xs) = "The first letter of " ++ all ++ " is " ++[x]


facto 0 = 1
facto n = facto (n-1) * n


third (_,_,x) = x


qsort [] = []
qsort (x:xs) = qsort small ++ (x:qsort large)
               where    small = [y | y <- xs , y <= x]
                        large = [y | y <- xs , y > x]
                        
myHead (x:xs)=x
myHead (_) = error "sda"



mult x y = x*y
multpThree  = mult 3
isUpperAlphanum = (`elem` ['A'..'Z'])

doitTwice f x = f (f x)

listeyeUygula _ _ [] = []
listeyeUygula _ [] _ = []

listeyeUygula f (x:xs) (y:ys) = f x y : listeyeUygula f xs ys




funcX n | n `mod` 3829 == 0 = n
        | otherwise = funcX (n-1)




flipf f x y = f y x
doIt f x y = f x (f x y)

largestDiv = head ( filter p [10000,9999..] )
             where p x = x `mod` 656 == 0

tkWhile = filter q ( map (^2) [1..100])
            where q x = x `mod` 2 == 1 && x <3000

                  
zin 1 = [1]
zin n | odd n = n:zin(n*3 + 1)
      | even n = n:zin(n `div` 2)


      






replit 0 k=[]
replit n k = k:(replit (n-1) k)

f _ [] = []
f n (x:xs) = replit n x ++ f n xs




gcd' n m | diff > 0 = gcd' n-m m
         | diff < 0 = gcd' m-n n
         | diff ==0 = n
         | otherwise = 1
        
        where diff = n-m
