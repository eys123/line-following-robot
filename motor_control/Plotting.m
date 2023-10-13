clf
clear
load("Motor_Control_Data.mat")

% Filtering matrix so that we only take 50 timesteps
row_indexes = 1:size(m, 1);
high_index_rows = row_indexes > 149;
m = m(high_index_rows, :);


% Assigning Variables to Sensor Data and Wheel Speed Data
leftSensor = m(:,1);
midLeftSensor = m(:,2);
rightSensor = m(:,3);
midRightSensor = m(:,4);
leftWheelSpeed = m(:,5);
rightWheelSpeed = m(:,6);

% Plotting over a timestep of 50
time_step = (linspace(1,50,50))';

tiledlayout(2,1)

% Plotting Sensor Data Over Time
ax1 = nexttile;
hold on
title("Sensor Data & Motor Speed Over Time")
plot(time_step,leftSensor,".","MarkerSize",10)
plot(time_step,midLeftSensor,".","MarkerSize",10)
plot(time_step,rightSensor,".","MarkerSize",10)
plot(time_step,midRightSensor,".","MarkerSize",10)
ylabel("IR Sensor Output")
xlabel("Timestep")
legend("Left Sensor","Mid-Left Sensor","Right Sensor","Mid-Right Sensor","Location","bestoutside")

% Plotting Wheel Speed Data Over Time
ax2 = nexttile;
hold on
plot(time_step,leftWheelSpeed)
plot(time_step,rightWheelSpeed)
ylabel('Commanding Motor Speeds')
xlabel("Timestep")
legend("Left Wheel","Right Wheel","Location","bestoutside")