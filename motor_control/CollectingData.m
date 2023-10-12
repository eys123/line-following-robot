
clear s
freeports = serialportlist("available");
baudrate = 9600;

% Choose port
s = serialport(freeports(2) ,baudrate);

% Getting values from Ardunio
str = "empty";
m = [];
row = 1;
data_count=0;
count_max=200;

while data_count<count_max
str = readline(s);
data = split(str, ",");
m(row, 1) = str2num(data(1));
m(row, 2) = str2num(data(2));
m(row, 3) = str2num(data(3));
m(row, 4) = str2num(data(4));
m(row, 5) = str2num(data(5));
m(row, 6) = str2num(data(6));
row = row + 1;
data_count = data_count +1;
end

% Save data as .mat files
save('Motor_Control_Data_1','m');
