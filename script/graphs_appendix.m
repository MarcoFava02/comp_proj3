%% Graphs Computational
% plotted the following functions:
% 20 * cos(0.694*t)
% -12.31*cos(2.304*t)+32.31*cos(0.104*t)
% 28.36 *cos(2.304*t)- 3.36*cos(0.104*x)
% -13.88*sin(0.694*x)

% I use basic Matlab commands and functions to plot multiple functions
figure()

%% plot 1
fplot(@(x) 20 * cos(0.694*x), [0,50],'color', '[0.4, 0.2, 0.6]')

%% plot 2
fplot(@(x) -12.31*cos(2.304*x)+32.31*cos(0.104*x), [0,50],'color', '[0.4, 0.2, 0.6]')

%% plkot 3 an 4
fplot(@(x) -13.88*sin(0.694*x), [0,50],'color', '[0.6, 0.3, 0.6]')

%% plot 5
fplot(@(x) +13.88*sqrt(1-(x/20)^2), [-20,20],'color', '[0.8, 0.2, 0.7]')
hold on % I add other plots to the original figure
fplot(@(x) -13.88*sqrt(1-(x/20)^2), [-20,20],'color', '[0.8, 0.2, 0.7]')

%% set plot properties
grid on % I add the grid to the plot
yl = ylabel('v_z(t) [ \mum/\mus ]'); % I set the axis' label
set(yl, 'FontSize', 16)
xl = xlabel('z [ \mum ]');
set(xl, 'FontSize', 16);