%%Sahin Olut 150140124 // BLG354E Signals And Systems HW2 Question 7c


x_func=[1 4 -5 2]
h_func=[1 0 -1]
y_func=conv(x_func,h_func)
figure(1)
stem([0:3],x_func)
figure(2)
stem([0:5],y_func)
figure(3)
stem([0:2],h_func)
